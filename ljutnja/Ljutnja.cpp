#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void ljutnja(int avalible_amount, std::vector<int> children, int sum_of_needs){
    std::sort(children.begin(), children.end());
    long total_anger{};
    int candy_differense{sum_of_needs - avalible_amount};

    for(int i{0}; i < children.size(); i++)
    {
        children[i] = std::min(children[i], int(candy_differense/(children.size() - i)));
        candy_differense -= children[i];
        total_anger += children[i] * children[i];
    }

    std::cout << total_anger << "\n";
}

int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int children_amount;
    int avalible_amount;
    int temp;
    int sum_of_needs;
    std::vector<int> children;

    std::cin >> avalible_amount >> children_amount;

    for(int i{0}; i < children_amount; i++)
    {
        std::cin >> temp;
        sum_of_needs += temp;
        children.push_back(temp);
    }

    ljutnja(avalible_amount, children, sum_of_needs);

    return 0;
}
