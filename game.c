/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#include "pio.h"
#include "pacer.h"
#include "tinygl.h"
#include "font.h"
#include "font5x7_1.h"
#include "ball.h"
#include "communication.h"
#include "paddle.h"

#define PACER_RATE 1000
#define DISPLAY_TASK_RATE 100 //@todo check
#define BALL_TASK_RATE 1

// @todo comment
#define WIN_MESSAGE "WIN!"
#define LOOSE_MESSAGE "LOOSE!"

// Current state of the program
typedef enum state_t{
	BALL_MOVEMENT_STATE=0, // Ball moving on matrix
	BALL_POS_WAIT_STATE=1, // Waiting for ball position
	RESULT_MESSAGE_STATE=2, // Displaying result message
	INSTRUCTION_MESSAGE_STATE=3
} State;

// @todo comment
static State state = BALL_POS_WAIT_STATE;
static uint16_t tick = 0;

/**
	Displays win message
*/
void showWinMessage(void)
{
	removeBall();
	tinygl_text(WIN_MESSAGE);
}

/**
	Displays loose message
*/
void showLooseMessage(void)
{
	removeBall();
	tinygl_text(LOOSE_MESSAGE);
}

/**
	Initialises the LED Matrix
*/
void displayInit(void)
{
	tinygl_init(DISPLAY_TASK_RATE);
	tinygl_font_set(&font5x7_1);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	tinygl_text_speed_set (1);  // @todo comment
}

/**
	Move the ball @todo docs
*/
void ball_task(void)
{
	moveBall();

	// Ball has moved off LED Matrix
	if (getBallStatus() == OFF_GRID){
		// Send ball position to other player
		// Invert the row so the ball appears on the correct side
		transferBall(NUM_ROWS-getBallPosition()-1);
		tinygl_clear();

		removeBall();

		tick = 0;
		state = BALL_POS_WAIT_STATE;

	}
	// Ball is on the paddle column
	else if (getBallStatus() == ON_PADDLE_AXIS){
		// Check collision between paddle and ball
		if (checkCollision(getBallPosition()) == 1){
			sendWin();
			showLooseMessage();
			state = RESULT_MESSAGE_STATE;
		}
		else{
			bounceBall();
		}
	}
}

/**
	Wait for ball position or win message
*/
void ballWaitTask(void)
{
	// Get message from other player
	Message message = getMessage();

	// Message contains ball position, create a ball at that position
	if (message.type == BALL_POSITION){
		setBallDirection(DOWN);
		setBallPosition(TOP_COLUMN, message.ballPosition);
		state = BALL_MOVEMENT_STATE;
		tick = 0;
	}
	// Display win message and enter RESULT_MESSAGE state
	else if (message.type == WIN){
		showWinMessage();
		state = RESULT_MESSAGE_STATE;
	}
}

/**
	@todo docs
*/
void gameInit()
{
	system_init();
	displayInit();
	ballInit();
	commInit();
	pacer_init(PACER_RATE);
	paddleInit();

	// Set up PIO
	pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
	pio_config_set(BUTTON1_PIO, PIO_INPUT);

	tinygl_clear();
}

int main(void)
{
	gameInit();

	while(1){
		pacer_wait();

		if (state == BALL_MOVEMENT_STATE){
			// Run once per second
			if(tick == PACER_RATE){
				ball_task();
			}

			pio_output_high(LED1_PIO); //@todo move??
		}

		// Waiting for ball position (or win message)
		if (state == BALL_POS_WAIT_STATE){
			ballWaitTask();

			// Start game as player 1 if button pressed
			if (pio_input_get(BUTTON1_PIO)){
				state = BALL_MOVEMENT_STATE;
				
			}

			pio_output_low(LED1_PIO);
		}

		//@todo docs
		if (state != RESULT_MESSAGE_STATE){
			navswitch_update();
			movePaddle();
		}		

		tinygl_update();

		// Reset tick every second
		if(tick == PACER_RATE){
			tick = 0;
		}

		tick += 1;
	}

	return 0;
}