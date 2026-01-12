#pragma once
#include "send_message_request.h"
#include "connect_to_group_req.h"
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


	/// <summary>
	/// parse connect to group request buffer to its main request object
	/// </summary>
	/// <param name="CTG_data_buffer"></param>
	/// <returns></returns>
	static shared_ptr<request> _parse_CTGR(vector<uint8_t> CTG_data_buffer);

public:

	
	//DONE SO FAR..
	// ADD_SESSION_REQ, SEND_MSG_REQ, CONNECT_TO_GROUP_REQ

	/// <summary>
	/// parse raw buffer to its main request object (expects the first 4 bytes to be the req type)
	/// </summary>
	/// <param name="buffer"></param>
	/// <returns></returns>
	static shared_ptr<request> parse(const vector<uint8_t>& buffer);


};

