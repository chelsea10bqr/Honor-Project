#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*   introductory paragraph!!!!!
implement several varieties of flood fill operations using recursion
and this mp8.c is wrapper structure, which will call recurse functions


*/
/*
 * basicFlood -- wrapper for flood filling recursively from a point until
 *               reaching black or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */

void
basicFlood (int32_t width, int32_t height,
	    const uint8_t* inRed, const uint8_t* inGreen,
	    const uint8_t* inBlue,
	    int32_t startX, int32_t startY,
	    uint8_t floodR, uint8_t floodG, uint8_t floodB,
	    uint8_t* outRed, uint8_t* outGreen,
	    uint8_t* outBlue)
{ memset(outRed,0,width*height);                                /*use memset to initialize the arrays*/
	memset(outBlue,0,width*height);
	memset(outGreen,0,width*height);
	basicRecurse(width,height,inRed,inGreen,inBlue,startX,startY,outRed);             /*call basic Recurse for red green and blue*/
	basicRecurse(width,height,inRed,inGreen,inBlue,startX,startY,outGreen);
  basicRecurse(width,height,inRed,inGreen,inBlue,startX,startY,outBlue);
  int32_t i,j,k;                                                           /*check RGB 3 arrays, if it is 1  use flood color, else use original color*/
	for ( i= 0; i < width*height; i++) {
  	if (outRed[i] == 1) {
  		outRed[i] = floodR;
  	}else{
		outRed[i] = inRed[i];
	}
  }
	for ( j= 0; j < width*height; j++) {
  	if (outGreen[j] == 1) {
  		outGreen[j] = floodG;
  	}else{
		outGreen[j] = inGreen[j];
	}
  }
	for ( k= 0; k < width*height; k++) {
  	if (outBlue[k] == 1) {
  		outBlue[k] = floodB;
  	} else{
		outBlue[k] = inBlue[k];
	}
	}


}


/*
 * colorsWithinDistSq -- returns 1 iff two colors are within Euclidean
 *                       distance squared of one another in RGB space
 * INPUTS: r1 -- red component of color 1
 *         g1 -- green component of color 1
 *         b1 -- blue component of color 1
 *         r2 -- red component of color 2
 *         g2 -- green component of color 2
 *         b2 -- blue component of color 2
 *         distSq -- maximum distance squared for the check
 * RETURN VALUE: 1 if the sum of the squares of the differences in the
 *               three components is less or equal to distSq; 0 otherwise
 * SIDE EFFECTS: none
 */
int32_t
colorsWithinDistSq (uint8_t r1, uint8_t g1, uint8_t b1,
                    uint8_t r2, uint8_t g2, uint8_t b2, uint32_t distSq)
{
   if((r1-r2)*(r1-r2)+(g1-g2)*(g1-g2)+(b1-b2)*(b1-b2)<= distSq)
	 {
		 return 1;
	 }

    return 0;

}


/*
 * greyFlood -- wrapper for flood filling recursively from a point until
 *              reaching near-black pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between black and boundary
 *                   pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
greyFlood (int32_t width, int32_t height,
	   const uint8_t* inRed, const uint8_t* inGreen,
	   const uint8_t* inBlue,
	   int32_t startX, int32_t startY,
	   uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	   uint8_t* outRed, uint8_t* outGreen,
	   uint8_t* outBlue)
{ memset(outRed,0,width*height);                                    /*use memset to initialize the arrays*/
	memset(outBlue,0,width*height);
	memset(outGreen,0,width*height);
	greyRecurse(width,height,inRed,inGreen,inBlue,startX,startY,distSq,outRed);            /*call basic Recurse for red green and blue*/
	greyRecurse(width,height,inRed,inGreen,inBlue,startX,startY,distSq,outGreen);
  greyRecurse(width,height,inRed,inGreen,inBlue,startX,startY,distSq,outBlue);
  int32_t i,j,k;
	for ( i= 0; i < width*height; i++) {                                       /*check RGB 3 arrays, if it is 1  use flood color, else use original color*/
  	if (outRed[i] == 1) {
  		outRed[i] = floodR;
  	}else{
		outRed[i] = inRed[i];
	}
  }
	for ( j= 0; j < width*height; j++) {
  	if (outGreen[j] == 1) {
  		outGreen[j] = floodG;
  	}else{
		outGreen[j] = inGreen[j];
	}
  }
	for ( k= 0; k < width*height; k++) {
  	if (outBlue[k] == 1) {
  		outBlue[k] = floodB;
  	} else{
		outBlue[k] = inBlue[k];
	}
	}


}


/*
 * limitedFlood -- wrapper for flood filling recursively from a point until
 *                 reaching pixels too different (in RGB color) from the
 *                 color at the flood start point, too far away
 *                 (> 40 pixels), or beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between pixel at origin
 *                   and boundary pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
limitedFlood (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen,
	      const uint8_t* inBlue,
	      int32_t startX, int32_t startY,
	      uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	      uint8_t* outRed, uint8_t* outGreen,
	      uint8_t* outBlue)
{ memset(outRed,0,width*height);                                     /*use memset to initialize the arrays*/
	memset(outBlue,0,width*height);
	memset(outGreen,0,width*height);
	limitedRecurse(width,height,inRed,inGreen,inBlue,startX,startY,startX,startY,distSq,outRed);             /*call basic Recurse for red green and blue*/
	limitedRecurse(width,height,inRed,inGreen,inBlue,startX,startY,startX,startY,distSq,outGreen);
  limitedRecurse(width,height,inRed,inGreen,inBlue,startX,startY,startX,startY,distSq,outBlue);
  int32_t i,j,k;                                                     /*check RGB 3 arrays, if it is 1  use flood color, else use original color*/
	for ( i= 0; i < width*height; i++) {
  	if (outRed[i] == 1) {
  		outRed[i] = floodR;
  	}else{
		outRed[i] = inRed[i];
	}
  }
	for ( j= 0; j < width*height; j++) {
  	if (outGreen[j] == 1) {
  		outGreen[j] = floodG;
  	}else{
		outGreen[j] = inGreen[j];
	}
  }
	for ( k= 0; k < width*height; k++) {
  	if (outBlue[k] == 1) {
  		outBlue[k] = floodB;
  	} else{
		outBlue[k] = inBlue[k];
	}
	}


}
