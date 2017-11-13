#pragma once
#include"stdafx.h"
#include"NetException.h"

namespace HomeWork
{

	class CommandLine
	{
	public:
		CommandLine(const CommandLine&) = delete;
		CommandLine& operator=(const CommandLine&) = delete;
		CommandLine(void) = default;
		~CommandLine(void) = default;

		enum Size : int { ONE = 1 };

		static std::string CommandLine::GetCommandLineArgument(void){
			int argc = 0;
			auto	loc = ::CommandLineToArgvW(::GetCommandLineW(),
				&argc);

			if (!loc)
				throw HomeWork::CommandLineToArgvWEception("Error CommandLineToArgvW",
					GetLastError());

			if (argc <= ONE)
				throw  NofilenameException("Path empti", GetLastError());

			std::wstring wstr(loc[ONE]);

			std::string rez = HomeWork::Convert::UnicodeToAnsi(wstr, wstr.length());

			LocalFree(loc);
			return rez;
		}
	};
}