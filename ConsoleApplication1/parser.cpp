#include "parser.h"

 shared_ptr<request> parser::_parse_SMR(vector<uint8_t> message_data_buffer)
{

	//TO DO
	//	ADD A FULL BUFFER VALIDATOR
	//


	/// SMIPLE GROUP_ID VALIDATOR
		if (message_data_buffer.size() < 4) throw runtime_error("buffer size is less than 4");
	//

	cout << "Parsing SEND_MESSAGE_REQ, buffer size: " << message_data_buffer.size() << endl;

	uint32_t group_id = BIT::bytes_to_uint32(message_data_buffer.data());
	uint32_t msg_size = BIT::bytes_to_uint32(message_data_buffer.data() + 8);


	return make_shared<send_message_req>(send_message_req(std::move(message_data_buffer), group_id));
}

 shared_ptr<request> parser::_parse_CTGR(vector<uint8_t> CTG_data_buffer)
 {
	 /// SMIPLE GROUP_ID VALIDATOR
	 if (CTG_data_buffer.size() != 8) throw runtime_error("buffer size to CTG is not valid");
	 //


	 cout << "Parsing CONNECT_TO_GROUP_REQ, buffer size: " << CTG_data_buffer.size() << endl;
	 uint32_t session_id = BIT::bytes_to_uint32(CTG_data_buffer.data());
	 uint32_t group_id = BIT::bytes_to_uint32(CTG_data_buffer.data() + 4);
	 return make_shared<connect_to_group_req>(connect_to_group_req(session_id, group_id));
 }

shared_ptr<request> parser::parse(const vector<uint8_t>& buffer)
{
	if (buffer.size() < 4) throw runtime_error("buffer size is less than 4");
	uint32_t req_type = BIT::bytes_to_uint32(buffer.data());
	
	switch (req_type) {

	case CONNECT_TO_GROUP: //4
		return _parse_CTGR(vector<uint8_t>(buffer.begin() + 4, buffer.end()));
	case SEND_MESSAGE: //6
		return _parse_SMR(vector<uint8_t>(buffer.begin() + 4, buffer.end()));
	}

	return shared_ptr<request>();
}
