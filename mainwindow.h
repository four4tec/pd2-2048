#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent * event);
    int pressup(int);
    int pressdown(int);
    int pressleft(int);
    int pressright(int);
    struct pplace{int x,y;}place[4][4];
    int value[4][4];
    QLabel *label[4][4];
    int randomnum();
    int setpic();
    int testend();
    QPushButton *quit;
};

#endif // MAINWINDOW_H
