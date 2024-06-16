#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this -> setWindowTitle("计算器");

    QFont f("仿宋", 14);
    ui -> ansLineEdit -> setFont(f);
    ui -> expLineEdit -> setFont(f);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_zerobutton_clicked()
{
    exp += '0';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_onebutton_clicked()
{
    exp += '1';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_twobutton_clicked()
{
    exp += '2';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_threebutton_clicked()
{
    exp += '3';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_fourbutton_clicked()
{
    exp += '4';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_fivebutton_clicked()
{
    exp += '5';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_sixbutton_clicked()
{
    exp += '6';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_sevenbutton_clicked()
{
    exp += '7';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_eightbutton_clicked()
{
    exp += '8';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_ninebutton_clicked()
{
    exp += '9';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_addbutton_clicked()
{
    exp += '+';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_subbutton_clicked()
{
    exp += '-';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_mulbutton_clicked()
{
    exp += '*';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_divbutton_clicked()
{
    exp += '/';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_leftbutton_clicked()
{
    exp += '(';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_rightbutton_clicked()
{
    exp += ')';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_pushButton_clicked()
{
    exp += '.';
    ui -> expLineEdit -> setText(exp);
}

void MainWindow::on_clearbutton_clicked()
{
    exp.clear();
    ui -> expLineEdit -> clear();
    ui -> ansLineEdit -> clear();
    ui -> sufexpLineEdit -> clear();
    ui -> preexpLineEdit -> clear();
}

void MainWindow::on_deletebutton_clicked()
{
    exp.chop(1);
    ui -> expLineEdit -> setText(exp);
}

int MainWindow::First_level(QChar a) {
    if (a == '+' || a == '-') return 1;
    else if (a == '*' || a == '/') return 2;
    else return 0;
}

bool MainWindow::my_digit(QChar x) {
    if (x >= '0' && x <= '9') return 1;
    else return 0;
}

bool MainWindow::Operator(QChar x) {
    if (x == '+' || x == '-' || x == '*' || x == '/') return 1;
    else return 0;
}

bool MainWindow::check(QString s) {
    int point_cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (i >= 1 && s[i] == '.' && Operator(s[i - 1])) return 0;// 小数点前面不能是运算符
        if (s[i] == '.') point_cnt++;
        if (i >= 1 && Operator(s[i]) && Operator(s[i - 1])) return 0;// 两个操作符相邻
        if (i >= 1 && s[i - 1] == '(' && (s[i] == '*' || s[i] == '/' || s[i] == '.')) return 0;//左括号后面不能是* / .
        if (i >= 1 && s[i] == ')' && (Operator(s[i - 1]) || s[i - 1] == '.')) return 0; //右括号之前不能是操作符和小数点
        if (i >= 1 && s[i] == '(' && s[i - 1] == ')') return 0;
        if (i >= 1 && s[i] == ')' && s[i - 1] == '(') return 0;
    }

    if (s.size() >= 1 && s[0] == '.') return 0; //小数点前不为空
    if (s.size() >= 1 && s.back() == '.') return 0; //小数点不能作为结尾
    if (point_cnt >= 2) return 0;//小数点个数
    if (s.size() >= 1 && Operator(s[0])) return 0;//表达式开头为操作符
    if (s.size() >= 1 && Operator(s.back())) return 0;//表达式开头为操作符

    int bracket_num = 0;//判断括号序列是否合法
    for (auto x : s) {
        if (x == '(') bracket_num ++;
        else if (x == ')') bracket_num --;
        if (bracket_num < 0) return 0;
    }
    if (bracket_num != 0) return 0;
    return 1;
}

QString MainWindow::sufexp(QString s) {
    //得出后缀表达式
    std::vector<QString> Suf;
    stack<QChar> op;
    for (int i = 0; i < s.size(); i++) {
        if (my_digit(s[i])) {
            int j = i;
            QString t;
            while (j < s.size() && (s[j] == '.' || my_digit(s[j]))) {
                t += s[j];
                j ++;
            }
            Suf.push_back(t);
            i = j - 1;
        }
        else if (s[i] == '(' || op.size() == 0) {
            op.push(s[i]);
        }
        else if (s[i] == ')') {
            while (op.size() && op.top() != '(') {
                Suf.push_back(op.top());
                op.pop();
            }
            op.pop();
        }
        else {
            if (s[i] == '-' && !my_digit(s[i - 1])) {
                QString t;
                t += '-';
                int j = i + 1;
                while (j < s.size() && (my_digit(s[j]) || s[j] == '.')) {
                    t += s[j];
                    j ++;
                }
                Suf.push_back(t);
                i = j - 1;
            }
            else {
                QChar x = s[i];
                if (op.size() && First_level(x) > First_level(op.top())) {
                    op.push(x);
                }
                else {
                    while (op.size() && First_level(op.top()) >= First_level(x)) {
                        Suf.push_back(op.top());
                        op.pop();
                    }
                    op.push(x);
                }
            }
        }
    }

    while (op.size()) {
        Suf.push_back(op.top());
        op.pop();
    }
    QString t;
    for (auto x : Suf) {
        t += x;
    }
    return t;
}

QString MainWindow::preexp(QString exp) { // 中缀 -> 前缀
    reverse(exp.begin(), exp.end());
    QString s = exp;

    std::vector<QString> Suf;
    stack<QChar> op;
    for (int i = 0; i < s.size(); i++) {
        if (my_digit(s[i])) {
            int j = i;
            QString t;
            while (j < s.size() && (s[j] == '.' || my_digit(s[j]))) {
                t += s[j];
                j ++;
            }
            Suf.push_back(t);
            i = j - 1;
        }
        else if (s[i] == ')' || op.size() == 0) {
            op.push(s[i]);
        }
        else if (s[i] == '(') {
            while (op.size() && op.top() != ')') {
                Suf.push_back(op.top());
                op.pop();
            }
            op.pop();
        }
        else {
            if (s[i] == '-' && !my_digit(s[i - 1])) {
                QString t;
                t += '-';
                int j = i + 1;
                while (j < s.size() && (my_digit(s[j]) || s[j] == '.')) {
                    t += s[j];
                    j ++;
                }
                Suf.push_back(t);
                i = j - 1;
            }
            else {
                QChar x = s[i];
                if (op.size() && First_level(x) > First_level(op.top())) {
                    op.push(x);
                }
                else {
                    while (op.size() && First_level(op.top()) >= First_level(x)) {
                        Suf.push_back(op.top());
                        op.pop();
                    }
                    op.push(x);
                }
            }
        }
    }

    while (op.size()) {
        Suf.push_back(op.top());
        op.pop();
    }
    QString t;
    for (auto x : Suf) {
        t += x;
    }

    reverse(t.begin(), t.end());
    return t;
}

void MainWindow::on_equalbutton_clicked()
{
    if (exp.size() == 0) {
        return;
    }

    if (!check(exp)) {
        QMessageBox::information(this,"错误","表达式不符合要求，请重新输入");
        exp.clear();
        ui -> ansLineEdit -> clear();
        ui -> sufexpLineEdit -> clear();
        ui -> preexpLineEdit -> clear();
        return;
    }

    //中缀转后缀
    QString suf = sufexp(exp);
    //中缀转前缀
    QString pre = preexp(exp);

    //计算结果
    QString s = exp;
    std::vector<QString> Suf;
    stack<QChar> op;
    for (int i = 0; i < s.size(); i++) {
        if (my_digit(s[i])) {
            int j = i;
            QString t;
            while (j < s.size() && (s[j] == '.' || my_digit(s[j]))) {
                t += s[j];
                j ++;
            }
            Suf.push_back(t);
            i = j - 1;
        }
        else if (s[i] == '(' || op.size() == 0) {
            op.push(s[i]);
        }
        else if (s[i] == ')') {
            while (op.size() && op.top() != '(') {
                Suf.push_back(op.top());
                op.pop();
            }
            op.pop();
        }
        else {
            if (s[i] == '-' && !my_digit(s[i - 1])) {
                QString t;
                t += '-';
                int j = i + 1;
                while (j < s.size() && (my_digit(s[j]) || s[j] == '.')) {
                    t += s[j];
                    j ++;
                }
                Suf.push_back(t);
                i = j - 1;
            }
            else {
                QChar x = s[i];
                if (op.size() && First_level(x) > First_level(op.top())) {
                    op.push(x);
                }
                else {
                    while (op.size() && First_level(op.top()) >= First_level(x)) {
                        Suf.push_back(op.top());
                        op.pop();
                    }
                    op.push(x);
                }
            }
        }
    }

    while (op.size()) {
        Suf.push_back(op.top());
        op.pop();
    }

    stack<double> num;

    auto Op = [&](QChar x) -> bool {
        double x1 = num.top();
        num.pop();
        double y1 = num.top();
        num.pop();
        if (x == '+') {
            num.push(x1 + y1);
        }
        else if (x == '-') {
            num.push(y1 - x1);
        }
        else if (x == '*') {
            num.push(x1 * y1);
        }
        else {
            if (x1 == 0) {
                QMessageBox::information(this,"错误","出现了除0的情况");
                exp.clear();
                ui -> ansLineEdit -> clear();
                ui -> sufexpLineEdit -> clear();
                ui -> preexpLineEdit -> clear();
                return 0;
            }
            else {
                num.push(y1 / x1);
            }
        }
        return 1;
    };

    for (auto x : Suf) {
        if (x.size() == 1 && Operator(x[0])) {
            if (!Op(x[0])) {
                return;
            };
        }
        else {
            num.push(x.toDouble());
        }
    }

    double ans = num.top();

    QString ss = QString::number(ans);
    ui -> ansLineEdit -> setText(ss);
    ui -> expLineEdit -> setText(exp);
    ui -> sufexpLineEdit -> setText(suf);
    ui -> preexpLineEdit -> setText(pre);
    exp.clear();
}


