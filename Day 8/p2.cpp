#include <fstream>
#include <iostream>
#include <numeric>
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
    std::string inputLine;
    std::vector<std::string> grid;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        grid.push_back(inputLine);
#ifdef DEBUG
        std::cout << "Added '" << inputLine << "' to grid\n";
#endif
    }

    std::vector<std::vector<bool>> visible(grid.size(), std::vector<bool>(grid[0].length(), false));

    // comb row-wise
    for (size_t i = 0; i < grid.size(); i++) {
        char curr = grid[i][0];

        // from left to right
        visible[i][0] = true;  // edge trees are always visible
        for (size_t j = 1; j < grid[0].length(); j++) {
            if (grid[i][j] > curr) {
                curr = grid[i][j];
                visible[i][j] = true;
            }
        }

        // from right to left
        curr = grid[i].back();
        visible[i].back() = true;  // edge trees are always visible
        for (size_t j = grid[0].length() - 1; j > 0; j--) {
            if (grid[i][j] > curr) {
                curr = grid[i][j];
                visible[i][j] = true;
            }
        }
    }

    // comb column-wise
    for (size_t i = 0; i < grid[0].length(); i++) {
        char curr = grid[0][i];
        visible[0][i] = true;  // edge trees are always visible

        // from top to bottom
        for (size_t j = 1; j < grid.size(); j++) {
            if (grid[j][i] > curr) {
                curr = grid[j][i];
                visible[j][i] = true;
            }
        }

        // from bottom to top
        curr = grid.back()[i];
        visible.back()[i] = true;  // edge trees are always visible
        for (size_t j = grid.size() - 1; j > 0; j--) {
            if (grid[j][i] > curr) {
                curr = grid[j][i];
                visible[j][i] = true;
            }
        }
    }

#ifdef DEBUG
    for (auto const &row : visible) {
        for (auto const &element : row) {
            std::cout << element << " ";
        }

        std::cout << "\n";
    }
#endif

    size_t visibleCount = 0;
    for (auto const &row : visible) {
        visibleCount += std::accumulate(row.begin(), row.end(), 0);
    }

    std::cout << "Visible trees: " << visibleCount << "\n";

#ifdef DEBUG
    std::cout << "\nInvisible trees: " << visible.size() * visible[0].size() - visibleCount << "\n";
#endif

    size_t maxVisibility = 0;
    for (size_t i = 1; i < visible.size() - 1; i++) {
        for (size_t j = 1; j < visible[0].size() - 1; j++) {
            if (visible[i][j] == false) {
                continue;
            }

            size_t score = 1;
            size_t curr = 0;
            // go right
            for (int k = j + 1; k < visible[0].size(); k++) {
                curr++;

                if (grid[i][j] <= grid[i][k]) {
                    break;
                }
            }
            score *= curr;

            curr = 0;
            // go left
            for (int k = j - 1; k >= 0; k--) {
                curr++;

                if (grid[i][j] <= grid[i][k]) {
                    break;
                }
            }
            score *= curr;

            curr = 0;
            // go up
            for (int k = i + 1; k < visible.size(); k++) {
                curr++;

                if (grid[i][j] <= grid[k][j]) {
                    break;
                }
            }
            score *= curr;

            curr = 0;
            // go down
            for (int k = i - 1; k >= 0; k--) {
                curr++;

                if (grid[i][j] <= grid[k][j]) {
                    break;
                }
            }
            score *= curr;

#ifdef DEBUG
            std::cout << "Score for (" << i << ", " << j << "): " << score << "\n";
#endif

            maxVisibility = std::max(score, maxVisibility);
        }
    }

    std::cout << "Max visibility: " << maxVisibility << std::endl;
    return 0;
}
