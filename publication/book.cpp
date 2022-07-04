#include "book.hpp"

vector<pair<string, string>> Book::getAdditionalData()
{
    vector<pair<string, string>> bookData;
    bookData.push_back(make_pair("type", "Book"));
    bookData.push_back(make_pair("author", getAuthor()));
    bookData.push_back(make_pair("numberOfCopies", to_string(getNumberOfCopies())));
    return bookData;
}