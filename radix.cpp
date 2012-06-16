#include "radix.hpp"

#include <cmath>
#include <map>
#include <queue>
#include <thread>

#include <iostream>

namespace j {
//  Prototypes      //
//
void rSort(List &list);
// Sort starting from highest digit.
void rSortMultiThreads (List &list, int begin, int end);
// Sort starting from lowest digit.
void rSortLowestToHighest (List &list, int begin, int end);

//  Implementations //
//
void rSort(List &list)
{
    // Return if list is empty.
    if (list.size() == 0) { return; }

    rSortMultiThreads(list, 0, list.size() - 1);
}

void rSortMultiThreads (List &list, int begin, int end)
{
    // Find out the largest number in the list.
    int largest = list[begin];
    for (int i = begin; i <= end; ++i) {
        if (largest < list[i]) {
            largest = list[i];
        }
    }

    // Find out the number of digits in the largest number.
    int k = 1;
    for (int n = largest; n >= 10; n /= 10, ++k);

    // Only need one bucket here.
    std::vector<std::queue<int> > bucket;
    for (int i = 0; i <= 9; ++i) {
        bucket.push_back(std::queue<int>());
    }

    // Need end marking records for sorting from highest digit.
    std::vector<int> record;
    for (int i = 0; i <= 9; ++i) {
        record.push_back(0);
    }

    // Sort from the highest digit once.
    // Prepare for multi-threading.
    for (int i = begin; i <= end; ++i) {
        int highestDigit = list[i] / std::pow(10, k - 1);
        bucket[highestDigit].push(list[i]);
    }

    for (unsigned i = begin, c = 0; c <= 9; ++c) {
        while (!bucket[c].empty()) {
            list[i] = bucket[c].front();
            bucket[c].pop();
            ++i;
            record[c] += 1;
        }
    }
    //std::cout << "List sorted by highest digit: ";
    //for (unsigned i = 0; i < list.size(); ++i) {
        //std::cout << list[i] << " ";
    //}
    //std::cout << std::endl << std::endl;
    //for (unsigned i = 0; i < record.size(); ++i) {
        //std::cout << record[i] << " ";
    //}
    //std::cout << std::endl << std::endl;

    // Start dispatching THREADS!!!
    int start = 0;
    std::vector<std::thread> tHolder;
    for (unsigned i = 0; i <= 9; start += record[i++]) {
        int end = start + record[i] - 1;
        std::cout << "this partition is: " << start << " to " << end << std::endl << std::endl;
        std::thread t(rSortLowestToHighest, std::ref(list), start, end);
        tHolder.push_back(std::move(t));
        //rSortLowestToHighest(list, start, end);
    }
    for (unsigned i = 0; i < tHolder.size(); ++i) {
        tHolder[i].join();
    }
}

void rSortLowestToHighest (List &list, int begin, int end)
{
    // Return if list is empty or contains only one element.
    if (begin >= end) { return; }

    // Find out the largest number in the list.
    int largest = list[begin];
    for (int i = begin + 1; i <= end; ++i) {
        if (largest < list[i]) {
            largest = list[i];
        }
    }

    // Find out the number of digits in the largest number.
    int k = 1;
    for (int n = largest; n >= 10; n /= 10, ++k);

    // Initialize buckets.
    std::vector<std::queue<int> > temp;
    for (int i = 0; i <= 9; ++i) {
        temp.push_back(std::queue<int>());
    }
    std::vector<std::queue<int> > buckets[k];
    for (int i = 0; i < k; ++i) {
        buckets[i] = temp;
    }

    // Sorting starts here.
    for (int i = 0; i < k; ++i) {
        for (int j = begin; j <= end; ++j) {
            int num = list[j];
            num %= static_cast<int>((std::pow(10, i + 1)));
            int curDigit = num / std::pow(10, i);
            buckets[i][curDigit].push(list[j]);
        }
        //std::cout << "This bucket is filled, digit - 1 = " << i << std::endl;
        for (unsigned j = begin, c = 0; c <= 9; ++c) {
            while (!buckets[i][c].empty()) {
                list[j] = buckets[i][c].front();
                buckets[i][c].pop();
                ++j;
            }
        }
        //std::cout << "The current list is: ";
        //for (unsigned i = 0; i < list.size(); ++i) {
            //std::cout << list[i] << " ";
        //}
        //std::cout << std::endl << std::endl;

    }
}

}
