#include "publication.hpp"

Publication::Publication(map<string, string> publicationData)
{
    if (publicationData.find("publicationCode") != publicationData.end())
        code = stoi(publicationData["publicationCode"]);
    else
        std::runtime_error("Código da publicação não passado corretamente pela interface");

    if (publicationData.find("title") != publicationData.end())
        title = publicationData["title"];
    else
        std::runtime_error("Título da publicação não passado corretamente pela interface");

    if (publicationData.find("publisher") != publicationData.end())
        publisher = publicationData["publisher"];
    else
        std::runtime_error("Editora não passado corretamente pela interface");

    if (publicationData.find("year") != publicationData.end())
        year = stoi(publicationData["year"]);
    else
        std::runtime_error("Ano da publicação não passado corretamente pela interface");
};

vector<pair<string, string>> Publication::getData()
{
    vector<pair<string, string>> publicationData;
    publicationData.push_back(pair<string, string>("publicationCode", to_string(code)));
    publicationData.push_back(pair<string, string>("title", title));
    publicationData.push_back(pair<string, string>("publisher", publisher));
    publicationData.push_back(pair<string, string>("year", to_string(year)));
    return publicationData;
}