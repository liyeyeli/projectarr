#include "lcd.h"

/*
//帧缓冲让开发板显示红色
void lcd_init(void)
{
    int fd_fb;//屏幕文件 fb0 的文件描述符
    int i,j;
    fd_fb = open("/dev/fb0",O_RDWR);
    if(fd_fb == -1)
    {
        perror("open /dev/fb0 error");
        return ;
    }

    int color = 0xff0000;
    for(i = 0; i < 480;i++)
    {
        for(j = 0;j < 800;j++)
        {
            write(fd_fb,&color,4);
        }
    }

    close(fd_fb);
}
*/

int fd_fb0 = -1;//帧缓冲设备文件描述符
int* plcd = NULL;//指向帧缓冲的首地址

//屏幕初始化,操作屏幕之前调用一次即可
void lcd_init()
{
    //(1) 打开设备
    fd_fb0 = open("/dev/fb0",O_RDWR);
	if(fd_fb0 == -1)
    {
        perror("open /dev/fb0 error");
        return ;
    }
    //(2) 获取屏幕信息

    //(3) int* plcd = mmap
    //   帧缓冲区域按行从左到右,从上到下,保存每个像素点的信息  ARGB 颜色值
    plcd = mmap(NULL,//第一个参数,映射到哪个地址上去,为NULL,系统自行分配
                800*480*4,//第二个参数,映射区域的长度
                PROT_WRITE | PROT_READ,//第三个参数,映射区域的权限
                MAP_SHARED,//第四个参数,映射方式,映射标记,"共享映射"
                fd_fb0,//第五个参数,文件描述符,表示你要映射哪个文件
                0);//第六个参数,文件偏移量,表示你要从哪个位置开始映射
    if(plcd == MAP_FAILED)
    {
        perror("mmap error");
        return ;
    }
}   

/*
    lcd_draw_point : 显示一个像素点的颜色为 color点
    @x :像素点的横坐标
    @y : 像素点的纵坐标
    @color :该像素点显示的颜色
    返回值:
        无
*/
void lcd_draw_point(int x,int y,int color)
{
    if(x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(plcd + 800*y + x) = color;
    }
}

//解除映射和关闭文件,使用完调用一次即可
void lcd_uninit(void)
{
    //(5) munmap
    munmap(plcd,800*480*4);
	//(6) close
    close(fd_fb0);
}

//清屏
void clear_lcd(int color)
{
    for(int i = 0;i < 480;i++)
    {
        for(int j = 0;j < 800;j++)
        {
            lcd_draw_point(j,i,color);
        }
    }
}

/*
    display_square : 在开发板上显示一个矩形
    @x0 : 矩形起始像素点的横坐标
    @y0 : 矩形起始像素点的纵坐标
    @w : 矩形的宽
    @h : 矩形的高
    @color : 矩形的颜色
    返回值 :
        无
*/
void display_square(int x0,int y0,int w,int h,int color)
{
    for(int y = 0; y < h;y++)
    {
        for(int x = 0;x < w;x++)
        {
            lcd_draw_point(x + x0,y + y0,color);
        } 
    }
    
}


/*
    display_circle :在开发板上画一个圆
    @x0 : 圆心的横坐标
    @y0 : 圆心的纵坐标
    @r :  圆心的半径
    @color : 圆的颜色
    返回值 :
        无
*/
void display_circle(int x0,int y0,int r,int color)
{
    for(int y = 0;y < 480;y++)
    {
        for(int x = 0;x < 800;x++)
        {
            //画圆公式 (x - x0)*(x - x0) + (y - y0)*(y - y0)   < r*r
            if( ((x - x0)*(x - x0) + (y - y0)*(y - y0))  < r*r)//在圆内
            {
                lcd_draw_point(x,y,color);
            }
            
        }
    }
}

/*
    display_circle :在开发板上画一个半圆
    @x0 : 圆心的横坐标
    @y0 : 圆心的纵坐标
    @r :  圆心的半径
    @color : 圆的颜色
    返回值 :
        无
*/
void display_bancircle(int x0,int y0,int r,int sta,int color)
{
    for(int y = 0;y < 480;y++)
    {
        for(int x = 0;x < 800;x++)
        {
            //画圆公式 (x - x0)*(x - x0) + (y - y0)*(y - y0)   < r*r
            if( ((x - x0)*(x - x0) + (y - y0)*(y - y0))  < r*r)//在圆内
            {
                if(sta == 1) //右半圆
                {
                    if(x >= x0)
                    {
                        lcd_draw_point(x,y,color);
                    }
                }
                if(sta == 2) //左半圆
                {
                    if(x <= x0)
                    {
                        lcd_draw_point(x,y,color);
                    }
                }
                if(sta == 3) //上半圆
                {
                    if(y <= y0)
                    {
                        lcd_draw_point(x,y,color);
                    }
                }
                if(sta == 4) //下半圆
                {
                    if(y >= y0)
                    {
                        lcd_draw_point(x,y,color);
                    }
                }
            }
            
        }
    }
}
