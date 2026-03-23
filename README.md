# mathparse

## Rules
The string can contain any element, it will parse only allowed characters (besides digits you can use chars from 'Symbols'). Firstly, it do the math in parenthesis, then square, pow, multiplication, division and at the end is sum.

## Symbols
* **\*** — multiplication
* **/** — division
* **^** — power
* **+** — addition
* **-** — subtract
* **v** — square root (kinda looking like √, but is easier to write)

## Issues
- This parser is unefficient because i'm shitty developer. It has a lot of duplication of code and maybe somewhere in future I will fix it

- If you want to do something like this *-2\*-5* you should do it like *(-2)\*(-5)*

- If you want to take a square root from a value, you would have to write a *v\<value\>* (where *v* is a root sign and *\<value\>* is a degree) after the value that you want to process, e.g. *4v2 = 2*, *(6+3)v2 = 3*. I know that it is bullshit.

- Right now you can write only integer values