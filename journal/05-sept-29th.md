# Research Journal 05

William Findlay
Sept. 29, 2020

## Elevator Pitch

As outlined in prior journal entries, my plan for the research project is to
implement an adaptive process confinement mechanism for Linux in eBPF. In
particular, the idea is to analyze sequences of security-sensitive events
generated in running processes and combine these sequences into an ad-hoc policy
language that matches the behaviour patterns of the underlying system. This
approach is informed by my prior work in using eBPF to implement sequence-based
anomaly detection mechanisms and more conventional process confinement
mechanisms. The current name I have chosen for this project is WARDEN
(a backronym for Will's Adaptive Response Dynamic Enforcement eNgine).

In addition to generating the underlying policy language itself, WARDEN will
facilitate the automatic creation of the policy files themselves through strong
integration with the underlying eBPF enforcement engine. This would serve to
maximize the transparency of the security system, hiding its details from
non-expert users while providing acceptable security in practice. I also hope to
provide interfaces for defining semantic aliases for the generated
sequence-based rules. The key insight here is that sequences of
security-sensitive operations can often be semantically understood at a higher
level. For example, a `fork->execve` sequence might be more easily understood as
`run_program`, while an `open->lseek->read->close` sequence might be understood
as `peek_file` or something similar. These measures taken together should
drastically increase policy expressiveness, auditability, and usability.

I've set up a GitHub repository for this project, although only preliminary experimentation
with statistics on sequences has been done so far: https://github.com/willfindlay/warden

## "A Sense of Self for Unix Processes" and "Automated Response Using System-Call Delays"

Both of these papers obviously hold a very special place in my heart, as the
work presented here forms the basis for my own work on ebpH, the topic of my
undergraduate thesis. This background affords me a very intimate knowledge of
the concepts and ideas presented here, as I have actually implemented them
myself in eBPF. Further, I am very familiar with the limitations of the
approaches presented here, particularly the difficulty of getting stable normal
profiles for more complex applications (something which I am still working on
in ebpH).

## Other Project Updates
