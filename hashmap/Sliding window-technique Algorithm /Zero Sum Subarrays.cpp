/**
--------------------------------------------------------------------
✅ Problem: Count Subarrays with Sum 0

Given an array `arr[]`, find the **number of subarrays** whose sum equals 0.

--------------------------------------------------------------------
✅ Approach: Prefix Sum + HashMap (Frequency Count)

💡 **Idea:**
- Use a prefix sum to keep track of cumulative sums while iterating.
- Maintain an **unordered_map** to store how many times each prefix sum has appeared.
- If the same prefix sum appears again, it means the subarray between these occurrences has **sum = 0**.
- Add the frequency of that prefix sum to the count each time it reappears.

--------------------------------------------------------------------
✅ Implementation:
*/

class Solution {
public:
    int findSubarray(vector<int> &arr) {
        int n = arr.size();
        unordered_map<int, int> prefixFreq;  // prefix_sum → frequency
        int prefixSum = 0;
        int count = 0;

        prefixFreq[0] = 1;  // base case: prefix sum 0 before start

        for (int i = 0; i < n; i++) {
            prefixSum += arr[i];

            // if prefixSum already seen, all previous occurrences form subarrays with sum 0
            if (prefixFreq.find(prefixSum) != prefixFreq.end()) {
                count += prefixFreq[prefixSum];
            }

            // increment frequency of current prefixSum
            prefixFreq[prefixSum]++;
        }

        return count;
    }
};

/**
--------------------------------------------------------------------
✅ Dry Run Example:

Input:
arr = [0, 0, 5, 5, 0, 0]

Prefix sums:
index:  0   1   2   3   4   5
arr:    0   0   5   5   0   0
sum:    0   0   5  10  10  10

Occurrences:
- sum 0 → appears multiple times → subarrays ending at those indices have sum 0
- sum 10 → appears 3 times → contributes additional zero-sum subarrays

Output: 6

--------------------------------------------------------------------
✅ Time Complexity:
O(n) — one pass through the array

✅ Space Complexity:
O(n) — for storing prefix sum frequencies

✅ Concepts Used:
- Prefix Sum
- HashMap (frequency counting)
- Cumulative Sum Technique
--------------------------------------------------------------------
*/
