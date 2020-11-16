#include "chessman.h"


chessman::chessman(QWidget* parent)
    : QLabel(parent) {
    this->resize(67,67);
    setMouseTracking(true);
}
chessman::~chessman() {}
void chessman::realmove(QPoint pos){
    raise();
    this->move(pos.rx()-33,pos.ry()-33);
}
void chessman::chess_init(chess_prefession prefession,chess_country country){
    chessmandata.attr.country=country;
    chessmandata.attr.prefession=prefession;
    chessmandata.status.status=UNCHEK;
    if(country==CHU){
        switch (prefession) {
        case JV:this->setPixmap(QPixmap(":/bj.png"));break;
        case MA:this->setPixmap(QPixmap(":/bm.png"));break;
        case XIANG:this->setPixmap(QPixmap(":/bx.png"));break;
        case SHI:this->setPixmap(QPixmap(":/bs.png"));break;
        case JIANG:this->setPixmap(QPixmap(":/bb.png"));break;
        case PAO:this->setPixmap(QPixmap(":/bp.png"));break;
        case BING:this->setPixmap(QPixmap(":/bz.png"));break;
        default:;break;
        }
    }else{
        switch (prefession) {
        case JV:this->setPixmap(QPixmap(":/rj.png"));break;
        case MA:this->setPixmap(QPixmap(":/rm.png"));break;
        case XIANG:this->setPixmap(QPixmap(":/rx.png"));break;
        case SHI:this->setPixmap(QPixmap(":/rs.png"));break;
        case JIANG:this->setPixmap(QPixmap(":/rb.png"));break;
        case PAO:this->setPixmap(QPixmap(":/rp.png"));break;
        case BING:this->setPixmap(QPixmap(":/rz.png"));break;
        default:;break;
        }
    }
    show();
}
void chessman::chess_setcoor(QPoint coor){
    chessmandata.status.coor=coor;
}
void chessman::chess_death(){
    chessmandata.status.status=DEATH;
    this->hide();
}
void chessman::chess_checked(){
    chessmandata.status.status=CHECK;
}
void chessman::chess_unchecked(){
    chessmandata.status.status=UNCHEK;
}
bool chessman::isalive(){
    return (chessmandata.status.status==DEATH)?false:true;
}

bool chessman::ischecked(){
    if(chessmandata.status.status==CHECK){
        return true;
    }else{
        return false;
    }
}
int chessman::getcoorX(){
    return chessmandata.status.coor.rx();
}
int chessman::getcoorY(){
    return  chessmandata.status.coor.ry();
}
QPoint chessman::getcoor(){
    return chessmandata.status.coor;
}
void chessman::setcoor(QPoint coor){
    chessmandata.status.coor=coor;
}
chess_country chessman::getcountry(){
    return chessmandata.attr.country;
}
chess_prefession chessman::getprefession(){
    return chessmandata.attr.prefession;
}
chessman_data chessman::getdata(){
    return chessmandata;
}
void chessman::setdata(chessman_data data){
    chessmandata=data;
}
void chessman::update(){
    if(isalive()){
        show();
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
        chess_unchecked();
>>>>>>> 1e94fa8... 修复悔棋之后死亡的棋子仍然占位的bug
>>>>>>> 06c9e9d... 修复悔棋bug
    }else{
        hide();
    }
}
void chessman::mousePressEvent(QMouseEvent* event) {
    emit chess_clicked(this);
}
