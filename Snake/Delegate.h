#pragma once
#include <functional>

template <class T>
class Delegate {
public:
	Delegate(std::function<T(T)>& fn) : fn(fn) {}
	void invoke(T t) {
		fn(t);
	}
private:
	std::function<T(T)> fn;
};
