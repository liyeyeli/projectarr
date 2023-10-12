#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
#include "filelist.h"

int main()
{
    int x,y;
    //1.屏幕初始化
    lcd_init();
    //2.运行函数
    clear_lcd(0x808080);
    //qipan();
    
    go_game(&x,&y);

    //3.关闭映射和文件
    lcd_uninit();
    return 0;
}