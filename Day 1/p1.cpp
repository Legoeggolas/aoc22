#include <algorithm>
#include <fstream>
#include <iostream>
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
    std::vector<int> cals = {0};
    while (std::cin.eof() != true) {
        if (std::cin.peek() == '\n') {
            cals.push_back(0);
            std::cin.get();
            continue;
        }

        int temp = 0;
        std::cin >> temp;
        cals.back() += temp;
        std::cin.get();
    }

    std::cout << *std::max_element(std::begin(cals), std::end(cals));
    return 0;
}
