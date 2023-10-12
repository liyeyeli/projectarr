#include <stdio.h>
#include "filelist.h"
#include "touch.h"
#include "bmp.h"
#include "lcd.h"

/*
    qipan : 画一个棋盘
    返回值 ：
        无
*/
void qipan()
{
    int x,y;         //划线
    for(x=80;x<=520;x++)    //画竖线
    {
        if(x%40==0)
        {
            for(y=40;y<=440;y++)
            {
                lcd_draw_point(x,y,0x000000);
            }
        }
    }
    for(y=40;y<=440;y++)    //画横线
    {
        if(y%40==0)
        {
            for(x=80;x<=520;x++)
            {
                lcd_draw_point(x,y,0x000000);
            }
        }
    }
}

/*
    draw_chess : 落黑白子
    @x : 按压的x坐标
    @y ：按压的y坐标
    @player : 玩家1 or 玩家2
    返回值
        无
*/
char chess[12][11] = {0};      //数组储存棋盘每个点的值 棋盘大小为12×11

void draw_chess(int* x,int* y,int* player)  //落子函数
{
    int xc = (*x-60)/40;    //确定棋盘上落子的x轴位置
    if(*x < 40)
    {
        xc = 0;
    }
    if(*x > 520 && *x < 580)
    {
        xc = 11;
    }
    int yc = (*y-20)/40;   ////确定棋盘上落子的x轴位置
    // if(yc < 0)
    // {
    //     yc = 0;
    // }
    // if(yc > 10)
    // {
    //     yc = 10;
    // }
   
    if(*player == 1 && chess[xc][yc] == 0 && xc<12 && yc<11)  //玩家1落子
    {
        chess[xc][yc] = 1;
        display_circle(xc*40+80,yc*40+40,10,0x000000);   //黑子
        *player = 2;
    }
    if(*player == 2 && chess[xc][yc] == 0 && xc<12 && yc<11) //玩家2落子
    {
        chess[xc][yc] = 2;
        display_circle(xc*40+80,yc*40+40,10,0xffffff);   //白子
        *player = 1;
    }

    *x = xc;     //将棋盘坐标传出去给判断函数
    *y = yc;
}


/*
    determine : 判断黑子赢还是白子赢
    @x ： 棋盘上x轴的坐标
    @y ： 棋盘上y轴的坐标
    返回值 ：
        黑子赢   1
        白子赢   2
*/
int determine(int* x,int* y)
{ 
    int i = 0;
    int j = 0;
    int win = 0;
    int count=0;
    int stat = chess[*x][*y];
    for(i=0;i<12;i++)        //遍历一遍棋盘
    {
        for(j=0;j<11;j++)       
        {
            if(i+4<=12 && chess[i][j] == stat && chess[i+1][j] == stat && 
            chess[i+2][j] == stat && chess[i+3][j] == stat && chess[i+4][j] == stat)  //检查横轴方向是否成五子
            {
                if(stat == 1)
                {
                    printf("BLACK WIN\n");
                    win = 1;
                }
                else if(stat == 2)
                {
                    printf("WHITE WIN\n");
                    win = 2;
                }
            }
            if(j+4<=11 && chess[i][j] == stat && chess[i][j+1] == stat && 
            chess[i][j+2] == stat && chess[i][j+3] == stat && chess[i][j+4] == stat) //检查纵轴方向是否成五子
            {
                if(stat == 1)
                {
                    printf("BLACK WIN\n");
                    win = 1;
                }
                else if(stat == 2)
                {
                    printf("WHITE WIN\n");
                    win = 2;
                }
            }
            if(i+4<=12 && j+4 <= 11 && chess[i][j] == stat && chess[i+1][j+1] == stat && 
            chess[i+2][j+2] == stat && chess[i+3][j+3] == stat && chess[i+4][j+4] == stat) //检查斜向下方向是否成五子
            {
                if(stat == 1)
                {
                    printf("BLACK WIN\n");
                    win = 1;
                }
                else if(stat == 2)
                {
                    printf("WHITE WIN\n");
                    win = 2;
                }
            }
            if(i+4<=12 && j+4 <= 11 && chess[i][j] == stat && chess[i+1][j-1] == stat && 
            chess[i+2][j-2] == stat && chess[i+3][j-3] == stat && chess[i+4][j-4] == stat)  //检查斜向上方向是否成五子
            {
                if(stat == 1)
                {
                    printf("BLACK WIN\n");
                    win = 1;
                }
                else if(stat == 2)
                {
                    printf("WHITE WIN\n");
                    win = 2;
                }
            }
        }
    }
    return win;
}

/*
    display : 显示所有图片
*/
void display()
{
    show_bmp("restar.bmp",600,200);
    show_bmp("withdraw.bmp",600,320);
}

/*
    display_winner :显示胜者
*/
void display_winner(int* win)
{
    if(*win == 1)
    {
        show_bmp("black.bmp",600,80);
    }
    if(*win == 2)
    {
        show_bmp("white.bmp",600,80);
    }
}

/*
    restar ： 重新开始一局游戏
*/
void restar(int* x,int* y)
{
    // if()
    // {
    //     for(int i = 0;i < 12;i++)        //将棋盘上所有点的值都置空表示无子
    //     {
    //         for(int j = 0;j < 11;j++)
    //         {
    //             chess[i][j] = 0;
    //         }
    //     }
    //     clear_lcd(0x808080);
    //     display();
    //     display();
    // }
}

/*
    
*/
void withdraw(int* x,int* y)
{
    if(*x >=12 && *x <=720 && *y >= 320 && *y <= 400)
    {

    }
}

/*
    go_game : 开始游戏
    @x : 落子的在lcd上x方向的值
    @y ：落子的在lcd上y方向的值
    返回值 ：
        无
*/
void go_game(int* x,int* y)
{
    qipan();
    display();
    int player = 1;      //黑棋玩家先下
    int win = 0;
    for(int i = 0;i < 12;i++)        //将棋盘上所有点的值都置空表示无子
    {
        for(int j = 0;j < 11;j++)
        {
            chess[i][j] = 0;
        }
    }
    while(1)
    {
        get_usr_touch(x,y);    //获取按压坐标
        printf("x = %d,y = %d\n",*x,*y);
        draw_chess(x,y,&player);   //玩家落子
        printf("x = %d,y = %d\n",*x,*y);
        restar(x,y);
        win = determine(x,y);
        if(win ==1 || win == 2)
        {
            display_winner(&win);
            break;
        }
    }
}