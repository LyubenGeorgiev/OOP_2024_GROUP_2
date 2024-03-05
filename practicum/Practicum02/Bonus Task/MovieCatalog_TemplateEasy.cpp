#include<iostream>
#include<cstring>
#include<fstream>

enum class ErrorInCatalog{
    catalog_not_open,
    read_from_empty_catalog,
    movie_not_in_catalog,
    no_error_occurred
};

struct SafeAnswer{
    int number;
    ErrorInCatalog error;
};

struct Movie{
    char name[128];
    unsigned int price;
};

SafeAnswer getNumberOfMovies(const char* catalogName){
    SafeAnswer answer;
    //Упътване: Намерете броят на редовете във файла
    return answer;
}

SafeAnswer averagePrice(const char* catalogName){
    SafeAnswer answer;
    // 1. Отоворете файлов поток за четене, който приема аргумент catalofName
    // 2. Проверете дали се е отворил файловият поток за четене с is_open()
    //   Ако файловият поток, не се е отоворил успеш върнете answer с грешка
    //   catalog_not_open
    // 3. Създайте променливи, където ще съхранявате сумата на цените и броят 
    //   на всички филми
    // 4. Започнете да четете от файла (файловия поток за четене) с оператор ">>"
    //    Оператор >> взема входа форматирано. Четете име на файл и цена заедно
    //    file >> <име-на-файл> >> <цена>;
    //    По този начин четете за 1 итерация 1 ред => броят на редовете = броят на итерациите
    // 5. Преди да върнете отговор, проверете дали броят на редовере > 0
    //    Ако броят на редовете е 0, то няма нищо във файла и върнете в answer 
    //    грешка read_from_empty_catalog
    // 6. Запишете резултата в answer (грешката е no_error_occurred)
    return answer;
}

SafeAnswer getMoviePrice(const char* catalogName, const char* movieName){
    SafeAnswer answer;
    // Първите две стъпки са аналогични на стъпките от averagePrice
    // Започнете да четете от файла (файловия поток за четене) с оператор ">>"
    // Оператор >> взема входа форматирано. Четете име на файл и цена заедно
    // file >> <име-на-файл> >> <цена>;
    // Ако името на файла е същото като movieName, върнете отговор като от 
    // точка 6 в averagePrice
    // Ако не намерите movieName в каталога, върнете answer с грешка
    // movie_not_in_catalog
    return answer;
}

Movie readMovie(std::ifstream& file){
    Movie movie;
    return movie;
}

Movie* saveMoviesInArray(std::ifstream& file, int numberOfMovies){
    return nullptr;
}

void freeMoviesFromArray(Movie*& moviesArray){
}


void sortMoviesInArray(Movie*& moviesArray, int numberOfMovies){
    // Selection sort
    // Използвайте алгоритъма на пряката селекция.
    // 1. Намирате индекса на най-малкия елемент в подмасива [i; numberOfMovies],
    //    където i е индексът на текущия елемент от масива. 
    // 2. Разменяте елемента на текущата позиция с елемента с най-малка стойнсот 
    //    в подмасива [i; numberOfMovies]
}

ErrorInCatalog saveMoviesSorted(const char* catalogName, const char* catalogSortedName){
    // Ако файл, отворен с файлов поток за писане, не съществува, то той се създава 
    // Първо намерете колко филма има във файла с име catalogName 
    // след това продължете с имплементацията на функцията

    // Погледнете примера за писане във файл
    return ErrorInCatalog::no_error_occurred;
}

int main(){
    SafeAnswer safeNumberOfMovies = getNumberOfMovies("movieCatalog.txt");
    if(safeNumberOfMovies.error == ErrorInCatalog::no_error_occurred){
        std::cout<<"The number of movies is: "<< safeNumberOfMovies.number << std::endl;
    }
    SafeAnswer safeAveragePrice = averagePrice("movieCatalog.txt");
    if(safeAveragePrice.error == ErrorInCatalog::no_error_occurred){
        std::cout<<"The average price is: "<< safeAveragePrice.number << std::endl;
    }

    SafeAnswer safePrice = getMoviePrice("movieCatalog.txt", "Black-bullet");
    if(safePrice.error == ErrorInCatalog::no_error_occurred){
        std::cout<<"The price for the Black bullet movies is: " << safePrice.number << std::endl;
    }

    ErrorInCatalog errorSorting = saveMoviesSorted("movieCatalog.txt", "movieCatalogSorted.txt");
    if(errorSorting == ErrorInCatalog::no_error_occurred){
        std::cout<<"Look the content of the movieCatalogSorted.txt file" << std::endl;
    }
}