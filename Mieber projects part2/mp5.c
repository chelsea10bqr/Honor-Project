/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
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
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp5.h
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */




 /*introductroy paragraph!!!
  *this program contains a selection of functions that act as simple drawing tools to create a PNG
  *image. functions that can draw lines, rectangles, triangles, parallelograms, and
  *circles, as well as a color gradient in a rectangular shape



 */
#include "mp5.h"

/*
	You must write all your code only in this file, for all the functions!
*/



/*
 *  near_horizontal
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int Z = 1;                               /*initialize the return value*/
	int32_t bound = 1;
	if (x_end-x_start==0) {
		return 0;
	}               /*initialize the return value*/
	if ((((y_end-y_start)/(x_end-x_start))<-1 )|| (((y_end-y_start)/(x_end-x_start))>1)) {   /*check the slope*/
	return 0;
	}
	if ((x_start == x_end) &&(y_start == y_end)) {     /*if two points are the same just draw a dot*/
		 Z = Z & draw_dot(x_start, y_start);           /*Z and the return value of draw_dot*/
		 	return Z;
	}
		 int32_t x = x_end;
		 int32_t y = y_end;
		 if (x_start > x_end) {         /*if the x_start> x_end*/
			x_end = x_start;             /*exchange the start point and end point*/
			x_start = x;
			y_end = y_start;
			y_start = y;

		 }
		 for(x = x_start; x <= x_end; x++) {     /*use for loop to determine draw the line */
			y = ((2*(y_end-y_start)*(x-x_start)+1)/(2*(x_end-x_start)))+y_start;
		 bound = bound & draw_dot(x,y);

	 }
	return bound;
}


/*
 *  near_vertical
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	int Z = 1;                                        /*the idea for near_vertical is similar to near_horizontal*/
	int32_t bound = 1;
	if ((x_end-x_start)!= 0) {

	if ((((y_end-y_start)/(x_end-x_start)) >= -1 )&& (((y_end-y_start)/(x_end-x_start))<=1)) {  /*check the slope*/
	return 0;
}
}

	if ((x_start == x_end) && (y_start == y_end)) {
		 Z = Z & draw_dot(x_start, y_start);
		 	return Z;
	}
		 int32_t x = x_end;
		 int32_t y = y_end;
		 if (y_start > y_end) {
			x_end = x_start;
			x_start = x;
			y_end = y_start;
			y_start = y;

		 }
		 for(y = y_start; y <= y_end; y++) {
			x = ((2*(x_end-x_start)*(y-y_start)+1)/(2*(y_end-y_start)))+x_start;
		 bound = bound & draw_dot(x,y);
	 }
	return bound;



}

/*
 *  draw_line
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
    int Z = 1;
		if (x_start == x_end) {                          /*if x_start = x_end, which means it is a vertical line(avoid denominator = 0)*/
    Z = Z &	near_vertical(x_start, y_start, x_end, y_end);
    return Z;
		}

		int slope = (y_end-y_start)/(x_end-x_start);  /*calculate the slope*/
		if (slope < -1 || slope > 1) {            /* if slope < -1 or > 1 use vertical*/
			Z = Z & near_vertical(x_start, y_start, x_end, y_end);
			return Z;
				}
		Z = Z & near_horizontal(x_start, y_start, x_end, y_end);   /*other conditions use horizontal*/
		return Z;
}


/*
 *  draw_rect
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	if (w < 0 || h < 0) {                    /*width or height smaller than 0, return 0*/
		return 0;
	}
  int32_t x_1 = x + w;                    /*the right edge of x*/
	int32_t y_2 = y + h;                   /*the bottom edge of y*/
	int Z = 1;                               /*call function draw_line  and AND all the return value of draw_line*/
	Z = Z & draw_line(x, y, x_1, y);
	Z = Z & draw_line(x, y, x, y_2);
	Z = Z & draw_line(x, y_2, x_1, y_2);
	Z = Z & draw_line(x_1, y, x_1, y_2);
	return Z;

}


/*
 *  draw_triangle
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	int Z = 1;                                      /*call function draw_line  and AND all the return value of draw_line*/
	Z = Z & draw_line(x_A, y_A, x_B, y_B);
	Z = Z & draw_line(x_A, y_A, x_C, y_C);
	Z = Z & draw_line(x_B, y_B, x_C, y_C);



	return Z;
}

/*
 *  draw_parallelogram
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	int32_t x_D;
	int32_t y_D;
	int Z = 1;       /*find the posiontion of point D*/
	x_D = x_A + (x_C - x_B);
	y_D = y_A + (y_C - y_B);
	Z = Z & draw_line(x_A, y_A, x_B, y_B);     /*call function draw_line  and AND all the return value of draw_line*/
  Z = Z & draw_line(x_A, y_A, x_D, y_D);
	Z = Z & draw_line(x_D, y_D, x_C, y_C);
	Z = Z & draw_line(x_B, y_B, x_C, y_C);
  return Z;

}


/*
 *  draw_circle
 *
 *
 *
 *
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
  int Z = 1;
	if(inner_r < 0 || outer_r < inner_r){     /*check the conditions for radius*/
		return 0;
	}
  int32_t x_1 = x - outer_r;              /*using a square for for loops to draw dot*/
	int32_t y_1 = y - outer_r;
	int32_t x_2 = x + outer_r;
	int32_t y_2 = y + outer_r;
	int32_t i;
	int32_t j;
	for ( i = y_1; i <= y_2; i++) {
		for( j = x_1; j <= x_2; j++){
			int32_t distance = (j-x)*(j-x)+(i-y)*(i-y);      /*check whether this pixel is in the range*/
			if ((distance <= outer_r*outer_r) && ( distance >= inner_r*inner_r)) {
				Z = Z & draw_dot(j,i);
			}
		}
	}
	return Z;
}


