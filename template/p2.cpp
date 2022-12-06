#include <fstream>
#include <iostream>
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
    std::string inputLine;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }
    }

    return 0;
}
