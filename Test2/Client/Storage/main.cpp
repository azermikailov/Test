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
		// Считываю второй аргумент командной строки
		std::string sPath = HomeWork::CommandLine::GetCommandLineArgument();
		HomeWork::MyFile myfile(sPath);  // Создаю обет касса и передаю путь к файлу 
		myfile.OpenFile();               // Отёсываю файл здесь чтобы понять если такой вообще 

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
		client.Send(HomeWork::Convert::DataToVector(                   // Сначала отправляю размер файла и его имя 
			                   myfile.SizeFile(),              
			                   HomeWork::CutPath(myfile.GetPath()))); //  Обрезаю и получаю имя файла и формат
		Sleep(TEN); // Немножко подождёт

		int iread = 0;
		MyCRITICAL trycritical, recvcritical;
		std::vector<unsigned char> vec(ONE, '\0');

		while (!myfile.Feof()) {                // Пока не конец файла 
			if (trycritical.TryCritical()) {    // Чтобы не заходил без надобности 
				client.Send(myfile.Read(iread)); // Отправляю вектор байтов
				recvcritical.EnterCritical();
				client.Recv(vec);              // Жду пока сервер пришлет весточку что он записал и готов принимать дальше
				recvcritical.LeaveCritical();
				trycritical.LeaveCritical();   // Освобождаем право собственности на указанный объект критического раздела.
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

std::string HomeWork::CutPath(std::string path) { // Принемаю копию без ( const & )  для измениения 
	auto sizeslesh = path.rfind('\\');
	if (sizeslesh)
		path.erase(0, sizeslesh + ONE);
	return path;
}

