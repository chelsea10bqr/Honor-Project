//									tab:8
//
// mp12.cpp - source file for Spring 2018 MP12 student code
//
// "Copyright (c) 2018 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
//
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta
// Version:	    1.00
// Creation Date:   20 April 2018
// Filename:	    mp12.cpp
// History:
//	SL	1.00	20 April 2018
//		First written.
//

#include <iostream>
#include <list>

#include <math.h>
#include <stdio.h>

#include "WALYmain.h"

#include "TurtleScreen.h"

#include "mp5.h"
#include "mp12.h"

using namespace std;
using namespace WALY;

// THESE ARE GLOBAL VARIABLES IN THE INTEREST OF TESTING.  THEY SHOULD
// BE FILE-SCOPE OR LOCAL TO frameUpdate.
FILE*           input = NULL;		// input stream
list<segment_t> lines;			// list of lines drawn
command_t       cmd = {CMD_NONE};	// current command
int32_t	        moveColor = 0xFFFFFF;	// current movement drawing color

int32_t
openInputStream (const char* fname)
{
  input = fopen(fname,"rb+");             //open the file
  if(input == NULL)
  {
    //if open file failure, return 0
    return 0;
  }
  return 1;
}

void
closeInputStream (void)
{
  //close the file
  fclose(input);
}

void
showLines (void)
{
    // you can use 'call showLines ()' in GDB to look at the
    // list of segments.  Don't forget to call makeVisibleChange
    // when you change this list, since the background won't be
    // redrawn unless you call that function (so changes will not
    // show up.
    for (list<segment_t>::iterator it = lines.begin ();
	 lines.end () != it; it++) {
Screen::debug () << it->color << " " << it->x1 << "," << it->y1 << "  " << it->x2 << "," << it->y2 << endl;
    }
}

void
drawEverything (void)
{
  for(list<segment_t>::iterator draw = lines.begin();lines.end()!=draw;draw++)
  {
    set_color(draw->color); //set the color to  command's color
    draw_line(draw->x1,draw->y1,draw->x2,draw->y2);// call the drawline function
  }

}
static double c_x,c_y;
void
readNewCommand (TurtleScreen* ts)
{
  char cur_line[201];
  char str[20];
  int32_t first;   //store the value of first and second integer
  int32_t second;
  if(NULL == fgets(cur_line,201,input))
  {// if it is null, exit
    fputs("Non-existent file!\n",stderr);
    return;
  }else{
    sscanf (cur_line,"%s",str);
    if(strcasecmp(str,"color")==0){//determine which is the type of the command
      sscanf(cur_line,"%*s %x",&first);
      moveColor = first;
      set_color(first);
    }else if(strcasecmp(str,"move")==0)
    {
      cmd.type = CMD_MOVE;
      sscanf(cur_line,"%*s %d %d",&first,&second);
      cmd.cmdFrames = second;
      cmd.startX = ts->getX();
      cmd.startY = ts->getY();
      c_x = ts->getX();
      c_y = ts->getY();
      double ex = cmd.startX+first*cos(ts->getDirection()*10*M_PI/180+(M_PI/2));//the equation to computer x and y
      double ey = cmd.startY-first*sin(ts->getDirection()*10*M_PI/180+(M_PI/2));
      cmd.framesLeft = cmd.cmdFrames;
      cmd.endX = round(ex);
      cmd.endY = round(ey);
      segment_t update = {moveColor,cmd.startX,cmd.startY,cmd.startX,cmd.startY};
      lines.push_back(update);

    }else if(strcasecmp(str,"restart")==0)
    {
      rewind(input);
    }else if(strcasecmp(str,"turn")==0)
    {
      sscanf(cur_line,"%*s %d",&first);
      if(first!=0){
      cmd.type = CMD_TURN;
      cmd.cmdFrames = abs(first);
      if(first>0){
        cmd.dir=1;
      }else{
        cmd.dir=-1;
      }
       cmd.framesLeft = cmd.cmdFrames;
    }
  }else if(strcasecmp(str,"wait")==0)
    {
      sscanf(cur_line,"%*s %d",&first);
      if(first>=0){
      cmd.type = CMD_WAIT;
      cmd.cmdFrames = first;
      cmd.framesLeft = cmd.cmdFrames;
    }
    }else{
        fputs("bad commands!\n",stderr);
      }
    }

}
void
frameUpdate (TurtleScreen* ts)
{
  while (CMD_NONE == cmd.type){
  if (feof(input))
    return;
  readNewCommand(ts);
}
//if command finished, set command to NONE and wait to read new one
if (cmd.framesLeft == 0){
  cmd.type = CMD_NONE;
  return;
}
segment_t& seg = lines.back();
switch (cmd.type){
  case CMD_MOVE:
  //move to the destination in some frames by setting X and Y
    c_x += 1.0*(cmd.endX-cmd.startX)/cmd.cmdFrames;
    c_y += 1.0*(cmd.endY-cmd.startY)/cmd.cmdFrames;
    ts->setX(round(c_x));
    ts->setY(round(c_y));
    cmd.framesLeft--;
    seg.x2 = round(c_x);
    seg.y2 = round(c_y);
    break;
  case CMD_TURN:
  //turn left if direction is 1, right if -1
    if (cmd.dir == 1)
      ts->turnLeft();
    if (cmd.dir == -1)
      ts->turnRight();
    cmd.framesLeft--;
    break;
  case CMD_WAIT:
    cmd.framesLeft--;// wait the frames
    break;
  default:
    break;
}

ts->makeVisibleChange();// make it visible
  }
