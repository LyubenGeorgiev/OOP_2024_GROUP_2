#pragma once
#include <cstddef>

class StringPool {
private:
	struct StringNode {
		char* data;
		size_t referenceCount;

		StringNode();
		StringNode(const StringNode&) = delete;
		StringNode& operator=(const StringNode&) = default;

		void allocateData(const char* str);

		~StringNode() = default;
	};

	StringNode* nodes;
	size_t size;
	size_t capacity;

	void resize(size_t cap);

	int lowerBound(const char* str, bool& found) const;
	const char* insert(const char* str, size_t index);
	
	void removeInternal(int idx);

	size_t calculateGrowth() const;

public:
	StringPool();
	StringPool(const StringPool&) = delete;
	StringPool operator=(const StringPool&) = delete;

	const char* getString(const char* str);
	void removeString(const char* str);

	void debug() const;

	~StringPool();
};