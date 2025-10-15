/*
🔹 Approach:
We create a result array `ans` of the same size as `nums`.  
The first element remains the same as nums[0].  
From index 1 onward, each element `ans[i]` is calculated as:
      ans[i] = ans[i-1] + nums[i]
This forms the cumulative (running) sum.

✅ Example:
Input:  [1, 2, 3, 4]
Output: [1, 3, 6, 10]

🔹 Time Complexity: 
O(n)  
(We iterate through the array once)

🔹 Space Complexity:
O(n)  
(We use an additional vector `ans` of the same size as nums)
*/

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);

        ans[0] = nums[0];  // Initialize first element

        for (int i = 1; i < nums.size(); i++) {
            ans[i] = nums[i] + ans[i - 1];  // Add current num to previous sum
        }

        return ans;
    }
};
