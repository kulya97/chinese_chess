#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include<QPushButton>
#include<qDebug>
#include "widget/chessboard.h"
#include"widget/chessman.h"
#include<qmap.h>
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void game_start();
private:
    void nextround();
    void backround();
private:
    Ui::MainWindow *ui;
    chessboard *p ;
    chessman *chesschu[16];
    chessman *chesshan[16];
    chessman *checkedchess;//拿起的棋子
    QPoint mousepos;//当前鼠标位置
    QTimer *timer;
    bool gamestatus=false;
    chess_country isredround=HAN;
    int timecount;
    int roudcount;

private slots:
    void my_chess_clicked(chessman *chess);
    void my_chess_move(QMouseEvent *event);
    void game_over(chessman *chess);
    void gametimer();
    void on_start_clicked();
    void on_regret_clicked();
    void on_restart_clicked();
    void on_back_clicked();
};
#endif // MAINWINDOW_H
