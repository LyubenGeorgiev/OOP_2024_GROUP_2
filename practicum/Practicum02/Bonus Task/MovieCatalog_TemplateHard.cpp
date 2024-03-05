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
}

SafeAnswer averagePrice(const char* catalogName){
}

SafeAnswer getMoviePrice(const char* catalogName, const char* movieName){
}

Movie readMovie(){ //добавете аргумент - файлов поток за четене
}

Movie* saveMoviesInArray(std::ifstream& file, int numberOfMovies){
    return nullptr;
}

void freeMoviesFromArray(){ // добавете нужните аргументи
}


void sortMoviesInArray(){ // добавете нужните аргументи
    //Selection sort
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