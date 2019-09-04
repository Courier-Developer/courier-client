//
// Created by Ô¬ÈðÔó on 2019-09-03.
//

#include"MyFile.h"

void MyFile::read_file(std::string _filepath)
{
	std::vector<char> vechar = convert_file(_filepath);
	if (!vechar.size())
	{
		return;
	}
	this->filepath = _filepath;
	this->filename = convertfilename(_filepath);
	vefile = vechar;
}

std::vector<char> MyFile::convert_file(std::string _filepath)
{
	std::ifstream file(_filepath, std::ios::binary);
	// Stop eating new lines in binary mode!!!
	std::vector<char> vec;
	if (!file)
	{
		printf("no file to read\n");
		return vec;
	}
	file.unsetf(std::ios::skipws);
	long fileSize;
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	vec.reserve(fileSize);
	std::istream_iterator<char> it(file), eos;
	copy(it, eos, inserter(vec, vec.begin()));
	file.close();
	return vec;
}

void MyFile::save_file(std::string _filepath, std::vector<char> data)
{
	if (!data.size())
	{
		printf("no file to save\n");
		return;
	}
	_filepath = "./file/" + _filepath;
	this->filepath = _filepath;
	std::ofstream file(filepath, std::ios::out | std::ios::binary);
	file.write((const char*)&data[0], data.size());
	file.close();
}

MyFile::MyFile(std::string _filepath, int _type)
{
	read_file(_filepath);
	type = _type;
}

MyFile::MyFile(int _type)
{
	type = _type;
}

std::vector<char> MyFile::getvefile()
{
	return vefile;
}

std::string MyFile::getfilename()
{
	return filename;
}