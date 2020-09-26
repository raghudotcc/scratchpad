---
title: Potential outcomes, Counterfactuals, and their Links

tags: Causality
type: Shortform
status: Ongoing
---

## You are inside my drafts. Please wait until I post this publicly.
### This posts needs further editing and information

We will describe and define **_potential outcomes_,** and we will also define **_counterfactuals_**. These are probably the most important thing in the field, and we will keep coming back to them every now and then to extend our understanding to other topics in causal inference as they form the basis of many other topics.

### Treatment and Outcomes

When we think about causal effects, what we are really thinking about is what are the outcomes pertaining to a treatment. There are a lot of names for treatment. Sometimes treatments are also called exposure as in something that you are exposed to, which can affect the outcome.

Suppose we are interested in the causal effect of some treatment A on some outcome Y. **Most of the time** in our essay we will only be looking at binary treatment paths and binary outcome, but in reality it can be non-binary too.

Treatment examples:

-   A = 1 if receive influenza vaccine; A = 0 otherwise.
-   A = 1 if take statins; A = 0 otherwise.

Outcome examples:

-   Y = 1 if develop cardiovascular disease within 2 years;
-   Y = 0 otherwise Y = time until death [an example of non-binary outcome i.e., time]

The reason we assign numeric value is when we analyse the treatments or outcomes, we need something that is computable in nature. You could also think real drug vs placebo, exposed vs unexposed, etc. But the field is really more complicated, as in there could be levels of exposure or a patient could be on multiple medications etc.

### Potential Outcomes

In the above paragraph, what we saw in the form of Y is called as observed outcome but potential outcomes are something that we would see under each possible treatment.

**Notation:** Ya is the outcome that would be observed if treatment was set to A = a. Note the superscript, It is to denote potential outcomes. So, in the previous case, the potential case before observing could have been Y0 and Y1.

Example 1: Suppose treatment is influenza vaccine and the outcome is the time until the individual gets the flu.

Y1: time until the individual would get the flu if they received the flu vaccine

Y0: time until the individual would get the flu if they did not receive the flu vaccine

Example 2: Suppose the treatment is regional (A=1) versus general (A=0) anesthesia for hip fracture surgery. The outcome (Y) is major pulmonary complications.

Y1: equal to 1 if major pulmonary complications and equal to 0 otherwise, if given regional anesthesia

Y0: equal to 1 if major pulmonary complications and equal to 0 otherwise, if given general anesthesia

### Counterfactuals

Counterfactual outcomes are the outcomes that would have been observed, had the treatment been different.

Sometimes counterfactuals and potential outcomes could be used interchangeably but we will see that there are some differences. In this case, what we see is that the data has already been collected, outcome has already been observed, but we try to hypothesis what could have happened in some alternative scenario.

For example:

-   If my treatment was A=1, then my counterfactual outcome would be Y0
-   If my treatment was A=0, then my counterfactual outcome would be Y1

Let us understand this by using a real life example of influenza vaccine.

Did influenza vaccine prevent me from getting the flu?

Notice that in wording that we are already implying that the vaccine has already been given.

**What actually happened:**

-   You got the vaccine and did not get sick.
-   Your actual exposure was A=1 (meaning, you got the vaccine)
-   The observed outcome was Y= Y1

**What would have happened(contrary to fact):**

-   Had you not gotten the vaccine, would you have gotten sick?
-   Your counterfactual exposure is A=0
-   The counterfactual outcome is Y0


## TBD

***Next:*** [[DAGs and Causality]]