#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Function to find the indices of the Longest Increasing Subsequence (LIS)
std::vector<int> lis(const std::vector<int> &a)
{
  int n = a.size(); // Get the size of the input array
  // Define a large value as infinity
  const int INF = std::numeric_limits<int>::max();

  // Initialize helper vectors
  // d: Stores the smallest possible last element of a subsequence of length i
  // p: Stores the index in a of the last element of the subsequence of length i
  // predecessor: Stores the index of the predecessor of each element in a
  std::vector<int> d(n + 1, INF), p(n + 1, -1), predecessor(n, -1);
  d[0] = std::numeric_limits<int>::min(); // Set the first element to negative infinity

  // Iterate through each element of the input array
  for (int i = 0; i < n; i++)
  {
    // Find the index where a[i] should be placed in d
    auto l = std::upper_bound(d.begin(), d.end(), a[i]) - d.begin();
    // Check if a[i] can replace the current element at d[l]
    if (d[l - 1] < a[i] && a[i] < d[l])
    {
      d[l] = a[i]; // Update d[l] with a[i]
      p[l] = i;    // Update the index in p
      // Set the predecessor of a[i]
      predecessor[i] = (l > 0) ? p[l - 1] : -1;
    }
  }

  // Find the index of the last element of the longest increasing subsequence
  int last_idx = 0;
  for (int l = 1; l <= n; l++)
  {
    if (d[l] < INF)
    {
      last_idx = p[l];
    }
  }

  // Reconstruct the sequence from the last index
  std::vector<int> sequence;
  while (last_idx != -1)
  {
    sequence.push_back(last_idx);
    last_idx = predecessor[last_idx];
  }
  std::reverse(sequence.begin(), sequence.end()); // Reverse to get the correct order
  return sequence;
}

int main()
{
  std::ios::sync_with_stdio(false); // Optimize I/O operations
  std::cin.tie(NULL);               // Untie cin and cout

  // Read number of elements and process each test case
  int no_elements;
  while (std::cin >> no_elements)
  {
    std::vector<int> arr(no_elements);
    // Read the elements of the array
    for (int &val : arr)
    {
      std::cin >> val;
    }
    // Find and print the LIS sequence
    auto sequence = lis(arr);
    std::cout << sequence.size() << std::endl; // Print the length of the LIS
    for (int index : sequence)
    {
      std::cout << index << " "; // Print the indices in the LIS
    }
    std::cout << "\n";
  }
  return 0;
}
