# Research Journal 01: Core Wars

William Findlay
Sept. 10, 2020

<!--
# The Basic Idea

- processes battle each other for control of time-sharing virtual machine (running the Redcode instruction set -> custom assembly language written for CoreWar)
- each process is trying to win by killing the other
    - the win condition: force the opposing program to try to execute a non-executable "instruction" (i.e. a value in the data segment)
- processes take turns, each executing one instruction at a time

# Random Thoughts

- the PCT instruction is being proposed as a defensive technique, but I think it could also be used offensively against programs like Raidar (after reading the second article, it seems like others had the same idea! cool.)
- for example, PCT could be used to prevent such programs from properly creating their pickets, or from properly replicating themselves when they sense danger
- this is absolutely hilarious: "I abandoned this line of work after one production run in which a sterile mutant ate and killed the only fertile creature in the universe."
- interesting how many attacks and defenses have survived in one form or another from the early descriptions in the second article
    - also interesting to see how much more damage these attacks could do back when systems had basically no protection
    - for example Apple II had no private address spaces or user/kernelspace separation, so a worm could just wipe the entire DOS
-->

## First Article

Core War is probably one of the coolest things I have seen in a very long time.
The idea is simple enough: two processes battling for control of a virtual
machine, each one trying to cause the other to encounter an exception and die;
what is remarkable to me about Core War is that its apparent simplicity belies
a deeply intricate and complex game of strategy beneath the surface. The idea of
programs fighting to the death in a battle arena implies that the fittest
program must survive --- a crude form of natural selection arises where
selective pressure comes from the desires of human programmers to win the
battle. Although Redcode is only a simple assembly-like language on the surface,
it offers a rich and diverse solution space for such programs to be defined.

I was so intrigued by CoreWar that I had to try it myself, which I did at this
link: https://crypto.stanford.edu/~blynn/play/redcode.html While I wasn't able
to beat either the MICE or the CHANG1 programs, I found I was able to grasp many
of the core concepts and "design patterns" that were discussed in the article.
By "design patterns" I am of course referring to common constructs that seem to
show up in many CoreWar programs and are known to produce interesting or useful
results. One example of such a design pattern, the IMP-GUN (spl 2; jmp -1; mov
0 1), allows you to continually launch a barrage of killer programs into
a neighboring address space. The simulation at the above URL provides
a visualization of the resulting programs in operation, and it is definitely
cool to see your IMPs being fired into enemy territory in real time. In a way,
patterns like the DWARF, IMP, IMP-GUN, and IMP-STOMPER are similar to the
analogous structures we see between populations in biology --- the useful
blueprints tend to show up time and time again.

![My two IMP-GUNs racing across the address space.](./figs/imp-guns.gif "IMP-GUNs")

The GIF above shows my two IMP-GUNs racing across the battlefield. Curiously,
a pattern emerges where each side's "bullets" chase the enemy's main program
indefinitely, never quite catching up to it.

Towards the end of the article, Dewdney discusses potential improvements to CoreWar,
including a new PCT instruction that would prevent an address from being overwritten
until it is next executed. This would provide programs with a way to defend themselves
from crude guessing attacks that involve bombing distance addresses with 0s. However,
I noted that this capability could also be used offensively against programs that copy themselves
from location to location. The PCT instruction could cause holes in the resulting copy
and thus interfere with the enemy's execution.

## Second Article

## Early Project Notes

- Thinking about doing something with eBPF, but what?
    - More BPF LSM programs? (been there, done that --- but there is still a lot of low hanging fruit here, even from an adaptive security perspective)
    - Perf events? Could be some really cool opportunities for modeling system behavior here... This would certainly be uncharted  territory, but there could be overhead concerns depending on sampling frequency
    - Maybe some kind of network IDS that learns patterns in traffic? I have less experience here but it could be nice to try something different for a change
- So far I've just been working on some preliminary experiments/brainstorming with different BPF programs, hoping to see what sticks