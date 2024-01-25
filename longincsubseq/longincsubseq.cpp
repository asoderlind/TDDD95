/**
 * TDDD95: Lab 1 - longincsubseq
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about finding the longest increasing subsequence
 * of a given sequence. We use dynamic programming to solve this
 * problem. We create an array where the index represents the length
 * of the subsequence and the value represents the smallest possible
 * last element of a subsequence of that length. We then iterate
 * through the sequence and update the array if we find a smaller
 * last element for a subsequence of a given length. We also keep
 * track of the predecessor of each element in the sequence to be
 * able to reconstruct the subsequence.
 *
 * Complexity: O(nlogn) where n is the length of the sequence.
 * Space: O(n) where n is the length of the sequence.
 */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ld EPS = 1e-9L;

/// @brief Find the longest increasing subsequence of a given sequence
/// @param inputArray The sequence
/// @return A vector containing the indices of the elements in the LIS
vector<int> lis(const vector<int> &inputArray)
{
  int n = inputArray.size();
  const int INF = numeric_limits<int>::max();

  // array of smallest possible last elements of subsequence of length i
  vector<int> dynamicProgrammingArray(n + 1, INF);

  // for value in dynamicProgramingArray[i], indexArray[i] stores index of value in
  // inputArray
  vector<int> indexArray(n + 1, -1);
  vector<int> predecessorArray(n, -1);
  dynamicProgrammingArray[0] = numeric_limits<int>::min();

  for (int i = 0; i < n; i++)
  {
    // Find the index where a[i] should be placed in d
    auto l = upper_bound(dynamicProgrammingArray.begin(), dynamicProgrammingArray.end(), inputArray[i]) - dynamicProgrammingArray.begin();

    // Check if a[i] can replace the current element at d[l]
    if (dynamicProgrammingArray[l - 1] < inputArray[i] && inputArray[i] < dynamicProgrammingArray[l])
    {
      // Update the dynamic programming array at index l
      dynamicProgrammingArray[l] = inputArray[i];

      // Update the index array at index l
      indexArray[l] = i;

      // Set the predecessor of a[i]
      predecessorArray[i] = (l > 0) ? indexArray[l - 1] : -1;
    }
  }

  // Find the index of the last
  // element of the longest increasing subsequence
  int finalPosIndex = 0;
  for (int l = 1; l <= n; l++)
  {
    if (dynamicProgrammingArray[l] < INF)
    {
      finalPosIndex = indexArray[l];
    }
  }

  // Reconstruct the sequence from the last index
  // by recursively finding the predecessor of each element
  vector<int> sequence;
  while (finalPosIndex != -1)
  {
    sequence.push_back(finalPosIndex);
    finalPosIndex = predecessorArray[finalPosIndex];
  }
  reverse(sequence.begin(), sequence.end()); // Reverse to get the correct order
  return sequence;
}

int main()
{
  ios::sync_with_stdio(false); // Optimize I/O operations
  cin.tie(NULL);               // Untie cin and cout

  int no_elements;
  while (cin >> no_elements)
  {
    vector<int> arr(no_elements);

    for (int &val : arr)
    {
      cin >> val;
    }

    auto sequence = lis(arr);
    cout << sequence.size() << endl;
    for (int index : sequence)
    {
      cout << index << " ";
    }
    cout << nl;
  }
  return 0;
}
