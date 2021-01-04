#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

//��ȫ��������(�������)
int safeInputInt() {
    int data;
    while (true) {
        cin >> data;
        //����cin.fail()�����������cin.clear()����������д������ݡ�
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
    //���ؾ���������û����ص�ֵ
    return data;
}

//ͼ��
class ALGraph {
private:
    //�ڽӱ��б�ʾ�ߵĽṹ��
    typedef struct ENode {
        int ivex;
        int weight;
        ENode *nextEdge;
    } ENode;

    //�ڽӱ��б�ʾ��Ľṹ��
    typedef struct VNode {
        string data;
        ENode *firstEdge;
    } VNode;

    //����������
    VNode mVexs[1000];
    int length = 0;
    //dfs��ֹ�ظ�·����
    int vis[1000] = {0};


public:
    //���췽����������
    ALGraph(int num) {

    }

    //��ӵ�ķ���
    void addDot(const string &data) {
        mVexs[length].data = data;
        mVexs[length].firstEdge = NULL;
        //���鳤������
        length++;
    }

    //��ӱߵķ���
    int addEdge(const string &p1, const string &p2, int weight) {
        int pos1 = getPos(p1);
        int pos2 = getPos(p2);
        if (pos1 == -1 || pos2 == -1) {
            return -1;
        }
        //����Ҫ�²����ֵ
        ENode *nENode1 = new ENode;
        nENode1->ivex = pos2;
        nENode1->nextEdge = NULL;
        nENode1->weight = weight;
        //����õ�û�����ӱ���Ϊ�����ӵ�һ����
        if (mVexs[pos1].firstEdge == NULL) {
            mVexs[pos1].firstEdge = nENode1;
        } else {
            //��������˱�����±߽ӵ���β(˳����������ǲ����Ѿ�������)
            ENode *r = mVexs[pos1].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos2) {
                    //������Ѿ������򷵻ش���
                    return -2;
                }
                r = r->nextEdge;

            }
            r->nextEdge = nENode1;
        }
        //����Ҫ�²����ֵ
        ENode *nENode2 = new ENode;
        nENode2->ivex = pos1;
        nENode2->nextEdge = NULL;
        nENode2->weight = weight;
        //����õ�û�����ӱ���Ϊ�����ӵ�һ����
        if (mVexs[pos2].firstEdge == NULL) {
            mVexs[pos2].firstEdge = nENode2;
        } else {
            //��������˱�����±߽ӵ���β(˳����������ǲ����Ѿ�������)
            ENode *r = mVexs[pos2].firstEdge;
            while (r->nextEdge) {
                if (r->ivex == pos1) {
                    //������Ѿ������򷵻ش���
                    return -2;
                }
                r = r->nextEdge;
            }
            r->nextEdge = nENode2;
        }
        return 0;
    }

    //ͨ���������ı���ȡ��ŵķ���
    int getPos(const string &data) {
        for (int i = 0; i < length; ++i) {
            if (mVexs[i].data == data) {
                //�����ҵ������
                return i;
            }
        }
        //���û�ҵ��ͷ���-1
        return -1;
    }

