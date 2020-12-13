# Title Slide

* In my project I am interested in improving the way containers are orchestrated
  and secured in Linux

* This involves an eBPF-based container implementation that I am tentatively
  calling BPFContain

* BPFContain gives defenders a simple yet secure container implementation with
  high-level policy language policy that supports easy modification and ad-hoc
  confinement use cases

# Outline Slide

* In this talk, I'll start by providing a high-level explanation of containers
  and their security implications

* Next I'll discuss the design of BPFContain's policy language and its
  implementation using eBPF

* Finally, I'll conclude with opportunities for future work and an overview of
  my contributions

<!-- Containers and Security -->

# Containers vs Full Virtualization I

* Traditionally, the alternative to using containers has been full
  virtualization using virtual machines

* In full virtualization, a guest operating system is managed by something
  called a hypervisor, which virtualizes and controls access to the physical hardware

* There are generally two kinds of hypervisor:
    * Type I hypervisors run directly on the physical hardware and run guest
      operating systems without the need for a host operating system
    * Type II hypervisors run on top of a host operating system to virtualize
      the guest operating systems
    * You've probably used at least a type II hypervisor before, for example
      VMWare or VirtualBox

* On the other hand, containers run directly on a host operating system using
  a thin virtualization layer provided by the OS

* Containers share the underlying OS kernel and resources, meaning that there is
  no need to run a full guest operating system

# Containers vs Full Virtualization II

* Compared with full virtualization, containers:
    * Tend to be lighter weight
    * They share the underlying host OS kernel, so they don't require a full
      guest operating system
    * They are managed directly by the host OS, without requiring a hypervisor
    * However, this thin virtualization layer typically means that they have
      weaker isolation guarantees

* On the other hand, full virtualization:
    * Tends to be heavier weight, particularly in the case of a type II hypervisor
    * Each virtual machine needs to include its own separate guest operating
      system, including a kernel and a userland
    * Since they don't share an underlying kernel, virtual machines generally
      provide much stronger isolation guarantees than containers

# Containers: Goals

* There are a few goals when designing a container management system

* The first goal is virtualization
    * We want to give each container its own virtual view of system resources
    * This would include things like the process tree, filesystem mountpoints,
      the networking stack, system memory, and I/O bandwidth

* Containers also seek to provide least-privilege, although this is generally
  treated as a secondary goal, as we will see later on
    * Specifically, we want to restrict access to sensitive resources and
      prevent a compromised container from compromising or impacting the rest of
      the system
    * This includes other containers as well as the host operating system itself

* A third goal for containers is a notion of composability
    * This is to allow composable micro-services to be defined using containers
    * To accomplish this, we need to provide a means for containers to interact
      with each other, but only in pre-defined ways so that we don't violate
      security expectations

# Containers: Complexity

* To accomplish all of these goals without relying on a full guest operating
  system, containers make extensive use of various security and isolation
  features provided by the operating system kernel

* The examples I mention here are specific to Linux, but generally this pattern
  would extend to other hosts as well

* For virtualization, containers use a combination of filesystem mounts,
  namespaces to provide a private view of enumerable resources, and cgroups to
  limit available quantities of resources

* For least-privilege, containers combine several security features of the
  kernel, including discretionary access control, seccomp-based system call
  filtering, dropped POSIX capabilities, and mandatory access control
  implementations provided by Linux Security Modules

* This results in a highly complex, heterogeneous mess when it comes to policy
  enforcement, which can result in policy being difficult to write, audit,
  reason about in practice

# Containers: Security

* A security-oriented survey of container management by Sultan et al cites
  container security as the primary factor inhibiting their widespread adoption
  in industry

* This is because security is generally implemented as an afterthought in
  container management systems
* This is especially problematic since containers share the underlying OS
  kernel, meaning that it is much easier for an insecure container to mess with
  the host system

* Paradoxically, proper virtualization and confinement of a container actually
  requires elevated privileges to begin with
* If we're not careful to drop privileges as we no longer lead them, this can
  increase the risk of privilege escalation if a process manages to escape confinement

* Also, if our host system does not have full support for underlying security
  mechanisms, such as SELinux or AppArmor, the container falls back to
  essentially having no security

* To fix container security, we need to rethink the way we implement containers
  and build them to be secure from the ground up

* This means starting with the least-privilege guarantees, and making any
  virtualization on top of that optional

