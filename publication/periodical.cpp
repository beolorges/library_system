#include "periodical.hpp"

vector<pair<string, string>> Periodical::getAdditionalData()
{
    vector<pair<string, string>> periodicalData;
    periodicalData.push_back(make_pair("type", "Periodical"));
    periodicalData.push_back(make_pair("month", month));
    periodicalData.push_back(make_pair("numberOfEdition", to_string(numberOfEdition)));
    return periodicalData;
}
