#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

string matchPatterns(const string &pattern1, const string &pattern2)
{
    istringstream ss1(pattern1), ss2(pattern2);
    string word1, word2;
    map<string, string> placeholderMap;
    vector<string> result;

    while (ss1 >> word1 && ss2 >> word2)
    {
        if (word1[0] == '<' && word2[0] == '<')
        {
            if (placeholderMap.find(word1) == placeholderMap.end())
            {
                placeholderMap[word1] = word2;
                result.push_back(word2);
            }
            else if (placeholderMap[word1] != word2)
            {
                return "-";
            }
            else
            {
                result.push_back(word2);
            }
        }
        else if (word1 != word2)
        {
            return "-";
        }
        else
        {
            result.push_back(word1);
        }
    }

    if (ss1 >> word1 || ss2 >> word2)
    {
        return "-";
    }

    string phrase;
    for (const auto &word : result)
    {
        if (!phrase.empty())
            phrase += " ";
        phrase += word.substr(1, word.size() - 2); // Remove angle brackets
    }
    return phrase;
}

int main(void)
{
    int testCases;
    cin >> testCases;
    cin.ignore();

    for (int i = 0; i < testCases; ++i)
    {
        string pattern1, pattern2;
        getline(cin, pattern1);
        getline(cin, pattern2);

        cout << matchPatterns(pattern1, pattern2) << endl;
    }
}