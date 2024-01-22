#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Function to find the indices of the Longest Increasing Subsequence (LIS)
std::vector<int> lis(const std::vector<int> &inputArray)
{
  int n = inputArray.size();
  const int INF = std::numeric_limits<int>::max();

  // array of smallest possible last elements of subsequence of length i
  std::vector<int> dynamicProgrammingArray(n + 1, INF);

  // for value in dynamicProgramingArray[i], indexArray[i] stores index of value in
  // inputArray
  std::vector<int> indexArray(n + 1, -1);

  // for value in
  std::vector<int> predecessorArray(n, -1);

  // set the first element to negative infinity
  dynamicProgrammingArray[0] = std::numeric_limits<int>::min();

  // Iterate through each element of the input array
  for (int i = 0; i < n; i++)
  {
    // Find the index where a[i] should be placed in d
    auto l = std::upper_bound(dynamicProgrammingArray.begin(), dynamicProgrammingArray.end(), inputArray[i]) - dynamicProgrammingArray.begin();

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
  std::vector<int> sequence;
  while (finalPosIndex != -1)
  {
    sequence.push_back(finalPosIndex);
    finalPosIndex = predecessorArray[finalPosIndex];
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

    // Print the length of the LIS
    std::cout << sequence.size() << std::endl;
    for (int index : sequence)
    {
      std::cout << index << " "; // Print the indices in the LIS
    }
    std::cout << "\n";
  }
  return 0;
}
