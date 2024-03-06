#include<iostream>
#include<fstream>

enum class Major{
    Se, 
    Is, 
    Cs,
    I
};

struct Student{
    char name[1024];
    int age;
    Major major;
};

void saveStudentToFile(std::ofstream& file, const Student& st){
    file << st.name       << std::endl;
    file << st.age        << std::endl;
    file << (int)st.major << std::endl;
}

void writeStudentsToFile(const char* fileName, const Student* students, int sz){
    std::ofstream file(fileName);

    if(!file.is_open()){
        return;
    }
    file << sz << std::endl;
    for(unsigned int i = 0; i < sz; i++){
        saveStudentToFile(file, students[i]);
    }

    file.close();
}

void readStudent(std::ifstream& file, Student& st){
    file.getline(st.name, 1024);

    file>>st.age;
    file.ignore();

    int majorInt;
    file>>majorInt;
    st.major = (Major)majorInt;
    file.ignore();
}

Student* readStudentsFromFile(const char* fileName, int& sz){
    std::ifstream file(fileName);

    if(!file.is_open()){
        return nullptr;
    }

    file >> sz;
    file.ignore();

    Student* result = new Student[sz];
    for(unsigned int i = 0; i < sz; i++){
        readStudent(file, result[i]);
    }

    file.close();
    return result;
}

int main(){
    Student st[2] = { "Ivan",  34, Major::Se,
			          "Petur", 20, Major::Is };

	writeStudentsToFile("students.txt", st, 2);

	int size;
	Student* result = readStudentsFromFile("students.txt", size);

	for (int i = 0; i < size; i++)
		std::cout << result[i].name << " " << result[i].age <<" " << (int)result[i].major << std::endl;
        delete[] result;
}