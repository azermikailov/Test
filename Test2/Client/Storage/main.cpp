#include "stdafx.h"

namespace HomeWork
{
	enum { ONE = 1,TEN = 10,};
	void Work(HomeWork::TcpClient, HomeWork::MyFile&);
	std::string CutPath(std::string);
}

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		SetConsoleTitleW(L" Client ");
		// �������� ������ �������� ��������� ������
		std::string sPath = HomeWork::CommandLine::GetCommandLineArgument();
		HomeWork::MyFile myfile(sPath);  // ������ ���� ����� � ������� ���� � ����� 
		myfile.OpenFile();               // ������� ���� ����� ����� ������ ���� ����� ������ 

		HomeWork::TcpClient client;
		client.Init();
		client.Connect();
		HomeWork::Work(std::move(client), myfile);
	}
	catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception" << std::endl;
	}
	return 0;
}

void HomeWork::Work(HomeWork::TcpClient client, HomeWork::MyFile& myfile)
{
	HomeWork::MyCRITICAL critical;
	try
	{
		critical.EnterCritical();
		client.Send(HomeWork::Convert::DataToVector(                   // ������� ��������� ������ ����� � ��� ��� 
			                   myfile.SizeFile(),              
			                   HomeWork::CutPath(myfile.GetPath()))); //  ������� � ������� ��� ����� � ������
		Sleep(TEN); // �������� �������

		int iread = 0;
		MyCRITICAL trycritical, recvcritical;
		std::vector<unsigned char> vec(ONE, '\0');

		while (!myfile.Feof()) {                // ���� �� ����� ����� 
			if (trycritical.TryCritical()) {    // ����� �� ������� ��� ���������� 
				client.Send(myfile.Read(iread)); // ��������� ������ ������
				recvcritical.EnterCritical();
				client.Recv(vec);              // ��� ���� ������ ������� �������� ��� �� ������� � ����� ��������� ������
				recvcritical.LeaveCritical();
				trycritical.LeaveCritical();   // ����������� ����� ������������� �� ��������� ������ ������������ �������.
			} 
		}
		client.Disconnect();
		critical.LeaveCritical();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception" << std::endl;
	}
}

std::string HomeWork::CutPath(std::string path) { // �������� ����� ��� ( const & )  ��� ���������� 
	auto sizeslesh = path.rfind('\\');
	if (sizeslesh)
		path.erase(0, sizeslesh + ONE);
	return path;
}

