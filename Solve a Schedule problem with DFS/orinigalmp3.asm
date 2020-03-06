.ORIG x3000   ;start at addrees x3000
;write an LC-3 program that
;translates a student’s daily schedule from a list to a two-
;dimensional matrix of pointers
;for initialization part R1 as a counter(80),R2 be the address which starts at x4000
;R3 as 0 to initilize memory space, 
;for translation part, R3(to store the address of first lettr of event), R2 be the address which
;starts at x5000, R4(to store the value of days),R5( to store the value of time),R6 1.to store
;the original value in R5 in order to multiply by5. 2.work as the memory location 
;for printing part, R2 as a counter for innner loop(4), R3 as a counter for outer loop(15),
;R4 be the address which starts at x4000, R6 be the time value for time slot
;FOR MP3 INTRO PARAGRAPH!!!!!!!
;Given a list of extra events, each of which can
;occur at one or more hours, this program  uses a stack
;to perform a depth-first search (DFS) of possible time
;combinations until a compatible combination is discovered
;for first part(check times), R5 store the address of extra event, R6 as the pointer of the stack,
;and load the value in the R4, R3 to store the shift left value, R2 count the time value(also the shift_right times)
;R0 to store the value in R2 for later use
;for second part(check days, each register have similar function
;for third part(conflict and clear) R4 as a counter(set to 80) R3 as the address which starts at x4000
;R1 store the negative value of address
;for fourth part(shift left) R2( time value) R4(time bitvector) R3(leftover bitvector) R1(negative value of R3)
;FOR STACK STRUCTURE!!!!!
;Each extra event occupies one memory location in a stack, store the leftover time bitvector in a stack for push and pop 
      AND R1,R1,#0        ;Initialize Registers
      AND R2,R2,#0         
      AND R3,R3,#0
      ADD R1,R1,#15       ;make R1 as a counter(80),R2 be the address which starts at x4000
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#15
      ADD R1,R1,#5
      LD  R2,TABLESTART   ;make R2 be the address of x4000
INITIALIZE                ;initialize the value in address x4000 to x 404F
      STR R3,R2,#0
      ADD R2,R2,#1
      ADD R1,R1,#-1
      BRp INITIALIZE
      AND R2,R2,#0
      LD  R2,EVENT        ;make R2 be the address of x5000
NEWEVENT
      ADD R3,R2,#0        ;use R3 to store the first event address,use R4 to store the 
CHECKNAME      
      ADD R2,R2,#1        ;check whether get NULL in event list
      LDR R0,R2,#0        
      BRp CHECKNAME   
      ADD R2,R2,#1        ;when NULL is detected, add 1 in R2 to get the value of days
      LDR R4,R2,#0        
      ADD R2,R2,#1        ;add 2 in R2 to get the value of time
      LDR R5,R2,#0
      ADD R6,R5,#-16      ;if the time value bigger than 15, out of range
      BRzp ERROR_1
      ADD R6,R5,#0        ;multiply the value of time by 5
      ADD R5,R5,R5
      ADD R5,R5,R5
      ADD R5,R6,R5
      AND R1,R4,#1        ;determine whether the event is on MONDAY
      BRz NEXT
      ADD R1,R5,#0        ;On MONDAY, add 0 
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0        ;determine whether this memory location has time conflict
      BRnp ERROR_2      
      STR R3,R6,#0        ;store the first letter address in that memory location
NEXT  
      AND R1,R4,#2        ;determine whether the event is on TUESDAY
      BRz NEXT_1          
      ADD R1,R5,#1        ;On TUESDAY, add 1
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0        ;determine whether this memory location has time confilict
      BRnp ERROR_2
      STR R3,R6,#0        ;store the first letter address in that memory location
NEXT_1
      AND R1,R4,#4        ;determine whether the event is on WEDNESDAY
      BRz NEXT_2          
      ADD R1,R5,#2        ;On WEDNESDAY, add 2
      LD  R6,TABLESTART   
      ADD R6,R1,R6
      LDR R0,R6,#0        ;determine whether this memory location has time conflict
      BRnp ERROR_2
      STR R3,R6,#0        ;store the first letter address in that memory location
NEXT_2
      AND R1,R4,#8        ;determine whether the event is on THURSDAY
      BRz NEXT_3
      ADD R1,R5,#3        ;On THURSDAY, add 3
      LD  R6,TABLESTART
      ADD R6,R1,R6
      LDR R0,R6,#0        ;determine whether this memory location has time conflict
      BRnp ERROR_2
      STR R3,R6,#0        ;store the first letter address in that memory location
NEXT_3
      AND R1,R4,#-16      ;determine whether the event is on FRIDAY
      BRz COMPLETE 
      ADD R1,R5,#4        ;On FRIDAY, add 4
      LD  R6,TABLESTART
      ADD R6,R1,R6 
      LDR R0,R6,#0        ;determine whether this memory location has time conflict
      BRnp ERROR_2
      STR R3,R6,#0        ;store the first letter address in that memory location
COMPLETE
      ADD R2,R2,#1        ;determine whether the event list ends
      LDR R6,R2,#0
      BRz DONE_1
      BRnzp NEWEVENT
DONE_1  
    LD  R6,STACK_START
    LD  R5,EXTRA
NEXT_EVENT
    LDR R2,R5,#0
    BRz MP3_DONE      
    LDR R4,R5,#2           ;Load the time bitvector in R4
    AND R2,R2,#0           ;initialize R2
CHECK_TIMES
    ADD R0,R2,#0
    AND R3,R4,#1           ;use bitmask to find first 1 in time bitvector
    BRz BEGINSHIFT         
    AND R3,R3,#0           ;if we find, shift this bitverctor one more time
SHIFT_AGAIN                ;and store it in stack
    ADD R4,R4,#-2
    BRn DONE_AGAIN
    ADD R3,R3,#1
    BRnzp SHIFT_AGAIN
DONE_AGAIN
    STR R3,R6,#0           ;store the leftover bitvetor into stack and minus 1 to R6
    ADD R6,R6,#-1          ;to make R6 point the top of stack
    BRnzp CHECK_DAYS       ;Then move to check the event in which days
BEGINSHIFT
    AND R3,R3,#0
RIGHTSHIFT                 ;for shift right
    ADD R4,R4,#-2
    BRn SHIFT_DONE
    ADD R3,R3,#1
    BRnzp RIGHTSHIFT
SHIFT_DONE
    ADD R2,R2,#1
    ADD R4,R3,#0
    BRp CHECK_TIMES
CHECK_DAYS                ;Load the day bitvector into R4 
    LDR R4,R5,#1 
    AND R1,R1,#0          ;initialize R1
BEGIN
    AND R3,R4,#1          ;begin to shift right
    BRz BEGINSHIFT_1      ;if the rightmost bit is zero, go to shift right 
    ADD R0,R2,#0          ;muliply R2 by 5 and store the value of R2 in R0
    ADD R2,R2,R2
    ADD R2,R2,R2
    ADD R2,R2,R0
    ADD R2,R1,R2
    LD  R3,TABLESTART     ;LD the R3 be x4000
    ADD R2,R3,R2          ;get the memory location 
    LDR R3,R2,#0          ;check if there is any conflict
    BRnp CONFLICTED       ;if it is not zero, conflicted
    LDR R3,R5,#0          ;if not,store the address of this event in that memory location
    STR R3,R2,#0
BEGINSHIFT_1              ;shift right
    AND R3,R3,#0
SHIFTRIGHT_DAYS
    ADD R4,R4,#-2
    BRn DONE_DAYS
    ADD R3,R3,#1
    BRnzp SHIFTRIGHT_DAYS
DONE_DAYS
    ADD R1,R1,#1          ;make the R1 to be a counter of days
    ADD R2,R0,#0
    ADD R4,R3,#0
    BRnp BEGIN
    ADD R5,R5,#3          ;when day has been checked, add 3 to R5 to analyze next event
    BRnzp NEXT_EVENT
CONFLICTED	
    AND R4,R4,#0          ;initialize R4
    LDR R1,R5,#0          ;load the address of the string in R1	
    NOT R1,R1             ;flip the R1
    ADD R1,R1,#1          ;add 1 to R1 to make it negative
    ADD R4,R4,#15         ;add R4 to 80
    ADD R4,R4,R4
    ADD R4,R4,R4
    ADD R4,R4,#15
    ADD R4,R4,#5
    LD  R3,TABLESTART     ;load x4000 in R3
WRONG_EVENT_2
    LDR R2,R3,#0          ;load the value in R3 to R2
    ADD R2,R1,R2          ;add R2 and R1
    BRnp NEXTLOCATION_2   ;if it is zero, clear the value
    AND R2,R2,#0
    STR R2,R3,#0
NEXTLOCATION_2            ;if it is not zero, move to next location
    ADD R3,R3,#1
    ADD R4,R4,#-1
    BRp WRONG_EVENT_2     ;if R4 becomes zero, 'chenck' finished

    LDR R4,R6,#1          ;Load the previous leftover time bitvector
    ADD R2,R0,#1          ;Add 1 to the value in R0 and store in R2
    ADD R6,R6,#1          ;pop the stack
    ADD R4,R4,#0          ;if R4 =0 go to the previous event 
    BRnp CHECK_TIMES      
    ADD R5,R5,#-3         ;returen to te previous event and compute the time value          
    AND R2,R2,#0          ;initialize R2 as a counter 
    LDR R4,R5,#0          ;load the address of stringz
    BRz ERROR_3           ;if it is zero, so cannot fit the original schedule
    LDR R4,R5,#2          ;load the previous evnet's time bitvector
    LDR R3,R6,#1          ;load the previous event's leftover time bitvector
    ADD R2,R2,#-1         
SHIFT_LEFT
    ADD R3,R3,R3          ;shift left the leftover time bitvector
    NOT R1,R3             ;flip it
    ADD R1,R1,#1          ;add 1 to become negative
    ADD R2,R2,#1          ;add 1 to counter as the previous time value
    ADD R1,R1,R4          ;add them together, if it is negative,stop shift left
    BRzp SHIFT_LEFT       ;begin to check next times
    LDR R4,R6,#1
    ADD R4,R4,#0
    BRnp CHECK_TIMES
ERROR_3                   ;for printing error message
    LEA R0,ERROR3_3
    PUTS
    BRnzp FI
TABLESTART .FILL x4000
MP3_DONE
      LD R0,SPACE         ;print the first 6 spaces
      OUT
      OUT
      OUT
      OUT
      OUT
      OUT
      LD R0,VERTICAL      ;print Mon to Fri
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
      AND R3,R3,#0        ;use R3 as a counter for outerloop(15)
      ADD R3,R3,#15
      LD  R4,TABLESTART   ;make R4 be the address x4000
      AND R6,R6,#0        ;initialize R6 to work as time slot value
OUTERLOOP
      AND R2,R2,#0        ;use R2 as a counter for innerloop(4)
      ADD R2,R2,#4
      LD R0,NEWLINE       ;print newline
      OUT
      ADD R1,R6,#0        ;print time slot
      JSR PRINT_SLOT
INNERLOOP
      LD R0,VERTICAL      ;print vertical lines
      OUT
      LDR R1,R4,#0        ;get the value from R4 address
      BRz FREE            ;whether this memory location is free
      JSR PRINT_CENTERED  ;print the event
      BRnzp LOOPD
FREE                      ;if this memory location is free, print 6 spaces by PRINT_CENTERED
      LEA R1,FREE_0  
      JSR PRINT_CENTERED
LOOPD ADD R4,R4,#1        ;add 1 to address in R4 
      ADD R2,R2,#-1       ;decrease the counter for innerloop
      BRzp INNERLOOP      ;if it is negative go to next line
      ADD R6,R6,#1        ;add 1 to R6 to print next time slot
      ADD R3,R3,#-1       ;decrease the counter for outerloop
      BRzp OUTERLOOP      ;if it is negative, halt
      BRnzp FI
ERROR_1
      ADD R0,R3,#0
      PUTS
      LEA R0,ERROR1_1
      PUTS
      BRnzp FI 
ERROR_2
      ADD R0,R3,#0
      PUTS
      LEA R0,ERROR2_2
      PUTS
FI
      HALT
EVENT      .FILL x5000
STACK_START .FILL x8000
EXTRA       .FILL x6000
VERTICAL   .FILL x007C
NEWLINE    .FILL x000A
FREE_0     .FILL x0020
           .FILL x0000
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
ERROR3_3    .STRINGZ "Could not fit all events into schedule.\n"

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
ERROR1_1 .STRINGZ " has an invalid slot number.\n"
ERROR2_2 .STRINGZ " conflicts with an earlier event.\n"

         .END
