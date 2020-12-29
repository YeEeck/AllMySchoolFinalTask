#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;


int safeInputInt() {
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

class ALGraph {
private:
    typedef struct ENode {
        int ivex;
        int weight;
        ENode *nextEdge;
    } ENode;

    typedef struct VNode {
        string data;
        ENode *firstEdge;
    } VNode;

    VNode mVexs[1000];
    int length = 0;

    int vis[1000] = {0};


public:
    ALGraph(int num) {

    }


    void addDot(const string &data) {
//        VNode *nVNode = new VNode;
//        nVNode->data = data;
//        nVNode->firstEdge = NULL;
//        mVexs[length] = *nVNode;
        mVexs[length].data = data;
        mVexs[length].firstEdge = NULL;
        length++;
    }

    int addEdge(const string &p1, const string &p2, int weight) {
        int pos1 = getPos(p1);
        int pos2 = getPos(p2);
        if (pos1 == -1 || pos2 == -1) {
            return -1;
        }
        ENode *nENode1 = new ENode;
        nENode1->ivex = pos2;
        nENode1->nextEdge = NULL;
        nENode1->weight = weight;
        if (mVexs[pos1].firstEdge == NULL) {
            mVexs[pos1].firstEdge = nENode1;
        } else {
            ENode *r = mVexs[pos1].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos2) {
                    return -2;
                }
                r = r->nextEdge;

            }
            r->nextEdge = nENode1;
        }
        ENode *nENode2 = new ENode;
        nENode2->ivex = pos1;
        nENode2->nextEdge = NULL;
        nENode2->weight = weight;
        if (mVexs[pos2].firstEdge == NULL) {
            mVexs[pos2].firstEdge = nENode2;
        } else {
            ENode *r = mVexs[pos2].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos1) {
                    return -2;
                }
                r = r->nextEdge;
            }
            r->nextEdge = nENode2;
        }
        return 0;
    }

    int getPos(const string &data) {
        for (int i = 0; i < length; ++i) {
            if (mVexs[i].data == data) {
                return i;
            }
        }
        return -1;
    }

    int dp[100][100];

    int *dfsb(int from, int to) {
        int weight = 0;
        int *res = new int[length]{0};
        if (from == to) {
            res[0] = 0;
            res[1] = 0;
            return res;
        }
        if (vis[from]) {
            return dp[from];
        }
        vis[from] = 1;

        ENode *r = mVexs[from].firstEdge;
        int *list;
        res[0] = 1000000;
        int maxList[100] = {0};
        while (r) {
            list = dfsb(r->ivex, to);
            if (list == NULL || list[1] == -1) {
                r = r->nextEdge;
                continue;
            }
            if (list[0] < res[0]) {
                res[0] = list[0];
                memset(maxList, 0, 100);
                for (int i = 0; i < list[1] + 2; ++i) {
                    maxList[i] = list[i];
                }
                weight = r->weight;
                res[0] += weight;
            }
            r = r->nextEdge;
        }
        if (res[0] == 1000000) {
            return NULL;
        }
        res[1] = maxList[1] + 1;
        for (int i = 0; i < maxList[1]; ++i) {
            res[2 + i] = maxList[2 + i];
        }
        res[2 + maxList[1]] = from;
        for (int i = 0; i < res[1] + 2; ++i) {
            dp[from][i] = res[i];
        }
        return res;
    }

    int *dfs(int from, int to) {
        memset(vis, 0, 1000);
        memset(dp, -1, 10000);
        int *res = dfsb(from, to);
        return res;
    }

    string getData(int index) {
        if (index >= length) return "none";
        return mVexs[index].data;
    }

    void display() {
        for (int i = 0; i < length; ++i) {
            cout << i + 1 << "." << mVexs[i].data << endl;
        }
    }

