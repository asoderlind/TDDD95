/** TDDD95: Lab 1 - intervalcover
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about covering a specified interval with a
 * minimum number of the given intervals. We use a greedy
 * approach to solve this problem. We sort the intervals by
 * their starting point and then we choose the interval that
 * stretches the furthest to the right. We then repeat this
 * process until we have covered the entire interval.
 *
 * Complexity: O(nlogn) where n is the number of intervals.
 * Space: O(n) where n is the number of intervals.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ld EPS = 1e-9L;

int interval2originalIndex(pair<double, double> interval, vector<pair<double, double>> originalIntervals)
{
    for (size_t i = 0; i < originalIntervals.size(); i++)
    {
        if (originalIntervals[i] == interval)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Cover the interval with the minimum number of intervals
/// @param interval The interval to cover
/// @param componentIntervals The intervals to cover with
/// @return A pair containing the number of intervals required to cover the interval and the indices of the intervals used
pair<int, vector<int>> cover(pair<double, double> interval, vector<pair<double, double>> componentIntervals, bool verbose = false)
{
    // Sort the intervals by their starting point
    vector<pair<double, double>> sortedIntervals = componentIntervals;
    sort(sortedIntervals.begin(), sortedIntervals.end());

    vector<int> selectedIndices;

    int bestIndex = -1;
    double furthestEnd = -INF;

    // Find all intervals that cover a and stretch furthest to the right
    for (size_t i = 0; i < sortedIntervals.size(); i++)
    {
        if (sortedIntervals[i].first <= interval.first && sortedIntervals[i].second > furthestEnd)
        {
            furthestEnd = sortedIntervals[i].second;
            bestIndex = i;
        }
    }

    // If there are no intervals that cover a, return impossible
    if (bestIndex == -1)
    {
        return {-1, vector<int>()};
    }

    selectedIndices.push_back(interval2originalIndex(sortedIntervals[bestIndex], componentIntervals));

    int currentIndex = bestIndex + 1;
    double currentEnd = furthestEnd;

    // Iterate through the intervals to cover the whole range
    while (currentEnd < interval.second)
    {
        double nextEnd = -INF;
        int nextIndex = -1;
        for (int i = currentIndex; i < sortedIntervals.size(); ++i)
        {
            if (sortedIntervals[i].first <= currentEnd)
            {
                if (sortedIntervals[i].second > nextEnd)
                {

                    nextEnd = sortedIntervals[i].second;
                    nextIndex = i;
                }
            }
            else
            {
                break; // We have reached the end of the intervals that can extend the coverage
            }
        }

        if (nextIndex == -1)
        { // No interval can extend the coverage
            return {-1, vector<int>()};
        }

        selectedIndices.push_back(interval2originalIndex(sortedIntervals[nextIndex], componentIntervals));
        currentEnd = nextEnd;
        currentIndex = nextIndex + 1;
    }

    return {selectedIndices.size(), selectedIndices};
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // read input
    pair<double, double> interval;
    while (cin >> interval.first >> interval.second)
    {
        int numIntervals;
        cin >> numIntervals;
        vector<pair<double, double>> componentIntervals;
        for (int i = 0; i < numIntervals; ++i)
        {
            double beginning, end;
            cin >> beginning >> end;
            componentIntervals.push_back(make_pair(beginning, end));
        }
        auto [numRequiredIntervals, intervals] = cover(interval, componentIntervals);
        if (numRequiredIntervals == -1)
        {
            cout << "impossible" << nl;
        }
        else
        {
            cout << numRequiredIntervals << nl;
            for (int i = 0; i < numRequiredIntervals; ++i)
            {
                cout << intervals[i] << " ";
            }
            cout << nl;
        }
    }
    return 0;
}