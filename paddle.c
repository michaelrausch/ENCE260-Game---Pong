/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#include "paddle.h"

static Paddle paddle;

/**
	
*/
void paddleInit(void)
{
	// Set initial position to middle of matrix
	tinygl_point_t top = {BOTTOM_COLUMN, 2};
	tinygl_point_t bottom = {BOTTOM_COLUMN, 4};
	
	paddle.top = top;
	paddle.bottom = bottom;
  
}

/** 
	Sets the paddle position and displays the paddle
*/
void drawPaddle (void)
{
	tinygl_draw_line (paddle.top,paddle.bottom,1);
}


/**
	
*/
void movePaddle(void)
{
	// Remove paddle from matrix before moving
	tinygl_draw_line(paddle.top,paddle.bottom, 0);
	
	if (navswitch_push_event_p(NAVSWITCH_NORTH) && paddle.top.y != MAX_TOP)
	{
		paddle.top.y -= 1;
		paddle.bottom.y -= 1;
	}
	
	if (navswitch_push_event_p(NAVSWITCH_SOUTH) && paddle.bottom.y != MAX_BOTTOM)
	{
		paddle.top.y += 1;
		paddle.bottom.y += 1;
	}
	drawPaddle();
}

/**
	
*/
void setPaddlePosition(tinygl_point_t pos1, tinygl_point_t pos2)
{
	// Remove ball from matrix before moving
	tinygl_draw_line(pos1, pos2,0);

	// Change position
	paddle.top = pos1;
	paddle.bottom = pos2;

	drawPaddle();
}

/**
	
*/
uint8_t checkCollision(uint8_t ballpos)
{
	if (ballpos < paddle.top.y || ballpos > paddle.bottom.y){
		return 1;
	}
	return 0;
}


			


