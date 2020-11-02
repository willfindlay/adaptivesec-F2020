# Research Journal 13

William Findlay
Nov. 3rd 2020

## Trends in USENIX Security Papers: 2000, 2010, and 2020

### USENIX 2000

### USENIX 2010

### USENIX 2020

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