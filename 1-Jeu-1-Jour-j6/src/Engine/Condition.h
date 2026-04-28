#pragma once

template<typename T>
class Condition
{
public:
	virtual bool Test(T* type) = 0;
};