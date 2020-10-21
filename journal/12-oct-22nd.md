# Research Journal 08

William Findlay
Oct. 8th 2020

## Findlay: bpfbox

Can't really write a journal entry about my own paper.

## Chao: Information Immune Systems

I the notion that an information immune system could be used to filter out
desired output from random input to be quite bizarre. To me this seems like
a bit of an exaggerated claim, since any random output with reasonable entropy
will be mostly noise. Just because you can filter known-bad output from that
pool of noise doesn't mean that the rest of the output will be good. Of course,
this is just my intuition, but it strikes me as an odd claim.

It is interesting to consider the parallels between natural immune systems and
defensive mechanisms used in our computers. For example, the idea of
signature-based IDS complementing an anomaly-based IDS mirrors the stable
signatures and learned patterns used in the immune system. Something I realized
while working on ebpH during my undergrad was that a complete solution would
likely involve several such IDS mechanisms working together, monitoring
different aspects of system behaviour and training models.

I am curious what would happen if the user accidentally flags good
data for rejection, training the IIS (via costimulation) that such data
should be rejected in the future. Would the user be able to reverse their
action? Based on the description, costimulation in the IIS seems to take an
all-or-nothing approach, where only detectors that have been costimulated
are instantiated. I would be curious whether something like a stimulation
threshold would be feasible---instead of immediately instantiating a detector,
there would be a required costimulation threshold in order to start rejecting,
and this threshold could be crossed multiple times in either direction.

I also wonder whether it would be possible for an adversary to maliciously train
an IIS to filter _good_ data instead of _bad_ data. In this way, the IIS could
be used for censorship for example. This kind of threat model would apply mostly
to group IISes.

## Project Thoughts

The information immune system has got me thinking about whether such an approach
might make sense in policy generation. Users would be presented with behavioural
patterns and flag them as being either desired or undesired. Of course, these
behavioural patterns would need to have semantic meaning for the user, or they
would be unable to make decisions on whether or not the behaviour is desired.
Also, an IIS for process confinement would need to be inoculated with known-bad
data, which may not necessarily be a trivial task. Another idea would be to have
the IIS share generated policy with its peers and use consensus to inform its
model of good and bad behaviour. This would approximate the group IIS model
proposed in the paper.

This would be an interesting approach, but I'm not fully convinced that it is
the right approach.
