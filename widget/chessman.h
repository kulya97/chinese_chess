#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QWidget>
#include <qlabel.h>
#include<qpoint.h>
#include<qvector.h>
#include<QMouseEvent>
#include<qDebug>

typedef enum chessprefession{
    ZERO,
    JIANG,
    SHI,
    XIANG,
    MA,
    JV,
    PAO,
    BING
} chess_prefession;
typedef enum country
{
    CHU,
    HAN
}chess_country;
typedef enum status{
    DEATH,
    CHECK,
    UNCHEK
} chess_status;
struct chessman_attr{
    chess_prefession prefession;//棋子的职业
    chess_country country;//棋子的国家
} ;
struct chessman_status{
    chess_status status;//棋子的状态
    QPoint coor;//棋子坐标
} ;
struct chessman_data{
    chessman_attr attr;
    chessman_status status;
};
class chessman :public QLabel
{
    Q_OBJECT
private:
    chessman_data chessmandata;
public:
    explicit chessman(QWidget* parent = Q_NULLPTR);
    ~chessman();
    void realmove(QPoint pos);//棋子真实移动
    void chess_init(chess_prefession prefession,chess_country country);//棋子设置数据
    void chess_setcoor(QPoint pos);//棋子移动
    void chess_death();//棋子死亡
    void chess_checked();//选中棋子
    void chess_unchecked();//放下棋子
    bool isalive();//棋子是否存活
    bool ischecked();//是否选中
    int getcoorX();//获取横坐标
    int getcoorY();//获取纵坐标
    chess_prefession getprefession();//获取棋子职业
    QPoint getcoor();//获取棋子坐标
    void setcoor(QPoint coor);//设置坐标
    chess_country getcountry();//获取棋子国家
    void setdata(chessman_data data);
    chessman_data getdata();
    void update();

signals:
    void chess_clicked(chessman *chess);//棋子点击信号
protected:
    void mousePressEvent(QMouseEvent* event);//棋子点击事件
};

#endif // CHESSPIECES_H
