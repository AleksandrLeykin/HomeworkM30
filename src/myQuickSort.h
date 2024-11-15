#ifndef MYQUICKSORT_H
#define MYQUICKSORT_H

#include <future> 
#include "RequestHandler.h"


struct Quicksort {
    void Thread_f(int* array, long left, long right, std::shared_ptr<std::promise<void>> promise);
    void quicksort(int *array, long left, long right);
    bool make_thread = true;  
};


void Quicksort::Thread_f(int* array, long left, long right, std::shared_ptr<std::promise<void>> promise) {
    std::future<void> f = std::async(std::launch::async, [&]() { quicksort(array, left, right); });
    f.wait();
    promise->set_value();
} 

void Quicksort::quicksort(int *array, long left, long right) {
   if(left >= right) return;

   long left_bound = left;
   long right_bound = right;

   long middle = array[(left_bound + right_bound) / 2];

   do {
       while(array[left_bound] < middle) {
           left_bound++;
       }
       while(array[right_bound] > middle) {
           right_bound--;
       }

       //Меняем элементы местами
       if (left_bound <= right_bound) {
           std::swap(array[left_bound], array[right_bound]);
           left_bound++;
           right_bound--;
       }
   } while (left_bound <= right_bound);
    
    auto promise = std::make_shared<std::promise<void>>();

   if(make_thread && (right_bound - left > 10000)) {
        RequestHandler pool;
        // если элементов в левой части больше чем 10000 вызываем асинхронно рекурсию для правой части
        pool.push_task(&Quicksort::Thread_f, this, std::ref(array),left,right_bound, promise);
        quicksort(array, left_bound, right);
        //f.wait(); // нельзя так написать
    } else {
        // запускаем обе части синхронно
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
   }
}

#endif