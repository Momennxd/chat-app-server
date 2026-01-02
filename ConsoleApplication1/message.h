#pragma once
#include <iostream>
#include <string>
using namespace std;

struct message
{
	uint32_t group_id;
	string sender_name;	
	string text;


	message(string _sender_name, uint32_t _group_id, string _msg) {
		this->sender_name = _sender_name;
		this->group_id = _group_id;
		this->text = _msg;
	}

	message() {
		this->sender_name = "";
		this->group_id = -1;
		this->text = "";
	}




	////////////////BUFFER STRUCTURE////////////
	/*
		[group_id: 4 bytes]
		[sender_len: 4 bytes]
		[sender bytes: sender_len bytes]
		[text_len: 4 bytes]
		[text bytes: text_len bytes]
	*/
	///////////////////////////////////////////
	inline static vector<uint8_t> serialize(const message& msg) {
		
		//message buffer structure : 
		//1- is fixed size uint32_t group_id
		//2- uint32_t variable represensts bytes count in the sender_name + the sender name actual bytes
		//3- uint32_t variable represensts bytes count in the text + the text actual bytes
		uint32_t sender_name_len = static_cast<uint32_t>(msg.sender_name.size());
		uint32_t text_len = static_cast<uint32_t>(msg.text.size());

							  //uint32_t			 ///uint32_t		///	number of chars		 ///uint32_t		///	number of chars 
		uint32_t total_size = sizeof(msg.group_id) + sizeof(uint32_t) + sender_name_len + sizeof(uint32_t) + text_len;
		vector<uint8_t> buffer(total_size);
		int sender_name_size = msg.sender_name.size(), text_size = msg.text.size();
		uint8_t* ptr = buffer.data();

		//group id
		memcpy(ptr, &msg.group_id, sizeof(msg.group_id));
		ptr += sizeof(msg.group_id);


		//sender name lengh
		memcpy(ptr, &sender_name_len, sizeof(uint32_t));
		ptr += sizeof(uint32_t);


		//sender name data
		memcpy(ptr, msg.sender_name.data(), sender_name_len);
		ptr += sender_name_len;


		//text length
		memcpy(ptr, &text_len, sizeof(uint32_t));
		ptr += sizeof(uint32_t);


		//text data
		memcpy(ptr, msg.text.data(), text_len);


		return buffer;
	}

	inline vector<uint8_t> serialize() const {
		return serialize(*this);
	}
};