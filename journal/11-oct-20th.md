# Research Journal 11

William Findlay
Oct. 20th 2020

## Guided policy generation for application authors

### Paper Details

**Title:** Guided policy generation for application authors

**Authors:** Sniffen, Brian T and Harris, David R and Ramsdell, John D

**Published in:** SELinux Symposium, 2006

**Link to Paper:** http://gelit.ch/td/SELinux/Publications/Mitre_Tools.pdf

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 16, 2020

### Problem

SELinux policy is difficult to write, particularly for non-expert users.
This paper seeks to make writing policy easier for system administrators,
and application authors. By making policy easier to write, the idea is to
expand to policy author community and accelerate the adoption of SELinux
as a means of hardening Linux systems.


### Contribution

The paper presents polgen, a tool for semi-automating the process of creating
SELinux policy for an application. To examine which security contexts an
application accesses, polgen leverages a modified version of strace along with
a parser that condenses strace's output into a set of operations on system
objects. polgen represents these accesses in an IR language called PSL which
can then be compiled into SELinux policy.

polgen also works to infer whether program behaviour conforms to specific design
patterns, which allows further inference of policy. A modelling program, spar,
constructs an information flow graph based on observed system calls and a second
program, typegen, automatically generates labels for system objects so that
tightly bound interactions are reflected in the resulting policy.

Since polgen may take some liberties while generating policy, the generated PSL
is first presented to the user so that it can be modified and trimmed down as
necessary. The _hope_ is that this IR language would be simple enough that users
could understand it even if they have no hope of understanding the underlying
SELinux policy language.


### Adaptive Analysis

**Adaptive Score:** 1

**Rationale:** The _intention_ here is good. SELinux is a horrific usability
nightmare and polgen is making a good early effort at trying to rectify this.
Unfortunately, I think the result is still too tied down in the SELinux
labelling and type enforcement soup to have any real merit for any users other
than security professionals. In my view, the only real way to fix SELinux is to
move away from SELinux---it was designed by NSA experts who are simply out of
touch with the way people use their computers in the real world. I give polgen
a 1 because, while it makes an honest effort to produce something more usable,
I think these efforts are ultimately misguided and provide little value to the
average user.


### Relation to Project

One of the big goals for my project is to create a process confinement mechanism
whose policy can be both automatically generated _and_ semantically understood.
This is a key departure from polgen which is simply too tied down to its SELinux
roots to offer any real usability benefits. Some of the aspects of polgen's
approach are quite reasonable; in particular, I am a big fan of analyzing system
call sequences to generate policy. In fact, this is probably quite similar to
the direction I want to go with my project. The key is generating this policy
and making it so that users can read and understand it, even if they are not
security experts. For that, I think you need a policy language that is tightly
coupled with the policy generation mechanism itself, and that is what I intend
to do.

## Madison: A New Approach to Policy Generation

### Paper Details

**Title:** Madison: A New Approach to Policy Generation

**Authors:** Karl MacMillan

**Published in:** SELinux Symposium, 2007

**Link to Paper:** http://selinuxsymposium.org/2007/papers/08-polgen.pdf

**Reviewed by:** William Findlay

**Date Reviewed:** Oct. 16, 2020

### Problem


### Contribution


### Adaptive Analysis

**Adaptive Score:** 1

**Rationale:**

### Relation to Project