//    void del(int data) {
//        int pos = data - 1;
//        ENode *r = mVexs[pos].firstEdge;
//        while (r) {
//            if (mVexs[r->ivex].firstEdge->ivex == pos) {
//                ENode *t = mVexs[r->ivex].firstEdge;
//                mVexs[r->ivex].firstEdge = mVexs[r->ivex].firstEdge->nextEdge;
//                delete (t);
//                continue;
//            }
//            ENode *p = mVexs[r->ivex].firstEdge;
//            ENode *pp = p->nextEdge;
//            while (pp) {
//                if (pp->ivex == pos) {
//                    p->nextEdge = pp->nextEdge;
//                    delete (pp);
//                    break;
//                }
//                p = p->nextEdge;
//                pp = pp->nextEdge;
//            }
//            ENode *t = r;
//            r = r->nextEdge;
//            delete (t);
//        }
//        mVexs[pos].data = "";
//    }

    int getLength() {
        return length;
    }
};


void getRoad(ALGraph alGraph) {
    cout << "\n请输入你的位置:";
    int pos = safeInputInt();
    cout << "\n请输入你要到达的位置:";
    int dist1 = safeInputInt();
    int *list = alGraph.dfs(pos - 1, dist1 - 1);
    if (list == NULL) {
        cout << "\n没有合适的路线" << endl;
    } else {
        cout << "\n找到线路，总长为 " << list[0] << " ，需经过 " << list[1] << " 个导航点" << endl;
        for (int i = list[1] + 1; i >= 2; --i) {
            if (i == 2) {
                cout << alGraph.getData(list[i]) << "->" << alGraph.getData(dist1 - 1);
                break;
            }
            cout << alGraph.getData(list[i]) << "->";

        }
        cout << endl;
    }
}

void del(const string &str) {
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string temp;
    while (getline(file, temp)) {
        if (temp.find(str) != std::__cxx11::string::npos) {
            continue;
        }
        tempF << temp;
        tempF << endl;
    }
    file.close();
    tempF.close();
    remove("data.txt");
    ofstream file2("data.txt");
    ifstream tempF2("temp.txt");
    while (getline(tempF2, temp)) {
        file2 << temp;
        file2 << endl;
    }
    file2.close();
    tempF2.close();
    remove("temp.txt");
}

void add(ALGraph *alGraph) {
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string name;
    while (true) {
        cout << "请输入要添加的导航点的名称:";
        cin >> name;
        if (alGraph->getPos(name) == -1) {
            break;
        } else {
            cout << "\n已有同名点存在，请重新输入" << endl;
        }
    }
    tempF << "A " << name;
    tempF << endl;
    string temp;
    while (getline(file, temp)) {
        tempF << temp;
        tempF << endl;
    }
    while (true) {
        cout << "\n请输入要连接到这个导航点的导航点的序号(输入-1结束):";
        int num = safeInputInt();
        if (num == -1) {
            break;
        }
        cout << "\n请输入要连接到这个导航点的导航点与这个导航点的权值:";
        int weight = safeInputInt();
        if (alGraph->getData(num - 1) != "none") {
            tempF << "B " << name << " " << alGraph->getData(num - 1) << " " << weight;
            tempF << endl;
        }
    }
    file.close();
    tempF.close();
    remove("data.txt");
    ofstream file2("data.txt");
    ifstream tempF2("temp.txt");
    while (getline(tempF2, temp)) {
        file2 << temp;
        file2 << endl;
    }
    file2.close();
    tempF2.close();
    remove("temp.txt");
}

