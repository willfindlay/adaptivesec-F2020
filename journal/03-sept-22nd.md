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

This paper was insanely cool --- I think in part because of how visceral it was
to see screenshots of actual recombined programs. A clear problem that immediately
jumped out to me was that of unresolved symbols when linking recombined object
files; even with closely related ancestor programs, I would imagine that carelessly
recombined object files could still produce a significant number of linker errors.
I was pleasantly surprised by the simple solution proposed in the paper: simply resolve
these linker errors by borrowing from the other parent's object files where necessary.
This kind of reminded me of the idea of dominant and recessive genes in nature,
in that it is possible to have a copy of both variants at the same time.

It would have been nice to have a bit more information about the specific
fitness scripts employed for GNU `sed` and `Dillo`, as well as the overall
fitness level of the resultant variants. In particular, I am curious whether the
generated versions of `sed` possessed some or all of their original
functionality. It would also be necessary to determine the extent of code
coverage for the fitness scripts in order to truly gauge how effectively each
fitness script captures the desired functionality of generated applications. For
example, a fitness script that only captures 40% of desired functionality can
only maximally determine that resulting applications are 40% functional.

By far the coolest part of the paper was the discussion of Quake variants.
I think the fact that the genetic algorithm was able to *repair* a graphical bug
by combining two versions of Quake is an astonishing result. A major
contributing factor towards these interesting results was the fact that
recombination occurred between divergent versions of Quake rather than two
linear versions. While many free and open source software repositories *do* have
two or more divergent forks, it is not necessarily easy to find divergent forks
that are both actively and separately maintained. Some examples do come to mind,
such as Gimp/Glimpse, vi/vim, and several popular variants of GNU Emacs, but in
general I believe such cases to be the exception rather than the rule.

## Really Cool Project Idea

- observe the system and automatically generate coarse grained rules that match observed patterns of behavior
- provide a mechanism for defining allow/deny operations on these coarse grained rules
- provide a mechanism for combining and editing these rules
- users can associate rules with specific programs, an eBPF enforcement engine would then enforce them
- users can mix and match and edit rules as they see fit
- rules would be optionally parameterized by their LSM object IDs (for example, you could parameterize a rule that contained an inode access by that inode or filesystem number, but you wouldn't necessarily have to do this)
- in addition to generating rules, you could also generate the policy that uses these rules and this generation could optionally either be parameterized or generic

I've created a git repository for this project: https://github.com/willfindlay/WARDEN
