#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "widget/chessman.h"
#include <QLabel>
#include<QMouseEvent>
#include<qlist.h>
#include<qDebug>
//float InvSqrt(float x);//开方 ps：此方法比系统方法效率更高
double getdistance2(QPoint p1,QPoint p2);//求两点之间直线距离的平方
class chessboard:public QLabel
{
    Q_OBJECT

public:
    QPoint chessboard_coor[10][9];//棋盘位置数据

    QVector<QList<chessman_data>> data;//棋谱
    QVector<QList<chessman_data>> databackup;//棋谱备份
    QList<chessman *> chesslist;//棋子指针列表
    chessman *chessboard_data[10][9];//定义棋盘数据

public:
    explicit chessboard(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~chessboard();
    QPoint coor2pos(QPoint coor);//棋盘坐标转真实坐标
    QPoint pos2coor(QPoint pos);//真实坐标转棋盘坐标
    void addchess(chessman *chess,QPoint coor);//增加棋子
    void resetchess(chessman *chess);//棋子返回原位
    void resetboard();//棋盘数据复位
    bool movechess(chessman *chess,QPoint coor);//移动棋子
    void updateboard(QList<chessman_data> datalist);
    bool regret();//悔棋的都是辣鸡
    bool back();//老子不悔棋了行吧
private:
    void setchess(chessman *chess,QPoint coor);//放置棋子
    bool isexistchess(QPoint coor);//坐标是否存在棋子
    bool issamecountry(chessman *chess,chessman *chess2);//棋子是否是相同国家
    chess_country getchesscountry(QPoint coor);//获取棋子国家
    chessman *getchessfromcoor(QPoint coor);//获取指定位置的棋子
    void killchess(chessman *killer,chessman *victim);//吃子
    void setdata();//设置数据
signals:
    void chess_move(QMouseEvent *event);//自定义一个信号
    void gameover(chessman *chess);//对局结束
protected:
    /******************/
    void mouseMoveEvent(QMouseEvent *event);//重写mouseMoveEvent函数

};


#endif // CHESSBOARD_H
