#include "chessboard.h"
#include<math.h>
double getdistance2(QPoint p1,QPoint p2){
    QPoint p=p1-p2;
    return (p.rx()*p.rx()+p.ry()*p.ry());
}
chessboard::chessboard(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    setPixmap(QPixmap(":/board.png"));
    setGeometry(0,0,700,712);
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            if(i<5){
                chessboard_coor[i][j]=QPoint(85+j*67,45+i*67);
            }else{
                chessboard_coor[i][j]=QPoint(85+j*67,58+i*67);
            }
        }
    }
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setMouseTracking(true);

}
chessboard::~chessboard() {

}
QPoint chessboard::coor2pos(QPoint coor){
    QPoint pos;
    pos.rx()=chessboard_coor[coor.ry()][coor.rx()].x();
    pos.ry()=chessboard_coor[coor.ry()][coor.rx()].y();
    return pos;
}
QPoint chessboard::pos2coor(QPoint pos){
    QPoint coor(-1,-1);
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            if(getdistance2(chessboard_coor[i][j],pos)<900){
                coor=QPoint(j,i);
                break;
            }
        }
    }
    return coor;
}
void chessboard::setchess(chessman *chess,QPoint coor){
    chessboard_data[coor.ry()][coor.rx()]=chess;
    chessboard_data[chess->getcoorY()][chess->getcoorX()]=nullptr;
    chess->setcoor(coor);
    chess->realmove(coor2pos(coor));
    setdata();
}
void chessboard::setdata(){
    QList<chessman_data> a;
    for(auto item:chesslist){
        chessman_data chessdata=item->getdata();
        a.append(chessdata);
    }
    data.append(a);
    databackup.clear();
    databackup=data;
}
void chessboard::updateboard(QList<chessman_data> datalist){
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            chessboard_data[i][j]=nullptr;
        }
    }
    for(int i=0;i<datalist.size();i++){
        chesslist.at(i)->setdata(datalist.at(i));
        chesslist.at(i)->realmove(coor2pos(chesslist.at(i)->getcoor()));
        chessboard_data[ chesslist.at(i)->getcoorY()][chesslist.at(i)->getcoorX()]=chesslist.at(i);
        chesslist.at(i)->update();
    }
}
bool chessboard::regret(){
    if(data.size()<=32){
        return false;
    }
    data.removeLast();
    QList<chessman_data> mlist=data.last();
    updateboard(mlist);
    return true;
}
bool chessboard::back(){
    if(data.size()==databackup.size()){
        return false;
    }
    QList<chessman_data> mdatalist=databackup.at(data.size());
    data.append(mdatalist);
    updateboard(mdatalist);
    return true;
}
void chessboard::resetboard(){
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            chessboard_data[i][j]=nullptr;
        }
    }
    data.clear();
    chesslist.clear();
}
bool chessboard::movechess(chessman *chess, QPoint coor){
    QPoint mcoor= chess->getcoor();
    double mdistance =getdistance2(mcoor,coor);
    chess_country mcountry=chess->getcountry();
    chess_prefession mprefession=chess->getprefession();
    int mx=coor.rx()-mcoor.rx();
    int my=coor.ry()-mcoor.ry();
    int stepx=(mx>0)?1:-1;
    int stepy=(my>0)?1:-1;
    int chesscount=0;
    if(isexistchess(coor)){//目标位置存在棋子
        if(issamecountry(chess,getchessfromcoor(coor))){//是相同国家,直接结束
            return false;
        }
        if(mprefession==PAO){//执行吃子特殊规则（将帅相对）
            if(mcoor.rx()!=coor.rx()&&mcoor.ry()!=coor.ry()){//不是同一行或者列
                return false;
            }
            if(mcoor.rx()==coor.rx()){
                for(int i=mcoor.ry()+stepy;i!=coor.ry();i+=stepy){
                    if(isexistchess(QPoint(mcoor.rx(),i))){
                        chesscount++;
                    }
                }
            }else if(mcoor.ry()==coor.ry()){
                for(int i=mcoor.rx()+stepx;i!=coor.rx();i+=stepx){
                    if(isexistchess(QPoint(i,mcoor.ry()))){
                        chesscount++;
                    }
                }
            }
            if(chesscount!=1){//中间有一个棋子
                return false;
            }
        }else if(mprefession==JIANG){//执行吃子特殊规则（将帅相对）
            if(mcoor.rx()!=coor.rx()){//不是同一行
                return false;
            }
            for(int i=mcoor.ry()+stepy;i!=coor.ry();i+=stepy){
                if(isexistchess(QPoint(mcoor.rx(),i))){
                    return false;
                }
            }
        }
        killchess(chess,getchessfromcoor(coor));
        return true;
    }
    switch (mprefession) {
    case JV:
        if(mcoor.rx()!=coor.rx()&&mcoor.ry()!=coor.ry()){//不是同一行或者列
            return false;
        }
        if(mcoor.rx()==coor.rx()){
            for(int i=mcoor.ry()+stepy;i!=coor.ry();i+=stepy){//中间无棋子
                if(isexistchess(QPoint(mcoor.rx(),i))){
                    return false;
                }
            }
        }else if(mcoor.ry()==coor.ry()){
            for(int i=mcoor.rx()+stepx;i!=coor.rx();i+=stepx){//中间无棋子
                if(isexistchess(QPoint(i,mcoor.ry()))){
                    return false;
                }
            }
        }
        break;
    case MA:
        qDebug()<<mdistance;
        if(mdistance!=5){
            return false;
        }
        if(mcoor.rx()==coor.rx()){
            for(int i=mcoor.ry()+stepy;i!=coor.ry();i+=stepy){//中间无棋子
                if(isexistchess(QPoint(mcoor.rx(),i))){
                    return false;
                }
            }
        }else if(mcoor.ry()==coor.ry()){
            for(int i=mcoor.rx()+stepx;i!=coor.rx();i+=stepx){//中间无棋子
                if(isexistchess(QPoint(i,mcoor.ry()))){
                    return false;
                }
            }
        }
        break;
    case PAO:
        if(mcoor.rx()!=coor.rx()&&mcoor.ry()!=coor.ry()){//不是同一行或者列
            return false;
        }

        if(mcoor.rx()==coor.rx()){
            for(int i=mcoor.ry()+stepy;i!=coor.ry();i+=stepy){//中间无棋子
                if(isexistchess(QPoint(mcoor.rx(),i))){
                    return false;
                }
            }
        }else if(mcoor.ry()==coor.ry()){
            for(int i=mcoor.rx()+stepx;i!=coor.rx();i+=stepx){//中间无棋子
                if(isexistchess(QPoint(i,mcoor.ry()))){
                    return false;
                }
            }
        }

        break;
    case XIANG:
        if(mdistance!=8){
            return false;
        }
        if(mcountry==CHU&&coor.ry()>4){//纵坐标超限
            return false;
        }
        if(mcountry==HAN&&coor.ry()<5){
            return false;
        }
        break;
    case SHI:
        if(mdistance!=2){//斜对角的距离平方为2
            return false;
        }
        if(coor.rx()<3||coor.rx()>5){//横坐标超限
            return false;
        }
        if(mcountry==CHU&&coor.ry()>2){//纵坐标超限
            return false;
        }
        if(mcountry==HAN&&coor.ry()<7){
            return false;
        }
        break;
    case JIANG:
        if(mdistance!=1){//移动超过一格
            return false;
        }
        if(coor.rx()<3||coor.rx()>5){//横坐标超限
            return false;
        }
        if(mcountry==CHU&&coor.ry()>2){//纵坐标超限
            return false;
        }
        if(mcountry==HAN&&coor.ry()<7){
            return false;
        }
        break;
    case BING:
        if(mdistance!=1){//移动超过一格
            return false;
        }
        if(mcountry==CHU&&((mcoor.ry()<5&&(coor.ry()-mcoor.ry())<1)||(mcoor.ry()>=5&&(coor.ry()-mcoor.ry()<0)))){
            return false;
        }
        if(mcountry==HAN&&((mcoor.ry()>=5&&(mcoor.ry()-coor.ry())<1)||(mcoor.ry()<5&&(mcoor.ry()-coor.ry()<0)))){
            return false;
        }
        break;
    default:break;
    }
    setchess(chess,coor);
    return true;
}
void chessboard::addchess(chessman *chess,QPoint coor){
    chesslist.append(chess);
    setchess(chess,coor);
}
void chessboard::killchess(chessman *killer, chessman *victim){
    victim->chess_death();
    setchess(killer,victim->getcoor());
    if(victim->getprefession()==JIANG){
        emit gameover(killer);
    }
}
void chessboard::resetchess(chessman *chess){
    chess->realmove(coor2pos(chess->getcoor()));
}
chessman *chessboard::getchessfromcoor(QPoint coor){
    return chessboard_data[coor.ry()][coor.rx()];
}
bool chessboard::isexistchess(QPoint coor){
    return (getchessfromcoor(coor)==nullptr)?false:true;
}
bool chessboard::issamecountry(chessman *chess, chessman *chess2){
    return (chess->getcountry()==chess2->getcountry())?true:false;
}
chess_country chessboard::getchesscountry(QPoint coor){
    return getchessfromcoor(coor)->getcountry();
}
void chessboard::mouseMoveEvent(QMouseEvent * event){

    emit chess_move(event);
}
