#ifndef FEVERRPC_UTILS_H_
#define FEVERRPC_UTILS_H_

#include "msgpack.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

struct Login {
    string username;
    string password;
    string ip;
    MSGPACK_DEFINE(username, password,ip);
};

vector<char> read_file(string file_name);
void save_file(string file_name, vector<char> &data);
int login(Login);

#endif // FEVERRPC_UTILS_H_