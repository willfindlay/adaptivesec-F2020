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

Of course, it's not immediately clear what the best solution would be to fix
this problem. Primarily, the difficulty boils down to adoptability and backwards
compatibility of such a solution. In the Linux kernel, we adhere to a guiding
principle known as "Don't break Userland" which effectively stipulates that
changes to the kernel should not break existing userspace APIs. In web browsers
there exists much the same situation: changes to the browser should not break
the functionality of existing websites. Since many web applications have come to
rely on the overly permissive interactions between JavaScript code within the
sandbox of a webpage, it would be unacceptable to apply blanket changes that
reduce or eliminate these interactions altogether. Instead, a more tactful
approach would need to be taken. I suspect that the next paper will propose such
an approach, but it would be interesting to consider other possibilities as
well.

## Visual Security Policy for the Web

The idea of a web security policy based on the visual layout of a web page
intuitively makes **a lot** of sense. After all, the backbone of the web (HTML
and CSS) is written declaratively and is strongly connected to the visual
representation of the resulting webpage. By defining a security policy language
that works in a similar fashion to HTML and CSS, it is significantly more likely
that even novice users would be able to quickly familiarize themselves with the
technology.

What does concern me about this approach is its adoptability, given that it is
meant to be most useful to amateur web users. While it seems clear to me that
such users shouldn't have much difficulty using ViSP, it is unclear that they
would be motivated to do so, particularly as it is not a transparent solution.
Many casual users are altogether apathetic towards security, particularly if
they are not overly invested in the outcome. Such a user would need to be
convinced that securing the JavaScript on their webpage would be worthwhile.
Perhaps the best solution might be for companies like Google to distribute
built-in ViSP policies with their embed links. This would make the process far
more transparent for novice users, allowing them to confine external JavaScript
in much the same way that they included it in the first place: by copying and
pasting.

## Project Updates

- Been running a few simple BPF programs in the background to determine what sequences of LSM hooks are most common and whether there is a significant difference in sequence frequency
- So far, results seem quite promising -- A few sequences seem to dominate the others by a significant margin... Honing in on a magic number should hopefully allow weeding out the nonsense sequences from the important ones
- Since it will likely be important to consider variable length sequences, I'll probably need to develop a simple weighting system to compensate for difference in sequence length (which would almost certainly affect their frequency)
