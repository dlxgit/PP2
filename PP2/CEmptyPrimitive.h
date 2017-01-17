#pragma once
#include "ISyncPrimitive.h"

class CEmptyPrimitive :public ISyncPrimitive
{
public:
	CEmptyPrimitive() {};
	
	void Begin() override {};

	void End() override {};
};
