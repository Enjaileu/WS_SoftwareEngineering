#pragma once

class IObserver {
public:

	virtual ~IObserver() {}

	virtual void OnNotify(int idEvent) = 0;
};