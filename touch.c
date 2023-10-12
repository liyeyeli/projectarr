#include "touch.h"
#include <linux/input.h>
#include "lcd.h"
#include <stdlib.h>

//宏定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//设备文件
#define TOUCH_PATH "/dev/input/event0"

int GetDirection()
{
    //1.打开触摸屏 
    lcd_init();
    
    int fd = open(TOUCH_PATH,O_RDONLY);//只读打开
    if(fd<0)
    {
        perror("open fail");
        return 0;
    }

    int x_start=-1,y_start=-1;	//坐标的初值
    // int x_end = -1,y_end = -1;    //坐标终点
    
    struct input_event ev;
    while(1)
    {
        //2.不停地从文件中读取数据
        read(fd, &ev, sizeof(struct input_event));
        
        //3.解析数据
        if(ev.type == EV_ABS)   //触摸事件 
        {
            if(ev.code == ABS_X)
            {
                if (-1 == x_start)        //x轴
                {
                    x_start = ev.value*800/1040;	//起点
                }
                // x_end = ev.value;      //终点
                
            }
            if(ev.code == ABS_Y)		//y轴
            {
                if (-1 == y_start)
                {
                    y_start = ev.value*480/600;
                }
            }
        }
        
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)   //按键事件
        {
            if(x_start > 600)
            {
                return 1;
            }
            if(x_start < 200)
            {
                return 2;
            }
            if(x_start >= 200 && x_start <= 600)
            {
                return 3;
            }
            close(fd);
        }

        if(ev.type == EV_REL)
        {

        }
    }
}

void get_usr_touch(int* x,int* y)
{
    int fd = open(TOUCH_PATH,O_RDONLY);//只读打开
    if(fd<0)
    {
        perror("open fail");
    }

    struct input_event ev;

    while(1)
    {
        //不停地从文件中读取数据
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == EV_ABS)
        {
            if(ev.code == ABS_X)
            {
                *x = ev.value*800/1024;
            }
            if(ev.code == ABS_Y)
            {
                *y = ev.value*480/600;
            }
        }

        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
}

/*
    get_fingle_move : 获取手指滑动的方向
    返回值：
        返回 UP    1
        返回 DOWN  2
        返回 LEFT  3
        返回 RIGHT 4
*/
int get_fingle_move(int* x,int* y)
{
    //1.获取坐标
    int x0 = -1,y0 = -1;//初始坐标
    int x1,y1;//实时坐标
    int fd = open(TOUCH_PATH,O_RDONLY);//只读打开
    if(fd<0)
    {
        perror("open fail");
    }

    struct input_event ev;

    while(1)
    {
        //不停地从文件中读取数据
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == EV_ABS && ev.code == ABS_X)
        {
            if(x0 == -1)
            {
                x0 = ev.value*800/1024;
            }
            x1 = ev.value;
        }
        if(ev.type == EV_ABS && ev.code == ABS_Y)
        {
            if(y0 == -1)
            {
                y0 = ev.value*800/1024;
            }
            y1 = ev.value;
        }

        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
        printf("x = %d,y = %d\n",*x,*y);
    }
    printf("start(%d , %d), leave(%d , %d)",x0,y0,x1,y1);
    //2.判断上下左右
    int way;
    if(abs((y1-y0)/(x1-x0)) >= 1)
    {
        if(y1-y0 > 0)
        {
            printf("DOWN\n");
            way = DOWN;
        }
        if(y1-y0 < 0)
        {
            printf("UP\n");
            way = UP;
        }
    }
    if(abs((y1-y0)/(x1-x0)) <= 1)
    {
        if(x1-x0 > 0)
        {
            printf("LEFT\n");
            way = LEFT;
        }
        if(y1-y0 < 0)
        {
            printf("RIGHT\n");
            way = RIGHT;
        }
    }
    return way;
}