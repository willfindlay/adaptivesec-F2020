# Research Journal 09

William Findlay
Oct. 13th 2020

## iOracle: Automated Evaluation of Access Control Policies in iOS

### Paper Details

**Title:** iOracle: Automated Evaluation of Access Control Policies in iOS

**Authors:** Luke Deshotels, Răzvan Deaconescu, Costin Carabas, Iulia Mandă, William Enck, Mihai Chiroiu, Ninghui Li, and Ahmad-Reza Sadeghi.

**Published in:** ACM ASIA-CCS 2018

**Link to Paper:** https://dl.acm.org/doi/pdf/10.1145/3196494.3196527

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 10, 2020

### Problem

Modern operating systems like iOS often require complex security policies
comprised of multiple interacting policy frameworks and enforcement engines,
including access controls built into the operating system itself. Since these
policy creation and enforcement mechanisms may interact in complex and
non-intuitive ways, it is often very easy to misconfigure a security policy and
leave it open to attacks. This paper seeks to find a reasonable solution to this
problem by making it easier for defenders to audit policy in such a complex
environment.

### Contribution

The authors built an application, iOracle, which reverse engineers iOS security
policies pertaining to system executables and automatically constructs a logic
database (written in Prolog) to which defenders can issue high level queries
about the security properties of applications residing on the system. The
authors showed that iOracle was able to reveal information about how existing
attack vectors could have been found more easily as well as identify several
previously undiscovered attack vectors. Further, iOracle provides information
about how to modify the existing security policy to resolve these security
problems. This semi-automation of policy auditing represents a significant step
toward reducing the inherent risk of policy misconfiguration in complex
environments such as iOS.

### Adaptive Analysis

**Adaptive Score:** 2

**Rationale:** This research greatly helps defenders by taking what was
originally a hard problem (identifying weaknesses in a complex soup of policy
definition and enforcement mechanisms) and making it significantly easier. It
does so by providing a semi-automatic, unified approach to auditing iOS access
control policy. Attackers will have a difficult time responding to this because
the system is able to detect attack vectors before human adversaries have even
discovered them. Further, when an iOracle query identifies a vulnerability in
the security policy, it shows the defenders how the vulnerability can be fixed
using the semantics of the underlying policy language. The only way I can see
to defeat this would be to defeat the policy enforcement mechanisms themselves.



## Analyzing and Comparing the Protection Quality of Security Enhanced Operating Systems

### Paper Details

**Title:** Analyzing and Comparing the Protection Quality of Security Enhanced Operating Systems

**Authors:** Hong Chen, Ninghui Li, and Ziqing Mao

**Published in:** NDSS 2009

**Link to Paper:** https://www.cs.purdue.edu/homes/ninghui/papers/comparison_ndss09.pdf

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 10, 2020

### Problem

Briefly explain the problem the paper addresses.

### Contribution

Briefly explain what they did to address their problem, whether it was to
develop an attack, build a defence, make a theory, do a user study, or
something else.

### Adaptive Analysis

**Adaptive Score:**

**Rationale:**
