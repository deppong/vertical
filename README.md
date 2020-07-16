# Vertical, an Esolang made to suck.
### Made up of vertical characters, Vertical is a stack based language that has a single stack and a single register
The project comes with 3 files:
* helloworld.vrt
* hwoneliner.vrt (hello world written on one line)
* cat.vrt (prints input directly to output)

It allows for the following inputs and ignores all other characters (including spaces, newlines and tabs).
```
l - push register to stack
I - pop from stack
1 - increment register
| - decrement register
) - reset register
[ - increment top value of stack
] - decrement top value of stack
T - swap the top 2 items on the stack
/ - start loop
\ - jump to corresponding loop start while the value at the top of the stack is not zero
! - print the top value of the stack
( - write input of one char to the register
```

## How does the helloworld.vrt actually work?
The general idea behind it is that adds values to the register that equal the characters desired from the [ascii table](http://www.asciitable.com/) and pushes the to a stack and then resets the register, but with a lot of characters (like e, l, o, and r) they are so close that you don't really need to loop to their corresponding value and can just as easily increment or decrement the register.

#### note: these comments are not found in the actual file, and it would not compile properly due to lowercase ls, and parentheses in the comments!
```
11111 11111l)                   increment register up to 10 (ascii for newline) then push it to the stack and clear register
1111 1111l)                     set a counter value of 8 to the stack and clear register
/                               start a loop
    1111                        increment the register by 4
    ]                           decrement the top value of the stack (which is our counter value)
\                               jump back to the start of our loop until the top value of the stack is 0
1l)TI                           add 1 to the register (8 * 4 = 32) so it is 33 (ascii for exclamation point) then swap the 33 on the stack
                                with our counter value and pop it 
                                ---- This is the general idea of the loops! ----
11111 11111l)                   counter value of 10
/
    11111 11111                 10 * 10
    ]
\
lTI                             add 100 (d) to stack, swap it, and pop it!
1111 1111l                      add 108 (l) to stack
111 111l                        add 114 (r) to stack 
|||l                            decrement 114 to 111 (o) and push to stack
||||||||||||||||||||||||l)      decrement to 87 (W) and push to stack, then clear register
1111 1111l)                     set counter to 8 
/
    1111                        4 * 8
    ]
\
l)TI                            32 (space) push to stack
11111 11111l)                   set counter to 10
/
    11111 11111                 10 * 10
    ]
\
11111111111lTI                  push 111 (o) to stack
|||ll                           push 108 (l) to stack twice
|||||||l                        push 101 (e) to stack
|||||||||||||||||||||||||||||l) push  72 (H) to stack and clear register

!I!I!I!I!I!I!I!I!I!I!I!I!       print and pop the stack 13 times (!dlroW olleH)
```
## Other
(Esolang wiki page)[esolangs.org/wiki/Vertical]
