//
// Created by Ԭ���� on 2019-09-03.
//

#include<vector>
#include<string>
#include<cstdio>
#include<fstream>
#include<istream>
#include<iterator>

#ifndef COURIER_CLIENT_MYFILE_H
#define COURIER_CLIENT_MYFILE_H

class MyFile {
private:
	int type;//2�ļ� 3ͼƬ
	std::string filepath;
	std::string filename;
	std::vector<char> vefile;
	std::string convertfilename(std::string _filepath)
	{
		std::string _filename;
		for (int i = _filepath.size() - 1; i >= 0; i--)
		{
			if (_filepath[i] == '\\'|| _filepath[i] == '/')
			{
				_filename = _filepath.substr(i + 1, _filepath.size() - 1);
				break;
			}
			if (!i)
			{
				_filename = _filepath;
			}
		}
		return _filename;
	}

	std::vector<char> convert_file(std::string filepath);

public:
	MyFile() { type = 2;  };

	MyFile(std::string _filepath, int _type);

	MyFile(int _type);

	void read_file(std::string _filepath);

	void save_file(std::string _filepath, std::vector<char> data);

	std::vector<char> getvefile();

	std::string getfilename();
};

#endif //COURIER_CLIENT_MYFILE_H
