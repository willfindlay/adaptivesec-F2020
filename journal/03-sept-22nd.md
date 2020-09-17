# Research Journal 03

William Findlay
Sept. 22, 2020

## Software Diversity: Security, Entropy and Game Theory

## Object-Level Recombination of Commodity Applications

## Really Cool Project Idea

- observe the system and automatically generate coarse grained rules that match observed patterns of behavior
- provide a mechanism for defining allow/deny operations on these coarse grained rules
- provide a mechanism for combining and editing these rules
- users can associate rules with specific programs, an eBPF enforcement engine would then enforce them
- users can mix and match and edit rules as they see fit
- rules would be optionally parameterized by their LSM object IDs (for example, you could parameterize a rule that contained an inode access by that inode or filesystem number, but you wouldn't necessarily have to do this)
- in addition to generating rules, you could also generate the policy that uses these rules and this generation could optionally either be parameterized or generic

I've created a git repository for this project: https://github.com/willfindlay/WARDEN
