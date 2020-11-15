# Research Journal 16

William Findlay
Nov. 17th 2020

## Classification of Papers

See my spreadsheet on Teams.

## Web Scraper

The webscraper is done. See https://github.com/willfindlay/ConDense

What we have:

* We have a scraper
* We have a wrangler that turns it into the spreadsheet we want
    * Including author count

What's next:

* Calculate useful stats (like what?)
    * Author count
    * Reference count
    * Area/Classification?
* Charts!
    * Author count by conference year
    * Reference count by conference by year
    * Classification ratios (Attack:Defense, etc.) by conference by year
    * Area by conference by year? (maybe)
    * etc.

## Thoughts on the Readings

### Establishing a Baseline for Measuring Advancement in theScience of Security – an Analysis of the 2015 IEEESecurity & Privacy Proceedings

The focus here is on the quality of scientific reporting in security papers.

* Not so much attack vs defense
* Rather, do they present:
    * Research objectives?
    * Limitations?
    * Threats to validity?
    * Etc.

In theory, it would be nice to move towards higher quality scientific reporting
in security. But this doesn't really solve the problem of increasingly
irrelevant and impractical security literature in academia.

However, we can certainly borrow some of the ideas here (e.g. how the
paper is structured, the types of research questions, etc.).

"Five of the authors developed and evolved a rubric of indicators of scientific research based upon the literature."

* This sounds similar to the rubric we have been discussing in class
* But it seems to be much finer-grained
    * (probably closer to what we initially discussed than where we ended up)

"Six other authors applied this rubric to evaluate the 55 papers in the 2015
IEEE Security and Privacy conference proceedings."

* It seems that the scope of their study is also much narrower than our own

"Because of the opportunistic nature of much of the current security research..."

* I think this hits the nail on the head
* A new attack comes up, and everyone piles on

"In security science, as an applied discipline, in addition to providing
scientific knowledge, theories should also be  useful to practitioners to
support decision-making."

* Now they are approaching our thesis: Security research needs to matter in practice.
* I would argue that this extends beyond theory and into the realm of practicality
* Current research trends are far too narrow and tend not to focus on the problems that really matter
    * Anil's analogy: It's like fixing a tiny leak in the roof instead of the water gushing in right next to you

Would be useful to check out references [21, 10, 11] as they refer to studies that
"provide classifications of the type of research reports [...] published".

Section 3.1 seems useful to compare with our classification categories. I also
like the idea of using concise labels like AL, M, L instead of spelling out each
category. It's also interesting that their model supports multiple
classifications per paper. I think something like this _might_ be beneficial for
our study as well.

As an aside, I think that this paper will be useful to refer back to when I am
conducting and writing up my own future research. They have a lot of solid ideas
on how security research papers should be structured and written that I think
can help make my own work more rigorous.

### Characterizing Scientific Reporting in Security Literature:An analysis of ACM CCS and IEEE S&P Papers

A criterion given here that would be nice to include in our analysis:

* "Does the paper include an artifact?" -- A nice binary question with implications for practicality

## Project Updates

Now working on eBPF containers, tentatively calling the project "cell".

How it works:

* Write a high-level policy file for your container
* Each "app" has "rights" and "restrictions"
* Policy is default-deny
* Rights grant access (can be coarse-grained or fine-grained)
* Restrictions work like a "super-deny". They revoke rights and can be coarse-grained or fine-grained
    * For example, I could give a program the "access /home" right but revoke the "access /home/photos" right

An example:

```yaml
# my_container.yml

apps:
  - /bin/myapp1
    rights:
      - ipc /bin/myapp2
      - access /home
      - network
    restrictions:
      - access /home/photos
  - /bin/myapp2
    rights:
      - ipc /bin/myapp1
      - execute /bin/myapp3
  - /bin/myapp3
```
