#include"stdafx.h"
#include"NetException.h"

namespace HomeWork
{
	NetException::NetException(IN const std::string& wsMsg,
		IN DWORD dwCode) : strMsg(wsMsg), dwCode(dwCode) { }


	const char*	NetException::what(void) const {
		return (this->strMsg = this->What()).c_str();
	}

	std::string NetException::What(void) const {
		LPVOID lpMsgBuf = nullptr;
		std::stringstream stream;
		stream << this->strMsg << std::endl;

		if (this->dwCode) {
			if (::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				0,
				this->dwCode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lpMsgBuf),
				0,
				0))
			{
				stream << reinterpret_cast<LPCWSTR>(lpMsgBuf) << std::endl;
				::LocalFree(lpMsgBuf);
			}
		}
		return stream.str();
	}

	DWORD NetException::GetErrorCode(void) const throw() {
		return this->dwCode;
	}
}
