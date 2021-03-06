// laba5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <allocators>
#include <mutex>
#include <vector>
#include <string>
#include <Windows.h>
#include <valarray>

int main()
{
	setlocale(LC_ALL, "Russian");
	int readerCount, writerCount, writerIntensity, writeTime, readerIntensity, readTime;
	std::cout << "Введите количество читателей" << std::endl;
	std::cin >> readerCount; //читателей
	std::cout << "Введите количество писателей" << std::endl;
	std::cin >> writerCount; //писателей
	std::cout << "Введите интенсивность писателей" << std::endl;
	std::cin >> writerIntensity;
	std::cout << "Введите время записи" << std::endl;
	std::cin >> writeTime;
	std::cout << "Введите интенсивность читателей" << std::endl;
	std::cin >> readerIntensity;
	std::cout << "Введите время чтения" << std::endl;
	std::cin >> readTime;

	int data = 0;
	bool possibleToRead = true, possibleToWrite = true;
	std::mutex lock;

	auto lambdaReader = [&] (int id) mutable ->  void
	{
		int currrentid = id;
		bool wait = false;
		while (true)
		{
			if (!wait)
			{
				std::cout << "Читатель " + std::to_string(currrentid) + " обратился к данным" << std::endl;
			}
			if (possibleToRead)
			{
				possibleToWrite = false;
				std::cout << "Читатель " + std::to_string(currrentid) + " получил доступ к данным" << std::endl;
				Sleep(readTime);
				std::cout << "Читатель " + std::to_string(currrentid) + " прочитал данные со значением " + std::to_string(data) << std::endl;
				wait = false;
				possibleToWrite = true;
			}
			else
			{
				if (!wait)
				{
					std::cout << "Читатель " + std::to_string(currrentid) + " ожидает, доступ заблокирован " << std::endl;
				}
				wait = true;
				continue;
			}
			Sleep(readerIntensity);
		}
	};

	auto lambdaWriter = [&](int id) mutable -> void
	{
		int currrentid = id;
		bool wait = false;
		bool waitReaders = false;
		while (true)
		{
			if (!wait)
			{
				std::cout << "Писатель " + std::to_string(currrentid) + " обратился к данным" << std::endl;
			}
			if (!lock.try_lock())
			{
				if (!wait)
				{
					std::cout << "Другой писатель обратился к данным раньше, писатель " + std::to_string(currrentid) + " ожидает" << std::endl;
				}
				wait = true;
				continue;
			}
			else
			{
				possibleToRead = false;
				while (!possibleToWrite)
				{
					if (!waitReaders)
					{
						std::cout << "Писатель " + std::to_string(currrentid) + " ожидает пока активные читатели закончат работу с данными" << std::endl;
						waitReaders = true;
					}
				}
				
				std::cout << "Писатель " + std::to_string(currrentid) + " получил доступ к данным" << std::endl;
				Sleep(writeTime);
				data ++;
				std::cout << "Писатель " + std::to_string(currrentid) + " изменил значние данных на " + std::to_string(data) << std::endl;
				waitReaders = false;
				wait = false;
				possibleToRead = true;
				lock.unlock();
				Sleep(writerIntensity);
			}
		}
	};

	std::vector<std::thread> threads;
	for (auto i = 0; i < writerCount; i++)
	{
		threads.push_back(std::thread(lambdaWriter, i));
	}

	for (auto i = 0; i < readerCount; i ++)
	{
		threads.push_back(std::thread(lambdaReader, i));
	}

	
	system("PAUSE");
    return 0;
}

