#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
    size_t count = 0;
    std::string inputLine;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        std::istringstream ss(inputLine);
        char delim;
        size_t firstBegin, firstEnd, secBegin, secEnd;
        ss >> firstBegin >> delim >> firstEnd >> delim >> secBegin >> delim >> secEnd;

        if (firstBegin <= secBegin && secBegin <= firstEnd) {
            ++count;
            continue;
        }

        if (firstBegin <= secEnd && secEnd <= firstEnd) {
            ++count;
            continue;
        }

        if (secBegin <= firstBegin && firstEnd <= secEnd) {
            ++count;
            continue;
        }

        if (secBegin <= firstEnd && firstEnd <= secEnd) {
            ++count;
            continue;
        }
    }

    std::cout << count;

    return 0;
}
