#include <iostream>
#include <string>
#include <string.h>

using namespace std;
class A{
public:
    A(){cout<<"default constructor no name"<<endl;}
    A(char *_name){
        name = (char *)malloc(strlen(_name));
        strcpy(name, _name);
        cout<<"default constructor addr: " << (void*)name << endl;
        cout<<"default constructor this: " << (void*)this << endl;
    }
    A(const A &a){
        cout<<"copy constructor, deep copy"<<endl;
        name = (char *)malloc(strlen(a.name));
        strcpy(name, a.name);
        cout<<"[copy] constructor this: " << (void*)this << endl;
        cout<<"[copy]before addr:0x"<<(void*)name<<endl;
    }
    A(A &&a){
        cout<<"move constructor"<<endl;
        name=a.name;
        a.name = nullptr;
        cout<<"[move]before addr:0x"<<(void*)name<<endl;
    }
    void printf_addr(){cout<<"name addr:0x"<<(void*)name<<endl;}
    void printf_name(){cout<<"name :"<<name<<endl;}
    ~A(){
        cout<< "Deconstructor this " << (void*)this << endl;
        cout << "free addr " << (void*)name << endl;
        free(name);
    }
// private:
    char *name;
};

char *my_name = (char*)"huang";

A getA_dire_return(void)
{
    A a(my_name);
    cout << "return" << endl;
    return a;
}
A &&getA_rvalue_return(void)
{
    A a(my_name);
    return move(a);
}

int main()
{
    // auto a = getA_dire_return();
    A a(my_name);
    a.printf_addr();
    a.printf_name();
    cout << "move to B" << endl;
    // auto B = move(a); // 使用移动构造
    auto B = a; // 使用拷贝构造
    B.printf_addr();
    B.printf_name();
    return 0;
}