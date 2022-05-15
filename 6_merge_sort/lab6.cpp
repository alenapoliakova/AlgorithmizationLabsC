#include <stdio.h>
#include <stdlib.h>


void print_array(int* array, int len) {
    for (int i = 0; i <= len; i++){
        printf("%d ", array[i]);
    }
}

void print_slice(int* array, int start_pos, int end_pos) {
    for (int i = start_pos; i <= end_pos; i++){
        printf("%d ", array[i]);
    }
}


void merge(int* array, int left, int right) {
    // Слияние двух массивов, left - левый массив, right - правый массив

    int* sorted_array = (int*)malloc((right - left + 1) * sizeof(int));
    int j, i, n = 0;

    for (i = left, j = (right + left) / 2 + 1; (i <= (left + right) / 2) && (j <= right);) {
        if (array[i] <= array[j]) {
            sorted_array[n] = array[i];
            i++;
        }
        else {
            sorted_array[n] = array[j];
            j++;
        }
        n++;
    }
    n--;
    while (i <= (left + right) / 2) {
        n++;
        sorted_array[n] = array[i];
        i++;
    }
    while (j <= right) {
        n++;
        sorted_array[n] = array[j];
        j++;
    }

    // Замена значений
    for (i = 0; i <= right - left; i++)
        array[i + left] = sorted_array[i];
}


void mergeSort(int* a, int left, int right, int count) {
    if (left < right) {
        int middle_position = (left + right) / 2;
        printf("x=%d l=%d r=%d  ", a[middle_position], left, right);
        print_array(a, count);
        printf("\n");

        mergeSort(a, left, middle_position, count);  // Сначала отсортировать левую часть
        mergeSort(a, middle_position+1, right, count);  // Отсортировать правую часть

        print_slice(a, left, middle_position);
        printf("& ");
        print_slice(a, middle_position+1, right);

        merge(a, left, right);  // Объединение массивов
        printf("  sort: ");
        print_slice(a, left, right);
        printf("\n");
    }
}

int main() {
    int nums[7]={10, 6, 7, 1, 3, 9, 4};
    int size = sizeof(nums) / sizeof(nums[0]) - 1;

    printf("before sort: ");
    print_array(nums, size);
    printf("\n\n");

    int left = 0;
    int right = size;

    mergeSort(nums, left, right, size);

    printf("\nafter sort: ");
    print_array(nums, size);
}