int main() {
    first:;
    ALGraph alGraph(100);
    //init
    ifstream file("data.txt", ios::in);
    if (!file.is_open()) {
        cout << "错误:数据文件不存在" << endl;
        getchar();
        getchar();
        return 0;
    }
    string temp;
    while (getline(file, temp)) {
        if (temp[0] == 'A') {
            alGraph.addDot(temp.substr(2, temp.length() - 2));
        } else if (temp[0] == 'B') {
            int posBlank = temp.find(' ');
            posBlank = temp.find(' ', posBlank + 1);
            int posBlank2 = temp.find(' ', posBlank + 2);
            alGraph.addEdge(temp.substr(2, posBlank - 2), temp.substr(posBlank + 1, posBlank2 - (posBlank + 1)),
                            stoi(temp.substr(posBlank2 + 1, temp.length() - (posBlank2 + 1))));
        }
    }
    file.close();
//    alGraph.addDot("大门");
//    alGraph.addDot("图书馆");
//    alGraph.addDot("实验楼D");
//    alGraph.addDot("实验楼C");
//    alGraph.addDot("实验楼B");
//    alGraph.addDot("实验楼A");
//    alGraph.addDot("教学楼A");
//    alGraph.addDot("教学楼B");
//    alGraph.addDot("教学楼C");
//    alGraph.addDot("操场");
//    alGraph.addDot("宿舍楼D");
//    alGraph.addDot("宿舍楼C");
//    alGraph.addDot("三食堂");
//    alGraph.addDot("超市");
//    alGraph.addDot("一食堂");
//    alGraph.addDot("体育馆");
//
//    alGraph.addEdge("大门", "图书馆", 100);
//    alGraph.addEdge("大门", "实验楼D", 30);
//    alGraph.addEdge("实验楼D", "实验楼C", 20);
//    alGraph.addEdge("实验楼C", "实验楼B", 20);
//    alGraph.addEdge("实验楼B", "实验楼A", 20);
//    alGraph.addEdge("实验楼A", "图书馆", 20);
//    alGraph.addEdge("大门", "教学楼A", 10);
//    alGraph.addEdge("教学楼A", "教学楼B", 20);
//    alGraph.addEdge("教学楼B", "教学楼C", 20);
//    alGraph.addEdge("教学楼C", "图书馆", 20);
//    alGraph.addEdge("图书馆", "操场", 50);
//    alGraph.addEdge("操场", "超市", 10);
//    alGraph.addEdge("图书馆", "宿舍楼D", 50);
//    alGraph.addEdge("宿舍楼D", "宿舍楼C", 50);
//    alGraph.addEdge("宿舍楼C", "三食堂", 20);
//    alGraph.addEdge("宿舍楼C", "超市", 10);
//    alGraph.addEdge("超市", "三食堂", 10);
//    alGraph.addEdge("三食堂", "一食堂", 100);
//    alGraph.addEdge("体育馆", "教学楼C", 100);
//    alGraph.addEdge("体育馆", "一食堂", 10);
    //init end
    while (true) {
        cout << "------欢迎使用紫金学院导航系统------" << endl;
        cout << "导航点:" << endl;
        alGraph.display();
        cout << endl << "操作选项:" << endl;
        cout << "A.导航至某一导航点" << endl;
        cout << "B.删除指定导航点" << endl;
        cout << "C.添加某一导航点" << endl;
        cout << "D.结束程序" << endl;
        cout << "------------------------------------" << endl;
        char t;
        while (true) {
            string str;
            cout << "请输入你要执行的操作:";
            cin >> str;
            if (str.length() != 1) {
                cout << "输入有误，请重新输入" << endl;
                continue;
            }
            t = toupper(str[0]);
            break;
        }

        //route
        switch (t) {
            case 'A': {
                getRoad(alGraph);
                system("pause");
                system("cls");
                break;
            }

            case 'B': {
                cout << "请输入要删除的导航点序号:";
                int pos = safeInputInt() - 1;
                string delStr = alGraph.getData(pos);
                if (pos < 0 || pos > alGraph.getLength()) {
                    cout << "输入的序号有误" << endl;
                    system("pause");
                    system("cls");
                    break;
                } else {
                    del(alGraph.getData(pos));
                    system("pause");
                    system("cls");
                    goto first;
                }
            }

            case 'C': {
                add(&alGraph);
                system("pause");
                system("cls");
                goto first;
            }

            case 'D': {
                exit(0);
            }
            default: {
                cout << "错误的输入选项，请重新输入" << endl;
                system("pause");
            }
        }
    }
}
