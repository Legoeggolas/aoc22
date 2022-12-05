#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
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
    int curr = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    while (std::cin.eof() != true) {
        if (std::cin.peek() == '\n') {
            pq.push(curr);
            curr = 0;
            if (pq.size() > 3) {
                pq.pop();
            }
            std::cin.get();
            continue;
        }

        int temp = 0;
        std::cin >> temp;
        curr += temp;
        std::cin.get();
    }

    pq.push(curr);
    if (pq.size() > 3) {
        pq.pop();
    }

    curr = 0;
    while (!pq.empty()) {
        curr += pq.top();
        pq.pop();
    }

    std::cout << curr;
    return 0;
}
