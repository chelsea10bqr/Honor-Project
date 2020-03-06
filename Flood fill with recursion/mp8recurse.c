#include <stdlib.h>
#include <string.h>

#include "mp8.h"

/*   introductory paragraph!!!!!
implement several varieties of flood fill operations using recursion
and this mp8recurse.c is recurse structure, which will be called by wrapeer structure functions


*/
/*
 * basicRecurse -- flood fill recursively from a point until reaching
 *                 black or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
basicRecurse (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen,
	      const uint8_t* inBlue,
	      int32_t x, int32_t y,
	      uint8_t* marking)
{ if ((0>x || x>=width || 0>y || y>=height) || ((inRed[x+y*width]==0) && (inGreen[x+y*width]==0) && (inBlue[x+y*width]==0)))  /*check the condition whether the point is in the range and whether this pixel is black*/
	{
		return;                                                                                             /*if it is black, just stop recurse and back to last function*/
	}
	marking[x+y*width]=1;                                                                                /*if it is not black, mark this pixel 1*/
	if((marking[x+(y-1)*width]!=1)&& (0<=(x+(y-1)*width))&& ((x+(y-1)*width)< (width * height)))         /*use if to check whether we have visited this pixel*/
	basicRecurse(width,height,inRed,inGreen,inBlue,x,y-1,marking);                                       /*call Recurse function 4 times for 4 directions*/
	if((marking[(x+1)+y*width]!=1)&& (0 <=((x+1)+y*width))&& (((x+1)+y*width)< (width * height)))
	basicRecurse(width,height,inRed,inGreen,inBlue,x+1,y,marking);
	if((marking[x+(y+1)*width]!=1)&& (0 <=(x+(y+1)*width))&&(( x+(y+1)*width)< (width * height)))
	basicRecurse(width,height,inRed,inGreen,inBlue,x,y+1,marking);
	if((marking[(x-1)+y*width]!=1)&& (0 <=((x-1)+y*width))&& (((x-1)+y*width)< (width * height)))
	basicRecurse(width,height,inRed,inGreen,inBlue,x-1,y,marking);


}


/*
 * greyRecurse -- flood fill recursively from a point until reaching
 *                near-black pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between black and boundary
 *                   pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */

void
greyRecurse (int32_t width, int32_t height,
	     const uint8_t* inRed, const uint8_t* inGreen,
	     const uint8_t* inBlue,
	     int32_t x, int32_t y, uint32_t distSq,
	     uint8_t* marking)
{

	if ((0>x || x>=width || 0>y || y>=height) || colorsWithinDistSq(inRed[x+y*width],inGreen[x+y*width],inBlue[x+y*width],0,0,0,distSq))  /*check the condition whether the point is in the range and whether this pixel is in color range*/
	{
		return;                                       /*if it is in the range  just stop*/
	}
	marking[x+y*width]=1;
	if((marking[x+(y-1)*width]!=1)&& (0<=(x+(y-1)*width))&& ((x+(y-1)*width)< (width * height)))                    /*use if to check whether we have visited this pixel*/
	greyRecurse(width,height,inRed,inGreen,inBlue,x,y-1,distSq,marking);                                           /*call Recurse function 4 times for 4 directions*/
	if((marking[(x+1)+y*width]!=1)&& (0 <=((x+1)+y*width))&& (((x+1)+y*width)< (width * height)))
  greyRecurse(width,height,inRed,inGreen,inBlue,x+1,y,distSq,marking);
	if((marking[x+(y+1)*width]!=1)&& (0 <=(x+(y+1)*width))&&(( x+(y+1)*width)< (width * height)))
	greyRecurse(width,height,inRed,inGreen,inBlue,x,y+1,distSq,marking);
	if((marking[(x-1)+y*width]!=1)&& (0 <=((x-1)+y*width))&& (((x-1)+y*width)< (width * height)))
	greyRecurse(width,height,inRed,inGreen,inBlue,x-1,y,distSq,marking);



}


/*
 * limitedRecurse -- flood fill recursively from a point until reaching
 *                   pixels too different (in RGB color) from the color at
 *                   the flood start point, too far away (> 40 pixels), or
 *                   beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         origX -- starting x position of the flood
 *         origY -- starting y position of the flood
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between pixel at origin
 *                   and boundary pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
limitedRecurse (int32_t width, int32_t height,
	        const uint8_t* inRed, const uint8_t* inGreen,
	        const uint8_t* inBlue,
	        int32_t origX, int32_t origY, int32_t x, int32_t y,
		uint32_t distSq, uint8_t* marking)
{ if(((x-origX)*(x-origX)+(y-origY)*(y-origY))>1600 )
	{
		return;                                           /*check the condition whether it is too far away from original color, and check whether it is in the 40 pixels range*/
	}
	if ((0>x || x>=width || 0>y || y>=height) ||!colorsWithinDistSq(inRed[x+y*width],inGreen[x+y*width],inBlue[x+y*width],inRed[origX+origY*width],inGreen[origX+origY*width],inBlue[origX+origY*width],distSq))
	 {
		return;
	}
	marking[x+y*width]=1;
	if((marking[x+(y-1)*width]!=1)&& (0<=(x+(y-1)*width))&& ((x+(y-1)*width)< (width * height)))    /*use if to check whether we have visited this pixel*/
	limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x,y-1,distSq,marking);              /*call Recurse function 4 times for 4 directions*/
	if((marking[(x+1)+y*width]!=1)&& (0 <=((x+1)+y*width))&& (((x+1)+y*width)< (width * height)))
  limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x+1,y,distSq,marking);
	if((marking[x+(y+1)*width]!=1)&& (0 <=(x+(y+1)*width))&&(( x+(y+1)*width)< (width * height)))
	limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x,y+1,distSq,marking);
	if((marking[(x-1)+y*width]!=1)&& (0 <=((x-1)+y*width))&& (((x-1)+y*width)< (width * height)))
	limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x-1,y,distSq,marking);

}
