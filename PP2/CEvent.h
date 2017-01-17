#pragma once
#include "ISyncPrimitive.h"

class CEvent : public ISyncPrimitive
{
public:
	CEvent() :
		m_primitive(CreateEvent(NULL, false, true, NULL))
	{

	}

	void Begin() override
	{
		WaitForSingleObject(m_primitive, INFINITE);
	}

	void End() override
	{
		SetEvent(m_primitive);
	}

private:
	HANDLE m_primitive;
};