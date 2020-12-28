#include <iostream>
#include <cstring>

using namespace std;

#define INF (~(0x1<<31))

int safeInputInt() {
    int data;
    while (true) {
        cin >> data;
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "����� " << str << " ����һ����Ч��ѡ��" << endl;
            cout << "����������:";
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
        return mVexs[index].data;
    }

    void display() {
        for (int i = 0; i < length; ++i) {
            cout << i+1 << "." << mVexs[i].data << endl;
        }
    }
};


int main() {
    ALGraph alGraph(100);
    alGraph.addDot("����");
    alGraph.addDot("ͼ���");
    alGraph.addDot("ʵ��¥D");
    alGraph.addDot("ʵ��¥C");
    alGraph.addDot("ʵ��¥B");
    alGraph.addDot("ʵ��¥A");
    alGraph.addDot("��ѧ¥A");
    alGraph.addDot("��ѧ¥B");
    alGraph.addDot("��ѧ¥C");
    alGraph.addDot("�ٳ�");
    alGraph.addDot("����¥D");
    alGraph.addDot("����¥C");
    alGraph.addDot("��ʳ��");
    alGraph.addDot("����");
    alGraph.addDot("һʳ��");
    alGraph.addDot("������");
    alGraph.display();
    alGraph.addEdge("����", "ͼ���", 100);
    alGraph.addEdge("����", "ʵ��¥D", 30);
    alGraph.addEdge("ʵ��¥D", "ʵ��¥C", 20);
    alGraph.addEdge("ʵ��¥C", "ʵ��¥B", 20);
    alGraph.addEdge("ʵ��¥B", "ʵ��¥A", 20);
    alGraph.addEdge("ʵ��¥A", "ͼ���", 20);
    alGraph.addEdge("����", "��ѧ¥A", 10);
    alGraph.addEdge("��ѧ¥A", "��ѧ¥B", 20);
    alGraph.addEdge("��ѧ¥B", "��ѧ¥C", 20);
    alGraph.addEdge("��ѧ¥C", "ͼ���", 20);
    alGraph.addEdge("ͼ���", "�ٳ�", 50);
    alGraph.addEdge("�ٳ�", "����", 10);
    alGraph.addEdge("ͼ���", "����¥D", 50);
    alGraph.addEdge("����¥D", "����¥C", 50);
    alGraph.addEdge("����¥C", "��ʳ��", 20);
    alGraph.addEdge("����¥C", "����", 10);
    alGraph.addEdge("����", "��ʳ��", 10);
    alGraph.addEdge("��ʳ��", "һʳ��", 100);
    alGraph.addEdge("������", "��ѧ¥C", 100);
    alGraph.addEdge("������", "һʳ��", 10);

    cout << "\n���������λ��:";
    int pos = safeInputInt();
    cout << "\n��������Ҫ�����λ��:";
    int dist1 = safeInputInt();
    int *list = alGraph.dfs(pos - 1, dist1 - 1);
    if (list == NULL) {
        cout << "û�к��ʵ�·��" << endl;
    } else {
        cout << "�ҵ���·���ܳ�Ϊ " << list[0] << " ���辭�� " << list[1] << " ��վ��" << endl;
        for (int i = list[1] + 1; i >= 2; --i) {
            if (i == 2) {
                cout << alGraph.getData(list[i]) << "->" << alGraph.getData(dist1-1);
                break;
            }
            cout << alGraph.getData(list[i]) << "->";

        }
        cout << endl;
    }
    getchar();getchar();
    return 0;
}
