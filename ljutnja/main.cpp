#include <iostream>
#include <vector>
#include <queue>

int main()
{
    int M, N;
    std::cin >> M >> N;

    std::priority_queue<int> children;
    int value;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> value;
        children.push(value);
    }

    while (M--)
    {
        int max_value = children.top();
        children.pop();
        children.push(max_value - 1);
    }

    long long sum = 0;
    while (!children.empty())
    {
        int x = children.top();
        sum += (long long)x * x;
        children.pop();
    }

    std::cout << sum << std::endl;
    return 0;
}
