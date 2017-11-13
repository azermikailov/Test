#pragma once
#include"stdafx.h"

namespace HomeWork
{
	class SizeFile
	{
		_finddata_t info;
		intptr_t handle;
	public:
		SizeFile(void){
			this->info = { 0 };
			this->handle = 0;
		}

		_fsize_t Size(const std::string& path)throw(){
			this->handle = _findfirst(path.c_str(), &this->info);
			return info.size;
		}

		~SizeFile(void){
			if(this->handle)
			_findclose(this->handle);
		}
	};
}
