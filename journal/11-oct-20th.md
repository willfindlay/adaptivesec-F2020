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

**Date Reviewed:** Oct. 17, 2020

### Problem

SELinux policy is _still_ difficult to write, even after advances such as polgen
and the modular SELinux reference policy. The goal of this paper is to try and
make it easier for defenders to write SELinux policy, just like it was for
polgen above.

### Contribution

In the time that passed since polgen, SELinux introduced new mechanisms for
writing modular policy (the reference policy) that expose higher level
interfaces for policy authors to use. This paper presents Miranda, an effort to
integrate automatic policy generation with the reference policy itself so that
policy authors can use generated interfaces when writing SELinux policy. The
idea is that this method would be complimentary to existing policy generation
methods such as polgen.


### Adaptive Analysis

**Adaptive Score:** 1

**Rationale:** This research helps defenders by offering a means of generating
re-usable interfaces that can be plugged into policy as needed. The hope is that
this would help to abstract away many of the complex details of the underlying
policy while providing semantically understandable interfaces to use the
generated reference policy. Unfortunately, I still think that this approach
is too tied down to the underlying SELinux specifics to be of any real use to
non-expert users and so I give it a 1.

### Relation to Project

This work is nice because I think it captures a key point in policy generation:
generate the underlying policy and group it into semantically understandable
clumps (i.e. distinct reference policy modules). I'd like to carry forward this
idea in my project, but greatly simplify the underlying policy language and
enforcement mechanism so that generated policy is still auditable by non-expert
users.
