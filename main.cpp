#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "ctype.h"
#include "map"

class Text{

private:
    struct Element{
        std::string str;
        Element *pPrev;
        Element *pNext;
    } * Word;
    struct WordElem{
        std::string str;
        int count;
    };
public:
    static int counter;
    ~Text()
    {
        while (Word != nullptr){

            Element *pNext = Word->pNext;
            delete Word;
            Word = pNext;
        }
    }

    Text() {
        Word = nullptr;
        counter = 0;
    }


    void AddElem(const std::string str)
    {
        if (Word == nullptr){

            Word = new Element;
            Word->str = str;
            Word->pNext = nullptr;
            Word->pPrev = nullptr;
            return;
        }

        Element *Last = Word;
        while( Last->pNext != nullptr){

            Last= Last->pNext;
        }
        Last->pNext = new Element;
        Last->pNext->str = str;
        Last->pNext->pNext = nullptr;
        Last->pNext->pPrev = Last;
    }

    void Print(std::ostream & stream, const std::string & str1, size_t n)
    {
        Element *Last = Word;
        while (Last != nullptr) {
            if (Last->str == str1){

                Element * FindWord = Last;
                size_t i = 0;
                while (FindWord->pPrev != nullptr && i < n){

                    FindWord = FindWord->pPrev;
                    i++;
                }
                for (size_t j = 0; j < i + 1 + n; j++){

                    if (FindWord == nullptr) break;
                    stream << FindWord->str << " ";
                    FindWord = FindWord->pNext;
                }
                stream << std::endl;

            }
            Last = Last->pNext;
        }
    }
};

    bool File(std::ifstream & fin)
    {
        std::string ff;
        std::cout<<"Your FILE: ";
        do
        {
            std::cin>>ff;
            if (ff == "null") return false;
            fin.open(ff, std::ios_base::in);
            if (fin.is_open()){

                return true;
            }
            else{
                std::cout << "Error! Other ?FILE? or enter 'null' to exit:" << std::endl;
            }
        }
        while (true);
    }

    Text* split(std::string & str)
    {
        Text* elem = new Text;
        std::string word = "";
        for (size_t i = 0; i < str.size(); i++){

            if (ispunct(str[i]) or str[i] == ' '){

                if (word != ""){

                    elem->AddElem(word);
                    Text::counter++;
                    word = "";
                }
            }
            else{
                word += str[i];
            }
        }
        if (word != ""){

            elem->AddElem(word);
            //Text::counter++;
        }
        std::map<std::string, size_t> slova;
        for (int i = 0; i < str.size(); i++) {
            if(slova.find(str)== slova.end())
            {
                slova[str]= 0;
            }
            else{
                slova[str]++;
            }
        }

        return elem;
    }

int Text::counter = 0;


int main() {
    //counter=0;
    std::ifstream fin;
    //if(!fin.is_open())
        //return -1;
    if (! File(fin)) return 0;

        std::string strFind;
       std::cout<<"FIND. Your word? ";
        std::cin>>strFind;
       size_t n = 0;
       std::cout<<"OUTPUT. The range of output words? ";
       std::cin>>n;

    std::string text;

    std::vector<std::string> ptr;
    const int N = 2;

    for (int i=0; i<N; i++) {
        std::string str;
        std::cin >> str;
        ptr.push_back(str);
    }
    for (int i=0; i<ptr.size(); i++) {
        std::cout  << ptr[i] << std::endl; // покажем что содержится в ptr
    }

    while (getline(fin, text))
    {
        Text* elemF = split(text);
        elemF->Print(std::cout, strFind, n);
        delete elemF;
    }

//    std::map<std::string, size_t> slova;
//    while (getline(fin, text))
//    {
//        Text* elemF = split(text);
//        while (elemF != nullptr) {
//            if(slova.find()== slova.end())
//                {
//                    slova[]= 0;
//                }
//            else{
//                slova[]++;
//            }
//        }
//    }

    //std::cout<< "\nNumber of coincidences: "<<Text::counter<< std::endl;
    fin.close();
    return 0;
}