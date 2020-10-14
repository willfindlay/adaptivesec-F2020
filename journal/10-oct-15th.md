# Research Journal 10

William Findlay
Oct. 15th 2020

## TRON: Process-Specific File Protection for the UNIX Operating System

### Paper Details

**Title:** TRON: Process-Specific File Protection for the UNIX Operating System

**Authors:** Andrew Berman and Virgil Bourassa and Erik Selberg

**Published in:** Proceedings of the USENIX 1995 Technical Conference

**Link to Paper:** https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.56.9149&rep=rep1&type=pdf

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 14, 2020

### Problem

Existing Unix DAC is a far too granular approach for the proper protection of
files. UNIX DAC can protect users from other users, but fails to protect users
from their own processes. A compromised process or malicious application can
interfere with any file that its user can write to, read any file that its user
can read, or execute any application that its user is allowed to execute. This
problem is further exacerbated when such a process runs with the privileges of
the superuser---now they can bypass any discretionary protection mechanisms on
the system. These factors motivate a need for a granular, process-specific
approach for file protection. This paper presents an early effort to solve this
problem.

### Contribution

The paper presents TRON, a kernel-level mechanism for enforcing per-process
protection domains at the system call level. Protection domains are inherited
across forks and are transitioned using the special `tron_fork` system call.
TRON interposes on system calls by modifying the Unix system call table to
redirect control to the appropriate TRON wrapper for a given system call. The
TRON wrapper makes the appropriate access control decision based on the current
TRON protection domain for the process and then invokes the original system call
implementation if access is granted. If access is not granted, the system call
fails and traps to the process' registered "violation handler".

### Adaptive Analysis

**Adaptive Score:** 1

**Rationale:** TRON helps defenders by providing a discretionary means for
restricting the access each process has to files on the system. Since TRON is
implemented in kernelspace and does not break any existing userspace APIs, it is
at least transparent to applications that do not wish to make use of it.
Further, a userspace library helps to simplify interaction with TRON's
kernelspace components and wrapper programs are provided to allow TRON to be
used with existing applications without needing to modify the application code
itself.

Unfortunately, I see a few barriers in the way of adoption here. Firstly, TRON
assumes that the end user is familiar with the implications of granting or
revoking certain privileges on given files. It is not clear that a non-expert
user would be able to use TRON to effectively limit the damage that a process
can do. Since TRON is discretionary, it does nothing to prevent a user from
shooting themselves in the foot by granting overly permissive privileges to
a process. Further, although TRON does provide some helper applications to
enable confinement of processes without modifying application code, more
sophisticated use cases may still require modification of the target
application. Finally, the fact that TRON requires hooking into the system call
table would likely be prohibitive for adoption in industry. Such hooks can be
quite difficult to implement correctly and such an implementation may present
non-negligible risks when used in practice. In light of these limitations,
I give TRON an adaptive score of 1.

### Relation to Project

In my project, I am hoping to create a more adaptive process confinement
solution in Linux. While I agree with many aspects of TRON's approach, there are
a few things I would do differently. First of all, I think that wrapping system
calls by modifying the system call table is an incorrect approach, due to the
safety considerations involved in production use cases. In Linux, we now have
eBPF which allows safe and reliable introspection and extension of userspace and
kernelspace functionality. I imagine that if eBPF were available at the time,
it would have been strongly considered for the TRON implementation. I will
use eBPF to implement my process confinement mechanism to help increase
adoptability.

Another issue I take with TRON is that it is not necessarily easy for non-expert
defenders to know which system-call-level permissions should and should not be
given to a particular process. Specifying access directly at the system call
level is likely too arcane for non-expert users to understand and use
effectively in practice. A key insight in my project will be that taking
sequences of access events together may be more semantically understandable in
practice. For example, rather than saying that a process is allowed to fork
itself and execute a file, these facts could be taken together as "this process
is allowed to run this program". By assigning semantic labels to strings of
actions, we can reduce the burden on defenders by making it easier to write and
understand security policy.


## A Secure Environment for Untrusted Helper Applications (Confining the Wily Hacker)

### Paper Details

**Title:** A Secure Environment for Untrusted Helper Applications (Confining the Wily Hacker)

**Authors:** Ian Goldberg and David Wagner and Randi Thomas and Eric Brewer

**Published in:** Proceedings of the Sixth USENIX UNIX Security Symposium

**Link to Paper:** https://www.usenix.org/legacy/publications/library/proceedings/sec96/full_papers/goldberg/goldberg.pdf

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 14, 2020

### Problem

Problem the paper is trying to solve.

### Contribution

How they solve the problem

### Adaptive Analysis

**Adaptive Score:**

**Rationale:**

### Relation to Project

How this related to my project / how I plan to do things differently or similarly


