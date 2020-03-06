.ORIG x3000
; Add this test code to the start of your file (just after .ORIG).
; I'd put it in another file, but we can't use the PRINT_SLOT and 
; PRINT_CENTERED labels outside of the mp1.asm file (at least, not 
; easily).

; Read the comments in this file to understand what it's doing and
; for ways that you can use this test code.  You can also just run
; it and diff the output with the output produced by our 'gold'
; (bug-free!) version.
;
; After assembling mp1 with lc3as, execute the test script by typing
;    lc3sim -s script1 > your_output
; (look at the script--it just loads mp1 with a file command, then
; continues execution; when the LC-3 halts, the script is finished,
; so the simulator halts).
;
; You can then type
;    diff your_output out1
; to compare your code's output with ours.
;

	; feeling lazy, so I'm going to set all of the bits to the same value
	LD	R0,BITS
	ADD	R2,R0,#0
	ADD	R3,R0,#0
	ADD	R4,R0,#0
	ADD	R5,R0,#0
	ADD	R6,R0,#0

	; let's try PRINT_SLOT ... 11:00
	AND	R1,R1,#0
	LEA R1,STRING

	; set a breakpoint here in the debugger, then use 'next' to
	; execute your subroutine and see what happens to the registers;
	; they're not supposed to change (except for R7)...
	JSR	PRINT_CENTERED

	; we're short on human time to test your code, so we'll do 
	; something like the following instead (feel free to replicate)...
	LD	R7,BITS
	NOT	R7,R7
	ADD	R7,R7,#1
	ADD	R0,R0,R7
	BRz	R0_OK
	LEA	R0,R0_BAD
	PUTS
R0_OK	

	; this trap changes register values, so it's not sufficient
	; to check that all of the registers are unchanged; HALT may
	; also lead to confusion because the register values differ
	; for other reasons (R7 differences, for example).
	HALT

BITS	.FILL	xABCD	; something unusual
VLINE	.FILL	x7C	; ASCII vertical line character
R0_BAD	.STRINGZ "PRINT_SLOT changes R0!\n"

; your code should go here ... don't forget .ORIG and .END



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
STRING   .FILL x0000


.END

