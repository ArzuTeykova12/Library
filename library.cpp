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

// Ôóíêöèÿ çà ÷åòåíå íà èíôîðìàöèÿòà çà êíèãèòå îò ôàéë
void read_books() {
    ifstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "Ãðåøêà ïðè îòâàðÿíåòî íà ôàéëà." << endl;
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

// Ôóíêöèÿ çà çàïèñâàíå íà èíôîðìàöèÿòà çà êíèãèòå âúâ ôàéë
void write_books() {
    ofstream file("informaciya_za_knigite.txt");
    if (!file) {
        cout << "Ãðåøêà ïðè îòâàðÿíåòî íà ôàéëà." << endl;
        return;
    }
    for (int i = 0; i < num_books; i++) {
        file << books[i].isbn << " " << books[i].title << " " << books[i].author << " " << books[i].genre << " " << books[i].price << " " << books[i].year << endl;
    }

    file.close();
}

// Ôóíêöèÿ çà äîáàâÿíå íà íîâà êíèãà
void add_book() {
    if (num_books >= MAX_BOOKS) {
        cout << "Íÿìà ïîâå÷å ìÿñòî çà íîâè êíèãè." << endl;
        return;
    }
    Book book;
    cout << "Âúâåäåòå ISB íîìåð íà êíèãàòà: ";
    cin >> book.isbn;

    // Ïðîâåðêà äàëè êíèãàòà âå÷å íå ñúùåñòâóâà
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == book.isbn) {
            cout << "Êíèãàòà âå÷å ñúùåñòâóâà." << endl;
            return;
        }
    }

    cout << "Âúâåäåòå çàãëàâèå íà êíèãàòà: ";
    getline(cin >> ws, book.title);
    cout << "Âúâåäåòå àâòîð íà êíèãàòà: ";
    getline(cin >> ws, book.author);
    cout << "Âúâåäåòå æàíð íà êíèãàòà: ";
    getline(cin >> ws, book.genre);
    cout << "Âúâåäåòå öåíà íà êíèãàòà: ";
    cin >> book.price;
    cout << "Âúâåäåòå ãîäèíà íà èçäàâàíå íà êíèãàòà: ";
    cin >> book.year;

    books[num_books++] = book;
    cout << "Êíèãàòà å äîáàâåíà óñïåøíî." << endl;
}

// Ôóíêöèÿ çà èçòðèâàíå íà êíèãà
void remove_book() {
    string isbn;
    cout << "Âúâåäåòå ISB íîìåð íà êíèãàòà, êîÿòî òðÿáâà äà áúäå èçòðèòà: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            for (int j = i; j < num_books - 1; j++) {
                books[j] = books[j+ 1];
            }
            num_books--;
            cout << "Êíèãàòà å èçòðèòà óñïåøíî." << endl;
            return;
        }
    }

    cout << "Êíèãàòà íå å íàìåðåíà." << endl;
}

// Ôóíêöèÿ çà ïðîìÿíà íà äàäåíî ïîëå íà êíèãà
void update_book() {
    string isbn;
    cout << "Âúâåäåòå ISB íîìåð íà êíèãàòà, êîÿòî òðÿáâà äà áúäå ïðîìåíåíà: ";
    cin >> isbn;
    for (int i = 0; i < num_books; i++) {
        if (books[i].isbn == isbn) {
            int choice;
            cout << "Èçáåðåòå ïîëå çà ïðîìÿíà: " << endl;
            cout << "1. Çàãëàâèå" << endl;
            cout << "2. Àâòîð" << endl;
            cout << "3. Æàíð" << endl;
            cout << "4. Öåíà" << endl;
            cout << "5. Ãîäèíà íà èçäàâàíå" << endl;
            cout << "Âàøèÿò èçáîð: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "Âúâåäåòå íîâî çàãëàâèå: ";
                getline(cin >> ws, books[i].title);
                break;
            }
            case 2: {
                cout << "Âúâåäåòå íîâ àâòîð: ";
                getline(cin >> ws, books[i].author);
                break;
            }
            case 3: {
                cout << "Âúâåäåòå íîâ æàíð: ";
                getline(cin >> ws, books[i].genre);
                break;
            }
            case 4: {
                cout << "Âúâåäåòå íîâà öåíà: ";
                cin >> books[i].price;
                break;
            }
            case 5: {
                cout << "Âúâåäåòå íîâà ãîäèíà íà èçäàâàíå: ";
                cin >> books[i].year;
                break;
            }
            default: {
                cout << "Íåâàëèäåí èçáîð." << endl;
                break;
            }
            }

            cout << "Êíèãàòà å ïðîìåíåíà óñïåøíî." << endl;
            return;
        }
    }

    cout << "Êíèãàòà íå å íàìåðåíà." << endl;
}

