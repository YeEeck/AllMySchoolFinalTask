//This code run in C++11 standard
//Code by YeEeck

#include <iostream>
#include <set>
#include <windows.h>

using namespace std;

typedef struct Student {
    string num;//ѧ��
    string name;//����
    int age;//����
    double score;//�ɼ�
    Student *next;
} Student;

class StudentsList {
private:
    Student *head;
    int length;

public:
    StudentsList();

    int listSize();

    void insertStudent();

    void delStudent();

    void findStudent();

    void display();

    void sortPrint();

    void countE();
};

StudentsList::StudentsList() {
    head = new Student;
    head->next = NULL;
    length = 0;
}

int StudentsList::listSize() {
    return length;
}

void StudentsList::insertStudent() {
    Student *r = head->next;
    string num, name;
    int age, score;
    cout << "������ѧ��ѧ��:";
    cin >> num;
    cout << "\n������ѧ������:";
    cin >> name;
    cout << "\n������ѧ������:";
    cin >> age;
    cout << "\n������ѧ���ɼ�:";
    do {
        cin >> score;
        if (score < 0) {
            cout << "ѧ���ɼ�����Ϊ����������������:";
        }
    } while (score < 0);
    while (r) {
        if (r->num == num) {
            cout << "����:ѧ���Ѵ���" << endl;
            return;
        }
        r = r->next;
    }
    Student *nStu = new Student;
    nStu->num = num;
    nStu->name = name;
    nStu->age = age;
    nStu->score = score;
    nStu->next = NULL;
    r = nStu;
    length++;
}

void StudentsList::delStudent() {
    cout << "������Ҫɾ����ѧ��ѧ��:";
    string num;
    cin >> num;
    Student *r = head->next;
    Student *p = head;
    while (r) {
        if (r->num == num) {
            p->next = r->next;
            delete (r);
            return;
        }
        r = r->next;
        p = p->next;
    }
}

void StudentsList::findStudent() {
    cout << "������Ҫ���ҵ�ѧ��ѧ��:";
    string num;
    cin >> num;
    Student *r = head->next;
    while (r) {
        if (r->num == num) {
            cout << "ѧ��ѧ��:" << r->num << endl;
            cout << "ѧ������:" << r->name << endl;
            cout << "ѧ������:" << r->age << endl;
            cout << "ѧ���ɼ�:" << r->score << endl;
            return;
        }
    }
    cout << "δ�ҵ���ѧ��" << endl;
}

void StudentsList::display() {
    Student *r = head->next;
    while (r) {
        cout << "ѧ��ѧ��:" << r->num << endl;
        cout << "ѧ������:" << r->name << endl;
        cout << "ѧ������:" << r->age << endl;
        cout << "ѧ���ɼ�:" << r->score << endl << endl;
    }
    cout << "--------��ӡ���--------" << endl;
}

void StudentsList::sortPrint() {
    set<string> set1;
    cout << "�Ƿ��ѧ����Ϣ��ѧ���ɼ����в����(Y/N):";
    char t;
    cin >> t;
    t = toupper(t);
    if (t == 'Y') {
        for (int i = 0; i < length; ++i) {
            Student *r = head->next;
            string maxNum, maxName;
            int maxAge = 0, flag = 0;
            double maxScore = -1;
            while (r) {
                if (set1.count(r->num)) {
                    continue;
                }
                if (r->score > maxScore) {
                    maxNum = r->num;
                    maxName = r->name;
                    maxAge = r->age;
                    maxScore = r->score;
                    flag = 1;
                    break;
                }
                r = r->next;
            }
            if (!flag) {
                cout << "ѧ���б�Ϊ��" << endl;
                return;
            }
            cout << "ѧ��ѧ��:" << maxNum << endl;
            cout << "ѧ������:" << maxName << endl;
            cout << "ѧ������:" << maxAge << endl;
            cout << "ѧ���ɼ�:" << maxScore << endl << endl;
            set1.insert(r->num);
        }
    }
}

void StudentsList::countE() {
    Student *r = head->next;
    int num = 0;
    while (r) {
        if (r->score < 60) {
            num++;
        }
    }
    cout << "���������" << num << "��" << endl;
}



void printPanel() {
    cout << "----------ѧ����Ϣ����ϵͳ----------" << endl;
    cout << "| 1.���ѧ��                       |" << endl;
    cout << "| 2.ɾ��ѧ��                       |" << endl;
    cout << "| 3.��ʾ����ѧ��                   |" << endl;
    cout << "| 4.����ѧ����Ϣ                   |" << endl;
    cout << "| 5.��ȡѧ������                   |" << endl;
    cout << "| 6.��ѧ���ɼ��Ӵ�С���������   |" << endl;
    cout << "| 7.��ȡ����������                 |" << endl;
    cout << "| 8.�˳�ϵͳ                       |" << endl;
    cout << "------------------------------------" << endl;
}

int main() {
    StudentsList sList;
    int first = 0;
    while (true) {
        if (first){
            system("pause");
            system("cls");
        }
        first = 1;
        printPanel();
        int num;
        cout << endl << "������Ҫִ�е�ѡ�����:";
        cin >> num;
        switch (num) {
            case 1: {
                sList.insertStudent();
                cout << "�������" << endl;
                continue;
            }
            case 2: {
                sList.delStudent();
                cout << "ɾ�����" << endl;
                continue;
            }
            case 3: {
                sList.display();
                continue;
            }
            case 4: {
                sList.findStudent();
                continue;
            }
            case 5: {
                cout << "ϵͳ�ڴ��� " << sList.listSize() << " ��ѧ��";
                continue;
            }
            case 6: {
                sList.sortPrint();
                continue;
            }
            case 7: {
                sList.countE();
            }
            case 8: {
                goto exit;
            }
            default: {
                cout << "�޷�ʶ���ѡ����ţ�����������" << endl;
                continue;
            }
        }
    }
    exit:;
    return 0;
}