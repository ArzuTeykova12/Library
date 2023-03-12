#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include<locale>

using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    string isbn;
    string title;
    string author;
    string genre;
    double price;
    int year;
};

Book books[MAX_BOOKS];
int num_books = 0;
int books_count = 0;

// Функция за четене на информацията за книгите от файл
void read_books() {
    ifstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "Грешка при отварянето на файла." << endl;
        return;
    }
    string isbn, title, author, genre;
    double price;
    int year;
    while (file >> isbn >> title >> author >> genre >> price >> year) {
        Book book = { isbn, title, author, genre, price, year };
        books[num_books++] = book;
    }

    file.close();
}

// Функция за записване на информацията за книгите във файл
void write_books() {
    ofstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "Грешка при отварянето на файла." << endl;
        return;
    }
    for (int i = 0; i < num_books; i++) {
        file << books[i].isbn << " " << books[i].title << " " << books[i].author << " " << books[i].genre << " " << books[i].price << " " << books[i].year << endl;
    }

    file.close();
}

// Функция за добавяне на нова книга
void add_book() {
    if (num_books >= MAX_BOOKS) {
        cout << "Няма повече място за нови книги." << endl;
        return;
    }
    Book book;
    cout << "Въведете ISB номер на книгата: ";
    cin >> book.isbn;

    // Проверка дали книгата вече не съществува
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == book.isbn) {
            cout << "Книгата вече съществува." << endl;
            return;
        }
    }

    cout << "Въведете заглавие на книгата: ";
    getline(cin >> ws, book.title);
    cout << "Въведете автор на книгата: ";
    getline(cin >> ws, book.author);
    cout << "Въведете жанр на книгата: ";
    getline(cin >> ws, book.genre);
    cout << "Въведете цена на книгата: ";
    cin >> book.price;
    cout << "Въведете година на издаване на книгата: ";
    cin >> book.year;

    books[num_books++] = book;
    cout << "Книгата е добавена успешно." << endl;
}

// Функция за изтриване на книга
void remove_book() {
    string isbn;
    cout << "Въведете ISB номер на книгата, която трябва да бъде изтрита: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            for (int j = i; j < num_books - 1; j++) {
                books[j] = books[j+ 1];
            }
            num_books--;
            cout << "Книгата е изтрита успешно." << endl;
            return;
        }
    }

    cout << "Книгата не е намерена." << endl;
}

// Функция за промяна на дадено поле на книга
void update_book() {
    string isbn;
    cout << "Въведете ISB номер на книгата, която трябва да бъде променена: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            int choice;
            cout << "Изберете поле за промяна: " << endl;
            cout << "1. Заглавие" << endl;
            cout << "2. Автор" << endl;
            cout << "3. Жанр" << endl;
            cout << "4. Цена" << endl;
            cout << "5. Година на издаване" << endl;
            cout << "Вашият избор: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "Въведете ново заглавие: ";
                getline(cin >> ws, books[i].title);
                break;
            }
            case 2: {
                cout << "Въведете нов автор: ";
                getline(cin >> ws, books[i].author);
                break;
            }
            case 3: {
                cout << "Въведете нов жанр: ";
                getline(cin >> ws, books[i].genre);
                break;
            }
            case 4: {
                cout << "Въведете нова цена: ";
                cin >> books[i].price;
                break;
            }
            case 5: {
                cout << "Въведете нова година на издаване: ";
                cin >> books[i].year;
                break;
            }
            default: {
                cout << "Невалиден избор." << endl;
                break;
            }
            }

            cout << "Книгата е променена успешно." << endl;
            return;
        }
    }

    cout << "Книгата не е намерена." << endl;
}

// Функция за търсене на книги по зададен жанр/автор/година на издаване
void search_books() {
    int choice;
    cout << "Изберете критерий за търсене: " << endl;
    cout << "1. Жанр" << endl;
    cout << "2. Автор" << endl;
    cout << "3. Година на издаване" << endl;
    cout << "Вашият избор: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        string genre;
        cout << "Въведете жанр за търсене: ";
        getline(cin >> ws, genre);

        cout << "Намерени книги: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].genre == genre) {
                cout << books[i].title << " от " << books[i].author << ", цена: " << books[i].price << " лв." << endl;
            }
        }
        break;
    }
    case 2: {
        string author;
        cout << "Въведете автор за търсене: ";
        getline(cin >> ws, author);
        cout << "Намерени книги: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].author == author) {
                cout << books[i].title << " от " << books[i].author << ", цена: " << books[i].price << " лв." << endl;
            }
        }
        break;
    }
    case 3: {
        int year;
        cout << "Въведете година на издаване за търсене: ";
        cin >> year;

        cout << "Намерени книги: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].year == year) {
                cout << books[i].title << " от " << books[i].author << ", цена: " << books[i].price << " лв." << endl;
            }
        }
        break;
    }
    default: {
        cout << "Невалиден избор." << endl;
        break;
    }
    }
}

// Функция за извеждане на книги по зададен ценови диапазон
void display_books_by_price_range() {
    double min_price, max_price;
    cout << "Въведете минимална цена: ";
    cin >> min_price;
    cout << "Въведете максимална цена: ";
    cin >> max_price;
    cout << "Намерени книги: " << endl;
    for (int i = 0; i < num_books; i++) {
        if (books[i].price >= min_price && books[i].price <= max_price) {
            cout << books[i].title << " от " << books[i].author << ", цена: " << books[i].price << " лв." << endl;
        }
    }
}
void save_books_to_file() {
    ofstream file("informaciya_za_knigite.txt");

    if (!file) {
        cout << "Грешка при отваряне на файла." << endl;
        return;
    }

    for (int i = 0; i < books_count; i++) {
        file << books[i].isbn << "|" << books[i].title << "|" << books[i].author << "|"
            << books[i].genre << "|" << books[i].price << "|" << books[i].year << endl;
    }

    file.close();
}

void load_books_from_file() {
    ifstream file("informaciya_za_knigite.txt");

    if (!file) {
        cout << "Грешка при отваряне на файла." << endl;
        return;
    }

    string line;
    int i = 0;

    while (getline(file, line)) {
        istringstream ss(line);
        getline(ss, books[i].isbn, '|');
        getline(ss, books[i].title, '|');
        getline(ss, books[i].author, '|');
        getline(ss, books[i].genre, '|');
        ss >> books[i].price;
        ss.ignore();
        ss >> books[i].year;

        i++;
    }

    books_count = i;

    file.close();
}


int main() {
    setlocale(LC_ALL, "");
    load_books_from_file();
    int choice;
    while (true) {
        cout << "Изберете опция: " << endl;
        cout << "1. Вписване на нова книга" << endl;
        cout << "2. Изтриване на книга" << endl;
        cout << "3. Промяна на дадено поле на книга" << endl;
        cout << "4. Търсене на книги" << endl;
        cout << "5. Извеждане на книги по ценови диапазон" << endl;
        cout << "6. Изход" << endl;
        cout << "Вашият избор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            add_book();
            break;
        }
        case 2: {
            remove_book();
            break;
        }
        case 3: {
            update_book();
            break;
        }
        case 4: {
            search_books();
            break;
        }
        case 5: {
            display_books_by_price_range();
            break;
        }
        case 6: {
            save_books_to_file();
            cout << "Довиждане!" << endl;
            return 0;
        }
        default: {
            cout << "Невалиден избор." << endl;
            break;
        }
        }
    }

    return 0;
}







