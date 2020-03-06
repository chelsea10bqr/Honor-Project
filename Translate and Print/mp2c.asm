.ORIG x3000   ;start at addrees x3000

      AND R1,R1,#0
      AND R2,R2,#0
      AND R3,R3,#0
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#5
      LD  R2,TABLESTART
INITIALIZE
      STR R3,R2,#0
      ADD R2,R2,#1
      ADD R1,R1,#-1
      BRp INITIALIZE
      AND R2,R2,#0
      LD  R2,EVENT
NEWEVENT
      ADD R3,R2,#0
CHECKNAME      
      ADD R2,R2,#1
      LDR R0,R2,#0
      BRp CHECKNAME
      ADD R2,R2,#1
      LDR R4,R2,#0
      ADD R2,R2,#1
      LDR R5,R2,#0
      ADD R6,R5,#-16
      BRzp ERROR_1
      ADD R6,R5,#0
      ADD R5,R5,R5
      ADD R5,R5,R5
      ADD R5,R6,R5
      AND R1,R4,#1
      BRz NEXT
      ADD R1,R5,#0
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0
      BRnp ERROR_2      
      STR R3,R6,#0
NEXT  
      AND R1,R4,#2
      BRz NEXT_1
      ADD R1,R5,#1
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0
      BRnp ERROR_2
      STR R3,R6,#0
NEXT_1
      AND R1,R4,#4
      BRz NEXT_2
      ADD R1,R5,#2
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0
      BRnp ERROR_2
      STR R3,R6,#0
NEXT_2
      AND R1,R4,#8
      BRz NEXT_3
      ADD R1,R5,#3
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0
      BRnp ERROR_2
      STR R3,R6,#0
NEXT_3
      AND R1,R4,#-16
      BRz COMPLETE
      ADD R1,R5,#4
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0
      BRnp ERROR_2
      STR R3,R6,#0
COMPLETE
      ADD R2,R2,#1
      LDR R6,R2,#0
      BRz DONE_1
      BRnzp NEWEVENT
DONE_1  
      LD R0,SPACE
      OUT
      OUT
      OUT
      OUT
      OUT
      OUT
      LD R0,VERTICAL
      OUT
      AND R1,R1,#0
	  LEA R1,MON
      JSR PRINT_CENTERED
      LD R0,VERTICAL
      OUT
      AND R1,R1,#0
      LEA R1,TUE
      JSR PRINT_CENTERED
      LD R0,VERTICAL
      OUT
      AND R1,R1,#0
      LEA R1,WED
      JSR PRINT_CENTERED
      LD R0,VERTICAL
      OUT
      AND R1,R1,#0
      LEA R1,THU
      JSR PRINT_CENTERED
      LD R0,VERTICAL
      OUT
      AND R1,R1,#0
      LEA R1,FRI
      JSR PRINT_CENTERED
      AND R2,R2,#0
      ADD R2,R2,#4
      AND R3,R3,#0
      ADD R3,R3,#15
      LD  R4,TABLESTART
      AND R6,R6,#0
OUTERLOOP
      LD R0,NEWLINE
      OUT
      ADD R1,R6,#0
      JSR PRINT_SLOT
INNERLOOP
      LD R0,VERTICAL
      OUT
      LDR R1,R4,#0
      BRz FREE
      JSR PRINT_CENTERED
      BRnzp LOOPD
FREE
      LEA R1,FREE_0  
      JSR PRINT_CENTERED
LOOPD ADD R4,R4,#1
      ADD R2,R2,#-1
      BRzp INNERLOOP
      ADD R6,R6,#1
      ADD R3,R3,#-1
      BRzp OUTERLOOP
      HALT
ERROR_1  .FILL x0000
ERROR_2  .FILL x0000
TABLESTART .FILL x4000
EVENT      .FILL x5000
VERTICAL   .FILL x007C
NEWLINE    .FILL x000A
FREE_0     .FILL x0000
MON        .FILL x004D
           .FILL x006F
           .FILL x006E
           .FILL x0000
TUE        .FILL x0054
           .FILL x0075
           .FILL x0065
           .FILL x0000
WED        .FILL x0057
           .FILL x0065
           .FILL x0064
           .FILL x0000
THU        .FILL x0054
           .FILL x0068
           .FILL x0075
           .FILL x0000
FRI        .FILL x0046
           .FILL x0072
           .FILL x0069
           .FILL x0000
