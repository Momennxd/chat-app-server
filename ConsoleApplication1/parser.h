#pragma once
#include "send_message_request.h"
#include "BIT.h"

class parser
{
private:



	/// <summary>
	/// parse send message request buffer to its main request object
	/// </summary>
	/// <param name="message_data_buffer"></param>
	/// <returns></returns>
	static shared_ptr<request> _parse_SMR(vector<uint8_t> message_data_buffer);
public:

	
	//DONE SO FAR..
	// ADD_SESSION_REQ, SEND_MSG_REQ

	static shared_ptr<request> parse(const vector<uint8_t>& buffer);


};

