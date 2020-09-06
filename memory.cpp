#include <iostream>
#include <chrono>
#include <unistd.h>
using namespace std;
using namespace chrono;

int main()
{
    // int *p = new int(2^100);

    int *test = new (nothrow) int[1402];
    if(test == nullptr){
        cout << "malloc fail" << endl;
    }else{
        cout << "malloc success" << endl;
    }
    delete [] test;
    test = nullptr;
    if(test == nullptr){
        cout << "malloc fail" << endl;
    }else{
        cout << "malloc success" << endl;
    }
    while(1){
        auto start = system_clock::now();
        sleep(1);
        auto end   = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "running time is " << duration.count() << "us" << endl;
    }
    return 0;
}