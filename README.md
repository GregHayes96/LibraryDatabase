# LibraryDatabase

Functioning library application made up of two classes, books and patrons. users can be created and books can be added to the database.

Books:

    Contains constructors for initilisation which give the class object a title, author, ISBN, copy right date, checked out information, and genre.
    Appropriate getters and setters to alter copy right information, ISBN.
    Overload operators for comparing ISBN

Patron:

    Contructors for setting name, Card no, and fees owed
    Getters and setters for all private class information
    Overload opertors for comparison function

Transaction:

    struct which contains stored information of every library transaction. who rented a book, what book, how much they owe
    Stored in a class vector

Future updates:

    Transaction struct search function to be added, for database searching and data editing
    improved error handling

