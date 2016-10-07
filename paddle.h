/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

// 
#define MAX_TOP 0
#define MAX_BOTTOM 6

#define BOTTOM_COLUMN 4

typedef struct paddle
{
	tinygl_point_t top;
	tinygl_point_t bottom;
} Paddle;

/**

*/
void paddleInit(void);

/**

*/
void drawPaddle (void);

/**

*/
void movePaddle(void);

/**

*/
void setPaddlePosition(tinygl_point_t pos1, tinygl_point_t pos2);

/**

*/
uint8_t checkCollision(uint8_t ballpos);

#endif