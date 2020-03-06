/*									tab:8
 *
 * mp6.c - implementation file for ECE220 "Blocky" game
 *
 * "Copyright (c) 2017-2018 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    5
 * Creation Date:   7 November 2017
 * Filename:	    mp2.c
 * History:
 *	SL	1	7 November 2017
 *		First written.
 *      JXG     2	8 November 2017
 *		Added ncurses support.
 *	SL	3	30 November 2017
 *		Polished for MP distribution.
 *	SL	4	18 February 2018
 *		Edited slightly for ECE220H S18 distribution.
 *	SL	5	18 February 2018
 *		Stripped down from gold version.
 */


#include <stdint.h>
#include <stdio.h>

#include "mp6.h"


/*
 * The maximum number of blocks in one piece.  Do not change for
 * this assignment (you can do as you like with the code afterward).
 */
#define MAX_PIECE_SIZE 4

/*
 * Pieces are defined by an array of offsets from the center point.
 * Each piece consists of a set of adjacent blocks that together form
 * the piece.  The first index of the array is the piece type, the
 * second is the orientation (0-3), the third is block index within
 * the piece (0 to MAX_PIECE_SIZE - 1), and the fourth gives the
 * x (0) and y (1) offsets of the block relative to the center point.
 * Note that the first block is always the center point of the piece.
 *
 * Offsets may be replicated if a piece contains fewer than MAX_PIECE_SIZE
 * blocks.
 *
 * Clockwise rotation changes the orientation in the positive (mod 4)
 * direction, and counter-clockwise rotation changes the orientation in
 * the negative (mod 4) direction.
 */




 /* INTRODUCTORY PARAGRAPH !!!!!!!!!
  implement a game of
falling blocks by writting 11 functions such as move left right and rorate.
ubesides, sing multi-dimensional arrayso represent information in C
*/

static const int32_t piece_def[NUM_PIECE_TYPES][4][MAX_PIECE_SIZE][2] = {
    {   /* PIECE_TYPE_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0,  1}},
	{{0, 0}, { 0,  1}, { 0,  2}, {-1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0, -1}},
	{{0, 0}, { 0, -1}, { 0, -2}, { 1,  0}}
    },
    {   /* PIECE_TYPE_REV_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0, -1}},
	{{0, 0}, { 0,  1}, { 0,  2}, { 1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0,  1}},
	{{0, 0}, { 0, -1}, { 0, -2}, {-1,  0}}
    },
    {   /* PIECE_TYPE_LINE */
	{{0, 0}, {-1,  0}, { 1,  0}, { 2,  0}},
	{{0, 0}, { 0, -1}, { 0,  1}, { 0,  2}},
	{{0, 0}, { 1,  0}, {-1,  0}, {-2,  0}},
	{{0, 0}, { 0,  1}, { 0, -1}, { 0, -2}}
    },
    {   /* PIECE_TYPE_TEE */
	{{0, 0}, {-1,  0}, { 0, -1}, { 1,  0}},
	{{0, 0}, { 0, -1}, { 1,  0}, { 0,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  0}},
	{{0, 0}, { 0,  1}, {-1,  0}, { 0, -1}}
    },
    {   /* PIECE_TYPE_ESS */
	{{0, 0}, { 0, -1}, { 1,  0}, { 1,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  1}},
	{{0, 0}, { 0,  1}, {-1,  0}, {-1, -1}},
	{{0, 0}, {-1,  0}, { 0, -1}, { 1, -1}}
    },
    {   /* PIECE_TYPE_REV_ESS */
	{{0, 0}, { 0, -1}, {-1,  0}, {-1,  1}},
	{{0, 0}, { 1,  0}, { 0, -1}, {-1, -1}},
	{{0, 0}, { 0,  1}, { 1,  0}, { 1, -1}},
	{{0, 0}, {-1,  0}, { 0,  1}, { 1,  1}}
    }
};


