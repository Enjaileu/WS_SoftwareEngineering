#include "ISubject.h"

void ISubject::AddObserver(IObserver* observer) {
	observers.push_back(observer);
}

void ISubject::RemoveObserver(IObserver* observer) {
	auto iter = std::find(begin(observers), end(observers), observer);
	if (iter != end(observers)) {
		std::iter_swap(iter, end(observers) - 1);
		observers.pop_back();
	}
}
