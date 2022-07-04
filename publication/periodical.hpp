#ifndef PERIODICAL_HPP
#define PERIODICAL_HPP

#include "publication.hpp"

#include <string>
#include <map>

using namespace std;

class Periodical : public Publication
{
private:
    string month;
    int numberOfEdition;

public:
    Periodical(const int code, const string title, const string publisher, const int year, const string month, const int numberOfEdition) : Publication(code, title, publisher, year), month(month), numberOfEdition(numberOfEdition){};
    Periodical(const map<string, string> publicationData, const string month, const int numberOfEdition) : Publication(publicationData), month(month), numberOfEdition(numberOfEdition){};
    ~Periodical(){};

    vector<pair<string, string>> getAdditionalData();

    inline string getMonth() const { return month; };
    inline int getNumberOfEdition() const { return numberOfEdition; };
};

#endif