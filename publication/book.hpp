#ifndef BOOK_HPP
#define BOOK_HPP

#include "publication.hpp"

#include <string>
#include <map>

using namespace std;

class Book : public Publication
{
private:
    string author;
    int numberOfCopies;

public:
    Book(const int code, const string title, const string publisher, const int year, const string author, const int numberOfCopies) : Publication(code, title, publisher, year), author(author), numberOfCopies(numberOfCopies){};
    Book(const map<string, string> publicationData, const string author, const int numberOfCopies) : Publication(publicationData), author(author), numberOfCopies(numberOfCopies){};
    ~Book(){};

    inline int getNumberOfCopies() const { return numberOfCopies; };
    inline string getAuthor() const { return author; };

    vector<pair<string, string>> getAdditionalData();

    void loanCopy() { numberOfCopies--; };
    void returnCopy() { numberOfCopies++; };
};

#endif