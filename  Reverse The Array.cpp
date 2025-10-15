/*
🔹 Approach:
The function reverses the part of the array that comes **after index m**.
Two pointers (`start = m+1` and `stop = arr.size() - 1`) are used to swap elements 
until they meet or cross. This efficiently reverses the subarray in-place.

🔹 Time Complexity:  
O(n - m) ≈ O(n) in the worst case  
(Each element in the second part of the array is visited once)

🔹 Space Complexity:  
O(1)  
(No extra data structure is used; reversal is done in-place)

*/

void reverseArray(vector<int> &arr , int m) {
    int start = m + 1;
    int stop = arr.size() - 1;
    
    while(start < stop) {
        swap(arr[start], arr[stop]);
        start++;
        stop--;
    }
}
