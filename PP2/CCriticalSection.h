#pragma once
#include "ISyncPrimitive.h"

class CCriticalSection : public ISyncPrimitive
{
public:
	CCriticalSection()		
	{
		InitializeCriticalSection(&m_primitive);
	}

	void Begin() override
	{
		EnterCriticalSection(&m_primitive);
	}

	void End() override
	{
		LeaveCriticalSection(&m_primitive);
	}

private:
	CRITICAL_SECTION m_primitive;
};