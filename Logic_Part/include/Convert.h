//

#ifndef COURIER_CLIENT_CONVERT_H
#define COURIER_CLIENT_CONVERT_H

#include"db-classes.hpp"
#include "../UI-Interface/UserInfo.h"
#include "../UI-Interface/GroupInfo.h"
#include "../UI-Interface/PacketInfo.h"
#include "../UI-Interface/MessageInfo.h"
#include<vector>


namespace Convert {
	UserInfo cv_user_to_client(userinfo _su);
	
	UserInfo cv_friend_to_client(Friend _su);

	GroupInfo cv_group_to_client(chatGroup_with_members _cg);

	MessageInfo cv_message_to_client(Message _mes);

	PacketInfo cv_packet_to_client(package _pa);

	std::vector<MessageInfo> cv_vmessage_to_client(std::vector<Message> _vmes);

	std::vector<GroupInfo> cv_vgroup_to_client(std::vector<chatGroup_with_members> _vcg);

	std::vector<UserInfo> cv_vfriend_to_client(std::vector<Friend> _su);

	std::vector<PacketInfo> cv_vpacket_to_client(std::vector<package> _pa);

	Message cv_message_to_server(MessageInfo _cmes);
};

#endif //COURIER_CLIENT_CONVERT_H
