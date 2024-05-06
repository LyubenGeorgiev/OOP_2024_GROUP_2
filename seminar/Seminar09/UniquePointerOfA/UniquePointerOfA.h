#pragma once

struct A
{
	int a = 4;
	int b = 1;
};


class UniquePointerOfA
{
	A* ptr;

	void moveFrom(UniquePointerOfA&& other) noexcept;

public:
	UniquePointerOfA(A* ptr);
	UniquePointerOfA(const UniquePointerOfA& other) = delete;
	UniquePointerOfA& operator=(const UniquePointerOfA& other) = delete;

	UniquePointerOfA(UniquePointerOfA&& other) noexcept;
	UniquePointerOfA& operator=(UniquePointerOfA&& other) noexcept;

	A& operator*();
	const A& operator*() const;

	~UniquePointerOfA();
};
