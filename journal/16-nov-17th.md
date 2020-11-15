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
