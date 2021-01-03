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
        //����cin.fail()�����������cin.clear()����������д������ݡ�
        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            cout << "����� " << str << " ����һ����Ч����ֵ" << endl;
            cout << "����������:";
        } else {
            break;
        }
    }
    //���ؾ���������û����ص�ֵ
    return data;
}

void panel() {
    system("cls");
    cout << "---------Сѧ����������ϵͳ---------" << endl;
    cout << "1.������ϰ" << endl;
    cout << "2.���㿼��" << endl;
    cout << "3.��ѯ�ɼ�" << endl;
    cout << "4.����ɼ�" << endl;
    cout << "5.ɾ���ɼ�" << endl;
    cout << "6.�˳�ϵͳ" << endl;
    cout << "------------------------------------" << endl;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void calExam() {
    system("cls");
    cout << "----------���㿼��������----------" << endl;
    string number, name;
    cout << "\n���������ѧ��:";
    cin >> number;
    cout << "\n�������������:";
    cin >> name;
    cout << "\n��������Ҫ���Ե�����:";
    int times;
    if ((times = safeInputInt()) == 0) {
        cout << "\n����Ƿ�������������:";
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
                cout << "������ȷ" << endl;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "����������������롣" << endl;
                    errorTimes++;
                } else {
                    cout << "������󣬴�Ϊ " << result << endl;
                    break;
                }
            }
        }
    }
    double score = (double) RNum / (double) QNum * 100;
    cout << "�˴ο��� " << QNum << " �⣬�÷�Ϊ " << score << endl;
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
    cout << "----------������ϰ������----------" << endl;
    cout << "(���� -1 ������ϰ)" << endl;
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
                cout << "������ȷ" << endl;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "����������������롣" << endl;
                    errorTimes++;
                } else {
                    cout << "������󣬴�Ϊ " << result << endl;
                    break;
                }
            }
        }
    }
    over:;
    cout << "�˴���ϰ " << QNum << " �⣬��ȷ��Ϊ " << (double) RNum / (double) QNum * 100 << "%" << endl;
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
