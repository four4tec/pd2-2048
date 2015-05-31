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
#include <QPropertyAnimation>
#include <QRect>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui
    ui->setupUi(this);
    setWindowTitle("2048 demo - by fourtec");
    setFixedSize(500,650);
    setObjectName("MainWindow");
    setStyleSheet("#MainWindow{border-image:url(:/pics/num/back.jpg);}");
    //variable
    memset(value,0,sizeof(value));
    grade=0;
    end=0;
    for(int i=0;i<16;i++)
    {
        place[i].x=i%4*105+40;
        place[i].y=i/4*105+40;
    }
    //label*16
    for(int i=0;i<17;i++)
    {
        label[i]=new QLabel(centralWidget());
        label[i]->setScaledContents(1);
        label[i]->hide();
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
    //ani
    for(int i=0;i<17;i++){
        ani[i]=new QPropertyAnimation(label[i],"geometry");
    }
    memset(aniplace,-1,sizeof(aniplace));
    //setpic
    randomnum();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(end){return;}
    if(event->key()==Qt::Key_Right){storestep();pressright(0);}
    else if(event->key()==Qt::Key_Left){storestep();pressleft(0);}
    else if(event->key()==Qt::Key_Up){storestep();pressup(0);}
    else if(event->key()==Qt::Key_Down){storestep();pressdown(0);}
    else{return;}

    for(int i=0;i<16;i++){if(value[i]==2048){win();}}
    testend();
    QString str=QString::number(grade);
    gradelabel->setText("Score : "+str);
}
int MainWindow::pressleft(int mode)
{
    int i,j,k,cpvalue[16],check[4]={0},chk=0,rec;
    for(i=0;i<16;i++){cpvalue[i]=value[i];}
    for(i=0;i<4;i++){
        memset(check,0,sizeof(check));
        for(j=1;j<4;j++){
            rec=-1;
            if(value[i*4+j]==0){continue;}
            for(k=j-1;k>=0;k--){
                if(value[i*4+k]==0){rec=k;}
                if(value[i*4+j]==value[i*4+k] && check[k]!=1){rec=k;check[k]=1;}
                else if(value[i*4+k]!=0){check[k]=1;}
            }
            if(rec==-1){continue;}
            if(check[rec]==0){value[i*4+rec]=value[i*4+j];value[i*4+j]=0;if(!mode){animate(i,j,i,rec);}}
            else{if(!mode){grade+=value[i*4+rec];animate(i,j,i,rec);}value[i*4+rec]*=2;value[i*4+j]=0;}
        }
    }
    for(i=0;i<16;i++){if(cpvalue[i]==value[i]){chk++;}}
    if(chk>=16){return 1;}
    if(!mode){
        randomnum();
    }
    return 0;
}
int MainWindow::pressright(int mode)
{
    int i,j,k,cpvalue[16],check[4]={0},chk=0,rec;
    for(i=0;i<16;i++){cpvalue[i]=value[i];}
    for(i=0;i<4;i++){
        memset(check,0,sizeof(check));
        for(j=2;j>=0;j--){
            rec=-1;
            if(value[i*4+j]==0){continue;}
            for(k=j+1;k<4;k++){
                if(value[i*4+k]==0){rec=k;}
                if(value[i*4+j]==value[i*4+k] && check[k]!=1){rec=k;check[k]=1;}
                else if(value[i*4+k]!=0){check[k]=1;}
            }
            if(rec==-1){continue;}
            if(check[rec]==0){value[i*4+rec]=value[i*4+j];value[i*4+j]=0;if(!mode){animate(i,j,i,rec);}}
            else{if(!mode){grade+=value[i*4+rec];animate(i,j,i,rec);}value[i*4+rec]*=2;value[i*4+j]=0;}
        }
    }
    for(i=0;i<16;i++){if(cpvalue[i]==value[i]){chk++;}}
    if(chk>=16){return 1;}
    if(!mode){
        randomnum();
    }
    return 0;
}
int MainWindow::pressup(int mode)
{
    int i,j,k,cpvalue[16],check[4]={0},chk=0,rec;
    for(i=0;i<16;i++){cpvalue[i]=value[i];}
    for(i=0;i<4;i++){
        memset(check,0,sizeof(check));
        for(j=1;j<4;j++){
            rec=-1;
            if(value[j*4+i]==0){continue;}
            for(k=j-1;k>=0;k--){
                if(value[k*4+i]==0){rec=k;}
                if(value[j*4+i]==value[k*4+i] && check[k]!=1){rec=k;check[k]=1;}
                else if(value[k*4+i]!=0){check[k]=1;}
            }
            if(rec==-1){continue;}
            if(check[rec]==0){value[rec*4+i]=value[j*4+i];value[j*4+i]=0;if(!mode){animate(j,i,rec,i);}}
            else{if(!mode){animate(j,i,rec,i);grade+=value[rec*4+i];}value[rec*4+i]*=2;value[j*4+i]=0;}
        }
    }
    for(i=0;i<16;i++){if(cpvalue[i]==value[i]){chk++;}}
    if(chk>=16){return 1;}
    if(!mode){
        randomnum();
    }
    return 0;
}
int MainWindow::pressdown(int mode)
{
    int i,j,k,cpvalue[16],check[4]={0},chk=0,rec;
    for(i=0;i<16;i++){cpvalue[i]=value[i];}
    for(i=0;i<4;i++){
        memset(check,0,sizeof(check));
        for(j=2;j>=0;j--){
            rec=-1;
            if(value[j*4+i]==0){continue;}
            for(k=j+1;k<4;k++){
                if(value[k*4+i]==0){rec=k;}
                if(value[j*4+i]==value[k*4+i] && check[k]!=1){rec=k;check[k]=1;}
                else if(value[k*4+i]!=0){check[k]=1;}
            }
            if(rec==-1){continue;}
            if(check[rec]==0){value[rec*4+i]=value[j*4+i];value[j*4+i]=0;if(!mode){animate(j,i,rec,i);}}
            else{if(!mode){grade+=value[rec*4+i];animate(j,i,rec,i);}value[rec*4+i]*=2;value[j*4+i]=0;}
        }
    }
    for(i=0;i<16;i++){if(cpvalue[i]==value[i]){chk++;}}
    if(chk>=16){return 1;}
    if(!mode){
        randomnum();
    }
    return 0;
}
int MainWindow::randomnum()
{
    srand(time(NULL));
    int add=0,a,b;
    for(int i=0;i<16;i++){if(value[i]!=0){add++;}}if(add==16){return 1;}

    while(1){
        a=rand()%16;
        b=rand()%100;
        if(value[a]==0){value[a]=b>25?2:4;break;}
    }
    int ania;
    for(int i=0;i<17;i++){if(aniplace[i]==-1){ania=i;break;}}
    QString str=QString::number(value[a]);
    label[ania]->setPixmap(":pics/num/"+str+".jpg");
    label[ania]->show();
    anim=new QPropertyAnimation(label[ania],"geometry");
    anim->setDuration(200);
    anim->setStartValue(QRect(place[a].x+25,place[a].y+25,50,50));
    anim->setEndValue(QRect(place[a].x,place[a].y,100,100));
    anim->start();
    label[ania]->setGeometry(place[a].x,place[a].y,100,100);
    for(int i=0;i<17;i++){if(aniplace[i]==-2){aniplace[i]=-1;}}
    aniplace[ania]=a;
    return 0;
}
int MainWindow::storestep()
{
    storevalue v;
    for(int i=0;i<16;i++){v.vvalue[i]=value[i];}
    v.vgrade=grade;
    last.push(v);
    return 0;
}
int MainWindow::animate(int bi,int bj,int ci,int cj)
{
    int locate=-1,locate2=-1;
    for(int i=0;i<17;i++){
        if(aniplace[i]==bi*4+bj){locate=i;}
        if(aniplace[i]==ci*4+cj){locate2=i;}
    }
    QPropertyAnimation *ania=new QPropertyAnimation(label[locate],"geometry");
    QPropertyAnimation *anib=new QPropertyAnimation(label[locate],"geometry");

    if(value[ci*4+cj]!=value[bi*4+bj]){
        ania->setDuration(200);
        ania->setStartValue(QRect(place[bi*4+bj].x,place[bi*4+bj].y,100,100));
        ania->setEndValue(QRect(place[ci*4+cj].x,place[ci*4+cj].y,100,100));
        ania->start();
        aniplace[locate]=ci*4+cj;
    }
    else{
        QSequentialAnimationGroup *group=new QSequentialAnimationGroup;
        ania->setDuration(200);
        ania->setStartValue(QRect(place[bi*4+bj].x,place[bi*4+bj].y,100,100));
        ania->setEndValue(QRect(place[ci*4+cj].x,place[ci*4+cj].y,100,100));
        QString str2=QString::number(2*value[bi*4+bj]);
        label[locate]->setPixmap(":pics/num/"+str2+".jpg");
        anib->setDuration(200);
        anib->setStartValue(QRect(place[ci*4+cj].x-15,place[ci*4+cj].y-15,130,130));
        anib->setEndValue(QRect(place[ci*4+cj].x,place[ci*4+cj].y,100,100));
        group->addAnimation(ania);
        group->addAnimation(anib);
        group->start();
        label[locate2]->hide();
        aniplace[locate]=ci*4+cj;
        aniplace[locate2]=-2;

    }
    return 0;
}
int MainWindow::testend()
{
    int i,cpvalue[16],ans[4]={0};
    for(i=0;i<16;i++){cpvalue[i]=value[i];}
    ans[0]=pressup(1);
    for(i=0;i<16;i++){value[i]=cpvalue[i];}
    ans[1]=pressdown(1);
    for(i=0;i<16;i++){value[i]=cpvalue[i];}
    ans[2]=pressleft(1);
    for(i=0;i<16;i++){value[i]=cpvalue[i];}
    ans[3]=pressright(1);
    for(i=0;i<16;i++){value[i]=cpvalue[i];}
    if(ans[0] && ans[1] && ans[2] && ans[3])
    {
        endlabel->setText("You lose...");
        endlabel->show();
        end=1;
        return 1;
    }
    return 0;
}
int MainWindow::win()
{
    endlabel->setText("You win!!!");
    endlabel->show();
    end=1;
    return 0;
}
int MainWindow::retry()
{
    for(int i=0;i<17;i++){label[i]->hide();}
    memset(value,0,sizeof(value));
    memset(aniplace,-1,sizeof(aniplace));
    end=0;
    randomnum();
    grade=0;
    last.clear();
    storestep();
    QString str=QString::number(grade);
    gradelabel->setText("Grade : "+str);
    endlabel->hide();
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
        for(int i=0;i<16;i++){value[i]=v.vvalue[i];label[i]->hide();}
        grade=v.vgrade;
        QString str=QString::number(grade);
        gradelabel->setText("Grade : "+str);
        int rec=0;
        memset(aniplace,-1,sizeof(aniplace));
        label[16]->hide();
        for(int i=0;i<16;i++){
            if(value[i]!=0){
                aniplace[rec]=i;
                QString str=QString::number(value[i]);
                label[rec]->setPixmap(":pics/num/"+str+".jpg");
                label[rec]->setGeometry(place[i].x,place[i].y,100,100);
                label[rec]->show();
                rec++;
            }
        }
    }
    return 0;
}
