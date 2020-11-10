# Research Journal 14

William Findlay
Nov. 3rd 2020

## Classification of Papers

### iOracle

First Author           = Deshotels
Title                  = iOracle: Automated Evaluation of Access Control Policies in iOS
Venue                  = ASIA-CCS 2018
Type                   = Defense (Audit)
Relevance              = High
Scope                  = Narrow
Feasibility/Utility    = Low
Durability of Insights = Medium
Notes                  = This work is highly relevant as it identifies vulnerable policy in one of the most widely used mobile OSes in the world. Unfortunately, its usefulness is highly specific to iOS and cannot be directly generlized to other OSes. I also give it a low score for feasibility, since it is only really useful to stakeholders who are already security experts and relies on a lot of guess-work to get around the proprietary security implementations in iOS. The insights are sort of durable, as I can imagine severak follow-up directions here.

### VulSAN

First Author           = Chen
Title                  = Analyzing and Comparing the Protection Quality of Security Enhanced Operating Systems
Venue                  = NDSS 2009
Type                   = Defense (Audit)
Relevance              = High
Scope                  = Medium
Feasibility/Utility    = Medium
Durability of Insights = Medium
Notes                  = Much of the same rationale applies here. However I upgraded, scope and utility categories as this work enables the comparison of multiple popular MAC implementations in Linux, which is both a widely used and open source operating system. I can imagine a lot of follow-up work here.

### TRON

First Author           = Berman
Title                  = TRON: Process-Specific File Protection for the UNIX Operating System
Venue                  = USENIX Security 1995
Type                   = Defense
Relevance              = High
Scope                  = Broad
Feasibility/Utility    = Medium
Durability of Insights = High
Notes                  = TRON was one of the first works that really looked into confining specific processes, moving beyond the coarse-grained, user-centric Unix DAC. Many of the ideas proposed here have persisted in modern process confinement research. I give a medium for feasibility/utility since it requires patching the system call table and there are usability issues with writing policy in terms of system call semantics.

### Janus

First Author           = Goldberg
Title                  = A Secure Environment for Untrusted Helper Applications (Confining the Wily Hacker)
Venue                  = USENIX Security 1996
Type                   = Defense
Relevance              = High
Scope                  = Medium
Feasibility/Utility    = Low
Durability of Insights = Medium
Notes                  = Janus proposes some good process confinement ideas, but it is hampered by a poor implementation choice (ptrace) that makes it unsuitable for adoption in practice. It is also not the first paper to propose similar system call interposition.

### Polgen

First Author           = Sniffen
Title                  = Guided policy generation for application authors
Venue                  = SELinux Symposium 2006
Type                   = Defense
Relevance              = Medium
Scope                  = Narrow
Feasibility/Utility    = Medium
Durability of Insights = Low
Notes                  = Only really applies to SELinux, does not divorce itself enough from underlying complex policy language to be that useful in practice.

### Madison

First Author           = MacMillan
Title                  = Madison: A New Approach to Policy Generation
Venue                  = SELinux Symposium 2007
Type                   = Defense
Relevance              = Medium
Scope                  = Narrow
Feasibility/Utility    = Medium
Durability of Insights = Low
Notes                  = Same as Polgen

## Project Updates

I've decided to change gears and work on my idea for implementing dynamic
user-defined capabilities in Linux. I've started working on an implementation,
in a private repo for now.

A few potential design considerations:

- How will users define new capabilities? I'm thinking probably via toml files.
- How will users assign capabilities to executables?
    - Filesystem extended attributes?
    - Configuration files + bpf maps?
    - Something else?
- Provide a mechanism for defining "negative capabilities"
    - Rather than allowlisting applications, denylist them instead
    - This could be useful if you only want to restrict one application from a certain behaviour
    - For example I don't want Zoom to access my home directory
- Testing:
    - Need to write unit tests
    - Need to measure performance overhead (probably similar tests to bpfbox?)
- Case studies:
    - Zoom
    - Discord
