#pragma once
#include "Student.h"

class Grade
{
	Student** students;
	unsigned studentsCount;
	unsigned groupCapacity;

	void moveFrom(Grade&& other) noexcept;
	void copyFrom(const Grade& other);
	void free();

	void resize(unsigned newCapacity);
	int getFirstFreeIndex() const;

public:
	Grade();
	Grade(const Grade& other);
	Grade& operator=(const Grade& other);

	Grade(Grade&& other) noexcept;
	Grade& operator=(Grade&& other) noexcept;

	void addStudent(const Student& other);
	void addStudent(Student&& other);

	void insertStudentAtIndex(unsigned index, const Student& other);
	void insertStudentAtIndex(unsigned index, Student&& other);

	void removeStudent(unsigned index);

	~Grade();
};