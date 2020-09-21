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

It's interesting to consider software diversity from a game-theoretic
perspective, particularly as a major driving factor behind the adoption of of
diverse software and system configurations is human choice. I am skeptical about
how highly diversity-based security ranks as a heuristic among users when
choosing the applications they run on their systems (particularly systems for
personal use, although these do not necessarily present the high value targets
we are concerned with). Although classification of system diversity is a useful
metric to consider, I think that the paper is correct in pointing out that such
decisions may need to be made automatically at the package management level.

I think the idea of a diversity-focused variant of CTF challenges helps to
characterize a relatively abstract paper in a very concrete way. I can imagine
such competitions actually occurring in real life. It would be interesting to
see how well the theoretical models proposed in the paper would match the actual
behavior of agents playing such a game.

I was a bit curious about the last paragraph of the conclusion which posits
that anomaly-based IDS software may already be diversity-type defenses
as characterized by the presented entropy model. I have done a fair amount of
work in intrusion detection during my undergraduate career and never really
made the connection between intrusion detection and diversity per se ---
of course, IDS systems are *adaptive* but do they actually introduce
diversity? I suppose it could be argued that fundamental differences in generated
behavioral profiles could count toward the diversity of the underlying system,
but I would have been interested in hearing a bit more about this in the paper
itself.


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
