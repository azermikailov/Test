#pragma once

#include"stdafx.h"
#include"WrapFile.h"
#include"SizeFile.h"
#include"MyCRITICAL.h"
namespace HomeWork
{
	class MyFile
	{
		HomeWork::WrapFile wrap;
		std::string path;
	public:
		enum { MYSIZE_F = 4096  };
		MyFile(const std::string&);

		const std::string GetPath(void)const throw();
		void OpenFile(void);
		unsigned long SizeFile(void) throw();

		int Feof(void) throw()
		{
			return ::feof(this->wrap);
		}

		std::vector<unsigned char> Read(int&);

		MyFile& operator =(const MyFile&) = default;
		MyFile(const MyFile&) = default;
	};

}