#pragma once
#include <iostream>
#include <vector>
#include "BankClient.h"
#include "ISyncPrimitive.h"

class CBank
{
public:
	CBank(size_t nClients, ISyncPrimitive & primitive);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	void WaitForClients();

private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_handles;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();

	const float LONG_OPERATIONS_DURATION = 3.f;
};