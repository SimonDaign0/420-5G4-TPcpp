#ifndef LIBRARY_H
#define LIBRARY_H

#include <memory>
#include <vector>

#include "book.h"
#include "user.h"

using namespace std;

class Library {
private:
  vector<unique_ptr<Book>> books;
  vector<unique_ptr<User>> users;

public:
  // Constructor and destructor
  Library();
  ~Library() = default;

  // Util
  string getBorrowerName(const Book &book);
  string formatBook(const Book &book);

  // Book management
  void addBook(const Book &book, string &log);
  void displayBookWithBorrower(const Book &book);
  bool removeBook(const string &isbn, string &log);
  Book *findBookByISBN(const string &isbn);
  vector<Book *> searchBooksByTitle(const string &title);
  vector<Book *> searchBooksByAuthor(const string &author);
  vector<Book *> getAvailableBooks();
  vector<Book *> getAllBooks();

  // User management
  void addUser(const User &user, string &log);
  User *findUserById(const string &userId);
  vector<User *> getAllUsers();

  // Library operations
  bool checkOutBook(const string &isbn, const string &userId, string &log);
  bool returnBook(const string &isbn, string &log);

  // Display methods
  void displayAllBooks();
  void displayAvailableBooks();
  void displayAllUsers();

  // Statistics
  int getTotalBooks() const;
  int getAvailableBookCount() const;
  int getCheckedOutBookCount() const;
};

#endif
