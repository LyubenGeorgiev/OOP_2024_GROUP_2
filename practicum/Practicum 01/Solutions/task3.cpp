#include <iostream>


enum class Degree {
    BACHELOR,
    MASTER,
    PHD,
    UNKNOWN,
};

struct Teacher {
    int id;
    Degree degree;
    int flunkedStudentsCount;
};

void initTeacher(Teacher &teacher, int id, Degree degree, int flunkedStudentsCount) {
    if (id < 10000 || id > 99999 || degree == Degree::UNKNOWN || flunkedStudentsCount < 0) {
        std::cout << "Invalid teacher!\n";
        return;
    }

    teacher = Teacher{id, degree, flunkedStudentsCount};
}

// Keep in mind we return literals so they won't go out of scope!!!
const char* printDegree(Degree degree) {
    switch (degree) {
    case Degree::BACHELOR:
        return "Bachelor";
    case Degree::MASTER:
        return "Master";
    case Degree::PHD:
        return "PhD";
    case Degree::UNKNOWN:
        return "Unknown";
    default:
        return "Error";
    }
}

void printTeacher(const Teacher &teacher) {
    std::cout << "Teacher{id: " << teacher.id
              << ", degree: " << printDegree(teacher.degree)
              << ", flunkedStudentsCount: " << teacher.flunkedStudentsCount << '}';
}

void readTeacher(Teacher &teacher) {
    // TODO
}

const int TEACHERS_COUNT = 10;

struct University {
    Teacher teachers[TEACHERS_COUNT];
    double averageFlunkedStudentsCount;
};

void readUniversity(University &university) {
    int totalFlunkedStudentsCount = 0;

    for (int i = 0; i < TEACHERS_COUNT; ++i) {
        readTeacher(university.teachers[i]);
        totalFlunkedStudentsCount += university.teachers[i].flunkedStudentsCount;
    }

    university.averageFlunkedStudentsCount = (double)totalFlunkedStudentsCount / TEACHERS_COUNT;
}

int bonusEligibleTeachersCount(const University &university, int minimumQuota) {
    int count = 0;

    for (int i = 0; i < TEACHERS_COUNT; ++i) {
        count += (university.teachers[i].flunkedStudentsCount >= minimumQuota);
    }

    return count;
}

void sortByFlunkedStudentsCountAscending(University &university) {
    for (int i = 0; i < TEACHERS_COUNT; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < TEACHERS_COUNT; ++j) {
            if (university.teachers[j].flunkedStudentsCount < university.teachers[minIndex].flunkedStudentsCount) {
                minIndex = j;
            }
        }

        std::swap(university.teachers[i], university.teachers[minIndex]);
    }
}