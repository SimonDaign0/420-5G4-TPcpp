# Author `Simon Daigneault`

# Construire le projet

Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt` et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`

# Ajout de nouvelles fonctionnalités

## Interface et Expérience Utilisateur

- Affichage du nom d’utilisateur plutôt que l’id dans l’affichage des livres.

## Gestion de Données

- Tri des résultats par titre, auteur pour l’affichage (utilisation de la fonction de tri de la STL).

## Journal d’activités

- Ajout de logs dans journal.txt pour l'ajout, le retrait, l'emprunt et le retour de livre ainsi que l'ajout d'utilisateurs.

# Correction du bug

- Creation et assignation du repertoire ./data si aucun repertoire n'est assigne au lancement du programme avec -d

# Question 1 : C++

## Expliquez en détails une fonctionnalité / notion dans le code que nous n'avons pas ou peu vu en cours. Montrez ici l’exemple sorti du code du projet.

Nous n'avons pas vu la manipulation de stringstream ou la manipulation de filesystem.

```cpp
// Parse from file format
void User::fromFileFormat(const string &line) {
  stringstream ss(line);
  string token;

  getline(ss, name, '|');
  getline(ss, userId, '|');

  string booksStr;
  getline(ss, booksStr, '|');

  borrowedBooks.clear();
  if (!booksStr.empty()) {
    stringstream booksSs(booksStr);
    string isbn;
    while (getline(booksSs, isbn, ',')) {
      borrowedBooks.push_back(isbn);
    }
  }
}
```

# Question 2 : Options de développement possible

## Proposez une solution plus adaptée pour la gestion de bibliothèque et faisant appel éventuellement à une technologie autre que le C++, et expliquez comment vous interfaceriez ça avec le C++. Quelle solution technologique utiliseriez vous ? Pensez au futur de cette bibliothèque à Alexandrie qui pourrait éventuellement contenir des millions de livres.

Pour la gestion des livres et des utilisateurs, je le ferais avec SQLite. Ce serait beaucoup plus efficace si le volume est très élevé. Pour l'integrer, je ferais des requetes SQLite en c++ au lieu de manipuler des fichiers texte avec filesystem.
