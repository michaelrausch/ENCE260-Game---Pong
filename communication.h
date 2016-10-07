/**
* Communication module
* @todo description
*
* Name:					      Student ID:
* Michael Rausch 			  65605682
* Alexander Buckton-Wishart   83066006
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "../../drivers/avr/ir_uart.h"

// Message sent to other player when they win
#define MESSAGE_WIN 7

#define MAX_ROW 6
#define MIN_ROW 0

typedef enum message_type {
	WIN,
	BALL_POSITION,
	INVALID,
	NO_MESSAGE_RCVD
} MessageType;

typedef struct message_s{
	MessageType type;
	uint8_t ballPosition;
} Message;

/*
	Set up IR
*/
void commInit(void);

/*
	Tell other player they have won the game
*/
void sendWin(void);

/*
	Send ball position to other player
	@param ballPosition: row the ball should appear on (between MIN_ROW and MAX_ROW)
 	@return 0 if position not valid, otherwise 1
*/
uint8_t transferBall(char ballPosition);

/*
	Wait for either the ball position or win message
	to be sent by the other player.
	@return Message struct with message type (and ball position).
*/
Message getMessage(void);

/*
	Checks if a ball position is within the row
	@return 0 if position not valid
	@return 1 if position valid
*/
uint8_t checkBallPositionValid(uint8_t position);

#endif
