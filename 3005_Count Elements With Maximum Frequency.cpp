/*
🔹 Approach:
1. We maintain a frequency array `count` of size 101 to store the occurrences of numbers 
   (based on the assumption that values in nums are in the range 0–100).
2. In the first loop, we count the frequency of each element and track the maximum frequency.
3. In the second loop, we count how many elements occur with this maximum frequency.
4. Finally, we compute the total elements that have the maximum frequency as: maxfreq * count

✅ Example:
Input: nums = [1,2,2,3,1,4]
Frequencies → {1:2, 2:2, 3:1, 4:1}
Maximum frequency = 2
Elements with this frequency: 1 and 2 → 2 numbers
Answer = 2 * 2 = 4

🔹 Time Complexity:
O(n + k)  
- O(n) for iterating over nums  
- O(k) for scanning the frequency array (here k = 101)

🔹 Space Complexity:
O(1)  
Size of frequency array is constant (101)
*/

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        vector<int> count(101, 0);  // Frequency array
        int maxfreq = 0;
        int c = 0;  // Number of elements having max frequency
        int ans = 0;

        // Count frequencies and track max frequency
        for (int num : nums) {
            count[num]++;
            maxfreq = max(maxfreq, count[num]);
        }

        // Count how many elements have the max frequency
        for (int i = 0; i < 101; i++) {
            if (count[i] == maxfreq) {
                c++;
            }
            ans = maxfreq * c;
        }

        return ans;
    }
};
