#pragma once

enum request_type {

	NULL_REQ = 0,

	//sessions
	ADD_SESSION = 1,
	REMOVE_SESSION = 2,

	//groups
	ADD_GROUP = 3,
	CONNECT_TO_GROUP = 4,
	DISCONNECT_FROM_GROUP = 5,

	//messages
	SEND_MESSAGE = 6
};




enum parser_data_patterns {

	INT_32 = 0,
	INT_8 = 1,
	STRING = 2

};