#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <fstream>
#include <set>
#include <queue>

using namespace std;

map<pair<string, string>, double> userData;

//��ȫ������������ģ��
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

//�˵���ʾ
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

//ɾ���ɼ�
void delScore() {
    system("cls");
    string number, name;
    cout << "---------ɾ������---------" << endl;
    cout << "��������Ҫɾ����ѧ��:";
    cin >> number;
    cout << "��������Ҫɾ��������:";
    cin >> name;
    //���û������ѧ�ź���������һ��pair������map���ȡ��Ӧ����
    pair<string, string> pair1(number, name);
    //count����Ӧ��ֵ�Ƿ���ڣ��������������ʾ������Ϣ
    if (userData.count(pair1)) {
        userData.erase(pair1);
        cout << "ɾ���ɹ�" << endl;
    } else {
        cout << "ɾ����ѧ�ź�����������" << endl;
    }
    system("pause");
}

//�Գɼ������������
void scoreSort() {
    system("cls");
    cout << "---------������---------" << endl;
    cout << "����ǰ:" << endl;
    //c++11�����ԣ�����map��
    for (auto const &ent:userData) {
        cout << "\nѧ��:" << ent.first.first << endl << "����:" << ent.first.second << endl << "�ɼ�:" << ent.second << endl;
    }
    cout << "\n\n�����:" << endl;
    //����һ��set��ֹ���������ظ�
    set<string> set1;
    //����д�������ļ�
    remove("data.txt");
    ofstream out("data.txt");
    //�������򣨽����ļ������޸ģ�
    for (int i = 0; i < userData.size(); ++i) {
        string maxNum, maxName;
        double max = 0;
        for (auto const &ent:userData) {
            //��ֹ�ظ�������Ѵ��ڵĻ�ֱ����һ��
            if (set1.count(ent.first.first)) {
                continue;
            }
            if (ent.second > max) {
                max = ent.second;
                maxNum = ent.first.first;
                maxName = ent.first.second;
            }
        }
        //��set����ֵ
        set1.insert(maxNum);
        cout << "\nѧ��:" << maxNum << endl << "����:" << maxName << endl << "�ɼ�:" << max << endl;
        out << maxNum << " " << maxName << " " << max << endl;
    }
    out.close();
    system("pause");
}

//�ɼ���ѯģ��
void find() {
    system("cls");
    string number, name;
    cout << "---------��ѯ����---------" << endl;
    cout << "��������Ҫ��ѯ��ѧ��:";
    cin >> number;
    cout << "��������Ҫ��ѯ������:";
    cin >> name;
    //�½�pair���ڲ�ѯmap����
    pair<string, string> pair1(number, name);
    //������ڲ�ȡ����Ӧֵ
    if (userData.count(pair1)) {
        cout << "ѧ�� " << number << " ������ " << name << " �ļ�¼����߷�Ϊ " << userData[pair1] << endl;
    } else {
        cout << "����Ϣ������" << endl;
    }
    system("pause");
}

//��װ����������ȡ����
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//���л���Ԫ��
typedef struct queueEmt {
    string str;
    int right;
} queueEmt;

