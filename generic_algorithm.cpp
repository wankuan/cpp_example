/**
 * @file generic_algorithm.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-06-14
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> groups = {1, 2, 3, 4, 5};
    vector<int>::value_type value;
    cout << "Please input the num your found" << endl;
    cin >> value;
    auto pos = find(groups.cbegin(), groups.cend(), value);
    if (pos == groups.cend()) {
        cout << "can not find the value" << endl;
    } else {
        cout << "fine the value" << endl;
        cout << "The pos is " << pos - groups.cbegin() << endl;
        cout << "The value is " << *pos << endl;
    }
}