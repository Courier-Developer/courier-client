//
// Created by ervinxie on 9/2/19.
//

#ifndef COURIER_CLIENT_PREDECLARE_H
#define COURIER_CLIENT_PREDECLARE_H
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <vector>
#include "../../Logic_Part/Dealer.h"
#include "res/PixMan.h"
class Receiver;
class ThemeManage;

extern Dealer dealer;
extern Receiver* receiver;
extern ThemeManage* themeManage;

class MainWindow;
class SignUp;
class LogIn;

class ChatList;
class Chatting;
class ChatWindow;
class ShowMessage;
class ContactInfo;
class ContactList;
class ContactWindow;
class GroupContactInfo;

class OtherWindow;

#endif //COURIER_CLIENT_PREDECLARE_H
