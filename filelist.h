#ifndef	_FILELIST_H
#define	_FILELIST_H	

/*
    qipan : 画一个棋盘
    返回值 ：
        无
*/
void qipan();

/*
    draw_chess : 落黑白子
    @x : 按压的x坐标
    @y ：按压的y坐标
    @player : 玩家1 or 玩家2
    返回值
        无
*/
void draw_chess(int* x,int* y,int* player) ;

/*
    go_game : 开始游戏
    @x : 落子的在lcd上x方向的值
    @y ：落子的在lcd上y方向的值
    返回值 ：
        无
*/
void go_game(int* x,int* y);

/*
    determine : 判断黑子赢还是白子赢
    @x ： 棋盘上x轴的坐标
    @y ： 棋盘上y轴的坐标
    返回值 ：
        黑子赢   1
        白子赢   2
*/
int determine(int* x,int* y);

void display();
void display_winner(int* win);
void restar(int* x,int* y);
void withdraw(int* x,int* y);


extern char chess[12][11];    //外部定义一个chess变量

#endif