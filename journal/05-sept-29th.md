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

In addition to generating the underlying policy language, WARDEN will
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

My preliminary experimentation lives in the `project` subdirectory in this repository,
rather than in the WARDEN repository.

## "A Sense of Self for Unix Processes" and "Automated Response Using System-Call Delays"

Both of these papers obviously hold a very special place in my heart, as the
work presented here forms the basis for my own work on ebpH, the topic of my
undergraduate thesis. This background affords me a very intimate knowledge of
the concepts and ideas presented here, as I have actually implemented them
myself in eBPF. Further, I am very familiar with the limitations of the
approaches presented here, particularly the difficulty of getting stable normal
profiles for more complex applications (something which I am still working on
in ebpH).

A fundamental difficulty for this kind of sequence analysis is sources of
non-determinism. Non-deterministic behaviour can destabilize profiles before
they normalize and, perhaps even worse, generate false positives in normal
monitoring. A key source of this kind of non-determinism is the concept of
signals and signal handlers, which can (and do) interrupt in-progress system
calls, disrupting current sequences and potentially introducing new system calls
into the middle of a sequence from the signal handler itself. While this problem
is quit easily fixable by storing a stack of sequences, other sources of
non-determinism are not so clearly handled. For example, consider complex
interactions between processes and threads or user I/O. Solving these issues
or at least mitigating them will be the key to increasing the adoptability
of systems like pH and ebpH.

Of course, this issue of non-determinism is  also a relevant concern for my
project, since I plan to use sequences of events in my policy languages. I think
a key difference here, however, is that rather than denying on sequences that
don't match, we want to deny on sequences that *do* match. In practice, this
should probably be done probabilistically (i.e. based on percent matches), as
otherwise non-deterministic behaviour now swings in the direction of false
*negatives* rather than false positives. I imagine that this matching
would probably take place with the help of a specialized data structure like
an LPM Trie. eBPF already has an LPM Trie map that might be well-suited to this
task, although its traditional use case is for matching IP address prefixes
for networking programs.

## Other Project Updates

- Starting to think about literature review
- Hajime Inoue's dissertation may the closest work to what I'm proposing here,
  but in general it is still quite far from what I'm trying to do
    - https://www.cs.unm.edu/~forrest/dissertations/inoue-dissertation.pdf
- Also related are policy generation mechanisms like Madison, audit2allow,
  aa\_easyprof, Polgen, and Slide
