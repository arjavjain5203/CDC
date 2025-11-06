#include <bits/stdc++.h>
using namespace std;

struct node {
    int data;
    node* next;
    node(int val) {
        data = val;
        next = nullptr;
    }
};

node* createLinkedList(vector<int>& values) {
    if (values.empty()) return nullptr;
    node* head = new node(values[0]);
    node* curr = head;
    for (int i = 1; i < values.size(); i++) {
        curr->next = new node(values[i]);
        curr = curr->next;
    }
    return head;
}

node* reverseList(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

node* merge(node* l1, node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    node* result = nullptr;

    if (l1->data < l2->data) {
        result = l1;
        result->next = merge(l1->next, l2);
    } else {
        result = l2;
        result->next = merge(l1, l2->next);
    }
    return result;
}

node* sortAlternatingList(node* head) {
    if (!head || !head->next) return head;

    node* asc = head;
    node* desc = head->next;

    node* ascCurr = asc;
    node* descCurr = desc;

    while (ascCurr->next && descCurr->next) {
        ascCurr->next = descCurr->next;
        ascCurr = ascCurr->next;
        if (ascCurr->next)
            descCurr->next = ascCurr->next;
        else
            descCurr->next = nullptr;
        descCurr = descCurr->next;
    }

    node* descRev = reverseList(desc);
    return merge(asc, descRev);
}

void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    cout << "Enter number of elements: ";
    int n;
    cin >> n;

    vector<int> values(n);
    cout << "Enter elements of linked list: ";
    for (int i = 0; i < n; i++) cin >> values[i];

    node* head = createLinkedList(values);

    cout << "Original alternating list: ";
    printList(head);

    node* sorted = sortAlternatingList(head);

    cout << "Sorted list in ascending order: ";
    printList(sorted);

    return 0;
}
