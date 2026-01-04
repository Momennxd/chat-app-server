//#include "messenger.h"
//
//
//
//
//
//messenger::messenger(data_center& dc)
//	: _data_center(dc) 
//{
//}
//
//void messenger::send_message(int group_id, const message& msg)
//{
//	auto session_set = _data_center.get_group_sessions(group_id);
//	for (auto& s : session_set) {
//		if (s) {
//			s->socket_write_async(msg);
//		}
//	}
//	
//}
