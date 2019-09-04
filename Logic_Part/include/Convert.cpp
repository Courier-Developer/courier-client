
#include"Convert.h"

UserInfo Convert::cv_user_to_client(userinfo _su)
{
	return UserInfo(_su.id, _su.username, _su.nickname, _su.signature, "", 1, 1);
}

UserInfo Convert::cv_friend_to_client(Friend _su)
{
	return UserInfo(_su.uid, _su.username, _su.nickname, "", "", _su.isOnline, _su.packageid);
}

GroupInfo Convert::cv_group_to_client(chatGroup_with_members _cg)
{
	std::vector<int> ve;
	for (auto tmp : _cg.members)
	{
		ve.push_back(tmp);
	}
	return GroupInfo(_cg.chatGroupId, _cg.chatGroupName, "", "", ve);
}

MessageInfo Convert::cv_message_to_client(Message _mes)
{
	return MessageInfo(_mes.sender, _mes.receiver, _mes.content, 1, _mes.isToGroup == 1 ? 2 : 1, _mes.type == MsgType::MSGTYPE_TEXT ? 1 : (_mes.type == MsgType::MSGTYPE_FILE ? 2 : 3), DateTime(_mes.createdTime));
}

PacketInfo Convert::cv_packet_to_client(package _pa)
{
	return PacketInfo(_pa.packageName, _pa.packageid);
}

std::vector<MessageInfo> Convert::cv_vmessage_to_client(std::vector<Message> _vmes)
{
	std::vector<MessageInfo>ve;
	for (auto tmp : _vmes)
	{
		ve.push_back(cv_message_to_client(tmp));
	}
	return ve;
}

std::vector<GroupInfo> Convert::cv_vgroup_to_client(std::vector<chatGroup_with_members> _vcg)
{
	std::vector<GroupInfo> ve;
	for (auto tmp : _vcg)
	{
		ve.push_back(cv_group_to_client(tmp));
	}
	return ve;
}

std::vector<UserInfo> Convert::cv_vfriend_to_client(std::vector<Friend> _su)
{
	std::vector<UserInfo> ve;
	for (auto tmp : _su)
	{
		ve.push_back(cv_friend_to_client(tmp));
	}
	return ve;
}

std::vector<PacketInfo> Convert::cv_vpacket_to_client(std::vector<package> _pa)
{
	std::vector<PacketInfo> ve;
	std::cout<<_pa.size()<<std::endl;
	for (auto tmp : _pa)
	{
		ve.push_back(cv_packet_to_client(tmp));
	}
	std::cout<<ve.size()<<std::endl;
	return ve;
}

Message Convert::cv_message_to_server(MessageInfo _cmes)
{
	Message mes;
	mes.content = _cmes.getContent();
	mes.createdTime = _cmes.getCreateTime().getString();
	mes.id = _cmes.getMessageId();
	mes.isToGroup = _cmes.getType() == 2 ? 1 : 0;
	mes.sender = _cmes.getSenderId();
	mes.receiver = _cmes.getReceiverId();
	if (_cmes.getContentKind() == 1)
	{
		mes.type = MsgType::MSGTYPE_TEXT;
	}
	else if (_cmes.getContentKind() == 2)
	{
		mes.type = MsgType::MSGTYPE_FILE;
	}
	else if (_cmes.getContentKind() == 3)
	{
		mes.type = MsgType::MSGTYPE_IMAGE;
	}
	return mes;
}