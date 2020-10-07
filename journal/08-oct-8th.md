# Research Journal 08

William Findlay
Oct. 8th 2020

## Wagner and Soto: Mimicry Attacks on IDS

I find that I disagree with a lot of the pH-specific commentary here. pH was
never intended to replace existing security mechanisms; rather, it was intended
to complement them. I conjecture that many of the attack vectors described here
would simply not be feasible on a properly configured system running pH. To
begin with, the threat model proposed here asserts that the attacker has access
to the same information available to the intrusion detection system with respect
to system behaviour. It is not normal for ordinary system users to have such
system-wide access without elevated privileges, let alone an attacker attempting
to break into the system. Even if we were to assume that attackers could gain
enough relevant information simply by inspecting the normal database, the attacker
would require a way of reading these files to begin with --- this assumes an
already dangerous level of access to the system.

Further, the authors completely neglect to consider the fact that normal databases
will vary wildly between varied systems. For instance, the normal database on
one system might depend on usage patterns, interactions with other applications
on the system configuration settings, and software versioning. It is intractable
to assume that an attacker who has managed to subvert the normal behaviour of
one system can apply exactly the same or even a similar tactic on another system.
The sequences will be too varied in practice to port attacks against pH from
one system to another with any degree of certainty.

I will admit that criticisms about not handling system call return codes and
arguments are at least somewhat valid. To be charitable, we will neglect the
criticisms that I have levied above and focus on preventing such mimicry attacks
from occurring. I see two general classes of mimicry attack that can be
extrapolated from what was presented in the paper: nop-based and
equivalence-based mimicry attacks. At least a partial representation of return
codes and system call arguments in an IDS could defeat both classes of attack.

For nop-based attacks, checking return codes would prevent simple nullifying
techniques (like providing a NULL pointer or garbage as a string argument to
open(2)). This could even be as simple as maintaining an acceptable threshold of
failed to successful calls, although such an approach may generated undesired
feedback loops when combined with other security mechanisms. Considering the
arguments themselves may also be desirable here to consider the case where
attackers may use "legitimate" system calls to fill the role of a nop-call.

Defeating equivalence-based mimicry attacks would require the consideration of
system call arguments. For example, it would be wise to consider
open("/var/log/test.log") and open("/etc/shadow") as two distinct items in
a given sequence. Introducing system call arguments into the behavioural
model may not be trivial, however, and depending on the implementation could
be prohibitively expensive in practice. At any rate, experimenting with ideas
like this in ebpH might be a useful endeavour. eBPF provides the perfect playground
for rapidly prototyping and testing such modifications due to its safety
and flexibility.

## Wagner and Dean: Static Analysis IDS

## The Evolution of System Call Monitoring

## Project Updates

