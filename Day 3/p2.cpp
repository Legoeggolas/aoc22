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
    size_t score = 0;
    while (!std::cin.eof()) {
        std::string elfOne, elfTwo, elfThree;
        std::getline(std::cin, elfOne);
        std::getline(std::cin, elfTwo);
        std::getline(std::cin, elfThree);
        if (!std::cin.good()) {
            break;
        }

        std::unordered_set<char>
            ruckOne{std::begin(elfOne), std::end(elfOne)},
            ruckTwo{std::begin(elfTwo), std::end(elfTwo)},
            ruckThree{std::begin(elfThree), std::end(elfThree)},
            common{};

        for (auto const item : ruckOne) {
            if (ruckTwo.count(item) == 1) {
                common.insert(item);
            }
        }

        for (auto const item : common) {
            if (ruckThree.count(item) == 1) {
                score += prio(item);
            }
        }
    }

    std::cout << score << std::endl;
    return 0;
}
