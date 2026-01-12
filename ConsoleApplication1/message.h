//#pragma once
//#include <iostream>
//#include <string>
//#include "BIT.h"
//using namespace std;
//
//struct message
//{
//	uint32_t group_id;
//	uint32_t sender_session_id;
//	string text;
//
//
//	message(uint32_t _sender_session_id, uint32_t _group_id, string _msg) {
//		this->sender_session_id = _sender_session_id;
//		this->group_id = _group_id;
//		this->text = _msg;
//	}
//
//	message() {
//		this->sender_session_id = 0;
//		this->group_id = 0;
//		this->text = "";
//	}
//
//
//
//	//      NEEEEEDS   REFACTORING    ASAP
//
//	////////////////BUFFER STRUCTURE////////////
//	/*
//		[group_id: 4 bytes]
//		[sender_len: 4 bytes]
//		[sender bytes: sender_len bytes]
//		[text_len: 4 bytes]
//		[text bytes: text_len bytes]
//	*/
//	///////////////////////////////////////////
//	//inline static vector<uint8_t> serialize(const message& msg) {
//	//	
//	//	//message buffer structure : 
//	//	//1- is fixed size uint32_t group_id
//	//	//2- uint32_t variable represensts bytes count in the sender_name + the sender name actual bytes
//	//	//3- uint32_t variable represensts bytes count in the text + the text actual bytes
//	//	uint32_t sender_name_len = static_cast<uint32_t>(msg.sender_name.size());
//	//	uint32_t text_len = static_cast<uint32_t>(msg.text.size());
//
//	//						  //uint32_t			 ///uint32_t		///	number of chars		 ///uint32_t		///	number of chars 
//	//	uint32_t total_size = sizeof(msg.group_id) + sizeof(uint32_t) + sender_name_len + sizeof(uint32_t) + text_len;
//	//	vector<uint8_t> buffer(total_size);
//	//	int sender_name_size = msg.sender_name.size(), text_size = msg.text.size();
//	//	uint8_t* ptr = buffer.data();
//
//	//	//group id
//	//	memcpy(ptr, &msg.group_id, sizeof(msg.group_id));
//	//	ptr += sizeof(msg.group_id);
//
//
//	//	//sender name lengh
//	//	memcpy(ptr, &sender_name_len, sizeof(uint32_t));
//	//	ptr += sizeof(uint32_t);
//
//
//	//	//sender name data
//	//	memcpy(ptr, msg.sender_name.data(), sender_name_len);
//	//	ptr += sender_name_len;
//
//
//	//	//text length
//	//	memcpy(ptr, &text_len, sizeof(uint32_t));
//	//	ptr += sizeof(uint32_t);
//
//
//	//	//text data
//	//	memcpy(ptr, msg.text.data(), text_len);
//
//
//	//	return buffer;
//	//}
//
//	//inline vector<uint8_t> serialize() const {		
//	//	return serialize(*this);
//	//}
//
//	//// 1 0 0 1  0 0 0 0  1 1 1 1  0 0 0 0
//	//inline static message deserialize(const vector<uint8_t>& buffer) {
//	//	if (buffer.size() < 12) throw runtime_error("buffer too small");
//	//	message msg;
//	//	msg.group_id = BIT::bytes_to_uint32(buffer.data());
//	//	uint32_t sender_len = BIT::bytes_to_uint32(buffer.data() + 4);
//	//	if (buffer.size() - 8 < sender_len) throw runtime_error("buffer too small");
//	//	msg.sender_name = string(reinterpret_cast<const char*>(buffer.data() + 8), sender_len);
//	//	uint32_t text_len = BIT::bytes_to_uint32(buffer.data() + 8 + msg.sender_name.size());
//	//	msg.text = string(reinterpret_cast<const char*>(buffer.data() + 12 + msg.sender_name.size()), text_len);
//	//	return msg;
//	//}
//
//};