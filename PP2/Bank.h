#pragma once
#include <iostream>
#include <vector>
#include "BankClient.h"
#include "CCriticalSection.h"
#include "CEmptyPrimitive.h"
#include "CMutex.h"
#include "CSemaphore.h"
#include "CEvent.h"
#include <memory>

class CBank
{
public:
	CBank(size_t nClients, size_t param);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	void WaitForClients();

private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_handles;
	int m_totalBalance;
	std::unique_ptr<ISyncPrimitive> m_syncPrimitive;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();

	const float LONG_OPERATIONS_DURATION = 3.f;
};