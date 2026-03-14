========================================================
 Custom Brainfuck Compiler Test Suite
========================================================

Setup Cell 0 to 10 for our multiplication loop
+++++ +++++
[
    > +++++ +       Add 6 to Cell 1
    > +             Add 1 to Cell 2 (We will use this for newlines later)
    << -            Decrement Cell 0
]
> +++++             Cell 1 is now 65 (ASCII A)

.                   Output A


> ++                Cell 2 currently has 10 Add 2 just to be safe if you changed it
                    Wait lets just make sure Cell 2 is exactly 10 (newline)
[-] +++++ +++++     Clear Cell 2 and set exactly to 10 (\n)
.                   Output newline
< '                 Go back to Cell 1 and output 65 as a number

Pointer Position
> .                 Go to Cell 2 and output newline
< ?                 Go to Cell 1 and output 1 (Cell 1s position)


We will save a macro to print ! (ASCII 33) and assign it to ID 5
> > > > +++++       Go to Cell 5 and set its value to 5
*[
    > +++++ +++++   Move to Cell 6
    +++++ +++++
    +++++ +++++
    +++             Cell 6 is now 33 (!)
    .               Print !
    [-]             Clear Cell 6 so it can be cleanly run multiple times
    <               Return to Cell 5
]

<<< . >>>           Go to Cell 2 print newline return to Cell 5
&                   Run Macro 5 (Prints !)
&                   Run Macro 5 (Prints !)


<<< . >>>           Go to Cell 2 print newline return to Cell 5
> "                 Move to Cell 6 and wait for user numeric input
<<<< . >>>>         Go to Cell 2 print newline return to Cell 6
'                   Print the users inputted number back to them

TEST: Character Input ()
<<<< . >>>>         Go to Cell 2 print newline return to Cell 6
> ,                 Move to Cell 7 and wait for user char input
<<<<< . >>>>>       Go to Cell 2 print newline return to Cell 7
.                   Print the users inputted char back to them


<<<<< .             Final newline to keep the terminal output clean!
