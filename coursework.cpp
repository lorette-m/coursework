#include <fstream>
#include <sstream>

#include <vector>
#include <chrono>

#include "HashTable.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "________________________________________________________ Text ________________________________________________________\n" << std::endl;
	
    std::string line = "";
    int lineCounter = 0;
    std::vector<std::string> words;
    std::string word;

    HashTable hashTable;

    std::ifstream in("text.txt"); // открываем файл для чтения

    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::cout << ++lineCounter << " " << line << std::endl;
            words.push_back(std::to_string(lineCounter));
            std::stringstream ss(line);
            while (ss >> word)
            {
                if (not((char(word[0]) >= 'а' and char(word[0]) <= 'я') and (char(word[word.size() - 1]) >= 'а' and char(word[word.size() - 1]) <= 'я'))
                    or
                    (not(char(word[0]) >= 'a' and char(word[0]) <= 'z') and (char(word[word.size() - 1]) >= 'a' and char(word[word.size() - 1]) <= 'z')))
                {
                    std::string fixWord = "";
                    for (int i = 0; i < (word.size()); i++)
                    {
                        if ((char(word[i]) >= 'А' and char(word[i]) <= 'я') or (char(word[i]) >= 'A' and char(word[i]) <= 'z'))
                        {
                            fixWord += tolower(word[i]);
                        }
                    }
                    if (fixWord != "" and fixWord != " ")
                    {
                        words.push_back(fixWord);
                        hashTable.insert(fixWord, lineCounter);
                    }
                }
                else
                {
                    words.push_back(word);
                    hashTable.insert(word, lineCounter);
                }
            }
        }
    }
    in.close();     // закрываем файл

    std::cout << "\n________________________________________________________ Words _______________________________________________________\n" << std::endl;
    for (int i = 0; i < words.size(); i++)
    {
        std::cout << words[i] << "   ";
    }

    std::cout << "\n______________________________________________________ HashTable _____________________________________________________\n" << std::endl;
    hashTable.display();
    
    return 0;
}