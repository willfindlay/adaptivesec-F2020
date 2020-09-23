# Research Journal 04

William Findlay
Sept. 24, 2020

## Content Provider Conflict on the Modern Web

## Visual Security Policy for the Web

## Project Updates

- Been running a few simple BPF programs in the background to determine what sequences of LSM hooks are most common and whether there is a significant difference in sequence frequency
- So far, results seem quite promising -- A few sequences seem to dominate the others by a significant margin... Honing in on a magic number should hopefully allow weeding out the nonsense sequences from the important ones
- Since it will likely be important to consider variable length sequences, I'll probably need to develop a simple weighting system to compensate for difference in sequence length (which would almost certainly affect their frequency)
