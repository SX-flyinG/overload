#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>

using namespace std;

class Book {
    string name;
public:
    Book() {
        this->name = "I am legend";
    }

    Book(string name) {
        this->name = name;
    }

    Book(const Book& other) {
        this->name = other.name;
    }

    Book operator=(const Book& other) {
        this->name = other.name;
        return *this;
    }

    // ?????????????? ????????? ??????
    friend ostream& operator<<(ostream& os, const Book& book);
};

ostream& operator<<(ostream& os, const Book& book) {
    os << book.name;
    return os;
}

class Human {
    char* name;
    Book* arrayOfBooks;
    int arrayOfBooksAmount;
public:
    Human(const char* name) {
        this->arrayOfBooksAmount = 1;
        this->arrayOfBooks = new Book[this->arrayOfBooksAmount];
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Human operator+(const Book& book) {
        Book* tempArrayOfBooks = new Book[this->arrayOfBooksAmount];
        for (int i = 0; i < this->arrayOfBooksAmount; i++) {
            tempArrayOfBooks[i] = this->arrayOfBooks[i];
        }

        delete[] this->arrayOfBooks;
        this->arrayOfBooksAmount++;

        this->arrayOfBooks = new Book[this->arrayOfBooksAmount];

        for (int i = 0; i < this->arrayOfBooksAmount - 1; i++) {
            this->arrayOfBooks[i] = tempArrayOfBooks[i];
        }

        this->arrayOfBooks[this->arrayOfBooksAmount - 1] = book;

        return *this;
    }

    Human operator-(const Book& book) {
        if (arrayOfBooksAmount == 0) {
            return *this;
        }
        Book* tempArrayOfBooks = new Book[this->arrayOfBooksAmount];
        for (int i = 0; i < this->arrayOfBooksAmount; i++) {
            tempArrayOfBooks[i] = this->arrayOfBooks[i];
        }

        delete[] this->arrayOfBooks;
        this->arrayOfBooksAmount--;

        this->arrayOfBooks = new Book[this->arrayOfBooksAmount];

        for (int i = 0; i < this->arrayOfBooksAmount - 1; i++) {
            this->arrayOfBooks[i] = tempArrayOfBooks[i];
        }

        this->arrayOfBooks[this->arrayOfBooksAmount - 1] = book;

        return *this;
    }

    Human operator=(const Human& other) {
        if (this != &other) {
            return *this;
        }

        char* tempName = new char[strlen(other.name) + 1];

        strcpy(tempName, other.name);

        delete[] this->name;

        this->name = new char[strlen(tempName) + 1];

        strcpy(this->name, tempName);

        return *this;
    }

    // a > b
    bool operator>(const Human& other) {
        if (strlen(this->name) > strlen(other.name)) {
            return true;
        }
        return false;
    }

    void PrintInfo() {
        cout << "Name: " << this->name << endl;
        cout << "Books: " << endl;
        for (int i = 0; i < this->arrayOfBooksAmount; i++) {
            cout << "Book name: " << this->arrayOfBooks[i] << endl;
        }
    }
};

int main() {
    Human obj = Human("Boryslav");

    obj.PrintInfo();

    Book book = Book("Moby Dick");
    obj = obj - book;
    obj = obj - book;

    obj.PrintInfo();

}