//    int dp[100][100];

    //dfs��·���ĵݹ鷽��
    int *dfsb(int from, int to) {
        int weight = 0;
        int *res = new int[length]{0};
        //����ҵ����˾�ֱ������
        if (from == to) {
            res[0] = 0;
            res[1] = 0;
            return res;
        }
        //�������㱻���ʹ��˾�ֱ�ӷ���NULL�˳�����ֹdfs��ͷ
        if (vis[from]) {
//            return dp[from];
            return NULL;
        }
        vis[from] = 1;

        ENode *r = mVexs[from].firstEdge;
        int *list;
        res[0] = 1000000;
        int maxList[100] = {0};
        //������ǰ��������еı�
        while (r) {
            //�ݹ鿪ʼ
            list = dfsb(r->ivex, to);
            //�������NULL��ֱ���˳�����һ����
            if (list == NULL || list[1] == -1) {
                r = r->nextEdge;
                continue;
            }
            //list[0]�洢Ȩֵ֮�ͣ����Ȩֵ֮��ҪС��Ŀǰ�����ݣ���Ŀǰ�������滻Ϊ�ոշ��صġ�
            if (list[0] < res[0]) {
                res[0] = list[0];
                //���
                memset(maxList, 0, 100);
                for (int i = 0; i < list[1] + 2; ++i) {
                    maxList[i] = list[i];
                }
                weight = r->weight;
                res[0] += weight;
            }
            r = r->nextEdge;
        }
        //���û�б��滻˵���������涼û��·������
        if (res[0] == 1000000) {
            return NULL;
        }
        //�����[1]�洢֮���·������
        res[1] = maxList[1] + 1;
        //���
        for (int i = 0; i < maxList[1]; ++i) {
            res[2 + i] = maxList[2 + i];
        }
        //�����Լ�
        res[2 + maxList[1]] = from;
//        for (int i = 0; i < res[1] + 2; ++i) {
//            dp[from][i] = res[i];
//        }
        return res;
    }

    //dfs��ڷ�������dfs���г�ʼ��
    int *dfs(int from, int to) {
        memset(vis, 0, 1000);
//        memset(dp, -1, 10000);
        int *res = dfsb(from, to);
        return res;
    }

    //ͨ����Ż�ȡ��Ŷ�Ӧ���ı�
    string getData(int index) {
        if (index >= length) return "none";//�����ų�����Χ�򷵻�"none"
        //���ض�Ӧ��ŵ��ı�
        return mVexs[index].data;
    }

    //������еĵ�����
    void display() {
        for (int i = 0; i < length; ++i) {
            cout << i + 1 << "." << mVexs[i].data << endl;//���ɲ˵��ã��˵���1��ʼ�������0��ʼ������Ҫ�޸ġ�
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

    //���鳤�ȣ�Ҳ�ǵ����������ȡ����
    int getLength() {
        return length;//���ص��������
    }
};


//������ȡ·���ĺ�������װ��dfs�������������ı���
void getRoad(ALGraph alGraph) {
    cout << "\n���������λ��:";
    int pos = safeInputInt();
    cout << "\n��������Ҫ�����λ��:";
    int dist1 = safeInputInt();
    //��ȡ���յ�����
    int *list = alGraph.dfs(pos - 1, dist1 - 1);
    if (list == NULL) {
        cout << "\nû�к��ʵ�·��" << endl;
    } else {
        cout << "\n�ҵ���·���ܳ�Ϊ " << list[0] << " ���辭�� " << list[1] << " ��������" << endl;
        //�����������Ĳ��������
        for (int i = list[1] + 1; i >= 2; --i) {
            if (i == 2) {
                cout << alGraph.getData(list[i]) << "->" << alGraph.getData(dist1 - 1);//���һ������Ҫ�ֶ�����
                break;
            }
            cout << alGraph.getData(list[i]) << "->";

        }
        cout << endl;
    }
}

//ɾ��ָ����ĺ���
void del(const string &str) {
    //�ļ����������ı���һ��д����һ����ɾ��ԭ���ģ��ٴ���һ��д��ȥ��������Ҫ��Ĳ�д�롣
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string temp;
    while (getline(file, temp)) {
        //�������ָ���ı���ֱ�Ӳ�д��
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

//��ӵ����㺯��
void add(ALGraph *alGraph) {
    //ͬ�����ļ�������ֱ�����ļ���д���Ӧ�����ݣ�Ȼ�����³�ʼ��
    ifstream file("data.txt", ios::in);
    ofstream tempF("temp.txt", ios::out);
    string name;
    while (true) {
        cout << "������Ҫ��ӵĵ����������:";
        cin >> name;
        //ϵͳ�����������
        if (alGraph->getPos(name) == -1) {
            break;
        } else {
            cout << "\n����ͬ������ڣ�����������" << endl;
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
        cout << "\n������Ҫ���ӵ����������ĵ���������(����0��������):";
        int num = safeInputInt();
        if (num <= 0) {
            break;
        }
        cout << "\n������Ҫ���ӵ����������ĵ�����������������Ȩֵ:";
        int weight = safeInputInt();
        if (alGraph->getData(num - 1) != "none") {
            tempF << "B " << name << " " << alGraph->getData(num - 1) << " " << weight;
            tempF << endl;
        } else {
            cout << "��Ӧ�ĵ����㲻���ڣ�����������" << endl;
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

//������
int main() {
    first:;//�������³�ʼ���ı��
    ALGraph alGraph(100);
    //init
    //ͨ���ļ�����ʼ����ͱ�
    ifstream file("data.txt", ios::in);
    if (!file.is_open()) {
        cout << "����:�����ļ�������" << endl;
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

    //��ǰ���µ��ڳ�����������ͱ�
//    alGraph.addDot("����");
//    alGraph.addDot("ͼ���");
//    alGraph.addDot("ʵ��¥D");
//    alGraph.addDot("ʵ��¥C");
//    alGraph.addDot("ʵ��¥B");
//    alGraph.addDot("ʵ��¥A");
//    alGraph.addDot("��ѧ¥A");
//    alGraph.addDot("��ѧ¥B");
//    alGraph.addDot("��ѧ¥C");
//    alGraph.addDot("�ٳ�");
//    alGraph.addDot("����¥D");
//    alGraph.addDot("����¥C");
//    alGraph.addDot("��ʳ��");
//    alGraph.addDot("����");
//    alGraph.addDot("һʳ��");
//    alGraph.addDot("������");
//
//    alGraph.addEdge("����", "ͼ���", 100);
//    alGraph.addEdge("����", "ʵ��¥D", 30);
//    alGraph.addEdge("ʵ��¥D", "ʵ��¥C", 20);
//    alGraph.addEdge("ʵ��¥C", "ʵ��¥B", 20);
//    alGraph.addEdge("ʵ��¥B", "ʵ��¥A", 20);
//    alGraph.addEdge("ʵ��¥A", "ͼ���", 20);
//    alGraph.addEdge("����", "��ѧ¥A", 10);
//    alGraph.addEdge("��ѧ¥A", "��ѧ¥B", 20);
//    alGraph.addEdge("��ѧ¥B", "��ѧ¥C", 20);
//    alGraph.addEdge("��ѧ¥C", "ͼ���", 20);
//    alGraph.addEdge("ͼ���", "�ٳ�", 50);
//    alGraph.addEdge("�ٳ�", "����", 10);
//    alGraph.addEdge("ͼ���", "����¥D", 50);
//    alGraph.addEdge("����¥D", "����¥C", 50);
//    alGraph.addEdge("����¥C", "��ʳ��", 20);
//    alGraph.addEdge("����¥C", "����", 10);
//    alGraph.addEdge("����", "��ʳ��", 10);
//    alGraph.addEdge("��ʳ��", "һʳ��", 100);
//    alGraph.addEdge("������", "��ѧ¥C", 100);
//    alGraph.addEdge("������", "һʳ��", 10);
    //init end
    //�ڲ�ѭ���Ĳ˵�
    while (true) {
        cout << "------��ӭʹ���Ͻ�ѧԺ����ϵͳ------" << endl;
        cout << "������:" << endl;
        alGraph.display();
        cout << endl << "����ѡ��:" << endl;
        cout << "A.������ĳһ������" << endl;
        cout << "B.ɾ��ָ��������" << endl;
        cout << "C.���ĳһ������" << endl;
        cout << "D.��������" << endl;
        cout << "------------------------------------" << endl;
        char t;
        //�ж������ı��Ƿ�Ϊ�����ַ�
        while (true) {
            string str;
            cout << "��������Ҫִ�еĲ���:";
            cin >> str;
            if (str.length() != 1) {
                cout << "������������������" << endl;
                continue;
            }
            t = toupper(str[0]);
            break;
        }

        //route ·�� �Բ�ͬѡ����з���
        switch (t) {
            case 'A': {
                getRoad(alGraph);
                system("pause");
                system("cls");
                break;
            }

            case 'B': {
                cout << "������Ҫɾ���ĵ��������:";
                int pos = safeInputInt() - 1;
                if (pos < 0 || pos > alGraph.getLength()) {
                    cout << "������������" << endl;
                    system("pause");
                    system("cls");
                    break;
                } else {
                    del(alGraph.getData(pos));
                    system("pause");
                    system("cls");
                    //д���ļ�֮�����³�ʼ��
                    goto first;
                }
            }

            case 'C': {
                add(&alGraph);
                system("pause");
                system("cls");
                //д���ļ�֮�����³�ʼ��
                goto first;
            }

            case 'D': {
                //Dֱ���˳�
                exit(0);
            }
            default: {
                cout << "���������ѡ�����������" << endl;
                system("pause");
                system("cls");
            }
        }
    }
}
