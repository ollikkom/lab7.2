#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

void print(const std::vector<std::string> &vect, const std::string &str, size_t count) {
    for (size_t i = 0; i < vect.size(); i++) {
        if (vect[i] == str) {
            if (count < i) {
                for (size_t j = i - count; j < i; j++)
                    std::cout << vect[j] << " ";
            } else {

                for (size_t j = 0; j < i; j++)
                    std::cout << vect[j] << " ";
            }

            std::cout << vect[i] << " ";

            for (size_t j = i + 1; j <= i + count; j++) {
                if (j == vect.size())
                    break;
                std::cout << vect[j] << " ";
            }

            std::cout << std::endl;
        }
    }
}

int main() {
    std::ifstream fin;
    std::string File;

    std::cout << "FILE name: " << std::endl;
    std::cin >> File;
    fin.open(File, std::ios_base::in);

    if (fin.is_open()) {
        std::string Findword;
        std::cout << "Find words:" << std::endl;
        std::cin >> Findword;

        size_t n = 0;
        std::cout << "N = " << std::endl;
        std::cin >> n;

        std::map<std::string, size_t> check;

        std::string buf;
        while (getline(fin, buf)) {
            std::vector<std::string> slova;

            std::string buf2;
            for (size_t i = 0; i < buf.size(); i++) {
                if (ispunct(buf[i]) || buf[i] == ' ') {
                    if (!buf2.empty()) {
                        slova.push_back(buf2);
                        buf2.clear();
                    }
                } else {
                    buf2 += buf[i];
                }
            }
            if (!buf2.empty())
                slova.push_back(buf2);


            for (size_t i = 0; i < slova.size(); i++) {
                if (check.find(slova[i]) == check.end()) {
                    check[slova[i]] = 1;
                } else {
                    ++check[slova[i]];
                }
            }

            print(slova, Findword, n);
        }
        std::cout << std::endl;

        for (auto &at : check) {
            std::cout << at.first << " " << at.second << std::endl;
        }

        fin.close();
    }
    return 0;
}