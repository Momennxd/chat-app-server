#include "parser.h"

shared_ptr<request> parser::_parse_SMR(vector<uint8_t> message_data_buffer)
{

	//TO DO
	//	ADD A FULL BUFFER VALIDATOR
	//


	/// SMIPLE GROUP_ID VALIDATOR
		if (message_data_buffer.size() < 4) throw runtime_error("undefined buffer");
	//

	uint32_t group_id = BIT::bytes_to_uint32(message_data_buffer.data());
	return make_shared<send_message_req>(send_message_req(std::move(message_data_buffer), group_id));
}

shared_ptr<request> parser::parse(const vector<uint8_t>& buffer)
{
	if (buffer.size() < 4) throw runtime_error("undefined buffer");

	uint32_t req_type = BIT::bytes_to_uint32(buffer.data());
	
	switch (req_type) {

	case 6:
		return _parse_SMR(vector<uint8_t>(buffer.begin() + 4, buffer.end()));
	}

	return shared_ptr<request>();
}
