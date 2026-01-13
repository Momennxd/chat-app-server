#pragma once
#include <vector>
#include "enums.h"

/////////////////////////////////////////////////
#define MAX_SPAN_IDLE_SESSION_SECONDS 3600
#define MONITOR_IDLE_SESSIONS_EACH 100










////////////////////// RESPONSE //////////////////////

#define OK 1

#define SERVER_ERROR 2

#define GROUP_NOT_EXIST 3

#define SESSION_CLOSED 4

#define SESSION_NOT_EXIST_IN_DB  4

#define NOT_INIT_SERVICE 5

#define UNDEFINED_REQUEST 6


#define MAX_MESSAGE_SIZE 10000


/////////////////////// REQUESTS DATA TYPES PATTERNS /////////////////////


/*
*
	NULL_REQ = 0,

	ADD_SESSION = 1,
	REMOVE_SESSION = 2,

	ADD_GROUP = 3,
	CONNECT_TO_GROUP = 4,
	DISCONNECT_FROM_GROUP = 5,

	SEND_MESSAGE = 6
*/

 static std::vector<std::vector<parser_data_patterns>> PDP_MAP{

	{}, 
	{},
	{},
	{},
	//connect to group req
	{parser_data_patterns::INT_32, parser_data_patterns::INT_32},
	{},
	//msg		group_id					// sender_session_id		//text size					// text bytes
	{parser_data_patterns::INT_32, parser_data_patterns::INT_32, parser_data_patterns::INT_32, parser_data_patterns::STRING}

};
