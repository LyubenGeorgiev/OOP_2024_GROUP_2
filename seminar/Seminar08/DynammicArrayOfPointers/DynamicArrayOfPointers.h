#include <iostream>

struct A
{
	int x = 3;
	int y = 2;
};

class DynamicArrayOfPointers {
	A** _data;
	size_t _capacity; 
	size_t _count = 0; 

	void free();
	void copyFrom(const DynamicArrayOfPointers& other);

	void resize(size_t newCap);

public:
	DynamicArrayOfPointers();
	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers& operator=(const DynamicArrayOfPointers& other);
	~DynamicArrayOfPointers();

	void pushBack(const A& current);
	void popBack();
	void removeAt(size_t index);

	size_t size() const;
	const A& operator[](size_t index) const;
	A& operator[](size_t index);
};