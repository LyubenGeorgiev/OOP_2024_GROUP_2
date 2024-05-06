#include "UniquePointerOfA.h"
#include <exception>

UniquePointerOfA::UniquePointerOfA(A* ptr) : ptr(ptr) { }

void UniquePointerOfA::moveFrom(UniquePointerOfA&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

A& UniquePointerOfA::operator*()
{
	return *ptr;
}

const A& UniquePointerOfA::operator*() const
{
	return *ptr;
}

UniquePointerOfA::~UniquePointerOfA()
{
	delete ptr;
}

UniquePointerOfA::UniquePointerOfA(UniquePointerOfA&& other) noexcept
{
	moveFrom(std::move(other));
}

UniquePointerOfA& UniquePointerOfA::operator=(UniquePointerOfA&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		moveFrom(std::move(other));
	}

	return *this;
}