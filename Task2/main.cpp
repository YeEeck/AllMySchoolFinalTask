#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

//安全输入整数(输入纠错)
int safeInputInt() {
    int data;
    while (true) {
        cin >> data;
        //调用cin.fail()捕获输入出错，cin.clear()清除缓存区中错误数据。
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
    //返回经过纠错的用户返回的值
    return data;
}

//图类
class ALGraph {
private:
    //邻接表中表示边的结构体
    typedef struct ENode {
        int ivex;
        int weight;
        ENode *nextEdge;
    } ENode;

    //邻接表中表示点的结构体
    typedef struct VNode {
        string data;
        ENode *firstEdge;
    } VNode;

    //声明点数组
    VNode mVexs[1000];
    int length = 0;
    //dfs防止重复路径用
    int vis[1000] = {0};


public:
    //构造方法，已弃用
    ALGraph(int num) {

    }

    //添加点的方法
    void addDot(const string &data) {
        mVexs[length].data = data;
        mVexs[length].firstEdge = NULL;
        //数组长度自增
        length++;
    }

    //添加边的方法
    int addEdge(const string &p1, const string &p2, int weight) {
        int pos1 = getPos(p1);
        int pos2 = getPos(p2);
        if (pos1 == -1 || pos2 == -1) {
            return -1;
        }
        //构建要新插入的值
        ENode *nENode1 = new ENode;
        nENode1->ivex = pos2;
        nENode1->nextEdge = NULL;
        nENode1->weight = weight;
        //如果该点没有连接边则为它连接第一条边
        if (mVexs[pos1].firstEdge == NULL) {
            mVexs[pos1].firstEdge = nENode1;
        } else {
            //如果连接了边则把新边接到结尾(顺便检查这个边是不是已经存在了)
            ENode *r = mVexs[pos1].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos2) {
                    //如果边已经存在则返回错误
                    return -2;
                }
                r = r->nextEdge;

            }
            r->nextEdge = nENode1;
        }
        //构建要新插入的值
        ENode *nENode2 = new ENode;
        nENode2->ivex = pos1;
        nENode2->nextEdge = NULL;
        nENode2->weight = weight;
        //如果该点没有连接边则为它连接第一条边
        if (mVexs[pos2].firstEdge == NULL) {
            mVexs[pos2].firstEdge = nENode2;
        } else {
            //如果连接了边则把新边接到结尾(顺便检查这个边是不是已经存在了)
            ENode *r = mVexs[pos2].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos1) {
                    //如果边已经存在则返回错误
                    return -2;
                }
                r = r->nextEdge;
            }
            r->nextEdge = nENode2;
        }
        return 0;
    }

    //通过导航点文本获取序号的方法
    int getPos(const string &data) {
        for (int i = 0; i < length; ++i) {
            if (mVexs[i].data == data) {
                //返回找到的序号
                return i;
            }
        }
        //如果没找到就返回-1
        return -1;
    }

