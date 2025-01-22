#include <iostream>

using namespace std;

struct Video {
    char title[256];
    char director[256];
    char genre[256];
    double popularityRating;
    double price;
};

int stringCompare(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
Video* searchByTitle(Video* videos, int size, const char* title) {
    for (int i = 0; i < size; ++i) {
        if (stringCompare(videos[i].title, title) == 0) {
            return &videos[i];
        }
    }
    return nullptr;
}
void searchByGenre(Video* videos, int size, const char* genre, Video** results, int& resultsSize) {
    resultsSize = 0;
    for (int i = 0; i < size; ++i)
    {
        if (stringCompare(videos[i].genre, genre) == 0)
        {
            results[resultsSize] = &videos[i];
            resultsSize++;
        }
    }
}
void searchByDirector(Video* videos, int size, const char* director, Video** results, int& resultsSize) {
    resultsSize = 0;
    for (int i = 0; i < size; ++i) {
        if (stringCompare(videos[i].director, director) == 0) {
            results[resultsSize] = &videos[i];
            resultsSize++;
        }
    }
}
Video* findMostPopularInGenre(Video* videos, int size, const char* genre) {
    Video* mostPopular = nullptr;
    double maxRating = -1.0e30; 

    for (int i = 0; i < size; ++i) {
        if (stringCompare(videos[i].genre, genre) == 0) {
            if (videos[i].popularityRating > maxRating) {
                maxRating = videos[i].popularityRating;
                mostPopular = &videos[i];
            }
        }
    }
    return mostPopular;
}
void displayAllVideos(Video* videos, int size) {
    cout << "Все фильмы:\n";
    for (int i = 0; i < size; ++i) {
        cout << "  Название: " << videos[i].title << "\n";
        cout << "  Режиссер: " << videos[i].director << "\n";
        cout << "  Жанр: " << videos[i].genre << "\n";
        cout << "  Рейтинг: " << videos[i].popularityRating << "\n";
        cout << "  Цена: " << videos[i].price << "$\n\n";
    }
}

void displayAllGenre(Video* videos, int size) {
    cout << "Все жанры:\n";
    for (int i = 0; i < size; ++i) {
        
        cout << "  Жанр: " << videos[i].genre << "\n";
    }
}

int main() {
    setlocale(LC_ALL,"ru");


    Video videoStore[5] = {
       {"The_Shawshank_Redemption", "Frank_Darabont", "Drama", 9.3, 15.99},
        {"The_Dark_Knight", "Christopher_Nolan", "Action", 9.0, 19.99},
        {"Pulp_Fiction", "Quentin_Tarantino", "Crime", 8.9, 14.50},
        {"The_Godfather", "Francis_Ford_Coppola", "Crime", 9.2, 18.75},
        {"The_Dark_Knight_Rises", "Christopher_Nolan", "Action", 8.4, 17.00}
    };

    int videoStoreSize = 5;

    int choice;
    do {
        cout << "Меню:\n";
        cout << "1. Показать все фильмы\n";
        cout << "2. Поиск фильма по названию\n";
        cout << "3. Поиск фильма по жанру\n";
        cout << "4. Поиск фильма по режиссеру\n";
        cout << "5. Поиск самого популярного фильма в жанре\n";
        cout << "6. показать все жанры\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllVideos(videoStore, videoStoreSize);
            break;
        case 2: {
            char searchTitle[256];
            cout << "Введите название фильма для поиска: ";
            cin >> searchTitle;

            Video* foundMovie = searchByTitle(videoStore, videoStoreSize, searchTitle);

            if (foundMovie == nullptr) {
                cout << "Фильм с названием '" << searchTitle << "' не найден.\n";
            }
            else {
                cout << "Найденный фильм (по названию):\n";
                cout << "  Название: " << foundMovie->title << "\n";
                cout << "  Режиссер: " << foundMovie->director << "\n";
                cout << "  Жанр: " << foundMovie->genre << "\n";
                cout << "  Рейтинг: " << foundMovie->popularityRating << "\n";
                cout << "  Цена: " << foundMovie->price << "$\n\n";
            }
            break;
        }
        case 3: {
            char searchGenre[256];
            cout << "Введите жанр для поиска: ";
            cin >> searchGenre;

            Video* genreSearchResults[5];
            int genreResultsSize;
            searchByGenre(videoStore, videoStoreSize, searchGenre, genreSearchResults, genreResultsSize);

            if (genreResultsSize == 0) {
                cout << "Фильмы с жанром '" << searchGenre << "' не найдены.\n";
            }
            else {
                cout << "Найденные фильмы (по жанру):\n";
                for (int i = 0; i < genreResultsSize; i++) {
                    cout << "  Название: " << genreSearchResults[i]->title << "\n";
                    cout << "  Режиссер: " << genreSearchResults[i]->director << "\n";
                    cout << "  Жанр: " << genreSearchResults[i]->genre << "\n";
                    cout << "  Рейтинг: " << genreSearchResults[i]->popularityRating << "\n";
                    cout << "  Цена: " << genreSearchResults[i]->price << "$\n\n";
                }
            }
            break;
        }
        case 4: {
            char searchDirector[256];
            cout << "Введите режиссера для поиска: ";
            cin >> searchDirector;

            Video* directorSearchResults[5];
            int directorResultsSize;
            searchByDirector(videoStore, videoStoreSize, searchDirector, directorSearchResults, directorResultsSize);

            if (directorResultsSize == 0) {
                cout << "Фильмы с режиссером '" << searchDirector << "' не найдены.\n";
            }
            else {
                cout << "Найденные фильмы (по режиссеру):\n";
                for (int i = 0; i < directorResultsSize; i++) {
                    cout << "  Название: " << directorSearchResults[i]->title << "\n";
                    cout << "  Режиссер: " << directorSearchResults[i]->director << "\n";
                    cout << "  Жанр: " << directorSearchResults[i]->genre << "\n";
                    cout << "  Рейтинг: " << directorSearchResults[i]->popularityRating << "\n";
                    cout << "  Цена: " << directorSearchResults[i]->price << "$\n\n";
                }
            }
            break;
        }
        case 5: {
            char popularGenre[256];
            cout << "Введите жанр для поиска самого популярного фильма: ";
            cin >> popularGenre;

            Video* mostPopularMovie = findMostPopularInGenre(videoStore, videoStoreSize, popularGenre);

            if (mostPopularMovie == nullptr) {
                cout << "Фильмы с жанром '" << popularGenre << "' не найдены.\n";
            }
            else {
                cout << "Самый популярный фильм в жанре '" << popularGenre << "':\n";
                cout << "  Название: " << mostPopularMovie->title << "\n";
                cout << "  Режиссер: " << mostPopularMovie->director << "\n";
                cout << "  Жанр: " << mostPopularMovie->genre << "\n";
                cout << "  Рейтинг: " << mostPopularMovie->popularityRating << "\n";
                cout << "  Цена: " << mostPopularMovie->price << "$\n\n";
            }
            break;
        }
        case 6:
            displayAllGenre(videoStore, videoStoreSize);
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    } while (choice != 0);

    return 0;
}