/**
 * @file vector.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-06-14
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> buffer(1000);
    cout << "The capacity is " << buffer.capacity() << endl;
    buffer.push_back(666);
    cout << "After push a ele, the capacity is " << buffer.capacity() << endl;
    cout << "After push a ele, the vector size is " << buffer.size() << endl;
    for(uint16_t i=0;i<500;++i){
        buffer.push_back(666);
    }
    buffer.reserve(3000);
    cout << "After reverse, the capacity reserver is " << buffer.capacity() << endl;
    cout << "After reverse, the vector size is " << buffer.size() << endl;

    buffer.shrink_to_fit();
    cout << "After shrink_to_fit, the capacity reserver is " << buffer.capacity() << endl;
    cout << "After shrink_to_fit, the vector size is " << buffer.size() << endl;
}