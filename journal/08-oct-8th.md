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

At the risk of quoting Rick and Morty, this just sounds like pH with extra
steps. Really what you're doing here is the same sequence-based analysis, but
instead of generating sequences at runtime, you are pre-generating expected
sequences by statically analyzing program binaries. If anything, this is
a _less_ adaptive approach and could potentially be restrictive in practice. The
approach here is also limited to analyzing C code, without regard for other
types of applications. pH, on the other hand, is transparent to the underlying
implementation of the observed applications.

The trivial model proposed in 4.1 is, at a close approximation, basically
equivalent to seccomp and seccomp-bpf in Linux. Applications specify system
calls that are allowed and disallowed. While rules may be arbitrarily
fine-grained based on system call arguments, there is no regard for a stateful
representation of these system calls --- each call is taken on its own.

The "impossible paths" problem in the callgraph model strikes me as a critical
limitation of the initially proposed approach. Ironically, this permits very
similar mimicry attacks to those proposed against pH. The attacker would be able
to follow the impossible execution path and potentially use it to execute
exploit code. I do like the clever workaround proposed in the paper (maintaining
a separate state machine to keep track of the call stack).

The digraph approach seems by far the most convincing, and this is indeed
reflected in its performance evaluation. The other two approaches seem to be
prohibitively slow even for modestly complex software. I'd be curious what the
performance overhead vs precision benefit of higher k-graphs would be.

The idea of ignoring certain system calls to improve model precision is
interesting. I wonder if this could also be applied to ebpH. Something to
experiment with when I have more free time.

After reading the entire paper, my thoughts are that this seems to be an
overly-contrived approach to what could (and perhaps should) be a much simpler
problem. The amount of implementation hoops they had to jump through to even get
this thing running is astonishing. A lot of the topics outlined as challenges
are actually challenges for pH as well --- but, in pH's case, the solution to
these challenges is often much simpler. For example, handling non-determinism
from signal handlers in pH is as simple as maintaining a separate sequence
during the signal handler.

"Despite these successes,  we feel strongly that our tool should not be used as
the sole defense against any of these attacks,  but  instead  should  be  used
to  complement  other techniques." This is just ironic.

## The Evolution of System Call Monitoring

Interesting to see this paper confirming many of the points I made about the
first paper. In particular, I think the point about diversity of normal behaviour
across systems is very important. One simply cannot assume that the same mimicry
attack would work on different hosts. These attacks would need to be crafted online,
which is a non-trivial task.

Most of the data modelling methods discussed in section 5 seem kind of contrived
and crappy. In particular, I am not convinced that just throwing a neural network
at a sequence of system calls and hoping for the best will yield either meaningful
or useful results, particularly as training would need to occur offline.

I liked the suggestion of using static and dynamic analysis to complement each
other. I hadn't considered the possibility of bootstrapping profiles with static
analysis and then tuning them at runtime.

## Project Updates

Haven't had much time to work on the project since last class. A lot of the
ideas in the papers from this week have been percolating in the back of my mind,
since my project is interested in analyzing event sequences to generate policy
language. I think it might be worth having another read of each of these papers
when I start thinking more about designing and implementing WARDEN.