* The same survey I cited earlier mentions an eventual goal of writing
  a container-specific LSM for enforcing least-privilege. This would improve
  upon existing implementations based on LSMs written for enforcing system-wide
  policy

# Containers: Threat Model I

* In container security, we generally consider four kinds of attacks

* An rogue application can attack the container itself, interfering with other
  processes running within the container or attempting to escape confinement

* Containers might also be used to attack other containers, either directly or
  indirectly through side channels for example

* Containers could also attack the host operating system itself

* Finally, an untrusted host operating system could attack containers that are
  running on top of it
* This turns out to be a much harder problem to solve, as it requires the use of
  hardware security features like trusted platform modules, so this type of
  attack is out of scope for this work

# Containers: Threat Model II

* The attacker could have many goals here, including:
    * Escalation of privilege, either by escaping confinement altogether or by
      launching collusion attacks in cooperation with other processes or containers
    * Disclosure of sensitive or secret information
    * Tampering with the host system or other containers
    * And denial of service, for example by killing important processes,
      disabling network interfaces, or hogging resources

# BPFContain's Mission Statement

* To help mitigate these threats, BPFContain's mission statement is:
    * To help defenders by providing a mechanism for defining simple, secure
      containers with policy that is easy to customize


<!-- BPFContain Policy -->

# Policy Design Goals

* When I was designing the policy language for BPFContain, I had four primary
  goals in mind

* First, BPFContain should support the same basic functionality as existing
  container management systems
    * Eventually, I'd like to support both confinement and virtualization
    * Although the current prototype only supports confinement, I have plans for
      introducing virtualization support later
    * BPFContain should also provide a simple and secure way for allowing
      containers to talk to each other, satisfying the goal of composability

* Secondly, BPFContain policy should be high-level and human-readable
    * My basic motto here was to try to be friendlier than bpfbox

* Thirdly, no security knowledge should be require to read and write basic policy
    * If I just want to stop some behaviour B sub i, I shouldn't need to worry
      about tuning n other behavioural parameters
    * However, it should still be possible to tune all n behavioural parameters
      if necessary

* Finally, BPFContain to should enforce least-privilege by default
    * Pragmatically, this means enforcing a default-deny policy and not needing
      to fall back to a total lack of security, as is the case with existing
      container mechanisms

# Policy Language

* BPFContain policy is written in a simple and human-readable data serialization
  language called YAML

* The policy itself is composed of a set of rights and restrictions
    * Rights specify what the container is allowed to do, while restrictions
      specify what a container is not allowed to do
    * A restriction always overpowers a right, meaning that any conflicts in
      policy are resolved in favour of denials

* By default, BPFContain policy is default-deny, meaning that, strictly speaking,
  a complete policy can be written by specifying a minimal set of rights without
  any restrictions---the restrictions are implicit

* However, if the user wants, they can set a given policy to be default-allow instead

* This provisions for simple use cases, such as blocking one specific feature in
  an application

# Example Policy: Discord I

* Here's a very simple BPFContain policy that might be shipped with a container
  for Discord

* The policy includes a unique name for the container, a command to run, and
  a set of rights that should be granted to the container, including access to
  the root filesystem, the proc filesystem, networking capabilities, and video
  and sound devices

* Also note that the policy specifies readonly access to the proc filesystem,
  meaning that Discord is not permitted to modify any files within it

* As you can see, this policy fits quite nicely on one slide.


# Example Policy: Discord II

* Suppose the user doesn't want to allow Discord to scan the list of processes
  on the system

* Disabling this behaviour is as simple as removing the right to access the
  procfs filesystem

# Example Policy: Discord III

* But what if there is no existing Discord policy, and maybe the user doesn't
  want to write one or doesn't have the necessary technical knowledge

* In this case, restricting the behaviour is as simple as writing a five-line
  default-allow policy

* The policy specifies one restriction, revoking access to procfs

* This policy is simple enough that it should be understandable by even an
  inexperienced user

<!-- BPFContain Implementation -->

# BPFContain Components

* BPFContain's policy enforcement engine is written in eBPF.

* eBPF maps hold per-container policy associated with individual system
  resources

* eBPF programs attached to LSM hooks are used to enforce policy

* Another eBPF program attached to a special library call associates the calling
  process group with a container ID.

* In userspace, a privileged daemon loads and manages the eBPF programs and maps.

* The user executes containers by invoking an unprivileged wrapper application.

# BPFContain Architecture

* This figure depicts BPFContain's architecture in a bit more detail

