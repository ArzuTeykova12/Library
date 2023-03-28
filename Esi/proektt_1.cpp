#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAX_BOOKS = 1000;

struct Book {
    string isbn;
    string title;
    string author;
    string genre;
    float price;
    int year;
};

Book books[MAX_BOOKS];
int num_books = 0;
int books_count = 0;

void save_books_to_file() {
    ofstream file("informaciya_za_knigite.txt", ios::out | ios::app);

    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < books_count; i++) {
        file << books[i].isbn << "|" << books[i].title << "|" << books[i].author << "|"
            << books[i].genre << "|" << books[i].price << "|" << books[i].year << endl;
    }
    file.flush();
    file.close();
    if (file.fail()) {
        cout << "Error writing to file." << endl;
        return;
    }
}


// Функция за добавяне на нова книга
void add_book() {
    if (num_books >= MAX_BOOKS) {
        cout << "No more room for new books." << endl;
        return;
    }

    Book book;
    cout << "Enter the ISBN of the book: ";
    cin >> book.isbn;

    // Check if the book already exists
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == book.isbn) {
            cout << "The book already exists." << endl;
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the title of the book: ";
    getline(cin >> ws, book.title);

    cout << "Enter the author of the book: ";
    getline(cin >> ws, book.author);

    cout << "Enter the genre of the book: ";
    getline(cin >> ws, book.genre);

    cout << "Enter the price of the book: ";
    cin >> book.price;

    // Validate that the price is greater than zero
    while (book.price <= 0) {
        cout << "Price must be greater than zero. Please enter a valid price: ";
        cin >> book.price;
    }

    cout << "Enter the year of publication: ";
    cin >> book.year;

    // Validate that the year is within a reasonable range
    while (book.year < 1900 || book.year > 2023) {
        cout << "Year must be between 1900 and 2023. Please enter a valid year: ";
        cin >> book.year;
    }

    books[num_books++] = book;

    fstream file;
    file.open("informaciya_za_knigite.txt", ios::app);
    file << book.isbn << "|" << book.title << "|" << book.author << "|" << book.genre << "|" << book.price << "|" << book.year << endl;
    file.close();
}


string bookToString(const Book& bookData) {
    string str = "";
    str += bookData.isbn + "|";
    str += bookData.title + "|";
    str += bookData.author + "|";
    str += bookData.genre + "|";
    str += to_string(bookData.price) + "|";
    str += to_string(bookData.year);
    return str;
}

Book lineToBook(string line) {
    Book book;
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    book.isbn = token;

    getline(ss, token, '|');
    book.title = token;

    getline(ss, token, '|');
    book.author = token;

    getline(ss, token, '|');
    book.genre = token;

    getline(ss, token, '|');
    if (token.empty()) {
        // Handle empty input string
        cout << "Error: Invalid input string: empty price field" << endl;
    }
    else {
        try {
            book.price = stod(token);
        }
        catch (const std::invalid_argument& e) {
            // Handle invalid input string
            cout << "Error: Invalid input string: " << e.what() << endl;
        }
    }

    getline(ss, token, '|');
    if (token.empty()) {
        // Handle empty input string
        cout << "Error: Invalid input string: empty year field" << endl;
    }
    else {
        try {
            book.year = stoi(token);
        }
        catch (const std::invalid_argument& e) {
            // Handle invalid input string
            cout << "Error: Invalid input string: " << e.what() << endl;
        }
    }

    return book;
}

void remove_book(fstream& file) {
    string isbn;
    cout << "Enter the ISBN of the book to be deleted: ";
    cin >> isbn;
    file.seekg(0);
    bool bookFound = false;

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        Book book = lineToBook(line);
        if (book.isbn == isbn) {
            bookFound = true;
            break;
        }
        lineNum++;
    }

    if (bookFound) {
        // Затваряме и отваряме отново файла
        file.close();
        file.open("informaciya_za_knigite.txt", ios::in);

        // Отваряме временен файл, където ще копираме всички редове, освен изтрития
        fstream tempFile("temp.txt", ios::out);
        if (!tempFile) {
            cerr << "Error creating temporary file." << endl;
            exit(1);
        }

        int currentLineNum = 0;
        while (getline(file, line)) {
            if (currentLineNum != lineNum) {
                tempFile << line << endl;
            }
            currentLineNum++;
        }

        // Затваряме двата файла
        file.close();
        tempFile.close();

        // Изтриваме оригиналния файл и преименуваме временния файл като оригиналния
        if (remove("informaciya_za_knigite.txt") != 0) {
            cerr << "Error deleting file." << endl;
            exit(1);
        }

        if (rename("temp.txt", "informaciya_za_knigite.txt") != 0) {
            cerr << "Error renaming file." << endl;
            exit(1);
        }

        cout << "The book has been deleted successfully." << endl;
    }
    else {
        cout << "Book not found." << endl;
    }
}




