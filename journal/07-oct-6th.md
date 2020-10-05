# Research Journal 07

William Findlay
Oct. 6th 2020

## Evaluating Security Products with Clinical Trials

At first glance, I like this idea. It's unconventional and it offers a solution
to the disparity between security evaluations in theory and how well security
software work in practice. What I am left wondering is what the motivation is
for users to participate in these clinical trials. In medical clinical trials,
participants may be motivated by a sense of self-preservation or desperation.
For example, a terminal cancer patient has clear motivation to participate in an
experimental drug trial. In computer security, this motivation is less clear;
the stakes are much lower but not low enough such that a user wouldn't care if
their system were to be damaged in some way by trial software. The paper does
provide some example incentives that I think are on the right track. I am left
thinking back to BOINC here. In BOINC, users were motivated to participate by
a public leaderboard with rewards. I wonder how well a system like that would
work if it were put in place here?

I definitely agree with the fact that, if security experts can't help non-expert
users in practice, it's no wonder that we have insecure systems. I think this
ultimately connects back to the idea of "changing the game" that we have
established in this course. In the current game, results in practice will be
vastly different than controlled experimental results due to attacker
innovation, complexity of system configuration and interactions, and users
error/apathy. The key here is understanding that results from out in the wild
would be much better at framing the security of a piece of software in the
context of the security game we are currently playing. Unfortunately, it seems
like we mostly really engage in controlled tests rather than field studies.

The approach presented here does make a lot of sense to me. The parallels
between computer security and medicine are obvious here and the paper does
a good job of comparing and contrasting the two fields. It's simply impossible
to capture, in a controlled lab setting, the complex and diverse configurations
and interactions that occur in the real world ---  much the same as it is in
medicine. Ultimately, I suppose that an approach like this would make the most
sense when combined with the more traditional testing frameworks we already have
in place.

I feel like the authors made a number of good considerations here; many of the
original questions I had about how well control groups and participation
incentives would work in practice were answered later on in the paper. One
slight problem that came up in my mind which was *not* addressed is how well
double or even single blinding would work here in practice. This would be
a particular challenge if usability is a major concern; we can only modify the
UI so much before breaking functionality or seriously impacting the results of
a usability study.

Despite all the positive things I have had to say so far, this approach is
undeniably unorthodox. Although the motivation is clear, it is not so clear that
we have arrived at a perfect solution, particularly in light of many of the
obstacles outlined in later sections. I am left wondering what the response has
been to this work from the research community: positive, negative, or apathetic?

## A Clinical Study of Risk Factors Related to Malware Infection

It's pretty cool to see the approach outlined in the previous paper being more
or less applied in practice here. Based on the presented results, it seems like
the clinical trial was indeed a successful endeavour. One thing that sort of
disappointed me (although it is completely understandable) is how few
participants were involved in the study. It would have been interesting to see
how well this methodology scales up in practice (in the first paper, they were
discussing multi-million-dollar studies with thousands of participants).

I was surprised by some of the ethnographic results presented in the related
work section, particularly the age demographics for infection risk. I would have
expected that older people would be more susceptible to infection, when in
reality the evidence seems pretty clear that it is in fact young people who are
most susceptible. On the other hand, I was not at all surprised to learn
that Windows users are more susceptible than users of other operating systems.

## Other Project Updates

- Been building out the bibliography for my literature review this week
- Started some early work on a WARDEN implementation

