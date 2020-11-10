/**
 * @file template.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-06-21
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T square(T x) {
    return x * x;
}

template <typename T>
class bot_vector {
    typename vector<T>::size_type size;

public:
    vector<T> arr;
    bot_vector() = default;
    bot_vector(const initializer_list<T> &v) : size(0) {
        for (auto beg = v.begin(); beg != v.end(); ++beg) {
            arr.push_back(*beg);
            ++size;
        }
    }
    void push(T x) {
        arr.push_back(x);
        size++;
    }
    void printf();
    typename vector<T>::size_type get_size() { return size; }

private:
};

template <typename T>
bot_vector<T> operator*(bot_vector<T> a1, bot_vector<T> a2) {
    bot_vector<T> ret;
    typename vector<T>::size_type i = 0;
    for (i = 0; i < a1.get_size(); ++i) {
        ret.push(a1.arr[i] * a2.arr[i]);
    }
    return ret;
}

template <typename T>
void bot_vector<T>::printf() {
    for (auto &val : arr) {
        cout << val << endl;
    }
}

int main() {
    int *p = nullptr;
    cout << square(5) << endl;
    cout << square(5.5) << endl;

    bot_vector<double> bot = {1, 2, 3, 4};
    // bot.push(1.1);
    // bot.push(2.2);
    // bot.push(3.3);
    // bot.push(4.4);
    bot.printf();
    auto new_bot = square(bot);
    new_bot.printf();

    int *ptr = new int[100];
    ptr = nullptr;
    int *a2 = (int *)malloc(200);
    a2 = nullptr;
}