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

// ������� �� ������ �� ������������ �� ������� �� ����
void read_books() {
    ifstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "������ ��� ���������� �� �����." << endl;
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

// ������� �� ��������� �� ������������ �� ������� ��� ����
void write_books() {
    ofstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "������ ��� ���������� �� �����." << endl;
        return;
    }
    for (int i = 0; i < num_books; i++) {
        file << books[i].isbn << " " << books[i].title << " " << books[i].author << " " << books[i].genre << " " << books[i].price << " " << books[i].year << endl;
    }

    file.close();
}

// ������� �� �������� �� ���� �����
void add_book() {
    if (num_books >= MAX_BOOKS) {
        cout << "���� ������ ����� �� ���� �����." << endl;
        return;
    }
    Book book;
    cout << "�������� ISB ����� �� �������: ";
    cin >> book.isbn;

    // �������� ���� ������� ���� �� ����������
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == book.isbn) {
            cout << "������� ���� ����������." << endl;
            return;
        }
    }

    cout << "�������� �������� �� �������: ";
    getline(cin >> ws, book.title);
    cout << "�������� ����� �� �������: ";
    getline(cin >> ws, book.author);
    cout << "�������� ���� �� �������: ";
    getline(cin >> ws, book.genre);
    cout << "�������� ���� �� �������: ";
    cin >> book.price;
    cout << "�������� ������ �� �������� �� �������: ";
    cin >> book.year;

    books[num_books++] = book;
    cout << "������� � �������� �������." << endl;
}

// ������� �� ��������� �� �����
void remove_book() {
    string isbn;
    cout << "�������� ISB ����� �� �������, ����� ������ �� ���� �������: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            for (int j = i; j < num_books - 1; j++) {
                books[j] = books[j+ 1];
            }
            num_books--;
            cout << "������� � ������� �������." << endl;
            return;
        }
    }

    cout << "������� �� � ��������." << endl;
}

// ������� �� ������� �� ������ ���� �� �����
void update_book() {
    string isbn;
    cout << "�������� ISB ����� �� �������, ����� ������ �� ���� ���������: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            int choice;
            cout << "�������� ���� �� �������: " << endl;
            cout << "1. ��������" << endl;
            cout << "2. �����" << endl;
            cout << "3. ����" << endl;
            cout << "4. ����" << endl;
            cout << "5. ������ �� ��������" << endl;
            cout << "������ �����: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "�������� ���� ��������: ";
                getline(cin >> ws, books[i].title);
                break;
            }
            case 2: {
                cout << "�������� ��� �����: ";
                getline(cin >> ws, books[i].author);
                break;
            }
            case 3: {
                cout << "�������� ��� ����: ";
                getline(cin >> ws, books[i].genre);
                break;
            }
            case 4: {
                cout << "�������� ���� ����: ";
                cin >> books[i].price;
                break;
            }
            case 5: {
                cout << "�������� ���� ������ �� ��������: ";
                cin >> books[i].year;
                break;
            }
            default: {
                cout << "��������� �����." << endl;
                break;
            }
            }

            cout << "������� � ��������� �������." << endl;
            return;
        }
    }

    cout << "������� �� � ��������." << endl;
}

// ������� �� ������� �� ����� �� ������� ����/�����/������ �� ��������
void search_books() {
    int choice;
    cout << "�������� �������� �� �������: " << endl;
    cout << "1. ����" << endl;
    cout << "2. �����" << endl;
    cout << "3. ������ �� ��������" << endl;
    cout << "������ �����: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        string genre;
        cout << "�������� ���� �� �������: ";
        getline(cin >> ws, genre);

        cout << "�������� �����: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].genre == genre) {
                cout << books[i].title << " �� " << books[i].author << ", ����: " << books[i].price << " ��." << endl;
            }
        }
        break;
    }
    case 2: {
        string author;
        cout << "�������� ����� �� �������: ";
        getline(cin >> ws, author);
        cout << "�������� �����: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].author == author) {
                cout << books[i].title << " �� " << books[i].author << ", ����: " << books[i].price << " ��." << endl;
            }
        }
        break;
    }
    case 3: {
        int year;
        cout << "�������� ������ �� �������� �� �������: ";
        cin >> year;

        cout << "�������� �����: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].year == year) {
                cout << books[i].title << " �� " << books[i].author << ", ����: " << books[i].price << " ��." << endl;
            }
        }
        break;
    }
    default: {
        cout << "��������� �����." << endl;
        break;
    }
    }
}

// ������� �� ��������� �� ����� �� ������� ������ ��������
void display_books_by_price_range() {
    double min_price, max_price;
    cout << "�������� ��������� ����: ";
    cin >> min_price;
    cout << "�������� ���������� ����: ";
    cin >> max_price;
    cout << "�������� �����: " << endl;
    for (int i = 0; i < num_books; i++) {
        if (books[i].price >= min_price && books[i].price <= max_price) {
            cout << books[i].title << " �� " << books[i].author << ", ����: " << books[i].price << " ��." << endl;
        }
    }
}
void save_books_to_file() {
    ofstream file("informaciya_za_knigite.txt");

    if (!file) {
        cout << "������ ��� �������� �� �����." << endl;
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
        cout << "������ ��� �������� �� �����." << endl;
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
        cout << "�������� �����: " << endl;
        cout << "1. �������� �� ���� �����" << endl;
        cout << "2. ��������� �� �����" << endl;
        cout << "3. ������� �� ������ ���� �� �����" << endl;
        cout << "4. ������� �� �����" << endl;
        cout << "5. ��������� �� ����� �� ������ ��������" << endl;
        cout << "6. �����" << endl;
        cout << "������ �����: ";
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
            cout << "���������!" << endl;
            return 0;
        }
        default: {
            cout << "��������� �����." << endl;
            break;
        }
        }
    }

    return 0;
}







