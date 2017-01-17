#pragma once
#include <windows.h>


class ISyncPrimitive
{
public:
	ISyncPrimitive()
	{

	}
	
	virtual void Begin() = 0;
	virtual void End() = 0;
};