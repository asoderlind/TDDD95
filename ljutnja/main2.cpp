#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::ios::sync_with_stdio(false); // Faster I/O
    std::cin.tie(nullptr);

    int M, N;
    std::cin >> M >> N;

    std::vector<int> data;
    data.reserve(N); // Reserve space
    std::priority_queue<int, std::vector<int>> children(std::less<int>(), std::move(data));

    int value;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> value;
        children.push(value);
    }

    for (int i = 0; i < M && !children.empty(); ++i)
    {
        value = children.top();
        children.pop();
        if (value > 1)
        {
            children.push(value - 1);
        }
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
