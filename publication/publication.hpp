#ifndef PUBLICATION_HPP
#define PUBLICATION_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;

class Publication
{
private:
    int code;
    string title;
    string publisher;
    int year;

public:
    Publication(int code, string title, string publisher, int year) : code(code), title(title), publisher(publisher), year(year){};
    Publication(map<string, string>);
    virtual ~Publication(){};

    vector<pair<string, string>> getData();
    virtual vector<pair<string, string>> getAdditionalData() = 0;

    inline int getCode() const { return code; };
    inline string getTitle() const { return title; };
    inline string getPublisher() const { return publisher; };
    inline int getYear() const { return year; };
};

#endif