* The daemon loads its LSM programs and maps into the kernel, and updates the
  policy maps with the correct policy information

* It instruments a special eBPF program on the bpfcontain_confine library call,
  which is used to move a process group into a given container ID

* As the container makes requests to access privileged resources, BPFContain's
  LSM programs query information from the policy maps and return a policy
  decision

<!-- Conclusion -->

# Future Work I

* In future iterations of BPFContain, I would like to add support for full
  virtualization of system resources

* On the policy language design side, this involves consideration for how to
  split things up

* For example, should we have mount rules and generic resource rules? Or perhaps
  finer-grained namespace rules and cgroup rules. Perhaps there is a better way
  to do this without tying the policy language down to Linux semantics

* In the kernel side, this might involve the introduction of new eBPF helpers to
  allow the BPF programs to enforce virtualization, transparently to the target
  application
* This has the nice side effect of not requiring any additional privileges at
  runtime
* For example, we might add eBPF helpers to enter a given namespace, enter
  a given cgroup, or remount a filesystem within a given mount namespace

# Future Work II

* An easy improvement to make is get rid of the privileged daemon, since we don't
  really need it
* Instead, we could just pin whatever BPF maps and programs we need in the
  kernel and exit immediately
* The user could then update policy by executing a privileged bpfcon load-policy
  command and view audit logs by executing a bpfcon logs command

* Something else I've been thinking about is providing some kind of global
  meta-policy that would define what kinds of BPFContain policy are allowed to
  be loaded into the kernel
* For example a system administrator could enforce no default allow policies or
  no interprocess communication between containers

# Contributions

* BPFContain's contributions can be framed in a few different ways:
    * Firstly, it is a security-first approach to containers
    * Secondly, it provides a simple approach to process confinement on Linux
    * Thirdly, it's actually an implementation of that container-specific LSM we
      discussed earlier

* Ultimately, BPFContain helps defenders by providing a simple, secure method
  for defining and managing containers and an easily customizable policy
  language for ad-hoc confinement.

<!-- Backup Slides (eBPF 101) -->

# In a Nutshell

* eBPF is a Linux kernel feature which allows userspace applications to make
  verifiably safe extensions to the kernel

* In the kernel, eBPF consists of two primary functional components, BPF programs and maps

* BPF programs are written in a restricted subset of C which is compiled into
  a special BPF bytecode
* These programs are then loaded into the kernel and attached to events using
  the BPF system call
* When an attached event fires, the program is executed via just in time
  compilation to the native instruction set

* Maps are specialized key-value data structures used for storing event data
* These maps are created in the kernel by invoking the BPF system call in userspace
* They may be accessed directly by both BPF programs and userspace
  applications using either the BPF system call or a direct memory mapping

# Verifiable Safety

* In order to provide verifiable safety, eBPF relies on a limited instruction
  set and restricted execution context

* To begin with, the eBPF instruction set is highly limited
* It includes only 11 registers, 10 of which are general purpose, and 114
  possible instructions, compared to over 2000 in x86
* For extra functionality, eBPF provides access to a limited subset of kernel
  helper functions using the call instruction

* The verifier enforces a 512 byte stack limit, bounds checked memory accesses,
  no unbounded loops, and no back edges in control flow
* This allows the verifier to be certain that a program will not access unsafe
  memory and that it is guaranteed to terminate

# KRSI: eBPF LSM Programs

* The last piece of the puzzle here is something called KRSI, which allows eBPF
  programs to be attacked to LSM hooks
* This enables eBPF programs to make policy decisions about access to sensitive
  resources
* eBPF LSMs work cooperatively with other LSMs, including SELinux and AppArmor









<!-- Discarded -->

# Incremental Steps

* Creating and launching a BPFContain container consists of 6 incremental steps

* First, the BPFContain daemon loads its BPF LSM programs and maps into the kernel

* Next, it parses the YAML policy files stored in a special policy directory

* After parsing the policy files, it populates the in-kernel maps with the
  policy information, keyed based on a unique ID associated with the container
  and a unique ID for a given resource

* When the user wishes to run a container, they invoke the "bpfcon run" command
  and specify the name of the container. Note that this command requires no
  special privileges to run.

* To start confinement, bpfcon run invokes a special library call that triggers
  the in-kernel enforcement engine to associate the process group with the
  container ID

* Then, bpfcon run simply invokes the command associated with the container's
  policy file
