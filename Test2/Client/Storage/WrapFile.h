#pragma once

#include"stdafx.h"

namespace HomeWork
{
	class WrapFile
	{
		FILE* f = nullptr;
	public:
		WrapFile(FILE* f = nullptr) : f(f) { }

		~WrapFile(void){
			if (this->f)
				fclose(f);
		}

		operator FILE** (void) throw(){
			return &this->f;
		}

		operator FILE* (void) throw(){
			return this->f;
		}

		WrapFile(const WrapFile &) = delete;
		WrapFile & operator=(const WrapFile &) = delete;
	};
}