//    int dp[100][100];

    //dfs求路径的递归方法
    int *dfsb(int from, int to) {
        int weight = 0;
        int *res = new int[length]{0};
        //如果找到点了就直接输入
        if (from == to) {
            res[0] = 0;
            res[1] = 0;
            return res;
        }
        //如果这个点被访问过了就直接返回NULL退出，防止dfs回头
        if (vis[from]) {
//            return dp[from];
            return NULL;
        }
        vis[from] = 1;

        ENode *r = mVexs[from].firstEdge;
        int *list;
        res[0] = 1000000;
        int maxList[100] = {0};
        //遍历当前这个点所有的边
        while (r) {
            //递归开始
            list = dfsb(r->ivex, to);
            //如果返回NULL则直接退出到下一条边
            if (list == NULL || list[1] == -1) {
                r = r->nextEdge;
                continue;
            }
            //list[0]存储权值之和，如果权值之和要小于目前的数据，则将目前的数据替换为刚刚返回的。
            if (list[0] < res[0]) {
                res[0] = list[0];
                //深拷贝
                memset(maxList, 0, 100);
                for (int i = 0; i < list[1] + 2; ++i) {
                    maxList[i] = list[i];
                }
                weight = r->weight;
                res[0] += weight;
            }
            r = r->nextEdge;
        }
        //如果没有被替换说明这里三面都没有路可以走
        if (res[0] == 1000000) {
            return NULL;
        }
        //数组的[1]存储之后的路径条数
        res[1] = maxList[1] + 1;
        //深拷贝
        for (int i = 0; i < maxList[1]; ++i) {
            res[2 + i] = maxList[2 + i];
        }
        //加上自己
        res[2 + maxList[1]] = from;
//        for (int i = 0; i < res[1] + 2; ++i) {
//            dp[from][i] = res[i];
//        }
        return res;
    }

    //dfs入口方法，对dfs进行初始化
    int *dfs(int from, int to) {
        memset(vis, 0, 1000);
//        memset(dp, -1, 10000);
        int *res = dfsb(from, to);
        return res;
    }

    //通过序号获取序号对应的文本
    string getData(int index) {
        if (index >= length) return "none";//如果序号超出范围则返回"none"
        //返回对应序号的文本
        return mVexs[index].data;
    }

    //输出所有的导航点
    void display() {
        for (int i = 0; i < length; ++i) {
            cout << i + 1 << "." << mVexs[i].data << endl;//生成菜单用，菜单从1开始，数组从0开始，所以要修改。
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

    //数组长度，也是导航点个数获取方法
    int getLength() {
        return length;//返回导航点个数
    }
};


//用来获取路径的函数，封装了dfs方法，加入了文本。
void getRoad(ALGraph alGraph) {
    cout << "\n请输入你的位置:";
    int pos = safeInputInt();
    cout << "\n请输入你要到达的位置:";
    int dist1 = safeInputInt();
    //获取最终的数据
    int *list = alGraph.dfs(pos - 1, dist1 - 1);
    if (list == NULL) {
        cout << "\n没有合适的路线" << endl;
    } else {
        cout << "\n找到线路，总长为 " << list[0] << " ，需经过 " << list[1] << " 个导航点" << endl;
        //倒序遍历输出的才是正序的
        for (int i = list[1] + 1; i >= 2; --i) {
            if (i == 2) {
                cout << alGraph.getData(list[i]) << "->" << alGraph.getData(dist1 - 1);//最后一个点需要手动补上
                break;
            }
            cout << alGraph.getData(list[i]) << "->";

        }
        cout << endl;
    }
}

//删除指定点的函数
void del(const string &str) {
    //文件操作，将文本从一个写到另一个，删除原来的，再从另一个写回去，不符合要求的不写入。
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string temp;
    while (getline(file, temp)) {
        //如果包含指定文本的直接不写入
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

//添加导航点函数
void add(ALGraph *alGraph) {
    //同样是文件操作，直接在文件里写入对应的数据，然后重新初始化
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string name;
    while (true) {
        cout << "请输入要添加的导航点的名称:";
        cin >> name;
        //系统不允许点重名
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
        cout << "\n请输入要连接到这个导航点的导航点的序号(输入0或负数结束):";
        int num = safeInputInt();
        if (num <= 0) {
            break;
        }
        cout << "\n请输入要连接到这个导航点的导航点与这个导航点的权值:";
        int weight = safeInputInt();
        if (alGraph->getData(num - 1) != "none") {
            tempF << "B " << name << " " << alGraph->getData(num - 1) << " " << weight;
            tempF << endl;
        } else {
            cout << "对应的导航点不存在，请重新输入" << endl;
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

//主函数
int main() {
    first:;//用来重新初始化的标记
    ALGraph alGraph(100);
    //init
    //通过文件来初始化点和边
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

    //以前留下的在程序里的输入点和边
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
    //内部循环的菜单
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
        //判断输入文本是否为单个字符
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

        //route 路由 对不同选项进行分流
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
                if (pos < 0 || pos > alGraph.getLength()) {
                    cout << "输入的序号有误" << endl;
                    system("pause");
                    system("cls");
                    break;
                } else {
                    del(alGraph.getData(pos));
                    system("pause");
                    system("cls");
                    //写入文件之后，重新初始化
                    goto first;
                }
            }

            case 'C': {
                add(&alGraph);
                system("pause");
                system("cls");
                //写入文件之后，重新初始化
                goto first;
            }

            case 'D': {
                //D直接退出
                exit(0);
            }
            default: {
                cout << "错误的输入选项，请重新输入" << endl;
                system("pause");
                system("cls");
            }
        }
    }
}
