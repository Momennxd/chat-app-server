#pragma once
#include "request.h"
#include "enums.h"
#include "BIT.h"
#include "send_message_request.h"

class parser
{
private:

	const vector<parser_data_patterns>& _PDPs;


	/// <summary>
	/// parse send message request buffer to its main request object
	/// </summary>
	/// <param name="message_data_buffer"></param>
	/// <returns></returns>
	shared_ptr<request> _parse_SMR(vector<uint8_t> message_data_buffer);
public:

	

	shared_ptr<request> parse(const vector<uint8_t>& buffer);


};

