#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p = new chessboard(this);//生成棋盘
    connect(p,SIGNAL(chess_move(QMouseEvent *)),this,SLOT(my_chess_move(QMouseEvent *)));
    connect(p,SIGNAL(gameover(chessman *)),this,SLOT(game_over(chessman *)));
    for(int i=0;i<16;i++){//生成棋子
        chesschu[i]=new chessman(p);
        chesshan[i]=new chessman(p);
        connect(chesschu[i],SIGNAL(chess_clicked(chessman *)),this,SLOT(my_chess_clicked(chessman *)));
        connect(chesshan[i],SIGNAL(chess_clicked(chessman *)),this,SLOT(my_chess_clicked(chessman *)));
    }
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(gametimer()));
}
MainWindow::~MainWindow()
{

    delete ui;
    delete p;
    delete timer;
    delete checkedchess;
    for(int i=0;i<16;i++){
        delete [] chesschu[i];
        delete [] chesshan[i];
    }

}

void MainWindow::game_start(){
    ui->start->setEnabled(false);
    ui->signer->setText("红方先手");
    ui->numlabel->setText(QString("第1回合"));
    gamestatus=false;
    isredround=HAN;
    roudcount=1;
    timer->start(1000);
    timecount=0;
    QPoint pos_chu[16]={QPoint(0,0),QPoint(1,0),QPoint(2,0),QPoint(3,0),QPoint(4,0),QPoint(5,0),QPoint(6,0),QPoint(7,0),QPoint(8,0)
                        ,QPoint(1,2),QPoint(7,2)
                        ,QPoint(0,3),QPoint(2,3),QPoint(4,3),QPoint(6,3),QPoint(8,3)};
    QPoint pos_han[16]={QPoint(0,9),QPoint(1,9),QPoint(2,9),QPoint(3,9),QPoint(4,9),QPoint(5,9),QPoint(6,9),QPoint(7,9),QPoint(8,9)
                        ,QPoint(1,7),QPoint(7,7)
                        ,QPoint(0,6),QPoint(2,6),QPoint(4,6),QPoint(6,6),QPoint(8,6)};
    chess_prefession prefession[16]={JV,MA,XIANG,SHI,JIANG,SHI,XIANG,MA,JV,PAO,PAO,BING,BING,BING,BING,BING};
    for(int i=0;i<16;i++){//生成棋子
        chesschu[i]->chess_init(prefession[i],CHU);
        chesshan[i]->chess_init(prefession[i],HAN);
        p->addchess(chesschu[i],pos_chu[i]);
        p->addchess(chesshan[i],pos_han[i]);
    }
}

void MainWindow::nextround(){
    roudcount++;
    isredround=(isredround==CHU)?HAN:CHU;
    if(isredround==HAN){
        ui->signer->setText("该红色方出手");
        int a=roudcount/2;
        ui->numlabel->setText(QString("第%1回合").arg(a));
    }else{
        ui->signer->setText("该黑色方出手");
    }
}
void MainWindow::backround(){
    roudcount--;
    isredround=(isredround==CHU)?HAN:CHU;
    if(isredround==HAN){
        ui->signer->setText("该红色方出手");
    }else{
        ui->signer->setText("该黑色方出手");
        int a=roudcount/2;
        ui->numlabel->setText(QString("第%1回合").arg(a));
    }
}
void MainWindow::my_chess_clicked(chessman *chess){
    if(chess->getcountry()!=isredround){//是否是自己的回合,不是就结束
        qDebug()<<"不是自己的棋子别瞎几把碰";
        return;
    }
    if(!chess->ischecked()){//棋子没被选中
        chess->chess_checked();
        checkedchess=chess;
        gamestatus=true;
        return;
    }
    gamestatus=false;
    chess->chess_unchecked();
    QPoint mcoor=p->pos2coor(mousepos);
    if(mcoor.rx()==-1||mcoor.ry()==-1){//点击错误位置
        p->resetchess(chess);
        return;
    }
    if(p->movechess(chess,mcoor)){
        nextround();
    }else{
        p->resetchess(chess);
    }
}

void MainWindow::my_chess_move(QMouseEvent *event){
    mousepos=event->pos();
    if(gamestatus){
        checkedchess->realmove(event->pos());
    }
}
void MainWindow::game_over(chessman *chess){
    QString str;
    int sec=timecount%60;
    int min=timecount/60%60;
    if(chess->getcountry()==HAN){
        str=QString("红方获胜\n"
                    "对局%1回合，耗时%2:%3\n"
                    "对局结束,是否开始下一局").arg(roudcount).arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0'));
    }else{
        str=QString("黑方获胜\n"
                    "对局%1回合，耗时%2:%3\n"
                    "对局结束,是否开始下一局").arg(roudcount).arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0'));
    }
    if(QMessageBox::information(this,"tips",str,QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)==QMessageBox::Yes){
        p->resetboard();
        game_start();
    }else{
        ui->start->setEnabled(true);
    }
}
void MainWindow::gametimer(){
    timecount++;
    int sec=timecount%60;
    int min=timecount/60%60;
    ui->timelabel->setText(QString("对局时间：%1:%2").arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0')));
}
void MainWindow::on_start_clicked()
{
    game_start();
}

void MainWindow::on_regret_clicked()
{
        if(p->regret()){
            backround();
        }
}

void MainWindow::on_back_clicked()
{
    if(p->back()){
    nextround();
    }
}

void MainWindow::on_restart_clicked()
{
    if(QMessageBox::information(this,"tips","是否重新开始",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)==QMessageBox::Yes){
        p->resetboard();
        game_start();
    }else{
        ui->start->setEnabled(true);
    }
}

