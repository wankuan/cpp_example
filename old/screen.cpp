// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Screen {
    friend class Window_mgr;

public:
    using pos = string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, char ch) : height(ht), width(wd), contents(ht * wd, ch) {}
    Screen &move(pos r, pos c);
    char get(pos r, pos c) const;

    Screen &set(char c);
    Screen &set(pos r, pos c, char ch);
    Screen &display(ostream &os) {
        do_display(os);
        return *this;
    }
    const Screen &display(ostream &os) const {
        do_display(os);
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
    void do_display(ostream &os) const { os << contents; }
};
inline Screen &Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}
inline char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}
inline Screen &Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}
Screen &Screen::set(pos r, pos c, char ch) {
    contents[r * width + c] = ch;
    return *this;
}
class Window_mgr {
public:
    using screen_index = vector<Screen>::size_type;
    void clear(void);
    Window_mgr(Screen *s) { p = s; }

private:
    Screen *p;
};

void Window_mgr::clear(void) { p->contents = string(p->height * p->width, ' '); }
int main() {
    Screen myscreen(2, 10, '*');
    myscreen.display(cout);
    cout << endl;
    myscreen.set(1, 9, 'M');
    myscreen.display(cout);
    cout << endl;
    cout << endl;
    Window_mgr mgr(&myscreen);
    mgr.clear();
    myscreen.display(cout);
    cout << endl;
}
