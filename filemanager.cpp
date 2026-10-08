#include "filemanager.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>

using namespace std;

// Constructor
FileManager::FileManager(const string &booksFile, const string &usersFile,
                         const string &logsFile)
    : booksFileName(booksFile), usersFileName(usersFile),
      logsFileName(logsFile) {}

bool FileManager::saveLogToFile(const string &log) {
  ofstream file(logsFileName, ios_base::app);
  if (!file.is_open()) {
    cout << "Erreur : Impossible d'ouvrir " << logsFileName
         << " en écriture.\n";
    return false;
  }
  auto now = chrono::system_clock::now();
  time_t time_now = chrono::system_clock::to_time_t(now);
  tm *local_time = localtime(&time_now);

  file << put_time(local_time, "%Y-%m-%d %H:%M:%S - ") << log << "\n";

  file.close();
  return true;
}

// Save all library data
bool FileManager::saveLibraryData(Library &library) {
  return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library &library) {
  bool booksLoaded = loadBooksFromFile(library);
  bool usersLoaded = loadUsersFromFile(library);
  return booksLoaded ||
         usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library &library) {
  ofstream file(booksFileName);
  if (!file.is_open()) {
    cout << "Erreur : Impossible d'ouvrir " << booksFileName
         << " en écriture.\n";
    return false;
  }

  auto books = library.getAllBooks();
  for (Book *book : books) {
    file << book->toFileFormat() << "\n";
  }

  file.close();
  return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library &library) {
  ofstream file(usersFileName);
  if (!file.is_open()) {
    cout << "Erreur : Impossible d'ouvrir " << usersFileName
         << " en écriture.\n";
    return false;
  }

  auto users = library.getAllUsers();
  for (User *user : users) {
    file << user->toFileFormat() << "\n";
  }

  file.close();
  return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library &library) {
  ifstream file(booksFileName);
  if (!file.is_open()) {
    cout << "Aucun fichier de livres existant trouvé. Démarrage avec une "
            "bibliothèque vide.\n";
    return false;
  }

  string line;
  int count = 0;
  while (getline(file, line)) {
    if (!line.empty()) {
      Book book;
      book.fromFileFormat(line);
      string log;
      library.addBook(book, log);
      // saveLogToFile(log);
      count++;
    }
  }

  file.close();
  cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
  return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library &library) {
  ifstream file(usersFileName);
  if (!file.is_open()) {
    cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans "
            "utilisateurs enregistrés.\n";
    return false;
  }

  string line;
  int count = 0;
  while (getline(file, line)) {
    if (!line.empty()) {
      User user;
      user.fromFileFormat(line);
      string log;
      library.addUser(user, log);
      // saveLogToFile(log);
      count++;
    }
  }

  file.close();
  cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
  return true;
}

// Check if file exists
bool FileManager::fileExists(const string &filename) {
  ifstream file(filename);
  return file.good();
}

// Create backup
void FileManager::createBackup() {
  if (fileExists(booksFileName)) {
    filesystem::copy_file(booksFileName, booksFileName + ".backup");
  }

  if (fileExists(usersFileName)) {
    filesystem::copy_file(usersFileName, usersFileName + ".backup");
  }

  cout << "Fichiers de sauvegarde créés.\n";
}
