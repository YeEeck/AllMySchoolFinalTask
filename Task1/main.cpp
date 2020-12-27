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
    Student *r = head;
    string num, name;
    int age, score;
    cout << "������ѧ��ѧ��:";
    cin >> num;
    while (r->next) {
        r = r->next;
        if (r->num == num) {
            cout << "����:ѧ���Ѵ���" << endl;
            return;
        }

    }
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

    Student *nStu = new Student;
    nStu->num = num;
    nStu->name = name;
    nStu->age = age;
    nStu->score = score;
    nStu->next = NULL;
    r->next = nStu;
    length++;
}

void StudentsList::delStudent() {
    cout << "\n������Ҫɾ����ѧ��ѧ��:";
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
    cout << "\nָ����ѧ�Ų�����" << endl;
}

void StudentsList::findStudent() {
    cout << "������Ҫ���ҵ�ѧ��ѧ��:";
    string num;
    cin >> num;
    Student *r = head->next;
    while (r) {
        if (r->num == num) {
            cout << "\n--------ѧ����Ϣ--------" << endl;
            cout << "ѧ��ѧ��:" << r->num << endl;
            cout << "ѧ������:" << r->name << endl;
            cout << "ѧ������:" << r->age << endl;
            cout << "ѧ���ɼ�:" << r->score << endl;
            cout << "--------��ӡ���--------" << endl;
            return;
        }
        r = r->next;
    }
    cout << "\nδ�ҵ���ѧ��" << endl;
}

void StudentsList::display() {
    Student *r = head->next;
    cout << "\n--------ѧ����Ϣ--------" << endl;
    while (r) {
        cout << "ѧ��ѧ��:" << r->num << endl;
        cout << "ѧ������:" << r->name << endl;
        cout << "ѧ������:" << r->age << endl;
        cout << "ѧ���ɼ�:" << r->score << endl << endl;
        r = r->next;
    }
    cout << "--------��ӡ���--------" << endl;
}

void StudentsList::sortPrint() {
    set<string> set1;
    for (int i = 0; i < length; ++i) {
        Student *r = head;
        string maxNum, maxName;
        int maxAge = 0, flag = 0;
        double maxScore = -1;
        while (r->next) {
            r = r->next;
            if (set1.count(r->num)) {
                continue;
            }
            if (r->score > maxScore) {
                maxNum = r->num;
                maxName = r->name;
                maxAge = r->age;
                maxScore = r->score;
                flag = 1;
                continue;
            }
        }
        if (!flag) {
            cout << "ѧ���б�Ϊ��" << endl;
            return;
        }
        cout << "\n--------ѧ����Ϣ--------" << endl;
        cout << "ѧ��ѧ��:" << maxNum << endl;
        cout << "ѧ������:" << maxName << endl;
        cout << "ѧ������:" << maxAge << endl;
        cout << "ѧ���ɼ�:" << maxScore << endl << endl;
        set1.insert(maxNum);
    }
    cout << "--------��ӡ���--------" << endl;
}

void StudentsList::countE() {
    Student *r = head->next;
    int num = 0;
    while (r) {
        if (r->score < 60) {
            num++;
        }
        r = r->next;
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
        if (first) {
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
                continue;
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