/*
 *  rect_gradient
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
  int Z = 1;
	if( w < 0 || h < 0){                  /*if width or height smaller than 0, return 0*/
		return 0;
	}
	int32_t x_1 = x + w;                 /*get the edge value*/
	int32_t y_1 = y + h;
	int32_t i;
	int32_t j;
	for ( i = x; i <= x_1; i++) {
		for (j = y; j <= y_1; j++) {
		  int32_t bitmask = 0xFF;                /*create bitmask for 3 byte (parts)*/
			int32_t bitmask_1 = 0xFF00;
			int32_t bitmask_2 = 0xFF0000;
			int32_t level1_a = start_color & bitmask;             /*first part of color*/
			int32_t level1_b = end_color & bitmask;
			int32_t level1 = (((2*(i-x)*(level1_b-level1_a)+1))/(2*(x_1-x)))+level1_a;
			int32_t level2_a = start_color & bitmask_1;
			int32_t level2_b = end_color & bitmask_1;
			level2_a = level2_a >> 8;                /*using right shif to deal with value in first 8 bit*/
			level2_b = level2_b >> 8;
			int32_t level2 = (((2*(i-x)*(level2_b-level2_a)+1))/(2*(x_1-x)))+level2_a;
			level2 = level2 << 8;                    /*make it back to original position*/
			int32_t level3_a = start_color & bitmask_2;
			int32_t level3_b = end_color & bitmask_2;
			level3_a = level3_a >> 16;              /*using right shif to deal with value in first 8 bit*/
			level3_b = level3_b >> 16;
			int32_t level3 = (((2*(i-x)*(level3_b-level3_a)+1))/(2*(x_1-x)))+level3_a;
			level3 = level3 << 16;                /*make it back to original position*/
      int32_t levelt = level1 + level2 + level3;           /*add 3 parts to get the total value of level*/
			set_color(levelt);                           /*call set_color to get color*/
			Z = Z & draw_dot(i,j);

		}
	}
   return Z;
}


/*
 *  draw_picture
 *
 *
 *
 *
 * INPUTS: none
 * OUTPUTS: alters the image by calling any of the other functions in the file
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
draw_picture(){
	rect_gradient( 0, 0, 208, 320, 0x3060FF, 0xFFFFFF);
	rect_gradient( 209, 0, 208,320, 0xFFFFFF, 0x20C0D0);
  rect_gradient( 417, 0, 208,320, 0x20C0D0, 0xFFFFFF);
	set_color(0x4040D0);
	draw_circle(53, 160, 22,56);
	rect_gradient(75,145, 34,40,0x4090D0,0xC0E0F0);
	rect_gradient( 106, 100, 22, 120,0x4040D0, 0x4040D0 );
	rect_gradient( 128, 140, 22, 40,0x4040D0, 0x20C0D0 );
	rect_gradient( 150, 100, 22, 120, 0x20C0D0, 0x20C0D0);
	rect_gradient( 192, 100, 22, 120, 0x20C0D0, 0X20C0D0);
	rect_gradient( 214, 100, 44, 24, 0x20C0D0, 0x4040D0);
	rect_gradient( 214, 148, 44, 24, 0x20C0D0, 0x4040D0);
	rect_gradient( 214, 196, 44, 24, 0x20C0D0, 0x4040D0);
	rect_gradient( 278, 100, 22, 120, 0x4040D0, 0x40A080);
	rect_gradient( 300, 198, 44, 22, 0x40A080, 0xC0F060);
  rect_gradient( 364, 100, 66, 24, 0xC0F060, 0xF0A030);
	rect_gradient( 364, 124, 22, 48, 0xC0F060,0xF0A030);
	rect_gradient( 364, 148, 66, 24, 0xC0F060,0xF0A030);
	rect_gradient( 408, 172, 22, 24, 0xC0F060,0xF0A030);
	rect_gradient( 364, 196, 66, 24, 0xC0F060,0xF0A030);
	rect_gradient( 450, 100, 22, 120,0xF0A030, 0xF0A030);
	rect_gradient( 472, 100, 44, 24, 0xF0A030,0xF03030);
	rect_gradient( 472, 148, 44, 24, 0xF0A030,0xF03030);
	rect_gradient( 472, 196, 44, 24, 0xF0A030,0xF03030);
	draw_parallelogram(569,100,560,100,536,220);
	draw_parallelogram(569,100,578,100,602,220);
	draw_rect(557,160,25,30);
	rect_gradient(397,240,22,70,0x3060FF,0x20C0F0);
	rect_gradient(441,240,22,70,0x20C0F0,0x3060FF);
	draw_line(419,240,441,310);
	draw_line(419,240,419,310);
	draw_line(441,240,441,310);
  set_color(0x3060FF);
	draw_circle(516,275,17,35);
  set_color(0xF0A030);
	draw_circle(569,300,0,10);
  set_color(0x3060FF );
	draw_circle(515, 50, 0, 45);
  rect_gradient(590,240,22,70,0x3060FF,0x20C0F0);
	set_color(0);
	draw_circle(500,35,0,10);
	draw_circle(535,35,0,10);
	draw_circle(500,75,0,10);
	draw_circle(535,75,0,10);




	return 0;
}
