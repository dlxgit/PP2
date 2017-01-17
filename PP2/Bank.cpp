#include "Bank.h"

CBank::CBank(size_t nClients)
{
	m_clients = std::vector<CBankClient>();
	for (size_t i = 0; i < nClients; ++i)
	{
		CreateClient();
	}
	m_totalBalance = 0;
	
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
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
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