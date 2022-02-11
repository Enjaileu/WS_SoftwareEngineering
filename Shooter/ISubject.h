#pragma once
#include "IObserver.h"
#include <vector>

class ISubject
{
public:
	~ISubject() {}

	virtual void AddObserver(IObserver* observer) = 0;
	virtual void RemoveObserver(IObserver* observer) = 0;
	virtual void Notify() = 0;

protected :
	std::vector<IObserver*> observers;
};

