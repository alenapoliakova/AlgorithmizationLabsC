#include <stdio.h>
#include <stdlib.h>


void print_array(int* arr, int length){
    for (int i = 0; i <= length; i++){
        printf("%d ", arr[i]);
    }
}

// Поднятие или всплытие
void elevate(int* mass, int i){
    if (i==0) {
        return;
    }
    int parent = (i - 1) / 2;
    while ((mass[i] > mass[parent])) {
        int x = mass[i];
        mass[i] = mass[parent];
        mass[parent] = x;
        
        if (parent == 0) break;
        
        i = parent;
        parent = (i - 1) / 2;
    }
}

// Создание кучи
void MakeHeap(int* mass, int i, int num) {
    mass[i] = num;
    if (i == 0) {
        return;
    }
    elevate(mass, i);  // Поднятие или всплытие
}

void Heap(int* mass, int n, int i){
    int pos = i;
    int left = 2 * i + 1;  // Левый ребёнок
    int right = 2 * i + 2;  // Правый ребёнок

    if (left < n && mass[left] > mass[pos]) {
        pos = left;
    }
    if (right < n && mass[right] > mass[pos]) {
        pos = right;
    }
    if (pos != i) {
        int y = mass[pos];
        mass[pos] = mass[i];
        mass[i] = y;
        Heap(mass, n, pos);
    }
}

void HeapSort(int* mass, int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        Heap(mass, n, i);
    }
    int ii = -1;
    for (int i = n - 1; i >= 0; i--) {
        int xc = mass[0];
        mass[0] = mass[i];
        mass[i] = xc;
        Heap(mass, i, 0);
        for (int  j= 0; j < n; j++){
            printf("%d ", mass[j]);
        }
        ii++;
        printf("n = %d", n-ii-1);
        printf("\n");
    }
    printf("After sort: ");
    for (int j = 0; j < n; j++){
        printf("%d ", mass[j]);
    }
    printf("\n");
}

int get_max(int* mass, int n){
    int count = -1;
    int max = -1;
    for (int i = 0; i < n+1; i++){
        if (max < mass[i]){
            max = mass[i];
            count++;
        }
    }
    mass[count] = mass[n];
    mass[n] = 0;
    for (int i = 0; i <= n; i++) {
        elevate(mass, i);
    }
    return max;
}

int main() {
    int nums[5] = {7, 1, 5, 4, 3};
    int size = sizeof(nums) / sizeof(nums[0]) - 1;
    
    printf("Before sort: ");
    print_array(nums, size);
    printf("\n");

    int* array = (int*)malloc((size) * sizeof(int));
    printf("Make heap\n");

    for (int i = 0; i <= size; i++) {
        MakeHeap(array, i, nums[i]);
        for (int j = 0; j <= i; j++) {
            printf("%d ", array[j]);
        }
        printf("n = %d\n", i + 1);
    }

    printf("Heap:\n");
    print_array(array, size);
    printf("n = %d\n", size+1);

    HeapSort(array, size+1);
    printf("\n");

    // Поиск максимального элемента
    
    // int max_elem = get_max(array, size);
    // size = size - 1;
    // printf("Max element: %d\n", max_elem);
    // printf("After find max: ");
    // print_array(array, size);

    // free(array);
}
