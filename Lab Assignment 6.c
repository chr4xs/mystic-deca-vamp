#include <stdio.h>

int search(int num[], int low, int high, int val) {
    if (low > high) {
        // Base case: value not found
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (num[mid] == val) {
        // Base case: value found at mid index
        return mid;
    } else if (num[mid] > val) {
        // Recursive case: search in the left half
        return search(num, low, mid - 1, val);
    } else {
        // Recursive case: search in the right half
        return search(num, mid + 1, high, val);
    }
}

int main() {
    int num[] = {1, 3, 5, 7, 9, 11};
    int low = 0;
    int high = 5;
    int val = 7;
    
    int index = search(num, low, high, val);
    
    if (index != -1) {
        printf("Value %d found at index %d\n", val, index);
    } else {
        printf("Value %d not found in the array\n", val);
    }

    return 0;
}
