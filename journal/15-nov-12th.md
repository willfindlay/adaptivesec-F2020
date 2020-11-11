# Research Journal 15

William Findlay
Nov. 12th 2020

## Classification of Papers

I decided to classify 8 CCS papers from Wednesday the 11th. See Teams for details.

Overall it seems like like the classification went pretty smoothly. However, in
some cases, I felt like the criteria might be a bit too granular to make a truly
informed classification. I think it might be best to try and find a happy medium
between what we're doing this time around and what we tried last time.

## Project Updates

Still working on getting my implementation up and running. I've also started
writing some example capability manifests along with parsing and unit tests.
So far, I'm planning for these to be written in toml, and I have most of
the details worked out. Here's an example:

```toml
# Provide a friendly name and optional global attributes for the capbility
[capability]
name   = 'access_my_photos'
access = ['read', 'write']
# This means that allowed accesses should be audited
audit  = true

[[file]]
path = '/home/{user}/[Pp]ictures/**'
# We could also define per-file attributes here if we wanted to
# They would overwrite the global attributes

[[file]]
path = '/home/{user}/[Pp]hotos/**'
```

I still have a few design aspects that are unclear to me:

1. The best way to handle files / directories when translating the policy to be
   used by the BPF program. I really don't like the way I'm currently doing this
   in bpfbox , so it would be nice to experiment with alternatives here. Could
   make use of new kernel d_path helper.
2. How will users grant capabilities? File system extended attributes?
   A separate config file? In the capability file itself? Lots of choices here.
