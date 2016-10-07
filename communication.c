/**
* @todo Game Name
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/


#include "communication.h"

/*
	Set up IR
*/
void commInit(void)
{
	ir_uart_init();
}

/*
	Tell other player they have won the game
*/
void sendWin(void)
{
	ir_uart_putc(MESSAGE_WIN);
}

/*
	Send ball position to other player
	@param ballPosition: row the ball should appear on (between MIN_ROW and MAX_ROW)
 	@return 0 if position not valid, otherwise 1
*/
uint8_t transferBall(char ballPosition)
{
	// Check position is valid
	if (checkBallPositionValid(ballPosition) != 1){
		return 0;
	}

	ir_uart_putc(ballPosition);

	return 1;
}

/*
	Wait for either the ball position or win message
	to be sent by the other player.
	@return Message struct with message type (and ball position).
*/
Message getMessage()
{
	uint8_t received; // Data received from other player
	Message message = {0,0};

	// Check if register contains data
	if (ir_uart_read_ready_p()){
		received = ir_uart_getc();

		// Message is a valid ball position
		if (checkBallPositionValid(received) == 1){
			message.type = BALL_POSITION;
			message.ballPosition = received;
		}

		// Message is a 'win' message
		else if(received == MESSAGE_WIN){
			message.type = WIN;
		}

		// Message was not valid
		else{
			message.type = INVALID;
		}

	}

	// No message received
	else{
		message.type = NO_MESSAGE_RCVD;
	}

	return message;
}

/*
	Checks if a ball position is within the row
	@return 0 if position not valid
	@return 1 if position valid
*/
uint8_t checkBallPositionValid(uint8_t position)
{
	if (position < MAX_ROW){
		return 1;
	}
	return 0;
}
