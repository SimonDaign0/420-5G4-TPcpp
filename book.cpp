#include <string>
using namespace std;

#include "book.h"
#include <sstream>

// Default constructor
Book::Book()
    : title(""), author(""), isbn(""), isAvailable(true), borrowerId("") {}

// Parameterized constructor
Book::Book(const string &title, const string &author, const string &isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true),
      borrowerId("") {}

// Getters
string Book::getTitle() const { return this->title; }
string Book::getAuthor() const { return this->author; };
string Book::getISBN() const { return this->isbn; };
bool Book::getAvailability() const { return this->isAvailable; };
string Book::getBorrowerId() const { return this->borrowerId; };

// Setters
void Book::setTitle(const string &title) { this->title = title; };
void Book::setAuthor(const string &author) { this->author = author; };
void Book::setISBN(const string &isbn) { this->isbn = isbn; };
void Book::setAvailability(bool available) { this->isAvailable = available; };
void Book::setBorrowerId(const string &id) { this->borrowerId = id; };

// Methods
string Book::toString() const {
  string statu_str = (isAvailable)
                         ? "\nStatu : Disponible"
                         : "\nStatu : Emprunté par : " + this->borrowerId;
  return "Titre : " + this->title + "\nAuteur : " + this->author +
         "\nISBN : " + this->isbn + statu_str + '\n';
};

void Book::checkOut(const string &borrowerId) {
  this->isAvailable = false;
  this->borrowerId = borrowerId;
};
void Book::returnBook() {
  this->isAvailable = true;
  this->borrowerId = "";
};

// Format for file storage
string Book::toFileFormat() const {
  string fmt = title + '|' + author + '|' + isbn + "|" +
               ((isAvailable) ? "1|" : ("0|" + this->borrowerId));
  return fmt;
};

// Parse from file format
void Book::fromFileFormat(const string &line) {
  stringstream ss(line);
  string token;

  getline(ss, title, '|');
  getline(ss, author, '|');
  getline(ss, isbn, '|');
  ss >> isAvailable;
  if (!isAvailable) {
    char delimiter;
    ss >> delimiter;
    getline(ss, borrowerId);
  } else {
    borrowerId = "";
  }
};
