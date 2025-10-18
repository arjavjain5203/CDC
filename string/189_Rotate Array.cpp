/*
🔹 Approach (Reversal Algorithm for Array Rotation):
To rotate the array to the right by k steps, we use the 3-step reverse method:

1. Reduce unnecessary rotations by using:
      k = k % size  
   (because rotating by the array length results in the same array)

2. Reverse the entire array.
   Example: [1,2,3,4,5,6,7] → [7,6,5,4,3,2,1]

3. Reverse the first 'k' elements.
   Example: k = 3 → [7,6,5 | 4,3,2,1] → [5,6,7 | 4,3,2,1]

4. Reverse the remaining elements.
   Final Result → [5,6,7,1,2,3,4]

✅ Example:
Input:  nums = [1,2,3,4,5,6,7], k = 3  
Output: [5,6,7,1,2,3,4]

🔹 Time Complexity:
O(n)  
(Each reverse call takes linear time, and we do it 3 times)

🔹 Space Complexity:
O(1)  
(All operations are done in-place without extra space)
*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k = k % size;                      // Handle values of k larger than size

        reverse(nums.begin(), nums.end());                       
        reverse(nums.begin() + k, nums.end());                   
        reverse(nums.begin(), nums.begin() + k);                 
    }
};
