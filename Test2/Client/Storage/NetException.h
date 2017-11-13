#pragma once
#include <exception>
#include <string>
#include <sstream>

namespace HomeWork
{
	class NetException :public std::exception
	{
	protected:
		mutable std::string strMsg;
		DWORD dwCode;
	public:
		NetException(IN const std::string&, IN DWORD);

		const char* NetException::what(void)const override;


		virtual std::string What(void) const;

		DWORD NetException::GetErrorCode(void) const throw();
	};

	class CommandLineToArgvWEception :public NetException
	{
	public:
		CommandLineToArgvWEception(IN const std::string& strMsg, IN DWORD iCode) :
			NetException(strMsg, iCode) { }
		virtual ~CommandLineToArgvWEception() { }
	};

	class WideCharToMultiByteException :public NetException
	{
	public:
		WideCharToMultiByteException(IN const std::string& strMsg, IN DWORD iCode) :
			NetException(strMsg, iCode) { }
		virtual ~WideCharToMultiByteException() { }
	};


	class NofilenameException :public NetException
	{
	public:
		NofilenameException(IN const std::string& strMsg, IN DWORD iCode) :
			NetException(strMsg, iCode) { }
		virtual ~NofilenameException() { }
	};


	class OpenFileException :public NetException
	{
	public:
		OpenFileException(IN const std::string& strMsg, IN DWORD iCode) :
			NetException(strMsg, iCode) { }
		virtual ~OpenFileException(void) { }
	};

	class ConvertException : public NetException
	{
	public:

		explicit ConvertException(IN const std::string& wsMsg,
			IN DWORD dwCode) : NetException(wsMsg, dwCode) { }
		virtual ~ConvertException(void) { }
	};

}
