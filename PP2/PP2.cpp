#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

int main()
{
	CBank* bank = new CBank();
	CBankClient* client1 = bank->CreateClient();
	CBankClient* client2 = bank->CreateClient();

	//fixed TODO: WaitForMultipleObjects
	while (true)
	{
		bank->WaitForClients();
	}

    return 0;
}