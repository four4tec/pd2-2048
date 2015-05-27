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
#include <unistd.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui
    ui->setupUi(this);
    setWindowTitle("2048 demo - by fourtec");
    setFixedSize(500,650);
    //variable
    memset(value,0,sizeof(value));
    grade=0;
    end=0;
    for(int i=0;i<16;i++)
    {
        place[i%4][i/4].x=i%4*120+20;
        place[i%4][i/4].y=i/4*120+20;
    }
    //label*16
    for(int i=0;i<16;i++)
    {
        label[i%4][i/4]=new QLabel(centralWidget());
        label[i%4][i/4]->setGeometry(place[i%4][i/4].x,place[i%4][i/4].y,100,100);
        label[i%4][i/4]->setPixmap(QPixmap(":numbers/num/0.jpg"));
    }
    //button q
    quit=new QPushButton(centralWidget());
    quit->setGeometry(425,500,60,35);
    quit->setText("Quit");
    quit->setFont(QFont("Courier",12,QFont::Bold));
    quit->setFocusPolicy(Qt::NoFocus);
    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
    //button r
    restart=new QPushButton(centralWidget());
    restart->setGeometry(335,500,80,35);
    restart->setText("restart");
    restart->setFont(QFont("Courier",12,QFont::Bold));
    restart->setFocusPolicy(Qt::NoFocus);
    connect(restart,SIGNAL(clicked()),this,SLOT(retry()));
    //label end
    endlabel=new QLabel(centralWidget());
    endlabel->setGeometry(25,500,200,50);
    endlabel->setFont(QFont("Courier",22,QFont::Bold));
    endlabel->hide();
    //label grade
    gradelabel=new QLabel(centralWidget());
    gradelabel->setGeometry(25,550,400,50);
    gradelabel->setFont(QFont("Courier",22,QFont::Bold));
    QString str=QString::number(grade);
    gradelabel->setText("Grade : "+str);
    //button laststep
    laststep=new QPushButton(centralWidget());
    laststep->setGeometry(225,500,100,35);
    laststep->setFocusPolicy(Qt::NoFocus);
    laststep->setFont(QFont("Courier",10,QFont::Bold));
    laststep->setText("Last step");
    connect(laststep,SIGNAL(clicked()),this,SLOT(steplast()));
    //setpic
    randomnum();
    setpic();
    storestep();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(end){return;}
    for(int i=0;i<16;i++){if(value[i%4][i/4]==2048){win();}}
    if(event->key()==Qt::Key_Right){storestep();pressright(0);}
    else if(event->key()==Qt::Key_Left){storestep();pressleft(0);}
    else if(event->key()==Qt::Key_Up){storestep();pressup(0);}
    else if(event->key()==Qt::Key_Down){storestep();pressdown(0);}
    else{return;}
    QString str=QString::number(grade);
    gradelabel->setText("Grade : "+str);
}
int MainWindow::pressup(int mode)
{
    int i,j,cpvalue[16],chk=0;
    for(i=0;i<16;i++){cpvalue[i]=value[i%4][i/4];}
    for(i=0;i<4;i++){for(j=0;j<3;j++){
        for(int i=0;i<4;i++){for(int j=2;j>=0;j--){if(value[i][j]==0){value[i][j]=value[i][j+1];value[i][j+1]=0;}}}
        if(value[i][j]==value[i][j+1]){value[i][j]*=2;value[i][j+1]=0;if(!mode){grade+=value[i][j];}}
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
        if(value[i][j]==value[i][j-1]){value[i][j]*=2;value[i][j-1]=0;if(!mode){grade+=value[i][j];}}
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
        if(value[i][j]==value[i+1][j]){value[i][j]*=2;value[i+1][j]=0;if(!mode){grade+=value[i][j];}}
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
        if(value[i][j]==value[i-1][j]){value[i][j]*=2;value[i-1][j]=0;if(!mode){grade+=value[i][j];}}
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
        QString str=QString::number(value[i%4][i/4]);
        label[i%4][i/4]->setPixmap(":numbers/num/"+str+".jpg");
        /*switch(value[i%4][i/4])
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
        }*/
    }
    return 0;
}
int MainWindow::testend()
{
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
        endlabel->setText("You lose...");
        endlabel->show();
        end=1;
        return 1;
    }
    return 0;
}
int MainWindow::retry()
{
    restart->setText("nope!");
    //time_t t1=time(NULL),t2=time(NULL);
    //while(t2-t1<3){t2=time(NULL);}
    memset(value,0,sizeof(value));
    end=0;
    randomnum();
    setpic();
    restart->setText("restart");
    grade=0;
    last.clear();
    storestep();
    QString str=QString::number(grade);
    gradelabel->setText("Grade : "+str);
    endlabel->hide();
    return 0;
}
int MainWindow::win()
{
    endlabel->setText("You win!!!");
    endlabel->show();
    end=1;
    return 0;
}
int MainWindow::steplast()
{
    end=0;
    if(!last.isEmpty())
    {
        endlabel->hide();
        storevalue v=last.top();
        last.pop();
        for(int i=0;i<16;i++){value[i%4][i/4]=v.vvalue[i];}
        grade=v.vgrade;
        QString str=QString::number(grade);
        gradelabel->setText("Grade : "+str);
        setpic();
    }
    return 0;
}
int MainWindow::storestep()
{
    storevalue v;
    for(int i=0;i<16;i++){v.vvalue[i]=value[i%4][i/4];}
    v.vgrade=grade;
    last.push(v);
    return 0;
}
