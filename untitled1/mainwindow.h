#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <QMessageBox>

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_onebutton_clicked();
    void on_twobutton_clicked();
    void on_threebutton_clicked();
    void on_fourbutton_clicked();
    void on_fivebutton_clicked();
    void on_sixbutton_clicked();
    void on_sevenbutton_clicked();
    void on_eightbutton_clicked();
    void on_ninebutton_clicked();
    void on_divbutton_clicked();
    void on_mulbutton_clicked();
    void on_leftbutton_clicked();
    void on_rightbutton_clicked();
    void on_zerobutton_clicked();
    void on_addbutton_clicked();
    void on_subbutton_clicked();

    void on_clearbutton_clicked();

    void on_deletebutton_clicked();

    void on_equalbutton_clicked();

    void on_pushButton_clicked();

public:
    Ui::MainWindow *ui;
    QString exp;

public:
    bool Operator(QChar x);
    bool my_digit(QChar x);
    int First_level(QChar a);
    QString sufexp(QString s);
    double calc(double x, double y, QChar t);
    QString preexp(QString exp);
    bool check(QString);
};



#endif // MAINWINDOW_H
