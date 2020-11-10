#include <iostream>
#include <string>
using namespace std;

string::size_type a;

class Person {
    friend istream &read(istream &is, Person &p);
    friend ostream &printInf(ostream &os, Person &p);

public:
    Person(istream &s);  //外部构造函数声明
    ~Person(void);       //外部析构函数声明
    string getName(void) const {
        return name;
    }
    string getAddress(void) const {
        return address;
    }
    void setName(string name) {
        this->name = name;
    }
    void setAddress(string address) {
        this->address = address;
    }

private:
    string name;
    string address;
};

istream &read(istream &is, Person &p) {
    is >> p.name >> p.address;
    return is;
}
ostream &printInf(ostream &os, Person &p) {
    os << p.name << " " << p.address;
    return os;
}
Person::Person(istream &s) {
    cout << "The object is being created" << endl;
    read(s, *this);
}
Person::~Person(void) {
    cout << "The object is being deleted" << endl;
}

int main() {
    Person p1(cin);
    printInf(cout, p1);
    cout << endl;
    return 0;
}
