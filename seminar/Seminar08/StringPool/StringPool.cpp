#include "StringPool.h"
#include <iostream>
#include <cstring>
#include <exception>

void StringPool::resize(size_t cap) {
	if (cap <= capacity)
		return;

	StringNode* newNodes = new StringNode[cap]{};
	for (size_t i = 0; i < size; i++){
        newNodes[i] = nodes[i];

    }
	delete[] nodes;
	nodes = newNodes;
	capacity = cap;
}

int StringPool::lowerBound(const char* str, bool& found) const {
	int left = 0;
	int right = size - 1;
	int leftmostIndex = -1;

	while (left <= right) {
		int mid = (right - left) / 2 + left;
		int cmp = strcmp(nodes[mid].data, str);

		if (cmp == 0) {
			found = true;
			return mid;
		}
		else if (cmp > 0) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
			leftmostIndex = mid;
		}
	}

	found = false;
	return leftmostIndex;
}

const char* StringPool::insert(const char* str, size_t index) {
	if (index > size)
		throw std::out_of_range("StringPool::insert invalid index!");

	if (size == capacity)
		resize(calculateGrowth());

	for (int i = size - 1; i >= (int)index; i--)
		nodes[i + 1] = nodes[i];

	nodes[index].allocateData(str);
	nodes[index].referenceCount = 1;

	++size;
	return nodes[index].data;
}

void StringPool::removeInternal(int idx)
{
	if (idx >= size)
		throw std::out_of_range("StringPool::removeInternal out of range!");
	
	delete[] nodes[idx].data;

	for (int i = idx; i < size - 1; i++)
		nodes[i] = nodes[i + 1];

	nodes[size - 1].data = nullptr;
	nodes[size - 1].referenceCount = 0;

	size--;
}

size_t StringPool::calculateGrowth() const {
	return capacity + capacity / 2;
}

StringPool::StringPool() : nodes(nullptr), size(0), capacity(0) {
	resize(8);
}

const char* StringPool::getString(const char* str) {
	bool found = false;
	int currentIndex = lowerBound(str, found);
	
	if (found)
	{
		nodes[currentIndex].referenceCount++;
		return nodes[currentIndex].data;
	}

	return insert(str, currentIndex + 1);
}

void StringPool::removeString(const char* str) {
	bool found = false;
	int idx = lowerBound(str, found);
	
	if (!found)
		return;
	
	if (nodes[idx].referenceCount == 1)
		removeInternal(idx);
	else
		nodes[idx].referenceCount--;
}

void StringPool::debug() const {
	for (size_t i = 0; i < size; i++) {
		std::cout << nodes[i].data << " ";
	}
	std::cout << std::endl;
}

StringPool::~StringPool() {
	for (size_t i = 0; i < size; i++)
		delete[] nodes[i].data;

	delete[] nodes;
}

StringPool::StringNode::StringNode() : data(nullptr), referenceCount(0) {}

void StringPool::StringNode::allocateData(const char* str)
{
	size_t len = strlen(str);
	data = new char[len + 1] {};
	strcpy(data, str);
}