PRINT_SLOT
    ST R7,SAVE_R7		; TRAP overwrites R7, so must save
	ST R6,SAVE_R6		; callee saves register values
	ST R1,SAVE_R1
    ST R0,SAVE_R0
    ADD R6,R1,#-2       ;Find if the first number is 0
    BRnz ZERO
    ADD R6,R6,#-10      ;Find if the first number is 1
    BRnz ONE
    LD R0,TWO           ;Print for the time between 20:00 to 22:00
    OUT
    ADD R6,R1,#15
    ADD R6,R6,#15
    ADD R6,R6,#5
    ADD R0,R6,#0
    OUT
    BRnzp DONE
ZERO                    ;Print for the time between 07:00 to 09:00
    LD R0,NUM_1
    OUT
    ADD R6,R1,#15
    ADD R6,R6,#15
    ADD R6,R6,#15
    ADD R6,R6,#10
    ADD R0,R6,#0
    OUT
    BRnzp DONE
ONE                     ;Print for the time between 10:00 to 19:00
    LD R0,NUM_2
    OUT
    ADD R6,R1,#15
    ADD R6,R6,#15
    ADD R6,R6,#15
    ADD R0,R6,#0
    OUT
DONE                ;Print for the rest ":00"
    LD R0,SYMBOL
    OUT
    LD R0,NUM_1
    OUT
    OUT
    LD R0,SPACE
    OUT
    LD R1,SAVE_R1		; restore register values for caller
	LD R6,SAVE_R6
	LD R7,SAVE_R7
    LD R0,SAVE_R0
    RET                 ;return
PRINT_CENTERED
    ST R7,SAVE_R7		
	ST R6,SAVE_R6		; callee saves register values
	ST R5,SAVE_R5 
    ST R4,SAVE_R4
    ST R3,SAVE_R3		
	ST R2,SAVE_R2		
	ST R1,SAVE_R1
    ST R0,SAVE_R0
    ADD R6,R1,#0    
    AND R3,R3,#0
    ADD R3,R3,#6        ; make a counter R3 to ignore more than 6 characters
LOOP                    ; Get the number of characters 
    LDR R0,R6,#0
    BRz FINISHED
    ADD R6,R6,#1
    ADD R3,R3,#-1       ; get the number of spaces
    BRp LOOP
FINISHED               
    ADD R4,R1,#0
    NOT R4,R4
    ADD R4,R4,#1
    ADD R4,R4,R6        ; Get the number of chars which will not exceed 6
    AND R5,R3,#1        ; Determine the number of spaces is odd or even by bitmask
    AND R2,R2,#0
    ADD R6,R3,#0
CONTINUE                ; Right shift the number of spaces
    ADD R6,R6,#-2
    BRn PRINT
    ADD R2,R2,#1        ; Get the number of leading space
    BRnzp CONTINUE
PRINT                   ; Print leading space
    ADD R6,R2,#0
PRINT_SPACE
    ADD R6,R6,#-1
    BRn PRINT_CHAR
    LD R0,SPACE
    OUT
    BRnzp PRINT_SPACE  
PRINT_CHAR               ; Print character
    LDR R0,R1,#0
    OUT
    ADD R1,R1,#1
    ADD R4,R4,#-1
    BRp PRINT_CHAR
TRAILING                ; Pring trailing space which is the same number of leading space
    ADD R2,R2,#-1
    BRn OVER
    LD R0,SPACE
    OUT
    BRnzp TRAILING
OVER                   ; If the number of spaces is odd, we need to add one more space in trailing space
    ADD R5,R5,#0
    BRz LOAD
    LD R0,SPACE
    OUT
LOAD
    LD R7,SAVE_R7		; restore register values for caller
	LD R6,SAVE_R6
	LD R5,SAVE_R5
    LD R4,SAVE_R4
    LD R3,SAVE_R3		
	LD R2,SAVE_R2
	LD R1,SAVE_R1
    LD R0,SAVE_R0
    RET                 ; return
TWO	    .FILL x0032		; ASCII value for '0, 1, 2, space and colon'
NUM_1	.FILL x0030
NUM_2	.FILL x0031
SYMBOL  .FILL x003A
SPACE   .FILL x0020
SAVE_R1 .FILL x0000    ; storage for saved register values
SAVE_R7 .FILL x0000
SAVE_R6 .FILL x0000
SAVE_R0 .FILL x0000
SAVE_R5  .FILL x0000
SAVE_R4  .FILL x0000
SAVE_R3  .FILL x0000
SAVE_R2  .FILL x0000



         .END



