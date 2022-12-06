#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

#define FILE "file"

inline size_t prio(char c) {
    size_t temp = 0;
    if (isalnum(c) == false) {
        std::cout << "Received an unknown char: " << c << "\n";
    }
    if ('a' <= c && c <= 'z') {
        temp = c - 'a';
        temp += 1;
    } else {
        temp = c - 'A';
        temp += 27;
    }

#ifdef DEBUG
    std::cout << "Score for " << c << " : " << temp << "\n";
#endif
    return temp;
};

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
    size_t score = 0;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        std::unordered_set<char> leftCompartment, rightCompartment;

        size_t mid = inputLine.length() / 2;
        for (auto it = inputLine.begin(); it != inputLine.begin() + mid; it++) {
            leftCompartment.insert(*it);
        }
        for (auto it = inputLine.begin() + mid; it != inputLine.end(); it++) {
            rightCompartment.insert(*it);
        }

        for (auto const item : rightCompartment) {
            if (leftCompartment.count(item) != 0) {
                score += prio(item);
                leftCompartment.erase(item);

#ifdef DEBUG
                std::cout << "Found common item: " << item << "\n";
#endif
            }
        }
    }

    std::cout << score << std::endl;
    return 0;
}
