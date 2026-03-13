++++++++ add 8 to cell 0
[ Start Loop
  >++++ Move up a cell and add 4
  [ Start Loop
    >++ Move up a cell and add 2
    >+++ Move up a cell and add 3
    >+++ Move up a cell and add 3
    >+ Move up a cell and add 1
    <<<<- Move back to cell 1 and subtrack 1
  ] End Loop when cell 1 = 0
  >+ Move up a cell and add 1
  >+ Move up a cell and add 1
  >- Move up a cell and subtrack 1
  >>+ Move up 2 cells 
  [ Start Loop
    < Move back a cell
  ] Stop Loop when when we get back to cell 1 which is already 0
  <- Move back a cell and subtrack 1
] Stop Loop when cell 0 = 0
>>.       H
>---.     e
+++++++.. ll
+++.      o
>>.    space
<-.       W
<.        o
+++.      r
------.   l
--------. d
>>+.      !
>++. newline