//���㿼��ģ��
void calExam() {
    //�½����У���������������
    queue<queueEmt> queue1;
    system("cls");
    cout << "----------���㿼��������----------" << endl;
    string number, name;
    cout << "\n���������ѧ��:";
    cin >> number;
    cout << "\n�������������:";
    cin >> name;
    cout << "\n��������Ҫ���Ե�����:";
    int times;
    //����������ļ���
    while ((times = safeInputInt()) <= 0) {
        cout << "\n����Ƿ�������������:";
    }
    int input;
    int num1, num2;
    int QNum = 0, RNum = 0;
    for (int i = 0; i < times; ++i) {
        queueEmt emt1;
        int type = getRandom(1, 4);
        num1 = getRandom(0, 99);
        num2 = getRandom(0, 99);
        int result = 0;
        //���������������
        switch (type) {
            case 1: {
                while (true) {
                    result = num1 + num2;
                    if (result < 100) break;
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " + " << num2 << " = ";
                emt1.str = to_string(num1) + " + " + to_string(num2) + " = ";
                break;
            }
            case 2: {
                while (num2 > num1) {
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " - " << num2 << " = ";
                emt1.str = to_string(num1) + " - " + to_string(num2) + " = ";
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
                emt1.str = to_string(num1) + " * " + to_string(num2) + " = ";
                break;
            }
            case 4: {
                num2 = getRandom(1, 99);
                while (num1 % num2 != 0) {
                    num1 = getRandom(1, 99);
                    num2 = getRandom(1, 99);
                }
                result = num1 / num2;
                cout << (int) num1 << " / " << (int) num2 << " = ";
                emt1.str = to_string(num1) + " / " + to_string(num2) + " = ";
                break;
            }
        }

        int errorTimes = 0;
        //ѭ���ж���������
        while (true) {
            input = safeInputInt();
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "\n������ȷ" << endl << endl;
                //�ṹ���ڱ�ʾ������ȷ
                emt1.right = 1;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "�����������������:";
                    //������ڴ����ڵĴ��Ҳ��¼�ڴ������ˣ��������Ҫ��¼���մ�������������ı���++ɾ������
                    errorTimes++;
                } else {
                    cout << "\n������󣬴�Ϊ " << result << endl;
                    //�������û��Լ�¼��������
                    emt1.right = 0;
                    break;
                }
            }
        }
        //Ϊ�ṹ��洢����ʽ�ַ�������ϼ�����
        emt1.str += to_string(input);
        //�������
        queue1.push(emt1);
    }
    double score = (double) RNum / (double) QNum * 100;
    cout << "�˴ο��� " << QNum << " �⣬�÷�Ϊ " << score << endl;
    pair<string, string> pair1(number, name);
    //�����������߷�С��Ŀǰ�������滻�������������ֱ��д��
    if (userData.count(pair1)) {
        if (userData[pair1] < score) {
            userData[pair1] = score;
        }
    } else {
        userData[pair1] = score;
    }
    int time = 0;
    //��������ֱ�����
    while (!queue1.empty()) {
        time++;
        if (queue1.front().right) {
            cout << endl << "��ȷ: ";
        } else{
            cout << endl << "����: ";
        }
        cout << time << ".  " + queue1.front().str << endl;
        queue1.pop();
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
        //�����������
        int type = getRandom(1, 4);
        num1 = getRandom(0, 99);
        num2 = getRandom(0, 99);
        int result = 0;
        switch (type) {
            case 1: {
                while (true) {
                    result = num1 + num2;
                    if (result < 100) break;//��֤����С��100
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " + " << num2 << " = ";
                break;
            }
            case 2: {
                //��֤�����Ϊ����
                while (num2 > num1) {
                    num1 = getRandom(0, 99);
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
                num2 = getRandom(1, 99);//��֤������Ϊ0
                //��֤���������
                while (num1 % num2 != 0) {
                    num1 = getRandom(1, 99);
                    num2 = getRandom(1, 99);
                }
                result = num1 / num2;
                cout << (int) num1 << " / " << (int) num2 << " = ";
                break;
            }
        }

        int errorTimes = 0;
        while (true) {
            input = safeInputInt();
            if (input == -1) goto over;//���ѭ��ֱ��goto������cpp��û��java���ֱȽ����ŵĶ��ѭ��������
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "\n������ȷ" << endl << endl;
                RNum++;
                break;
            } else {
                //�����ξ������
                if (errorTimes < 2) {
                    cout << "�����������������:";
                    //��ȷ�ʲ���Ҫ�ܴ����ڵļ������Ӱ��Ļ����԰�errorTimes++;ȥ��
                    errorTimes++;
                } else {
                    cout << "\n������󣬴�Ϊ " << result << endl;
                    break;
                }
            }
        }
    }
    over:;
    cout << "�˴���ϰ " << QNum << " �⣬��ȷ��Ϊ " << (double) RNum / (double) QNum * 100 << "%" << endl;
    system("pause");
}

//�����ʼ�����ݺ��� type = 0 Ϊ�������ݣ� type = 1 Ϊ�����������д��
void init(int type) {
    if (type == 0) {
        ifstream in("data.txt");
        string buf;
        //ѭ�������ļ���getline֧��string���� �ļ�������.getline()��֧��string
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
        in.close();
    } else {
        remove("data.txt");
        ofstream out("data.txt");
        //����map�������ݰ���ʽд���ļ������
        for (auto const &ent:userData) {
            out << ent.first.first << " " << ent.first.second << " " << ent.second << endl;
        }
        out.close();
    }
}

int main() {
    //��ʼ�����������
    srand(time(0));
    //���ļ���ʼ������
    init(0);
    start:;
    panel();//չʾ�˵�
    cout << "��������Ҫѡ���ѡ��:";
    int choice = safeInputInt();//���ð�ȫ���뺯��
    //·��
    switch (choice) {
        case 1: {
            calTest();
            goto start;//����switch����break��㣬ֱ��goto�ˣ���ʵwhile+continue��һ��
        }

        case 2: {
            calExam();
            goto start;
        }

        case 3: {
            find();
            goto start;
        }

        case 4: {
            scoreSort();
            goto start;
        }

        case 5: {
            delScore();
            goto start;
        }

        case 6: {
            init(1);//�������ݵ��ļ�
            return 0;
        }
    }
    return 0;
}
