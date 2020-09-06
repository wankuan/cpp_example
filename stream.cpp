/**
 * @file stream.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-06-21
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <bitset>
#include <complex>
using namespace std;

#define FILE_NAME "xxx.log"
int main()
{
    // ofstream file("xxx.log");
    ofstream test_fstream;
    test_fstream.open(FILE_NAME);
    if(test_fstream.is_open() == true){
        cout << "open file sucess " << endl;
    }
    test_fstream << "test write into file22222222 " << endl;
    test_fstream << 231 << endl;
    test_fstream << 1.234 << endl;
    test_fstream.close();
    ofstream a2(FILE_NAME, ofstream::app);
    a2 << "running in the other file operator" << endl;
    test_fstream << bitset<8>(14) << endl;
    test_fstream << complex<int>(2,3) << endl;
    test_fstream.close();
    if(test_fstream.is_open() == true){
        cout << "open file sucess " << endl;
    }else{
        cout << "The file has closed or not open success" << endl;
    }



    // while(1){
    //     sleep(1);
    //     cout << "running " << endl;
    // }
}