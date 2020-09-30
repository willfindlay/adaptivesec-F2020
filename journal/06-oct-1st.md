# Research Journal 05

William Findlay
Sept. 29, 2020

## Diversity-Based Traffic Management for Mitigating DoS

## NetADHICT

After reading the NetADHICT paper again, I noticed striking similarities between
the type of event sequence analysis I hope to do in WARDEN and the (p,n)-gram
enabled hierarchical clustering approach explored here. This of course is
despite the vastly disparate problem domains (network traffic vs OS-level system
security events). I first read this paper about a year ago, so it would make
sense that some of these ideas were percolating in the back of my mind. The
specific similarities I'm noticing are as follows:

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

## Other Project Updates

No real project updates this time, besides some thoughts I came up with while
reading the papers for this week. Project time will grow exponentially starting
this weekend.
