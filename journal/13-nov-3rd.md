# Research Journal 13

William Findlay
Nov. 3rd 2020

## Trends in USENIX Security Papers: 2000, 2010, and 2020

### USENIX 2000

- I see only one obvious attack paper:
    - A Chosen Ciphertext Attack Against Several E-Mail Encryption Protocols
- Most other papers seem to be about providing tools to help defenders
    - And some of these are definitely what I would consider adaptive
- A couple interesting papers:
    - Automated Response Using System-Call Delays (The pH paper!)
    - MAPbox is a pretty interesting sandboxing paper, as it seems like they are the
      originators of a very common technique: confining applications using
      high-level descriptions of their behaviour
- Overall comments:
    - Papers seem to be quite well-written
    - Diagrams were quite common, charts were less common
    - About 40-50 references each

### USENIX 2010

- A couple of attack papers this time:
    - Acoustic Side-Channel Attacks on Printers
    - Security and Privacy Vulnerabilities of In-Car Wireless Networks: A Tire Pressure Monitoring System Case Study
- Still many good papers for defenders
- Overall comments:
    - Papers seem to be a bit shorter now, but not significantly
    - Diagrams are still quite common, seeing a few more charts
    - References were a mixed bag

### USENIX 2020

- Lots of attack papers now:
    - Breaking Secure Pairing of Bluetooth Low Energy Using Downgrade Attacks
    - Call Me Maybe: Eavesdropping Encrypted LTE Calls With ReVoLTE
    - Poison Over Troubled Forwarders: A Cache Poisoning Attack Targeting DNS Forwarding Devices
    - NXNSAttack: Recursive DNS Inefficiencies and Vulnerabilities
    - Cached and Confused: Web Cache Deception in the Wild
    - Stealthy Tracking of Autonomous Vehicles with Cache Side Channels
    - Plug-N-Pwned: Comprehensive Vulnerability Analysis of OBD-II Dongles as A New Over-the-Air Attack Surface in Automotive IoT
    - KOOBE: Towards Facilitating Exploit Generation of Kernel Out-Of-Bounds Write Vulnerabilities
    - Automatic Techniques to Systematically Discover New Heap Exploitation Primitives
    - Remote Side-Channel Attacks on Anonymous Transactions
    - And more...
- Not as many good papers for defenders
    - A lot of the proposed defences seem to be lower effort, less adaptive
- Overall comments:
    - A TON more papers than in 2000, 2010
    - Significantly more attack papers
    - Lots of diagrams and lots of charts
    - Seems like papers have gotten longer again? (19 pages seems to be the most common from what I've seen)
    - References are a mixed bag again --- some papers have lots (one had 119 references!), others not so much

### Overall Thoughts

- It seems like attack papers have grown much more common over time
- Something crazy happened to the submission rate between 2010 and 2020
    - There are so many accepted papers in 2020...
- It also seems like over time adaptive solutions have become less and less common
    - I started off seeing a couple in 2000 and 2010, and now I see basically none in 2020
- This trend might have to do with the "Least Publishable Unit" --- academics want to do the minimum amount of work required to get a publication
    - Attack papers are easier to write than ordinary defence papers which are easier to write than adaptive defence papers

## Project Thoughts / Updates

I'm thinking about using YAML as a policy language and possibly as the underlying language for expressing sequences.
Over the reading week, I started messing around with some possible formats, and came up with something like the following:

A system call sequence:

```yaml
name: run_program
description: |
    Allows a fork or clone followed by an execve or execveat.
arguments:
    - name: program
      type: glob
order: strict
sequence:
    - fork, vfork, clone
    - execve program, execveat program
```

An example profile for `ls` using that sequence:

```yaml
profile: /usr/bin/ls
description: |
    An example policy for the ls binary.
default: allow
allow:
audit:
deny:
    - run_program '*'
```

Still unsure what role automatic generation will play in all of this. I was
originally thinking the sequence files would be generated and modified by the
user. Could also bootstrap with some pre-configured defaults, such as the
run_program example above.
