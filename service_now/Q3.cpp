#include<bits/stdc++.h>
using namespace std;

int height(vector<int>& tree, int z, int i, int level) {
    if (i >= tree.size()) {
        return -1;  
    }
    if (tree[i] == z) {
        return level;
    }
    
    int left = height(tree, z, 2 * i + 1, level + 1);
    if (left != -1) return left;
    
    return height(tree, z, 2 * i + 2, level + 1);
}



int found(vector<int>& tree, int a, int b) {
    int x = height(tree, a, 0, 0);
    int y = height(tree, b, 0, 0);
    
    return x + y;
}

int main() {
    int size;
    cin >> size;
    if (size == 0) {
        cout << "No element in the tree" << endl;
        return 0;
    }
    
    vector<int> tree;
    cout << "Enter elements of the tree: ";
    for (int i = 0; i < size; i++) {
        int temp;
        cin >> temp;
        tree.push_back(temp);
    }
    
    int a, b;
    cout << "Enter elements to find: ";
    cin >> a >> b;
    
    int result = found(tree, a, b);
    if (result != -1) {
        cout << "Output: " << result << endl;
    }
    
    return 0;
}
