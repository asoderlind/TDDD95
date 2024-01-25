/**
 * TDDD95: Lab 1 - knapsack
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about finding the optimal set of items to
 * put in a knapsack. We use dynamic programming to solve this
 * problem. We create a matrix where the rows represent the
 * items and the columns represent the capacity of the knapsack.
 * We then populate the matrix by picking the optimal value of
 * the previous item directly or by adding the value of the
 * current item to the optimal value of the remaining capacity.
 *
 * Complexity: O(nC) where n is the number of items and C is the capacity of the knapsack.
 * Space: O(nC) where n is the number of items and C is the capacity of the knapsack.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// @brief Solve the knapsack problem
/// @param C The capacity of the knapsack
/// @param n The number of items
/// @param values vector of values of the items
/// @param weights vector of weights of the items
/// @return A pair containing the optimal value and the indices of the items used
pair<int, vector<int>> knapsack(int C, int n, const vector<int> &values, const vector<int> &weights)
{
    vector<vector<int>> mat(n + 1, vector<int>(C + 1, 0));

    for (int item = 1; item <= n; ++item)
    {
        for (int capacity = 1; capacity <= C; ++capacity)
        {
            // Just pick the optimal value of the previous item directly
            int max_without_item = mat[item - 1][capacity];
            int max_with_item = 0;

            // If the item fits, try to add it
            if (weights[item - 1] <= capacity)
            {
                int remaining_capacity = capacity - weights[item - 1];

                // Add the value of the item to the optimal value of the remaining capacity
                max_with_item = mat[item - 1][remaining_capacity] + values[item - 1];
            }

            // Pick the maximum of the two
            mat[item][capacity] = max(max_without_item, max_with_item);
        }
    }

    // Find the items that were selected
    vector<int> selected_items;
    int capacity = C;
    for (int item = n; item > 0; --item)
    {
        if (mat[item][capacity] != mat[item - 1][capacity])
        {
            selected_items.push_back(item - 1);
            capacity -= weights[item - 1];
        }
    }

    return {static_cast<int>(selected_items.size()), selected_items};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int C, n;

    while (cin >> C >> n)
    {
        vector<int> values(n), weights(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> values[i] >> weights[i];
        }

        auto [num_selected_items, selected_items] = knapsack(C, n, values, weights);

        cout << num_selected_items << endl;
        for (int i = 0; i < num_selected_items; ++i)
        {
            if (i > 0)
                cout << " ";
            cout << selected_items[i];
        }
        cout << endl;
    }

    return 0;
}