/*
 * empty_board -- fills a board b with empty spaces (SPACE_EMPTY)
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, filled with empty spaces
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
int32_t
empty_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
   int32_t i,j;
   int z = 0  ;                                   /* declare parameters*/
   for(i = 0; i<BOARD_HEIGHT; i++)                    /*use two for loops to make the board filed with SPACE_EMPTY*/
   {                                                /*make the z as return value*/
     for (j = 0; j < BOARD_WIDTH; j++) {
       b[i][j] = SPACE_EMPTY;
     }
     z = 1;
   }
    return z;
}


/*
 * mark_piece -- forcibly writes a piece into a board, ignoring the
 *               board's current contents; you will need to understand
 *               the piece definition array (piece_def) in order to
 *               implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 *         v -- type of space to write (in the shape of the piece)
 * OUTPUTS: b -- the board, with the piece filled in with value v
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
mark_piece (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
            piece_type_t p, int32_t orient, int32_t x, int32_t y,
	    space_type_t v)
{
  int32_t i, W, H;
    for (i = 0; i < MAX_PIECE_SIZE; i++) {         /*transfer the v value to every piece for printing*/
      W = x + piece_def[p][orient][i][0];
      H = y + piece_def[p][orient][i][1];
     b[H][W] = v;

}
}

/*
 * test_piece_fit -- checks whether a piece fits into a board; you will
 *		     need to understand the piece definition array
 *		     (piece_def) in order to implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 * OUTPUTS: none
 * RETURN VALUE: if the piece does not fit within the board, returns
 *		 FIT_OUT_OF_BOARD; otherwise, if the piece would overwrite
 *		 non-empty board spaces, returns FIT_NO_ROOM_THERE;
 *		 otherwise, returns FIT_SUCCESS
 * SIDE EFFECTS: none
 */
fit_result_t
test_piece_fit (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
    int32_t i, W, H;
    for (i = 0; i < MAX_PIECE_SIZE; i++) {                   /* test the piece; whether it is out of the regions*/
      W = x + piece_def[p][orient][i][0];                    /*whether there are rooms under piece*/
      H = y + piece_def[p][orient][i][1];                     /*for different conditions, return different values*/
      if (W < 0 || W > BOARD_WIDTH-1|| H < 0 || H > BOARD_HEIGHT-1) {
        return FIT_OUT_OF_BOARD;
      }
      if(b[H][W]!= SPACE_EMPTY){
        return FIT_NO_ROOM_THERE;
      }

    }

    return FIT_SUCCESS;
}


/*
 * print_board -- prints a board to the screen using period ('.') to
 *		  represent empty spaces, percent ('%') to represent
 *		  old blocks, and asterisk ('*') to represent the current
 *		  piece (SPACE_BLOCK); see specification for example
 * 		  of board appearance
 * INPUTS: b -- the board
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: prints to the monitor
 */
void
print_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{ int32_t i,j;
   for(i = 0; i<BOARD_HEIGHT; i++)                  /*use two for loops to get every element in 2d arrays */
   {                                               /*determine what value it stored and print symbol*/
     for (j = 0; j < BOARD_WIDTH; j++) {
      if (b[i][j] == SPACE_EMPTY) {
        printf(".");
      }
      if (b[i][j] == SPACE_FULL) {
        printf("%%");
      }
      if (b[i][j] == SPACE_BLOCK) {
        printf("*" );
      }
      if (j==BOARD_WIDTH-1) {                     /*for the last colomn, print a new line*/
        printf("\n" );
      }
     }
   }

}



 /* try_to_move_down -- tries to move the current piece down one space in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved down (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_down (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  remove_piece(b,p, orient, x, y);
if(test_piece_fit(b,p,orient,x,y+1)== FIT_SUCCESS )             /*first remove the old one and test wheteher the new one fit the conditions*/
{                                                               /*if fitting, add the new one piece, if not add the old one back*/
add_piece(b,p, orient, x, y+1);
return 1;
}

add_piece(b,p,orient,x,y);


 return 0;
}


/*
 * try_to_move_left -- tries to move the current piece one space left in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved left (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_left (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{

  remove_piece(b,p, orient, x, y);                        /*first remove the old one and test wheteher the new one fit the conditions*/
