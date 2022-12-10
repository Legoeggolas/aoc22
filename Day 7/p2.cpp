#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#define FILE "file"

size_t const MAX_SZ = 100000;
size_t const AVAILABLE_DISK_SPACE = 70000000;
size_t const MIN_SZ_FOR_UPDATE = 30000000;

struct Directory {
    std::string name;
    size_t sz;
    std::shared_ptr<Directory> parent;
    std::unordered_map<std::string, std::shared_ptr<Directory>> children;
};

using DirPtr = std::shared_ptr<Directory>;

#ifdef DEBUG
void drawDirTree(DirPtr root, size_t level = 0) {
    for (size_t i = 0; i < level; i++) {
        std::cout << "\t";
    }

    std::cout << "- " << root->name << " : " << root->sz << "\n";
    for (auto const &[name, ptr] : root->children) {
        drawDirTree(ptr, level + 1);
    }
}
#endif

void updateParentSizeWithChildrenSize(DirPtr root) {
    for (auto const &[name, ptr] : root->children) {
        updateParentSizeWithChildrenSize(ptr);
        root->sz += ptr->sz;
    }
}

size_t cumulativeSize(DirPtr root) {
    size_t curr_sz = 0;
    if (root->sz <= MAX_SZ) {
#ifdef DEBUG
        std::cout << "[0] Adding " << root->name << "\n";
#endif
        curr_sz += root->sz;
    }

    for (auto const &[name, ptr] : root->children) {
        curr_sz += cumulativeSize(ptr);
    }

    return curr_sz;
}

size_t findClosestDir(DirPtr root, size_t const &lim) {
    auto currClosestMatch = std::numeric_limits<size_t>::max();
    if (root == nullptr) {
        return currClosestMatch;
    }

    if (root->sz < lim) {
        return currClosestMatch;
    }

    for (auto const &[name, ptr] : root->children) {
        auto const childClosestMatch = findClosestDir(ptr, lim);
        currClosestMatch = std::min(childClosestMatch, currClosestMatch);
    }

    return std::min(currClosestMatch, root->sz);
}

int main() {
    // Replace stdio with files
    std::ifstream infile(FILE ".in");
    std::ofstream outfile(FILE ".out");

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin.rdbuf(infile.rdbuf());
    std::cout.rdbuf(outfile.rdbuf());

    // Solution
    auto root = std::shared_ptr<Directory>(new Directory{"/", 0, nullptr, {}});
    auto curr = root;
    std::string inputLine;
    while (!std::cin.eof()) {
        std::getline(std::cin, inputLine);
        if (!std::cin.good()) {
            break;
        }

        if (std::cin.peek() == '$') {
            std::string sink, command, parameter = "";
            std::cin >> sink >> command;
            if (!std::cin.good()) {
                break;
            }

            // movement logic
            if (command != "ls") {
                std::cin >> parameter;
                if (!std::cin.good()) {
                    break;
                }

                if (parameter == "..") {
                    // move up
                    if (curr->name != "/" && curr->parent != nullptr) {
                        curr = curr->parent;
                    }

                } else if (parameter == "/") {
                    curr = root;
                } else {
                    auto found = curr->children.find(parameter);
                    if (found == curr->children.end()) {
                        curr->children[parameter] = std::shared_ptr<Directory>(new Directory{parameter, 0, curr, {}});
                    }
                    curr = curr->children[parameter];
                }

                continue;
            }

            // listing is handled by the outer loop
            // if the command was ls, control will fall to outer loop
            // otherwise continue
        }

        // listing logic
        std::string spec, name;
        std::cin >> spec >> name;
        if (!std::cin.good()) {
            break;
        }

        if (spec == "dir") {
            auto found = curr->children.find(name);
            if (found == curr->children.end()) {
                curr->children[name] = std::shared_ptr<Directory>(new Directory{name, 0, curr, {}});
            }
        } else {
            std::istringstream ss(spec);
            size_t temp;
            ss >> temp;
            curr->sz += temp;

#ifdef DEBUG
            std::cout << "Adding '" << name << "' to " << curr->name << "\n";
#endif
        }
    }

    updateParentSizeWithChildrenSize(root);

#ifdef DEBUG
    drawDirTree(root);

    std::cout << "Need " << MIN_SZ_FOR_UPDATE - (AVAILABLE_DISK_SPACE - root->sz) << " for update\n";
#endif

    std::cout << findClosestDir(root, MIN_SZ_FOR_UPDATE - (AVAILABLE_DISK_SPACE - root->sz));

    return 0;
}
