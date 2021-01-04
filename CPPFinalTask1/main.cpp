#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <fstream>
#include <set>
#include <queue>

using namespace std;

map<pair<string, string>, double> userData;

//安全接收整数输入模块
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

//菜单显示
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

//删除成绩
void delScore() {
    system("cls");
    string number, name;
    cout << "---------删除功能---------" << endl;
    cout << "请输入你要删除的学号:";
    cin >> number;
    cout << "请输入你要删除的姓名:";
    cin >> name;
    //用用户输入的学号和姓名建立一个pair用于在map里获取对应数据
    pair<string, string> pair1(number, name);
    //count检查对应数值是否存在，如果不存在则显示错误信息
    if (userData.count(pair1)) {
        userData.erase(pair1);
        cout << "删除成功" << endl;
    } else {
        cout << "删除的学号和姓名不存在" << endl;
    }
    system("pause");
}

//对成绩进行排序并输出
void scoreSort() {
    system("cls");
    cout << "---------排序功能---------" << endl;
    cout << "排序前:" << endl;
    //c++11新特性，遍历map。
    for (auto const &ent:userData) {
        cout << "\n学号:" << ent.first.first << endl << "姓名:" << ent.first.second << endl << "成绩:" << ent.second << endl;
    }
    cout << "\n\n排序后:" << endl;
    //建立一个set防止插入排序重复
    set<string> set1;
    //重新写入数据文件
    remove("data.txt");
    ofstream out("data.txt");
    //插入排序（仅对文件进行修改）
    for (int i = 0; i < userData.size(); ++i) {
        string maxNum, maxName;
        double max = 0;
        for (auto const &ent:userData) {
            //防止重复，如果已存在的话直接下一个
            if (set1.count(ent.first.first)) {
                continue;
            }
            if (ent.second > max) {
                max = ent.second;
                maxNum = ent.first.first;
                maxName = ent.first.second;
            }
        }
        //向set插入值
        set1.insert(maxNum);
        cout << "\n学号:" << maxNum << endl << "姓名:" << maxName << endl << "成绩:" << max << endl;
        out << maxNum << " " << maxName << " " << max << endl;
    }
    out.close();
    system("pause");
}

//成绩查询模块
void find() {
    system("cls");
    string number, name;
    cout << "---------查询功能---------" << endl;
    cout << "请输入你要查询的学号:";
    cin >> number;
    cout << "请输入你要查询的姓名:";
    cin >> name;
    //新建pair用于查询map数据
    pair<string, string> pair1(number, name);
    //如果存在才取出对应值
    if (userData.count(pair1)) {
        cout << "学号 " << number << " ，姓名 " << name << " 的记录下最高分为 " << userData[pair1] << endl;
    } else {
        cout << "此信息不存在" << endl;
    }
    system("pause");
}

//封装后的随机数获取函数
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//队列基本元素
typedef struct queueEmt {
    string str;
    int right;
} queueEmt;

//计算考试模块
void calExam() {
    //新建队列，用来存做过的题
    queue<queueEmt> queue1;
    system("cls");
    cout << "----------计算考试已启动----------" << endl;
    string number, name;
    cout << "\n请输入你的学号:";
    cin >> number;
    cout << "\n请输入你的姓名:";
    cin >> name;
    cout << "\n请输入你要考试的题数:";
    int times;
    //对题数输入的检验
    while ((times = safeInputInt()) <= 0) {
        cout << "\n输入非法，请重新输入:";
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
        //随机进行四则运算
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
        //循环判断输入正误
        while (true) {
            input = safeInputInt();
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "\n计算正确" << endl << endl;
                //结构体内表示计算正确
                emt1.right = 1;
                RNum++;
                break;
            } else {
                if (errorTimes < 2) {
                    cout << "计算错误，请重新输入:";
                    //这里把在次数内的答错也记录在错题内了，如果仅需要记录最终答错的数量将下面的变量++删除即可
                    errorTimes++;
                } else {
                    cout << "\n计算错误，答案为 " << result << endl;
                    //如果最终没算对记录这道题错误
                    emt1.right = 0;
                    break;
                }
            }
        }
        //为结构体存储的算式字符串添加上计算结果
        emt1.str += to_string(input);
        //进入队列
        queue1.push(emt1);
    }
    double score = (double) RNum / (double) QNum * 100;
    cout << "此次考试 " << QNum << " 题，得分为 " << score << endl;
    pair<string, string> pair1(number, name);
    //如果存在且最高分小于目前分数则替换，如果不存在则直接写入
    if (userData.count(pair1)) {
        if (userData[pair1] < score) {
            userData[pair1] = score;
        }
    } else {
        userData[pair1] = score;
    }
    int time = 0;
    //遍历队列直到清空
    while (!queue1.empty()) {
        time++;
        if (queue1.front().right) {
            cout << endl << "正确: ";
        } else{
            cout << endl << "错误: ";
        }
        cout << time << ".  " + queue1.front().str << endl;
        queue1.pop();
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
        //四则运算随机
        int type = getRandom(1, 4);
        num1 = getRandom(0, 99);
        num2 = getRandom(0, 99);
        int result = 0;
        switch (type) {
            case 1: {
                while (true) {
                    result = num1 + num2;
                    if (result < 100) break;//保证得数小于100
                    num1 = getRandom(0, 99);
                    num2 = getRandom(0, 99);
                }
                cout << num1 << " + " << num2 << " = ";
                break;
            }
            case 2: {
                //保证结果不为负数
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
                num2 = getRandom(1, 99);//保证除数不为0
                //保证结果能整除
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
            if (input == -1) goto over;//多层循环直接goto跳出，cpp就没有java那种比较优雅的多层循环跳出了
            cout << endl;
            QNum++;
            if (result == input) {
                cout << "\n计算正确" << endl << endl;
                RNum++;
                break;
            } else {
                //有两次纠错机会
                if (errorTimes < 2) {
                    cout << "计算错误，请重新输入:";
                    //正确率不需要受次数内的计算错误影响的话可以把errorTimes++;去掉
                    errorTimes++;
                } else {
                    cout << "\n计算错误，答案为 " << result << endl;
                    break;
                }
            }
        }
    }
    over:;
    cout << "此次练习 " << QNum << " 题，正确率为 " << (double) RNum / (double) QNum * 100 << "%" << endl;
    system("pause");
}

//程序初始化数据函数 type = 0 为读入数据， type = 1 为将保存的数据写出
void init(int type) {
    if (type == 0) {
        ifstream in("data.txt");
        string buf;
        //循环读入文件，getline支持string，而 文件输入流.getline()不支持string
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
        //遍历map并将数据按格式写入文件输出流
        for (auto const &ent:userData) {
            out << ent.first.first << " " << ent.first.second << " " << ent.second << endl;
        }
        out.close();
    }
}

int main() {
    //初始化随机数种子
    srand(time(0));
    //用文件初始化程序
    init(0);
    start:;
    panel();//展示菜单
    cout << "请输入你要选择的选项:";
    int choice = safeInputInt();//调用安全输入函数
    //路由
    switch (choice) {
        case 1: {
            calTest();
            goto start;//由于switch不能break多层，直接goto了，其实while+continue好一点
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
            init(1);//保存数据到文件
            return 0;
        }
    }
    return 0;
}