if(test_piece_fit(b,p,orient,x-1,y)== FIT_SUCCESS )       /*if fitting, add the new one piece, if not add the old one back*/
{
add_piece(b,p, orient, x-1, y);
return 1;
}

add_piece(b,p,orient,x,y);


   return 0;
}



/*
 * try_to_move_right -- tries to move the current piece one space right in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved right (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_right (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                   piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  remove_piece(b,p, orient, x, y);                          /*first remove the old one and test wheteher the new one fit the conditions*/
if(test_piece_fit(b,p,orient,x+1,y)== FIT_SUCCESS )      /*if fitting, add the new one piece, if not add the old one back*/
{
  add_piece(b,p, orient, x+1, y);
return 1;
}

add_piece(b,p,orient,x,y);


   return 0;
}



/*
 * try_to_rotate_clockwise --
 *	tries to rotate the current piece clockwise in the board; assumes
 *	that the piece is in the board and must thus be removed before it
 *	can be put into its new position (or back into its old position on
 *	failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated clockwise (on success),
 *		 or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_rotate_clockwise (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                         piece_type_t p, int32_t orient, int32_t x, int32_t y)
{  int32_t next;
    if (orient == 3) {                      /*if orient equals 3 the next orientation for clockwise is 0*/
      next = 0;
    }else{
      next = orient+1;                     /*add 1 to orient for the next piece orientation*/
    }

    remove_piece(b,p, orient, x, y);               /*first remove the old one and test wheteher the new one fit the conditions*/
    if(test_piece_fit(b,p,next,x,y)== FIT_SUCCESS )   /*if fitting, add the new one piece, if not add the old one back*/
    {
      add_piece(b,p, next, x, y);
    return 1;
  }

    add_piece(b,p,orient,x,y);

     return 0;




}


/*
 * try_to_rotate_cc --
 *	tries to rotate the current piece counter-clockwise in the board;
 *	assumes that the piece is in the board and must thus be removed
 *	before it can be put into its new position (or back into its old
 *	position on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated counter-clockwise (on
 *		 success), or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_rotate_cc (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  int32_t next;
    if (orient == 0) {                      /*if orient equals 0 the next orientation for clockwise is 3*/
      next = 3;
    }else{
      next = orient-1;                       /*minus 1 to orient for the next piece orientation*/
    }

    remove_piece(b,p, orient, x, y);              /*first remove the old one and test wheteher the new one fit the conditions*/
    if(test_piece_fit(b,p,next,x,y)== FIT_SUCCESS )      /*if fitting, add the new one piece, if not add the old one back*/
    {
      add_piece(b,p, next, x, y);
    return 1;
  }

    add_piece(b,p,orient,x,y);

     return 0;

}


/*
 * remove_row -- removes a single row from a board, moving rows above
 *		 it downward and adding a new empty row at the top of
 *		 the board; this function should be called by your
 *		 remove_full_rows function
 * INPUTS: b -- the board
 *	   row -- which row to remove
 * OUTPUTS: b -- the board, with the specified row removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
remove_row (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], int row)
{
  int i,j;
  for (i = row; i > 0; i--)                      /*use two for loops, the first one decrease from int row to get the previous row*/
   {
  for (j = 0; j < BOARD_WIDTH; j++)               /*this loop is to go over the whole row and copy the previous row*/
  {
    b[i][j] = b[i-1][j];
  }
 }

}



/*
 * remove_full_rows -- removes all rows filled with SPACE_FULL from a
 * 		       board, moving rows above them downward and adding
 *		       new empty rows at the top of the board
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, with full rows removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
remove_full_rows (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i,j;
  for(i = 0; i < BOARD_HEIGHT; i++)                 /*check each row whether it contains all SPACE_FULL*/
  {
    int result = 1;
    for (j= 0; j< BOARD_WIDTH; j++) {              /*IF  we find and values which is not equal SPACE_FULL, make the result be 0, and move to next row*/
      if (b[i][j]!= SPACE_FULL) {
        result = 0 ;
      }
  }
   if (result == 1) {

    remove_row(b, i);                               /*call remove function to remove this full row*/
  }

}




}
