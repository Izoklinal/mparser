# pathparse

## Rules
The string can contain any element, it will parse only allowed characters (besides digits you can use chars from 'Symbols'). Firstly, it do the math in parenthesis, then pow, multiplication, division and at the end is sum.

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