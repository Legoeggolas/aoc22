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

        /*
        Lose = 0
        Draw = 1
        Win = 2
        */
        size_t result = temp[2] - 'X';

        size_t playerShape = elfShape;
        if (result == 0) {
            playerShape = (3 + elfShape - 1) % 3;
        } else if (result == 2) {
            playerShape = (3 + elfShape + 1) % 3;
        }

        score += playerShape + 1;

        score += 3 * result;
    }

    std::cout << score;

    return 0;
}
