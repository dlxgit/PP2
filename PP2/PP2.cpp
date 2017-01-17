#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>
#include "CCriticalSection.h"
#include "CEmptyPrimitive.h"
#include "ISyncPrimitive.h"
#include "CEvent.h"
#include "CMutex.h"
#include "CSemaphore.h"

using namespace std;


void ShowUsageInfo()
{
	cout << "Using: PP2.exe \"nClients\" \"syncPrimitive\"" << endl;
	cout << "syncPrimitive is optional parameter. you can input:" << endl;
	cout << "0 - for " << endl;
	cout << "1 - critical section" << endl;
	cout << "2 - mutex" << endl;
	cout << "3 - semafor" << endl;
	cout << "4 - event" << endl;
}


bool HandleUserInput(int argc, char * argv[], size_t & nClients, size_t & primitiveType)
{
	if (argc > 3 || argc == 1 || argc == 2 && argv[1] == "/?")
	{
		ShowUsageInfo();
		return false;
	}

	try
	{
		nClients = std::stoi(argv[1]);
		primitiveType = std::stoi(argv[1]);
		if (nClients < 1 || nClients > 4)
		{
			throw std::invalid_argument("incorrect value of syncPrimitiveType");
		}
	}
	catch (const std::exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	if (argc == 2 || argc == 3)
	{
		return true;
	}
}

int main(int argc, char * argv[])
{	
	argc = 3;
	argv[1] = "3";
	argv[2] = "2";
	size_t nClients;
	size_t primitiveType;
	

	if (!HandleUserInput(argc, argv, nClients, primitiveType))
	{
		return 1;
	}

	CBank bank(nClients, primitiveType);
	
	bank.WaitForClients();

    return 0;
}