# Research Journal 02: Tierra

William Findlay
Sept. 17, 2020

## Random Thoughts

- Tierra puts a **strong** emphasis on *environment*
- The entire point of the design of the Tierran virtual machine and language is to create an environment that is conducive to evolution
    - Because classic Von Neumann machine languages are not meant to be "evolvable"
    - Too brittle -> very hard to pick a working program out of a random permutation of machine code instructions
- For Tierran, creating an evolvable environment for programs requires:
    - Shrinking the instruction set (to mimic natural proteins and amino acids)
    - Addressing instructions by their "templates" rather than individually, to mimic complementarity (https://en.m.wikipedia.org/wiki/Complementarity_(molecular_biology)) in biology
- How does this relate to (adaptive) security?
    - "Changing the game" involves creating an environment in which it no longer pays dividends to be an attacker
    - Creating software that can evolve could help add diversity to the environment (reduces the impact of finding common exploits)
    - a Tierran-like substrate might be conducive to creating evolvable programs
- What remains to be seen: How viable would Tierran software be in the real world? I think not so much...
    - In production, we don't want our code to replicate itself and we don't want unexpected changes in our code to break behavior
    - We need something that can evolve *macroscopically* rather than at the per-instruction level
    - Further, we need something with a "replication" function we can control
- What if we could annotate different logical parts of our programs (maybe with machine learning?) like genome sequencing?
    - Then when we deploy applications we could shuffle the main logical parts by selecting equivalents from our gene bank
    - This would require a lot of interface work (equivalent logical parts would require equivalent interfaces)
    - Probably not feasible, but an interesting thought experiment
- Could also perhaps pre-configure a seed population of viable applications and use dependency graphs to drive viable evolution
    - This might be something interesting to try

## Tierra

## More Project Thoughts
