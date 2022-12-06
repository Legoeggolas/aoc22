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
    std::string temp = "";
    size_t score = 0;
    while (!std::cin.eof()) {
        std::getline(std::cin, temp);
        if (!std::cin.good()) {
            break;
        }

        /*
        Rock = 0
        Paper = 1
        Scissors = 2
        */
        size_t elfShape = temp[0] - 'A';
        size_t playerShape = temp[2] - 'X';

        /*
        Rock - Paper = 0 - 1 = -1 % 3 = 2 = Loss
        Rock - Scissors = 0 - 2 = -2 % 3 = 1 = Win
        Paper - Scissors = 1 - 2 = -1 % 3 = 2 = Loss
        Others are straightforward
        */
        int result = (3 + (playerShape - elfShape)) % 3;
        score += playerShape + 1;

        size_t mult = 0;
        if (result == 0) {
            mult = 1;
        } else if (result == 1) {
            mult = 2;
        }

        score += 3 * mult;
    }

    std::cout << score;

    return 0;
}
