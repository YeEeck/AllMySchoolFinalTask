#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;

map<pair<string, string>, double> userData;

int safeInputInt() {
    int data = 0;
    while (true) {
        cin >> data;
        //调用cin.fail()捕获输入出错，cin.clear()清除缓存区中错误数据。
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "输入的 " << str << " 不是一个有效的数值" << endl;
            cout << "请重新输入:";
        } else {
            break;
        }
    }
    //返回经过纠错的用户返回的值
    return data;
}

void panel() {
    system("cls");
    cout << "---------小学生算数出题系统---------" << endl;
    cout << "1.计算练习" << endl;
    cout << "2.计算考试" << endl;
    cout << "3.查询成绩" << endl;
    cout << "4.排序成绩" << endl;
    cout << "5.删除成绩" << endl;
    cout << "6.退出系统" << endl;
    cout << "------------------------------------" << endl;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void calExam() {
    system("cls");
    cout << "----------计算考试已启动----------" << endl;
    string number, name;
    cout << "\n请输入你的学号:";
    cin >> number;
    cout << "\n请输入你的姓名:";
    cin >> name;
    cout << "\n请输入你要考试的题数:";
    int times;
    if ((times = safeInputInt()) == 0) {
        cout << "\n输入非法，请重新输入:";
    }
    int input;
    int num1, num2;
    int QNum = 0, RNum = 0;
    for (int i = 0; i < times; ++i) {
        int type = getRandom(1, 4);
        num1 = getRandom(0, 99);
        num2 = getRandom(0, 99);
        int result = 0;
        switch (type) {
            case 1: {
                while (true) {
                    result = num1 + num2;
                    if (result < 100) break;
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " + " << num2 << " = ";
                break;
            }
            case 2: {
                while (num2 > num1) {
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " - " << num2 << " = ";
                result = num1 - num2;
                break;
            }
            case 3: {
                while (true) {
                    result = num1 * num2;
                    if (result < 100) {
                        break;
                    }
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " * " << num2 << " = ";

                break;
            }
            case 4: {
                num2 = getRandom(1, 99);
                while (num1 % num2 != 0) {
                    num2 = getRandom(1, 99);
                }
                result = num1 / num2;
                cout << (int) num1 << " / " << (int) num2 << " =  ";
                break;
            }
        }

        int errorTimes = 0;
        while (true) {
            input = safeInputInt();
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "计算正确" << endl;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "计算错误，请重新输入。" << endl;
                    errorTimes++;
                } else {
                    cout << "计算错误，答案为 " << result << endl;
                    break;
                }
            }
        }
    }
    double score = (double) RNum / (double) QNum * 100;
    cout << "此次考试 " << QNum << " 题，得分为 " << score << endl;
    pair<string, string> pair1(number, name);
    if (userData.count(pair1)) {
        if (userData[pair1] < score) {
            userData[pair1] = score;
        }
    } else {
        userData[pair1] = score;
    }
    system("pause");
}

void calTest() {
    system("cls");
    cout << "----------计算练习已启动----------" << endl;
    cout << "(输入 -1 结束练习)" << endl;
    int input;
    int num1, num2;
    int QNum = 0, RNum = 0;
    while (true) {
        int type = getRandom(1, 4);
        num1 = getRandom(0, 99);
        num2 = getRandom(0, 99);
        int result = 0;
        switch (type) {
            case 1: {
                while (true) {
                    result = num1 + num2;
                    if (result < 100) break;
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " + " << num2 << " = ";
                break;
            }
            case 2: {
                while (num2 > num1) {
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " - " << num2 << " = ";
                result = num1 - num2;
                break;
            }
            case 3: {
                while (true) {
                    result = num1 * num2;
                    if (result < 100) {
                        break;
                    }
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " * " << num2 << " = ";

                break;
            }
            case 4: {
//                double dNum1, dNum2;
//                dNum1 = getRandom(1, 99);
                num2 = getRandom(1, 99);
                while (num1 % num2 != 0) {
                    num2 = getRandom(1, 99);
                }
                result = num1 / num2;
                cout << (int) num1 << " / " << (int) num2 << " =  ";
                break;
            }
        }

        int errorTimes = 0;
        while (true) {
            input = safeInputInt();
            if (input == -1) goto over;
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "计算正确" << endl;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "计算错误，请重新输入。" << endl;
                    errorTimes++;
                } else {
                    cout << "计算错误，答案为 " << result << endl;
                    break;
                }
            }
        }
    }
    over:;
    cout << "此次练习 " << QNum << " 题，正确率为 " << (double) RNum / (double) QNum * 100 << "%" << endl;
    system("pause");
}

void init(int type) {
    if (type == 0) {
        ifstream in("data.txt");
        string buf;
        while (getline(in, buf)) {
            string number, name;
            double score;
            int pos1 = buf.find(' ');
            int pos2 = buf.find(' ', pos1 + 1);
            number = buf.substr(0, pos1);
            name = buf.substr(pos1 + 1, pos2 - (pos1 + 1));
            score = stod(buf.substr(pos2 + 1, buf.length() - (pos2 + 1)));
            pair<string, string> pair1(number, name);
            userData[pair1] = score;
        }
    }
}

int main() {
    srand(time(0));
    init(0);
    start:;
    panel();
    int choice = safeInputInt();
    switch (choice) {
        case 1: {
            calTest();
            goto start;
        }

        case 2: {
            calExam();
            goto start;
        }
    }
    return 0;
}
