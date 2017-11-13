#include "stdafx.h"
#include "MyFile.h"

namespace HomeWork
{
	MyFile::MyFile(const std::string&path):path(path)
	{
	}

	void MyFile::OpenFile(void){
		if (fopen_s(this->wrap, this->path.c_str(),"rb"))
			throw HomeWork::OpenFileException("Error Open File ", GetLastError());
	}
	
	unsigned long MyFile::SizeFile(void) throw(){
		HomeWork::SizeFile sizeFile;
		return  sizeFile.Size(this->path);
	}

	const std::string MyFile::GetPath(void) const throw() {
		return this->path;
	}

	std::vector<unsigned char> MyFile::Read(int& iRead){
		std::vector<unsigned char>vec(this->MYSIZE_F, '\0');
			iRead = ::fread(&vec[0],
			sizeof(unsigned char),
			vec.size(),
			this->wrap);
			vec.resize(iRead);
		return vec;
	}
}