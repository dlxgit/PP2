#include "Bank.h"

CBank::CBank(size_t nClients, size_t param)
{
	m_clients = std::vector<CBankClient>();
	for (size_t i = 0; i < nClients; ++i)
	{
		CreateClient();
	}
	m_totalBalance = 0;
	switch (param)
	{
	case 1:
		m_syncPrimitive = std::make_unique<CCriticalSection>();
		break;
	case 2:
		m_syncPrimitive = std::make_unique<CMutex>();
		break;
	case 3:
		m_syncPrimitive = std::make_unique<CEvent>();
		break;
	default:
		m_syncPrimitive = std::make_unique<CEmptyPrimitive>();
		break;
	}
}

void CBank::WaitForClients()
{
	WaitForMultipleObjects(m_handles.size(), m_handles.data(), TRUE, INFINITE);
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	m_handles.push_back(CreateThread(NULL, 0, client->ThreadFunction, client, 0, NULL));
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	m_syncPrimitive->Begin();
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;
	int requiredBalance = totalBalance + value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (requiredBalance < 0)
	{
		std::cout << "! ERROR !" << std::endl;
	}
	else
	{
		SetTotalBalance(requiredBalance);
	}

	m_syncPrimitive->End();
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}


void CBank::SomeLongOperations()
{
	Sleep(LONG_OPERATIONS_DURATION);
}