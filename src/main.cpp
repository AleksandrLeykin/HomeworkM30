#include <iostream>
#include <random>
#include <chrono>
#include "myQuickSort.h"


int main(int, char**){    
    srand(0);
    long arr_size = 10000000;
    int* array = new int[arr_size];
    for(long i = 0; i < arr_size; ++i) {
       array[i] = rand() % 500;
    }
    // std::cout << "not sort ";
    // for (int i = 0; i < arr_size; i++) {
    //     if(i % 10000 == 0)
    //     std::cout << array[i] << " ";
    // }    
    std::cout << "\n";

    Quicksort qs;    
    auto begin = std::chrono::steady_clock::now();    
    qs.quicksort(array, 0, arr_size);
    auto end = std::chrono::steady_clock::now();  
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Thread sort. The time: " << elapsed_ms.count() << " ms\n";

    //проверка сортировки
    for(long i = 0; i< arr_size - 1; ++i) {
       if (array[i] > array[i + 1]) {
         std::cout << "Unsorted" << std::endl;
         break;
       }
    }
    // std::cout << "Sort thread ";
    // for (int i = 0; i < arr_size; i++) {
    //     if(i % 10000 == 0)
    //     std::cout << array[i] << " ";
    // }    
    std::cout << "\n";

    for(long i = 0; i < arr_size; ++i) {
       array[i] = rand() % 500;
    }

    // однопоточный запуск
    qs.make_thread = false;

    begin = std::chrono::steady_clock::now(); 
    qs.quicksort(array, 0, arr_size);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "No thread sort. The time: " << elapsed_ms.count() << " ms\n";

    //проверка сортировки
    for(long i = 0; i< arr_size - 1; ++i) {
       if (array[i] > array[i + 1]) {
         std::cout << "Unsorted" << std::endl;
         break;
       }
    }
    // std::cout << "Sort not thread ";
    // for (int i = 0; i < arr_size; i++) {
    //     if(i % 10000 == 0)
    //     std::cout << array[i] << " ";
    // }    
    // std::cout << "\n";

    delete[] array;
    return 0;
}
