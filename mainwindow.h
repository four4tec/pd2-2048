#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <Qstack>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    int retry();
    int steplast();

private:
    //?
    Ui::MainWindow *ui;
    QLabel *label[4][4];
    QLabel *endlabel;
    QLabel *gradelabel;
    QPushButton *laststep;
    QPushButton *quit,*restart;
    QPropertyAnimation *ani[4][4],*anim;
    //variable
    struct pplace{int x,y;}place[4][4];
    int value[4][4];
    int grade;
    bool end;
    typedef struct ns{int vvalue[16],vgrade;}storevalue;
    QStack<storevalue>last;
    //function
    void keyPressEvent(QKeyEvent * event);
    int pressup(int);
    int pressdown(int);
    int pressleft(int);
    int pressright(int);
    int randomnum();
    int setpic();
    int testend();
    int win();
    int storestep();
    int animate(int,int,int);
};

#endif // MAINWINDOW_H
