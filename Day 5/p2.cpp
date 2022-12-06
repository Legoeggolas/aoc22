#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    std::vector<std::string> inputLines;
    std::string inputLine;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        inputLines.push_back(inputLine);
    }

    // all stacks occupy 3 (box width) + 1 (space delimiter) characters
    // except the last one, that does not need the delimiter
    // to find the number of stacks, we can add this back and divide by 4
    size_t n_stacks = (inputLines[0].length() + 1) / 4;
    std::vector<std::vector<char>> stacks(n_stacks);

    size_t inputIndex = 0;
    for (; inputIndex < inputLines.size(); inputIndex++) {
        auto const &line = inputLines[inputIndex];

        if ('0' <= line[1] && line[1] <= '9') {
            break;
        }

        for (size_t index = 1; index < line.length(); index += 4) {
            if (isalpha(line[index]) == false) {
                continue;
            }
            stacks[index / 4].push_back(line[index]);
        }
    }

    // Stacks were constructed top to bottom
    // Reverse them for proper representation
    // and since pop_back() will be used
    for (auto &stack : stacks) {
        std::reverse(std::begin(stack), std::end(stack));

#ifdef DEBUG
        for (auto const &c : stack) {
            std::cout << c << " ";
        }

        std::cout << "\n";
#endif
    }

    inputIndex += 2;

    for (; inputIndex < inputLines.size(); inputIndex++) {
        auto const &line = inputLines[inputIndex];
        // break on final newline
        if (isalpha(line[0]) == false) {
            break;
        }

        std::string sink;  // stores unneeded words
        size_t quantity, src, dest;
        std::istringstream ss(line);

        // format: move <quantity> from <src> to <dest>
        ss >> sink >> quantity >> sink >> src >> sink >> dest;

#ifdef DEBUG
        std::cout << "Read op: " << src << "->" << dest << ":" << quantity << "\n";
#endif

        auto &srcStk = stacks[src - 1];
        auto &destStk = stacks[dest - 1];
        for (size_t i = quantity; i > 0; i--) {
#ifdef DEBUG
            if (i > srcStk.size()) {
                std::cout << "Not enough boxes in stack #" << src << "\n";
            }
#endif
            destStk.push_back(srcStk.back());
            srcStk.pop_back();
        }

        std::reverse(std::begin(destStk) + (destStk.size() - quantity), std::end(destStk));
    }

    std::string result = "";
    for (auto const &stack : stacks) {
        result.push_back(stack.back());
#ifdef DEBUG
        for (auto const &c : stack) {
            std::cout << c << " ";
        }

        std::cout << "\n";
#endif
    }

    std::cout << result << std::endl;

    return 0;
}
