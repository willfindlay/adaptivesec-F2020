# Research Journal 05

William Findlay
Sept. 29, 2020

## Diversity-Based Traffic Management for Mitigating DoS

Seems like this paper first introduces the concept of (p,n)-grams used later
in NetADHICT. While I have had a chance to read the NetADHICT paper before,
I've never looked at this one. It's interesting to see a bit of early context
on what the authors were thinking before NetADHICT.

Something that caught my eye early on in the paper was the notion of flash
crowds of traffic potentially appearing legitimate when in fact they were
originated maliciously. The truth of this statement is obvious, but it seems to
be something that most of the anomaly detection methods have completely missed.
Rather than classifying legitimate vs illegitimate, a better approach might be
a finer-grained classification based on a variety of attributes. That seems to
be what is being suggested here.

I really like the (p,n)-gram approach here because it insightfully captures the
highly positional nature of data within a packet (largely due to multiple layers
of encapsulation) and it saves significantly on runtime overhead at the same
time. Quite a simple and elegant solution to online network traffic
classification. I also really like the idea of using (p,n)-gram classification
to split traffic into separate queues. This seems like a really elegant way to
ensure that different classes of traffic get a proportional share of the network.

The one thing I am kind of sceptical about here is the idea of analyzing
patterns within packet payloads in addition to packet headers. Maybe this wasn't
so much the case when this paper was originally written, but these days, a very
significant potion of network traffic is encrypted. This might have significant
effects on the efficacy of an approach that looks for patterns within packet
payloads.

I noticed that the experimental implementation here fixes n=4. In the NetADHICT
paper, the results showed that n=2 was a superior value of n for capturing just
enough distinct (p,n)-grams within a packet. I'd be curious whether different
values for n were considered in the original paper or not (it was certainly
suggested that smaller values of n might be considered, but it seems like this
never ended up being tested).

## NetADHICT

After reading the NetADHICT paper again, I noticed striking similarities between
the type of event sequence analysis I hope to do in WARDEN and the
(p,n)-gram-enabled hierarchical clustering approach explored here. This of
course is despite the vastly disparate problem domains (network traffic vs
OS-level system security events). I first read this paper about a year and
a half ago, so it would make sense that some of these ideas were percolating in
the back of my mind. The specific similarities I'm noticing are as follows:

- ADHIC wants to capture the most frequent patterns and ignore very infrequent
  ones which may be related to packet contents rather than protocol-specific
  patterns; in WARDEN I plan to do much the same thing for LSM events --- my
  hypothesis here is that the most common sequences will be strongly related to
  important usage patterns and should be more semantically understandable to
  users and policy authors.
- ADHIC's hierarchical clustering produces semantically meaningful results. For
  example, nodes in the decision tree might separate TCP traffic from UDP
  traffic, or CUPS traffic from regular traffic. My hope is that WARDEN's
  sequence-based rules might also be semantically meaningful. Finding
  similarities with the ADHIC approach is probably a good sign here.
- I hope to use a tree structure in WARDEN for probabilistically splitting
  sequences. This approach is quite similar to ADHIC's splitting decision tree.

While I don't think (p,n)-grams are necessarily the answer for my work (system security events
don't necessarily have fixed positions within a frame like packet data does), other
aspects of the NetADHICT approach do merit consideration as to whether they can
be applied to my domain.

Overall thoughts on the paper: The first time I read this I thought it was
pretty cool. My security knowledge and specifically my experience in developing
adaptive security mechanisms have both matured significantly since then, so
I feel like I've gained a renewed appreciation for the "sophisticated
simplicity" that is being explored here. Sort of reminds me of our discussion
about pH in the last lecture, in that the original idea (lookahead pair based
analysis) was chosen for its simplicity but ended up working remarkably well.

## Other Project Updates

No real project updates this time, besides some project-related thoughts I came
up with while reading the papers for this week. Project time will grow
exponentially starting this weekend.
