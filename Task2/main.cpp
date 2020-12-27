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

class ALGraph{
private:
    typedef struct ENode{
        int ivex;
        int weight;
        ENode *nextEdge;
    }ENode;

    typedef struct VNode{
        int data;
        VNode *firstEdge;
    }VNode;

    VNode *mVexs;
    int length = 1;


public:
    ALGraph(int num){
        mVexs = new VNode[num+1];
    }


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