// Функция за промяна на дадено поле на книга
void update_book() {
    string isbn;
    cout << "Enter the ISBN number of the book to be changed: ";
    cin >> isbn;

    bool book_found = false; // променлива, която да отчита дали книгата е намерена или не
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            int choice;
            cout << "Select a field to change: " << endl;
            cout << "1. Book title" << endl;
            cout << "2. Author" << endl;
            cout << "3. Genre" << endl;
            cout << "4. Price" << endl;
            cout << "5. Year of publication" << endl;
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "Enter a new book title: ";
                getline(cin >> ws, books[i].title);
                break;
            }
            case 2: {
                cout << "Enter a new author: ";
                getline(cin >> ws, books[i].author);
                break;
            }
            case 3: {
                cout << "Enter a new genre: ";
                getline(cin >> ws, books[i].genre);
                break;
            }
            case 4: {
                cout << "Enter a new price: ";
                cin >> books[i].price;
                break;
            }
            case 5: {
                cout << "Enter a new year of publication: ";
                cin >> books[i].year;
                break;
            }
            default: {
                cout << "Wrong choice." << endl;
                break;
            }
            }

            cout << "The book has been modified successfully." << endl;
            book_found = true; // маркираме, че книгата е намерена
        }
    }

    if (book_found) {
        // Отваряме файла за промяна
        fstream file;
        file.open("informaciya_za_knigite.txt", ios::out);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        // Записваме всички книги от масива във файла
        for (int i = 0; i < num_books; i++) {
            file << books[i].isbn << "|" << books[i].title << "|" << books[i].author << "|" << books[i].genre << "|" << books[i].price << "|" << books[i].year << endl;
        }

        // Затваряме файла
        file.close();
    }
    else { // ако книгата не е намерена
        cout << "Book not found." << endl;
    }
}


// Функция за търсене на книги по зададен жанр/автор/година на издаване
void search_books() {
    int choice;
    cout << "Select criteria for search: " << endl;
    cout << "1. Genre" << endl;
    cout << "2. Author" << endl;
    cout << "3. Year of publication" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1: {
        string genre;
        cout << "Enter a genre to search: ";
        getline(cin, genre);

        cout << "Found books: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].genre == genre) {
                cout << books[i].title << " by " << books[i].author << ", price: " << books[i].price << " lv." << endl;
            }
        }
        break;
    }
    case 2: {
        string author;
        cout << "Enter an author to search: ";
        getline(cin >> ws, author);
        cout << "Found books: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].author == author) {
                cout << books[i].title << " by " << books[i].author << ", price: " << books[i].price << " lv." << endl;
            }
        }
        break;
    }
    case 3: {
        int year;
        cout << "Enter year of publication to search: ";
        cin >> year;

        cout << "Found books: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].year == year) {
                cout << books[i].title << " от " << books[i].author << ", цена: " << books[i].price << " лв." << endl;
            }
        }
        break;
    }
    default: {
        cout << "Wrong chice." << endl;
        break;
    }
    }
}

// Функция за извеждане на книги по зададен ценови диапазон
void display_books_by_price_range() {
    float min_price, max_price;
    cout << "Type minimum price: ";
    cin >> min_price;
    cout << "Type maximum price: ";
    cin >> max_price;
    cout << "Found books: " << endl;
    for (int i = 0; i < num_books; i++) {
        if (books[i].price >= min_price && books[i].price <= max_price) {
            cout << books[i].title << " by " << books[i].author << ", price: ";
            cout << fixed << setprecision(2) << books[i].price << " lv." << endl;
        }
    }
}

// Функция, която прочита една линия от файл и я превръща в структура Book
Book lineеToBook(std::string str) {
    std::istringstream iss(str);
    Book book;

    std::getline(iss, book.isbn, '|');
    std::getline(iss, book.title, '|');
    std::getline(iss, book.author, '|');
    std::getline(iss, book.genre, '|');
    iss >> book.price;
    iss.ignore(); // прескачаме разделителя между цената и годината
    iss >> book.year;

    return book;
}

// Функция, която прочита данните за книгите от файл
void readFile(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        books[num_books] = lineеToBook(line);
        num_books++;
        if (num_books == MAX_BOOKS) {
            std::cerr << "Max number of books reached." << std::endl;
            break;
        }
    }
}

int main() {
    readFile("informaciya_za_knigite.txt");
    int choice;
    cout << "###################MENU###################" << endl;
    cout << endl;
    /*login();*/
    cout << "To select a function, write the corresponding number!" << endl;
    cout << endl;
    while (true) {
        cout << "Select an option: " << endl;
        cout << "      1. Add a new book" << endl;
        cout << "      2. Delete a book" << endl;
        cout << "      3. Change a book field" << endl;
        cout << "      4. Search books" << endl;
        cout << "      5. Displaying books by price range" << endl;
        cout << "      6. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            add_book();
            break;
        }
        case 2: {
            fstream file("informaciya_za_knigite.txt", ios::in);
            if (!file.is_open()) {
                cout << "Error opening file." << endl;
                return 1;
            }
            remove_book(file);
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
            cout << "Bye!" << endl;
            exit(0);
            break;
        }
        default: {
            cout << "Wrong choice." << endl;
            break;
        }
        }
    }

    return 0;
}
