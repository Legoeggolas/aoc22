#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#define FILE "file"

int main() {
    // Replace stdio with files
    std::ifstream infile(FILE ".in");
    std::ofstream outfile(FILE ".out");

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin.rdbuf(infile.rdbuf());
    std::cout.rdbuf(outfile.rdbuf());

    // Solution
    std::string inputLine;
    size_t count = 0;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        std::unordered_map<char, int> window;
        auto insert = [&window](char c) -> void {
            auto found = window.find(c);
            if (found == window.end()) {
                window[c] = 0;
            }

            window[c]++;
        };
        auto erase = [&window](char c) -> void {
            window[c]--;
            if (window[c] == 0) {
                window.erase(c);
            }
        };

        size_t processed = 4;
        for (size_t i = 0; i < processed; i++) {
            char curr = inputLine[i];
            insert(curr);
        }

        for (; window.size() != 4 && processed < inputLine.length(); processed++) {
            char last = inputLine[processed - 4];
            char next = inputLine[processed];
            erase(last);
            insert(next);
        }

        if (window.size() == 4) {
            count = processed;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
