# Research Journal 02: Tierra

William Findlay
Sept. 17, 2020

## Tierra

Tierra makes a compelling argument about what it means to create artificial
life. In particular, it may be tempting to think about artificial life in terms
of how well it emulates the conditions of the natural world; the hypothesis of
Tierra is that this is a spurious line of reasoning. Instead, a sufficiently
configured virtual environment can offer amenable conditions for the simulation
of *other* kinds of life (quite unlike that which would be found in our world).
I think this is a very interesting approach as it attempts to solve a subtly yet
fundamentally different problem: What similarities and differences exist between
*other* forms of life and those that we see in nature?

It is interesting to see some of the direct comparisons between Tierra and other
projects like CoreWar, particularly in light of the hypothesis discussed above.
The point about CoreWar's deceptively large instruction set makes a lot of sense
to me (although there are only 10 basic instructions, each instruction takes
a set of arguments leading to exponential instructional complexity). While I was
initially surprised to learn that a large instruction set is *undesirable* for
emulating life, thinking back to some of my background knowledge (high school
biology), this does make sense; while there are only four nucleobases that make
up our genes, it is only when they are taken together that they produce
complicated strings of information. I found Tierra's approach for emulating
these properties exceedingly clever; when I first read about the idea of
template-based addressing, I immediately saw the parallel to molecular
biological interactions in the real world.

From a design perspective, Tierra is quite beautiful and I think it indeed
accomplishes the goals it set out to achieve (namely to establish a baseline for
comparison between life on Earth and life under other paradigms). However, it
remains for me to consider both its practicality (or lack thereof) for
real-world systems and its applicability to the domain of security (specifically
adaptive security). From a practicality standpoint, I don't think Tierra really
has much of a leg to stand on. I envision a few problems that would inhibit the
adoption of a Tierra-like system in any production environment. Firstly, its
instruction set would almost exclusively need to be virtualized without proper
hardware support in traditional Von Neumann architectures. Secondly, production
code (in general) is not *meant* to change over time, and certainly such changes
should not have any chance at breaking existing functionality or introducing
non-deterministic behavior. Further, we generally do not want code replication
itself uncontrollably in production environments --- even with the introduction
of a Reaper mechanism like in Tierra, the resource consumption of such a model
would be prohibitive.

While Tierra probably wouldn't be viable for use in production environments
(nor would I posit that it was intended to be, despite what the author might say in
his abstract), I think that we can certainly borrow some of its ideas and
possibly apply them in a more production-friendly manner. For instance, while
Tierra's evolution occurs on a microscopic (per-bit per-instruction) level, this
idea could be abstracted to the level of equivalent library dependencies for
example. I do foresee a few barriers to overcome before something like this
could be implemented; for example, interfaces across equivalent libraries would
need to be standardized to enable ad-hoc swapping across deployments. While this
is probably not a solvable problem, it makes for an interesting thought
experiment. By introducing polyculture into software deployments, we effectively
reduce the potential benefit for an attacker to find an exploit for one
particular configuration. This process could be automated through the use of
classifiers and dependency graphs.

## More Project Thoughts

## Random Thoughts

- Tierra puts a **strong** emphasis on *environment*
- The entire point of the design of the Tierran virtual machine and language is to create an environment that is conducive to evolution
    - Because classic Von Neumann machine languages are not meant to be "evolvable"
    - Too brittle -> very hard to pick a working program out of a random permutation of machine code instructions
- For Tierran, creating an evolvable environment for programs requires:
    - Shrinking the instruction set (to mimic natural proteins and amino acids)
    - Addressing instructions by their "templates" rather than individually, to mimic complementarity (https://en.m.wikipedia.org/wiki/Complementarity_(molecular_biology)) in biology
- 3 ingredients for adaptation:
    - sex, speciation, and death
    - Tierra doesn't really have the first, but does have the other two
    - The Reaper = death, population sizes ~ speciation
- How does this relate to (adaptive) security?
    - "Changing the game" involves creating an environment in which it no longer pays dividends to be an attacker
    - Creating software that can evolve could help add diversity to the environment (reduces the impact of finding common exploits)
    - A Tierran-like substrate might be conducive to creating evolvable programs
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
- Monoculture vs polyculture
    - Polyculture is bad for security on an individual level
    - But paradoxically it is better for security on the group level (attackers developing exploits need to be running 50 different versions of 50 different exploit software for example)
    - A lot of modern software seems to sit somewhere in the middle, but tending toward monoculture, at least across versions of popular libraries and open source projects
