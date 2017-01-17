#pragma once
#include "ISyncPrimitive.h"

class CMutex : public ISyncPrimitive
{
public:
	CMutex() :
		m_primitive(CreateMutex(NULL, false, NULL))
	{

	}

	void Begin() override
	{
		WaitForSingleObject(m_primitive, INFINITE);
	}

	void End() override
	{
		ReleaseMutex(m_primitive);
	}

private:
	HANDLE m_primitive;
};