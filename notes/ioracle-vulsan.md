# iOracle

The problem:

How it works:

Adaptive score:

# VulSAN

The problem:
    - to determine what vulnerabilities exist in hardened Linux systems
    - to compare the default policy of the two most popular Linux MAC frameworks
    - to provide defenders with an automatic means of auditing their security policy

How it works:
    - translate security policy and system state into prolog facts
    - encode various attack states (facts about attacker's privileges)
    - translate an attack scenario into a query
    - generate a graph or shortest attack paths to achieve the scenario

Adaptive score: 1.5
    - very similar technique to the iOracle paper
    - helps defenders by identifying weaknesses in the system configuration and
      security policy
    - not as helpful as iOracle because it does not provide recommendations on
      how to fix the vulnerability
    - limited to known attack scenarios that can be encoded as queries
    - also restricted to two MAC frameworks (SELinux and AppArmor)
