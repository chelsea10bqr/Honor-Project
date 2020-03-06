    LD  R6,STACK_START
    LD  R5,EXTRA
NEXT_EVENT
    LDR R2,R5,#0
    BRz MP3_DONE      
    LDR R4,R5,#2           ;Load the time bitvector in R4
    AND R2,R2,#0           ;initialize R2
CHECK_TIMES
    AND R3,R4,#1           ;use bitmask to find first 1 in time bitvector
    BRz BEGINSHIFT         
    AND R3,R3,#0           ;if we find, shift this bitverctor one more time
SHIFT_AGAIN                ;and store it in stack
    ADD R4,R4,#-2
    BRn DONE_AGAIN
    ADD R3,R3,#1
    BRnzp SHIFT_AGAIN
DONE_AGAIN
    STR R3,R6,#0
    ADD R6,R6,#-1
    BRnzp CHECK_DAYS
BEGINSHIFT
    AND R3,R3,#0
RIGHTSHIFT
    ADD R4,R4,#-2
    BRn SHIFT_DONE
    ADD R3,R3,#1
    BRnzp RIGHTSHIFT
SHIFT_DONE
    ADD R2,R2,#1
    ADD R4,R3,#0
    BRp CHECK_TIMES
CHECK_DAYS
    LDR R4,R5,#1
    AND R1,R1,#0
BEGIN
    AND R3,R4,#1
    BRz BEGINSHIFT_1
    ADD R0,R2,#0
    ADD R2,R2,R2
    ADD R2,R2,R2
    ADD R2,R2,R0
    ADD R2,R1,R2
    LD  R3,TABLESTART
    ADD R2,R3,R2
    LDR R3,R2,#0
    BRnp CONFLICTED
    LDR R3,R5,#0
    STR R3,R2,#0
BEGINSHIFT_1
    AND R3,R3,#0
SHIFTRIGHT_DAYS
    ADD R4,R4,#-2
    BRn DONE_DAYS
    ADD R3,R3,#1
    BRnzp SHIFTRIGHT_DAYS
DONE_DAYS
    ADD R1,R1,#1
    ADD R2,R0,#0
    Add R4,R3,#0
    BRnp BEGIN
    ADD R5,R5,#3
    BRnzp NEXT_EVENT
CONFLICTED	
    LDR R4,R6,#1
    ADD R2,R0,#1
    ADD R6,R6,#1
    ADD R4,R4,#0
    BRnp CHECK_TIMES
    AND R4,R4,#0
    LDR R1,R5,#-3
    NOT R1,R1
    ADD R1,R1,#1
    ADD R4,R4,#15
    ADD R4,R4,R4
    ADD R4,R4,R4
    ADD R4,R4,#15
    ADD R4,R4,#5
    LD  R3,TABLESTART
WRONG_EVENT
    LDR R2,R3,#0
    ADD R1,R1,R2
    BRnp NEXTLOCATION
    AND R2,R2,#0
    STR R2,R3,#0
NEXTLOCATION
    ADD R3,R3,#1
    ADD R4,R4,#-1
    BRp WRONG_EVENT
    ADD R5,R5,#-3
    LDR R4,R6,#1
    ADD R2,R0,#1
    ADD R4,R4,#0
    BRnp CHECK_TIMES
    LEA R0,ERROR3_3
    PUTS
    BRnzp FI
