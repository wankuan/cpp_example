#include <iostream>
#include <chrono>
#include <unistd.h>
using namespace std;
using namespace chrono;

int main()
{
    while(1){
        auto start = system_clock::now();
        sleep(1);
        auto end   = system_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        duration += 20ms;
        cout << "running time is " << duration.count() << "msß" << endl;
    }
    return 0;
}