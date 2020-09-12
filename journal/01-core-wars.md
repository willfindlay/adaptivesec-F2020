---
Title: "Research Journal 01: Core Wars"
Author: William Findlay
Date: Sept. 10, 2020
---

# The Basic Idea

- processes battle each other for control of time-sharing virtual machine (running the Redcode instruction set -> custom assembly language written for CoreWar)
- each process is trying to win by killing the other
    - the win condition: force the opposing program to try to execute a non-executable "instruction" (i.e. a value in the data segment)
- processes take turns, each executing one instruction at a time

# Random Thoughts

- the PCT instruction is being proposed as a defensive technique, but I think it could also be used offensively against programs like Raidar (after reading the second article, it seems like others had the same idea! cool.)
- for example, PCT could be used to prevent such programs from properly creating their pickets, or from properly replicating themselves when they sense danger
- this is absolutely hilarious: "I abandoned this line of work after one production run in which a sterile mutant ate and killed the only fertile creature in the universe."
