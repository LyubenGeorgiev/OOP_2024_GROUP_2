#pragma once
#include "StringView.h"

class FilePath
{
	StringView name;
	StringView extension;

public:
	FilePath(const MyString& fileName);
	const StringView& getName() const;
	const StringView& getExtension() const;
};

