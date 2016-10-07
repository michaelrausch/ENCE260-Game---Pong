/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#include "ball.h"

static Ball ball;

/**
	Initialises the ball struct with an initial position (0,0)
**/
void ballInit(void)
{
	tinygl_point_t position = {BOTTOM_COLUMN, MIDDLE_ROW};

	ball.direction = UP;
	ball.angle = LEFT;
	ball.angleDistanceRemaining = -1; // Forever
	ball.position = position;
}


/**
	Sets the balls position and displays the ball
**/
void setBallPosition(tinygl_coord_t x, tinygl_coord_t y)
{
	// Remove ball from matrix before moving it
	tinygl_draw_point(ball.position, 0);

	// Change position
	tinygl_point_t point = {x, y};
	ball.position = point;

	drawBall();
}


/** 
	Removes ball from display and reset its position to (0,0)
**/
void removeBall(void)
{
	// Reset position
	tinygl_point_t point = {0,0};
	ball.position = point;

	// Remove from LED matrix
	tinygl_pixel_set(ball.position, 0);
}


/** Sets the angle the ball should travel in
	@param angle (LEFT, STAIGHT, RIGHT) 
	@param distance: how many position updates until the ball goes straight again, -1 for infinity
**/
void setBallAngle(Angle angle, int8_t distance)
{
	ball.angle = angle;
	ball.angleDistanceRemaining = distance;
}


/** Sets the ball direction relative to the player
	@param direction (UP, DOWN) 
**/
void setBallDirection(BallDirection direction)
{
	ball.direction = direction;
}


/**
	Calculate the balls new position and move it there
**/
void moveBall(void)
{
	// Remove ball from matrix before moving
	tinygl_draw_point(ball.position, 0);
	
	// If ball is not above top column or below bottom column
	if (ball.position.x < NUM_COLS && ball.position.x >= 0){
		ball.position.x += ball.direction;
	}

	if (ball.angleDistanceRemaining != 0){
		// Ball is going to the left, and is not on the leftmost row 
		if (ball.angle == LEFT && ball.position.y != NUM_ROWS-1){
			ball.position.y += ball.angle;
		}
		// Ball is going to the right, and is not on the rightmost row 
		else if (ball.angle == RIGHT && ball.position.y != 0){
			ball.position.y += ball.angle;
		}
		// Ball couldn't move to left, set angle to right
		else if (ball.angle == LEFT){
			ball.angle = RIGHT;
			ball.position.y += ball.angle;
		}
		// Ball couldn't move to right, set angle to left
		else if (ball.angle == RIGHT){
			ball.angle = LEFT;
			ball.position.y += ball.angle;
		}

		ball.angleDistanceRemaining -= 1;
	}

	drawBall();
}


/**
	Change the balls direction from UP to DOWN or vice-versa
**/
void bounceBall(void)
{
	// Remove ball from matrix
	tinygl_draw_point(ball.position, 0);

	// Flip direction
	if (ball.direction == UP){
		ball.direction = DOWN;
	}
	else{
		ball.direction = UP;
	}

	// Move the ball in the new direction
	ball.position.x += ball.direction;

	drawBall();
}


/**
	Draw the ball in its current position on the LED matrix
**/
void drawBall(void){
	tinygl_draw_point(ball.position, 1);
}


/**
	Returns the balls current position on the y-axis
**/
uint8_t getBallPosition(void){
	return ball.position.y;
}


/** Returns the balls status
	@return OFF_GRID: Ball is ready to be sent to other player
			ON_PADDLE_AXIS: Ball is on the row above the paddle @todo change ON_PADDLE_AXIS to something better 
			MOVING: Ball is moving within the players matrix
**/
BallStatus getBallStatus(void){
	// Ball is on row above paddle
	if (ball.position.x > NUM_COLS-2){
		return ON_PADDLE_AXIS;
	}

	// Ball is on top row
	if (ball.position.x < 0){
		return OFF_GRID;
	}

	return MOVING;
}


/** 
	Returns the balls current angle
*/
Angle getBallAngle()
{
	if (ball.angleDistanceRemaining <= 0){
		return STRAIGHT;
	}
	return ball.angle;
}
