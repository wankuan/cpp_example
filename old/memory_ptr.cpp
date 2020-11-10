#include <iostream>
#include <memory>
#include <vector>

using namespace std;
int main() {
    // auto mm_pool = make_shared<int> (100,0);
    shared_ptr<int> sh_p = make_shared<int>(100);
    shared_ptr<int> p2 = make_shared<int>(200);
    int *test_get = p2.get();
    cout << "Before free, address is " << test_get << ",value is " << *test_get << endl;
    cout << "p.user_count() is " << sh_p.use_count() << endl;
    auto sh_p2 = sh_p;
    cout << "p.user_count() is " << sh_p.use_count() << endl;
    auto sh_p3 = sh_p;
    cout << "p.user_count() is " << sh_p.use_count() << endl;
    sh_p3 = p2;
    cout << "p.user_count() is " << sh_p.use_count() << endl;
    cout << "sh_p3.user_count() is " << sh_p3.use_count() << endl;
    p2 = sh_p2;
    sh_p3 = p2;
    cout << "After free, address is " << test_get << ",value is " << *test_get << endl;
}