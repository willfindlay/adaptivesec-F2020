# Research Journal 03

William Findlay
Sept. 22, 2020

## Areas of Interest

My areas of interest primarily lie in the areas of operating system security,
intrusion detection, operating system observability, process confinement, and
access control. In particular, I am interested in finding novel ways to use
eBPF, an emergent observability and kernel extension framework for Linux, to
implement new security mechanisms for Linux and to audit and augment existing
ones. Since eBPF enables a high degree of system observability, there should be
plenty of opportunities to integrate it with adaptive approaches for operating
system security, utilizing gathered information to build a model of system state
and detect attacks. Further, eBPF's safety and flexibility should enable both
rapid prototyping and dynamic loading and unloading of security policy in
response to certain system events or user intervention.

In the past, I have worked on [ebpH](https://github.com/willfindlay/ebpH), an
eBPF-based intrusion detection system written as a modern re-implementation of pH
([Process Homeostasis](https://people.scs.carleton.ca/~mvvelzen/pH/pH.html)),
and [bpfbox](https://github.com/willfindlay/bpfbox), an eBPF-based policy enforcement
engine which provides a simpler and more sophisticated alternative to existing
process confinement mechanisms on Linux.

## Software Diversity: Security, Entropy and Game Theory

## Object-Level Recombination of Commodity Applications

## Really Cool Project Idea

- observe the system and automatically generate coarse grained rules that match observed patterns of behavior
- provide a mechanism for defining allow/deny operations on these coarse grained rules
- provide a mechanism for combining and editing these rules
- users can associate rules with specific programs, an eBPF enforcement engine would then enforce them
- users can mix and match and edit rules as they see fit
- rules would be optionally parameterized by their LSM object IDs (for example, you could parameterize a rule that contained an inode access by that inode or filesystem number, but you wouldn't necessarily have to do this)
- in addition to generating rules, you could also generate the policy that uses these rules and this generation could optionally either be parameterized or generic

I've created a git repository for this project: https://github.com/willfindlay/WARDEN
