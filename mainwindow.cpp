#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QLabel>
#include <QWidget>
#include <QPicture>
#include <QPushButton>
#include <QFocusEvent>
#include <cmath>
#include <iostream>
#include <ctime>
#include <QFont>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("2048 demo - by fourtec");
    setFixedSize(500,650);
    memset(value,0,sizeof(value));
    for(int i=0;i<16;i++)
    {
        place[i%4][i/4].x=i%4*120+20;
        place[i%4][i/4].y=i/4*120+20;
    }
    for(int i=0;i<16;i++)
    {
        label[i%4][i/4]=new QLabel(centralWidget());
        label[i%4][i/4]->setGeometry(place[i%4][i/4].x,place[i%4][i/4].y,100,100);
        label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/0.jpg"));
    }
    quit=new QPushButton(centralWidget());
    quit->setGeometry(370,500,75,35);
    quit->setText("Quit");
    quit->setFont(QFont("Courier",12,QFont::Bold));
    quit->setFocusPolicy(Qt::NoFocus);
    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
    randomnum();
    setpic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Right){pressright(0);}
    else if(event->key()==Qt::Key_Left){pressleft(0);}
    else if(event->key()==Qt::Key_Up){pressup(0);}
    else if(event->key()==Qt::Key_Down){pressdown(0);}
    else{return;}

}
int MainWindow::pressup(int mode)
{
    int i,j,cpvalue[16],chk=0;
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    for(i=0;i<4;i++){for(j=0;j<3;j++){
        for(int i=0;i<4;i++){for(int j=2;j>=0;j--){if(value[i][j]==0){value[i][j]=value[i][j+1];value[i][j+1]=0;}}}
        if(value[i][j]==value[i][j+1]){value[i][j]*=2;value[i][j+1]=0;}
    }}
    for(i=0;i<16;i++){if(cpvalue[i]==value[i%4][i/4]){chk++;}}
    if(chk>=16){return 1;}
    if(mode==0)
    {
        randomnum();
        setpic();
        testend();
    }
    return 0;
}
int MainWindow::pressdown(int mode)
{
    int i,j,cpvalue[16],chk=0;
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    for(i=0;i<4;i++){for(j=3;j>0;j--){
        for(int i=0;i<4;i++){for(int j=1;j<4;j++){if(value[i][j]==0){value[i][j]=value[i][j-1];value[i][j-1]=0;}}}
        if(value[i][j]==value[i][j-1]){value[i][j]*=2;value[i][j-1]=0;}
    }}
    for(i=0;i<16;i++){if(cpvalue[i]==value[i%4][i/4]){chk++;}}
    if(chk>=16){return 1;}
    if(mode==0)
    {
        randomnum();
        setpic();
        testend();
    }
    return 0;
}
int MainWindow::pressleft(int mode)
{
    int i,j,cpvalue[16],chk=0;
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    for(i=0;i<3;i++){for(j=0;j<4;j++){
        for(int i=2;i>=0;i--){for(int j=0;j<4;j++){if(value[i][j]==0){value[i][j]=value[i+1][j];value[i+1][j]=0;}}}
        if(value[i][j]==value[i+1][j]){value[i][j]*=2;value[i+1][j]=0;}
    }}
    for(i=0;i<16;i++){if(cpvalue[i]==value[i%4][i/4]){chk++;}}
    if(chk>=16){return 1;}
    if(mode==0)
    {
        randomnum();
        setpic();
        testend();
    }
    return 0;
}
int MainWindow::pressright(int mode)
{
    int i,j,cpvalue[16],chk=0;
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    for(i=3;i>0;i--){for(j=0;j<4;j++){
        for(int i=1;i<4;i++){for(int j=0;j<4;j++){if(value[i][j]==0){value[i][j]=value[i-1][j];value[i-1][j]=0;}}}
        if(value[i][j]==value[i-1][j]){value[i][j]*=2;value[i-1][j]=0;}
    }}
    for(i=0;i<16;i++){if(cpvalue[i]==value[i%4][i/4]){chk++;}}
    if(chk>=16){return 1;}
    if(mode==0)
    {
        randomnum();
        setpic();
        testend();
    }
    return 0;
}
int MainWindow::randomnum()
{
    srand(time(NULL));
    int add=0;
    for(int i=0;i<16;i++){if(value[i%4][i/4]!=0){add++;}}if(add==16){return 1;}

    while(1){
        int a=rand()%16;
        int b=rand()%100;
        if(value[a%4][a/4]==0){value[a%4][a/4]=b>25?2:4;break;}
    }
    return 0;
}
int MainWindow::setpic()
{
    for(int i=0;i<16;i++)
    {
        switch(value[i%4][i/4])
        {
            case 0:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/0.jpg"));break;
            case 2:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/2.jpg"));break;
            case 4:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/4.jpg"));break;
            case 8:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/8.jpg"));break;
            case 16:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/16.jpg"));break;
            case 32:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/32.jpg"));break;
            case 64:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/64.jpg"));break;
            case 128:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/128.jpg"));break;
            case 256:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/256.jpg"));break;
            case 512:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/512.jpg"));break;
            case 1024:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/1024.jpg"));break;
            case 2048:label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/2048.jpg"));break;
        }
    }
    return 0;
}
int MainWindow::testend()
{
    QLabel *endlabel=new QLabel(centralWidget());
    endlabel->setGeometry(150,200,200,100);
    endlabel->show();
    int i,cpvalue[16],ans[4]={0};
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    ans[0]=pressup(1);
    for(i=0;i<16;i++){value[i%4][i/4]=cpvalue[i];}
    ans[1]=pressdown(1);
    for(i=0;i<16;i++){value[i%4][i/4]=cpvalue[i];}
    ans[2]=pressleft(1);
    for(i=0;i<16;i++){value[i%4][i/4]=cpvalue[i];}
    ans[3]=pressright(1);
    for(i=0;i<16;i++){value[i%4][i/4]=cpvalue[i];}
    if(ans[0] && ans[1] && ans[2] && ans[3])
    {
        QLabel *endlabel=new QLabel("You lose...",centralWidget());
        endlabel->setGeometry(50,470,200,100);
        endlabel->setFont(QFont("Courier",22,QFont::Bold));
        endlabel->show();
        return 1;
    }
    return 0;
}