// Ôóíêöèÿ çà òúðñåíå íà êíèãè ïî çàäàäåí æàíð/àâòîð/ãîäèíà íà èçäàâàíå
void search_books() {
    int choice;
    cout << "Èçáåðåòå êðèòåðèé çà òúðñåíå: " << endl;
    cout << "1. Æàíð" << endl;
    cout << "2. Àâòîð" << endl;
    cout << "3. Ãîäèíà íà èçäàâàíå" << endl;
    cout << "Âàøèÿò èçáîð: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        string genre;
        cout << "Âúâåäåòå æàíð çà òúðñåíå: ";
        getline(cin >> ws, genre);

        cout << "Íàìåðåíè êíèãè: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].genre == genre) {
                cout << books[i].title << " îò " << books[i].author << ", öåíà: " << books[i].price << " ëâ." << endl;
            }
        }
        break;
    }
    case 2: {
        string author;
        cout << "Âúâåäåòå àâòîð çà òúðñåíå: ";
        getline(cin >> ws, author);
        cout << "Íàìåðåíè êíèãè: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].author == author) {
                cout << books[i].title << " îò " << books[i].author << ", öåíà: " << books[i].price << " ëâ." << endl;
            }
        }
        break;
    }
    case 3: {
        int year;
        cout << "Âúâåäåòå ãîäèíà íà èçäàâàíå çà òúðñåíå: ";
        cin >> year;

        cout << "Íàìåðåíè êíèãè: " << endl;
        for (int i = 0; i < num_books; i++) {
            if (books[i].year == year) {
                cout << books[i].title << " îò " << books[i].author << ", öåíà: " << books[i].price << " ëâ." << endl;
            }
        }
        break;
    }
    default: {
        cout << "Íåâàëèäåí èçáîð." << endl;
        break;
    }
    }
}

// Ôóíêöèÿ çà èçâåæäàíå íà êíèãè ïî çàäàäåí öåíîâè äèàïàçîí
void display_books_by_price_range() {
    double min_price, max_price;
    cout << "Âúâåäåòå ìèíèìàëíà öåíà: ";
    cin >> min_price;
    cout << "Âúâåäåòå ìàêñèìàëíà öåíà: ";
    cin >> max_price;
    cout << "Íàìåðåíè êíèãè: " << endl;
    for (int i = 0; i < num_books; i++) {
        if (books[i].price >= min_price && books[i].price <= max_price) {
            cout << books[i].title << " îò " << books[i].author << ", öåíà: " << books[i].price << " ëâ." << endl;
        }
    }
}
void save_books_to_file() {
    ofstream file("informaciya_za_knigite.txt");

    if (!file) {
        cout << "Ãðåøêà ïðè îòâàðÿíå íà ôàéëà." << endl;
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
        cout << "Ãðåøêà ïðè îòâàðÿíå íà ôàéëà." << endl;
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
        cout << "Èçáåðåòå îïöèÿ: " << endl;
        cout << "1. Âïèñâàíå íà íîâà êíèãà" << endl;
        cout << "2. Èçòðèâàíå íà êíèãà" << endl;
        cout << "3. Ïðîìÿíà íà äàäåíî ïîëå íà êíèãà" << endl;
        cout << "4. Òúðñåíå íà êíèãè" << endl;
        cout << "5. Èçâåæäàíå íà êíèãè ïî öåíîâè äèàïàçîí" << endl;
        cout << "6. Èçõîä" << endl;
        cout << "Âàøèÿò èçáîð: ";
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
            cout << "Äîâèæäàíå!" << endl;
            return 0;
        }
        default: {
            cout << "Íåâàëèäåí èçáîð." << endl;
            break;
        }
        }
    }

    return 0;
}







