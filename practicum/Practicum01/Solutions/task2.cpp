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