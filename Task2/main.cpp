#include <iostream>

using namespace std;


int safeInputInt(){
    int data;
    while (true) {
        cin >> data;
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "输入的 " << str << " 不是一个有效的选项" << endl;
            cout << "请重新输入:";
        } else {
            break;
        }
    }
    return data;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
