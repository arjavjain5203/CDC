/*
🔹 Approach (Two-Pointer Technique):
This method removes duplicates from a sorted array in-place

1. Since the array is sorted, duplicates appear consecutively.
2. We maintain a pointer `j` which tracks the position of the next unique element.
3. We iterate from index 1 onward using `i`:
   - If nums[i] != nums[i - 1], it means we found a new unique element.
   - We assign it to nums[j] and increment j.

4. After the loop, `j` represents the count of unique elements
   and also the new length of the modified array.

✅ Example:
Input:  nums = [1,1,2,2,3]
Process:
i=1 → same as prev → skip  
i=2 → different → nums[1]=2  
i=3 → same → skip  
i=4 → different → nums[2]=3  
Final array (first j elements): [1, 2, 3]
Return: 3

🔹 Time Complexity:
O(n)  
(We traverse the array only once)

🔹 Space Complexity:
O(1)  
(Everything is done in-place; no extra space used)

*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        
        int j = 1;  // Pointer to place the next unique element

        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] != nums[i - 1]) {      // Found a new unique element
                nums[j++] = nums[i];          // Place it at index j, then increment j
            }
        }

        return j;  // j is the count of unique elements
    }
};
