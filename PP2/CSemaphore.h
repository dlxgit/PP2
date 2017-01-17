#pragma once
#include "ISyncPrimitive.h"

class CSemaphore : public ISyncPrimitive
{
public:
	CSemaphore() :
		m_primitive(CreateSemaphore(NULL, 1, 1, NULL))
	{

	}

	void Begin() override
	{
		WaitForSingleObject(m_primitive, INFINITE);
	}

	void End() override
	{
		ReleaseSemaphore(m_primitive, 1, NULL);
	}

private:
	HANDLE m_primitive;
};