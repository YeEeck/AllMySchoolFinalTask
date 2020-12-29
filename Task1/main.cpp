//This code run in C++11 standard
//Code by YeEeck

#include <iostream>
#include <set>
#include <windows.h>

using namespace std;

//整数输入纠错函数
int safeInputInt(){
    int data;
    while (true) {
        cin >> data;
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "输入的 " << str << " 不是一个有效的输入" << endl;
            cout << "请重新输入:";
        } else {
            break;
        }
    }
    return data;
}

//浮点数输入纠错函数
double safeInputDou(){
    double data;
    while (true) {
        cin >> data;
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "输入的 " << str << " 不是一个有效的输入" << endl;
            cout << "请重新输入:";
        } else {
            break;
        }
    }
    return data;
}

//表示单个学生的结构体
typedef struct Student {
    string num;//学号
    string name;//姓名
    int age;//年龄
    double score;//成绩
    Student *next;
} Student;


//学生信息表类
class StudentsList {
private:
    Student *head;
    int length;

public:
    StudentsList();//构造函数，用于初始化学生信息表

    int listSize();//获取表的长度

    void insertStudent();//插入一个学生的信息

    void delStudent();//删除一个学生信息

    void findStudent();//根据学号查询并输出对应的学生信息

    void display();//输出所有的学生信息

    void sortPrint();//将所有学生信息排序并输出

    void countE();//统计所有不及格的人数并输出
};

//构造函数，用于初始化学生信息表
StudentsList::StudentsList() {
    head = new Student;
    head->next = NULL;
    length = 0;
}

//获取表的长度
int StudentsList::listSize() {
    return length;
}

//插入一个学生的信息
void StudentsList::insertStudent() {
    Student *r = head;
    string num, name;
    int age;
    double score;
    cout << "请输入学生学号:";
    cin >> num;
    while (r->next) {
        r = r->next;
        if (r->num == num) {
            cout << "错误:学号已存在" << endl;
            return;
        }

    }
    cout << "\n请输入学生姓名:";
    cin >> name;
    cout << "\n请输入学生年龄:";
    age = safeInputInt();
    cout << "\n请输入学生成绩:";
    do {
        score = safeInputDou();
        if (score < 0) {
            cout << "学生成绩不能为负数，请重新输入:";
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

//删除一个学生信息
void StudentsList::delStudent() {
    cout << "\n请输入要删除的学生学号:";
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
    cout << "\n指定的学号不存在" << endl;
}

//根据学号查询并输出对应的学生信息
void StudentsList::findStudent() {
    cout << "请输入要查找的学生学号:";
    string num;
    cin >> num;
    Student *r = head->next;
    while (r) {
        if (r->num == num) {
            cout << "\n--------学生信息--------" << endl;
            cout << "学生学号:" << r->num << endl;
            cout << "学生姓名:" << r->name << endl;
            cout << "学生年龄:" << r->age << endl;
            cout << "学生成绩:" << r->score << endl;
            cout << "--------打印完毕--------" << endl;
            return;
        }
        r = r->next;
    }
    cout << "\n未找到该学生" << endl;
}

//输出所有的学生信息
void StudentsList::display() {
    Student *r = head->next;
    cout << "\n--------学生信息--------" << endl;
    while (r) {
        cout << "学生学号:" << r->num << endl;
        cout << "学生姓名:" << r->name << endl;
        cout << "学生年龄:" << r->age << endl;
        cout << "学生成绩:" << r->score << endl << endl;
        r = r->next;
    }
    cout << "--------打印完毕--------" << endl;
}

//将所有学生信息排序并输出
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
            cout << "学生列表为空" << endl;
            return;
        }
        cout << "\n--------学生信息--------" << endl;
        cout << "学生学号:" << maxNum << endl;
        cout << "学生姓名:" << maxName << endl;
        cout << "学生年龄:" << maxAge << endl;
        cout << "学生成绩:" << maxScore << endl << endl;
        set1.insert(maxNum);
    }
    cout << "--------打印完毕--------" << endl;
}

//统计所有不及格的人数并输出
void StudentsList::countE() {
    Student *r = head->next;
    int num = 0;
    while (r) {
        if (r->score < 60) {
            num++;
        }
        r = r->next;
    }
    cout << "不及格的有" << num << "人" << endl;
}

//输出菜单面板
void printPanel() {
    cout << "----------学生信息管理系统----------" << endl;
    cout << "| 1.添加学生                       |" << endl;
    cout << "| 2.删除学生                       |" << endl;
    cout << "| 3.显示所有学生                   |" << endl;
    cout << "| 4.查找学生信息                   |" << endl;
    cout << "| 5.获取学生个数                   |" << endl;
    cout << "| 6.将学生成绩从大到小输出并排序   |" << endl;
    cout << "| 7.获取不及格人数                 |" << endl;
    cout << "| 8.退出系统                       |" << endl;
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
        cout << endl << "请输入要执行的选项序号:";
        num = safeInputInt();
        switch (num) {
            case 1: {
                sList.insertStudent();
                cout << "插入完毕" << endl;
                continue;
            }
            case 2: {
                sList.delStudent();
                cout << "删除完毕" << endl;
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
                cout << "系统内存在 " << sList.listSize() << " 个学生" << endl;
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
                cout << "无法识别的选项序号，请重新输入" << endl;
                continue;
            }
        }
    }
    exit:;
    return 0;
}