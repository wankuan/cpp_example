/**
 * @file iterator.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-06-13
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <vector>
#include <iostream>
#include <typeinfo>
// using std::vector;
using namespace std;

int add(int a, int b)
{
    return a+b;
}
int add(int a, int b, int c)
{
    return a+b+c;
}
int add(int a, int b, int c, int d)
{
    return a+b+c+d;
}
int main(int argc, char *argv[])
{
    auto get_num = atol(argv[1]);
    vector<int> text = {2,3,4,5,6,7,8,9,10};
    text.push_back(11);
    for(auto &ele : text){
        cout << "The value is " << ele << endl;
    }
    cout << "size is " << text.size() << endl;
    auto beg = text.begin();
    auto end = text.end();
    cout << "iterator size " << end-beg << endl;
    while(beg != end){
        *beg = 0;
        ++beg;
    }
    text.back() = 100;

    for(auto &ele : text){
        cout << "After use iterator, the value is " << ele << endl;
    }
    auto mid = beg + (end - beg)/2;
    while(*mid != get_num && mid != end){
        if(get_num < *mid){
            end = mid;
        }else{
            beg = mid+1;
        }
        mid = beg + (end - beg)/2;
    }
    cout << "The num posi is " << mid-text.begin() << endl;
    vector<int> groups(10, 0);
    vector<int>::iterator it;
    vector<int>::const_iterator it2;
    auto a = groups.begin();
    it = groups.begin();
    it2 = groups.begin();
    cout << *it2 << endl;
    for(auto &ele : groups){
        *it = 1;
        it++;
        cout << "The value is " << ele << endl;
    }
    if(typeid(a) == typeid(it)){
        cout << "The type is the same!" << endl;
    }

    cout << add(10, 20) << endl;
    return 0;
}