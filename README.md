# API-Project-2020
Algorithms and principles of computer science final project:
it is the implemetation of a text editor, the possible actions are modify, delete,  print, undo and redo.

Example of actions:

(ind1,ind2)c: change the text of the rows between ind1 and ind2;

(ind1,ind2)d: delete the rows between ind1 and ind2;

(ind1,ind2)p: print the rows between ind1 and ind2;

(number)u: undo "number" actions (c or d);

(number)r: redo "number" action that have previously been undone;

q: signal of termination;

# Example
1,2c \n
fist row
second row
.
2,3c
new second row
third row
.
1,3p
1,1c
new first row
.
1,2p
2,2d
4,5p
1,3p
4,5d
1,4p
3u
1,6p
1r
1,3p
q

It gives this as output:
first row
new second row
third row
new first row
new second row
.
.
new first row
third row
.
new first row
third row
.
.
first row
new second row
third row
.
.
.
new first row
new second row
third row