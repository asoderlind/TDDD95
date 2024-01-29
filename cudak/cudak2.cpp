#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long int

ll startRange, endRange, targetSum;
const int maxDigits = 18, maxDigitSum = 136;
ll digitSumCount[maxDigits][maxDigitSum]; // DP table for precomputing digit sums

/**
 * Initializes the DP table.
 * Fills the digitSumCount array with counts of numbers having specific digit sums.
 */
void init()
{
    // Initialize DP table with zeros
    for (int digit = 0; digit < maxDigits; digit++)
        for (int sum = 0; sum < maxDigitSum; sum++)
            digitSumCount[digit][sum] = 0;

    // Base case: One way to achieve a sum of 0 with 0 digits
    digitSumCount[0][0] = 1;

    // Base case: One way to achieve each sum from 0 to 9 with one digit
    for (int i = 0; i < 10; i++)
        digitSumCount[1][i] = 1;

    // Fill the DP table for numbers up to maxDigits digits and sum up to maxDigitSum
    for (int digit = 2; digit < maxDigits; digit++)
        for (int sum = 0; sum < maxDigitSum; sum++)
            for (int digitValue = 0; digitValue < 10 && sum - digitValue >= 0; digitValue++)
                digitSumCount[digit][sum] += digitSumCount[digit - 1][sum - digitValue];
}

/**
 * Counts how many numbers up to a given number have a digit sum of a target sum using DP.
 * @param number The upper limit number.
 * @param digitSum The required sum of digits.
 * @return Count of numbers up to the given number having a digit sum of the target sum.
 */
ll countDigitSum(ll number, int digitSum)
{
    // Base cases
    if (number == 0 && digitSum == 0)
        return 1;
    if (digitSum < 0 || number == 0)
        return 0;

    // Initialize variables for sum calculation
    ll sum = 0, tempNumber = number;
    int lastDigit, numLength = 0;

    // Decompose number into its digits
    while (tempNumber)
    {
        lastDigit = tempNumber % 10;
        tempNumber /= 10;
        numLength++;
    }

    // Special case for single-digit number
    if (numLength == 1)
    {
        if (digitSum <= number)
            return 1;
        else
            return 0;
    }

    // Sum up counts using precomputed DP values
    for (int i = 0; i < lastDigit && digitSum - i >= 0; i++)
        sum += digitSumCount[numLength - 1][digitSum - i];

    // Recursive call for the next part of the number
    // Example: 12345 -> 2345, since the last digit 1 is taken care of in the loop above
    // and so we also subtract it from the number
    return sum + countDigitSum(number - lastDigit * pow(10, numLength - 1), digitSum - lastDigit);
}

/**
 * Finds the first number in the range [startRange, endRange] that has a digit sum of targetSum.
 * Uses binary search to optimize the search.
 * @return The first number in the range having a digit sum of targetSum.
 */
ll findFirstNumber()
{
    ll mid;
    // Binary search within the range [startRange, endRange]
    while (startRange != endRange)
    {
        mid = (startRange + endRange + 1) / 2;
        // Adjust search range based on the count of valid numbers
        if (countDigitSum(mid, targetSum) - countDigitSum(startRange, targetSum))
            endRange = mid - 1;
        else
            startRange = mid;
    }
    return startRange + 1;
}

/**
 * Main function.
 * Reads input, initializes DP, and calculates results.
 */
int main()
{
    // Initialize DP table
    init();

    // Read input
    cin >> startRange >> endRange >> targetSum;

    // Output the count of numbers in the range [startRange, endRange] with a digit sum of targetSum
    cout << countDigitSum(endRange, targetSum) - countDigitSum(startRange - 1, targetSum) << endl;

    // Output the first number in the range with a digit sum of targetSum
    cout << findFirstNumber() << endl;

    return 0;
}
