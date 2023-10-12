#ifndef	_LCD_H
#define	_LCD_H	

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

extern int *plcd;
extern int fd_fb0;

void lcd_init(void);
void lcd_draw_point(int x,int y,int color);
void lcd_uninit(void);
void clear_lcd(int color);
void display_square(int x0,int y0,int w,int h,int color);
void display_circle(int x0,int y0,int r,int color);
void display_bancircle(int x0,int y0,int r,int sta,int color);

#endif


