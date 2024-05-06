#include "Grade.h"

void Grade::moveFrom(Grade&& other) noexcept
{
	students = other.students;
	other.students = nullptr;

	groupCapacity = other.groupCapacity;
	studentsCount = other.studentsCount;
	other.groupCapacity = other.studentsCount = 0;
}

void Grade::copyFrom(const Grade& other)
{
	groupCapacity = other.groupCapacity;
	studentsCount = other.studentsCount;

	students = new Student * [groupCapacity] {nullptr};

	for (size_t i = 0; i < groupCapacity; i++)
	{
		students[i] = new Student(*(other.students[i]));
	}
}

void Grade::free()
{
	for (size_t i = 0; i < groupCapacity; i++)
	{
		delete students[i];
	}

	delete[]students;

	studentsCount = groupCapacity = 0;
}

void Grade::resize(unsigned newCapacity)
{
	Student** temp = new Student*[newCapacity] {nullptr};

	for (size_t i = 0; i < groupCapacity; i++)
	{
		temp[i] = students[i];
	}

	delete[] students;
	students = temp;

	groupCapacity = newCapacity;
}

Grade::Grade()
{
	groupCapacity = 20;
	studentsCount = 0;

	students = new Student * [groupCapacity] {nullptr};
}

Grade::Grade(const Grade& other)
{
	copyFrom(other);
}

Grade& Grade::operator=(const Grade& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Grade::Grade(Grade&& other) noexcept
{
	moveFrom(std::move(other));
}
Grade& Grade:: operator=(Grade&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

int Grade::getFirstFreeIndex() const
{
	for (size_t i = 0; i < groupCapacity; i++)
	{
		if (!students[i])
		{
			return i;
		}
	}

	return -1;
}

void Grade::addStudent(const Student& other)
{
	if (studentsCount >= groupCapacity)
	{
		resize(groupCapacity * 2);
	}

	int index = getFirstFreeIndex();
	students[index] = new Student(other);
	studentsCount++;
}

void Grade::addStudent(Student&& other)
{
	if (studentsCount >= groupCapacity)
	{
		resize(groupCapacity * 2);
	}

	int index = getFirstFreeIndex();
	students[index] = new Student(std::move(other));
	studentsCount++;
}

void Grade::insertStudentAtIndex(unsigned index, const Student& other)
{
	if (index >= groupCapacity)
	{
		resize(index + 1);
	}

	if (!students[index])
	{
		students[index] = new Student(other);
		studentsCount++;
	}
	else
	{
		*(students[index]) = other;
	}
}

void Grade::insertStudentAtIndex(unsigned index, Student&& other)
{
	if (index >= groupCapacity)
	{
		resize(index + 1);
	}

	if (!students[index])
	{
		students[index] = new Student(std::move(other));
		studentsCount++;
	}
	else
	{
		*(students[index]) = std::move(other);
	}
}

void Grade::removeStudent(unsigned index)
{
	if (index >= groupCapacity)
	{
		throw std::out_of_range("No space!");
	}

	delete students[index];
	students[index] = nullptr;
	studentsCount--;
}

Grade::~Grade()
{
	free();
}