# Research Journal 04

William Findlay
Sept. 24, 2020

## Content Provider Conflict on the Modern Web

I got about half way through reading this paper when it suddenly dawned on me
that what is being described here is really just a high stakes game of CoreWar
taking place in the web browser. On individual pages, within the "sandbox"
defined by the browser, competing JavaScript applications are free to openly
attack each other, replacing existing code, deleting important DOM objects, and
even faking clicks to subvert the validity of ad revenue. The parallels between
this environment and the environment described in CoreWar are immediately
obvious. In both situations, programs take advantage of the fact that the
environment imposes essentially no restrictions on their capabilities to
interfere with other running programs (of course in the case of the web browser,
we are still restricted to the sandbox imposed on the webpage itself). The fact
that this is a situation that exists in the modern web is honestly frightening.

## Visual Security Policy for the Web

## Project Updates

- Been running a few simple BPF programs in the background to determine what sequences of LSM hooks are most common and whether there is a significant difference in sequence frequency
- So far, results seem quite promising -- A few sequences seem to dominate the others by a significant margin... Honing in on a magic number should hopefully allow weeding out the nonsense sequences from the important ones
- Since it will likely be important to consider variable length sequences, I'll probably need to develop a simple weighting system to compensate for difference in sequence length (which would almost certainly affect their frequency)
