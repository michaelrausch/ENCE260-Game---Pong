/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "../../utils/tinygl.h"
#include "pio.h"

// Index of the top and bottom columns on LED Matrix
#define TOP_COLUMN 0
#define BOTTOM_COLUMN 4
#define MIDDLE_ROW 3

// Number of rows and column on the LED Matrix
#define NUM_ROWS 7
#define NUM_COLS 5

typedef enum ball_angle
{
	RIGHT=-1,
	LEFT=1,
	STRAIGHT=0
} Angle;

typedef enum ball_direction
{
	UP=-1,
	DOWN=1
} BallDirection;

typedef enum ball_status
{
	OFF_GRID, // Ball is ready to be sent to other player
	ON_PADDLE_AXIS, // Ball is on the same axis as the paddle
	MOVING // Ball is moving within the players matrix
} BallStatus;

// @todo Documentation
typedef struct ball
{
	BallDirection direction;
	Angle angle;
	int8_t angleDistanceRemaining;
	tinygl_point_t position;
} Ball;

// Draw the ball in its current position on the LED matrix
void drawBall(void);

// Initialises the ball struct with an initial position (0,0)
void ballInit(void);

// Sets the balls position and displays the ball
// @todo switch row and col
void setBallPosition(int8_t row, int8_t col);

// Remove ball from display and reset its position
void removeBall(void);

// Sets the angle of the ball (LEFT, STAIGHT, RIGHT)
// Distance: how many position updates until the ball goes straight again
void setBallAngle(Angle angle, int8_t distance);

// Gets the angle
Angle getBallAngle(void);

// Sets the ball direction (UP or DOWN) relative to the player
void setBallDirection(BallDirection direction);

// Move the ball to its next position
void moveBall(void);

// Change the balls direction from UP to DOWN or vice-versa
void bounceBall(void);

// Returns the balls current position on the y-axis
uint8_t getBallPosition(void);

// Returns the balls status
// OFF_GRID: Ball is ready to be sent to other player
// ON_PADDLE_AXIS: Ball is on the same axis as the paddle
// MOVING: Ball is moving within the players matrix
BallStatus getBallStatus(void);


#endif
