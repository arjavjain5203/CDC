/*
🔹 Approach (Bubble Sort):
Repeatedly compare adjacent elements and swap them if they are in the wrong order.
In each pass, the largest remaining element "bubbles up" to its correct position.

🔹 Time Complexity:
- Worst Case: O(n²)
- Average: O(n²)
- Best Case: O(n)  (when already sorted)

🔹 Space Complexity: 
O(1)  (in-place sorting)

🔹 Stable: ✅ Yes
*/

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped) break;  // Optimization: stop if no swap happened
    }
}
