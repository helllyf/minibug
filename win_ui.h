#ifndef _WIN_UI_H_ 
#define _WIN_UI_H_ 

#include "mini_bug.h"


/* 初始化窗口 */
void init_win(void);
void ko_win(WINDOW *koo_win);

/* 退出窗口 */
void exit_win(void);
/* 绘制主框架界面  */
void create_frame(void);
/* 生成消息区 */
void create_msg_zone(void);
/* 绘制标题窗口  */
void create_title_window(char *s);
/* 登录提示界面 */
void user_login(void);
/*菜单界面*/
void menu_dos(void);
/*bug添加界面*/
void add_dos(void);
/*所有bug显示界面*/
void show_dos(void); 
/*查找bug界面*/
void search_dos(void);
/*查找结果1为找到并显示，2为未找到*/
void search_dos_result1(void);
void search_dos_result2(void);
void del_dos(void);/*删除bug界面*/
void user_menu_dos(void);/*用户管理界面*/
void user_show_dos(void);/*用户显示界面*/
void user_add_dos(void);/*用户添加*/
void del_user_dos(void);/*用户删除*/
void show_message(char * s);/*标题显示界面*/
void begin_dos(void);/*开始界面*/
int go_back(WINDOW *goback_win);
void begin1_dos(void);/*开始界面*/
void rooling(void);/*滚动*/
int rool_go_back(WINDOW *goback_win);/*滚动显示*/
int  warm_dos(void); /*清空警告*/
void *thread1(void *arg);/*显示闪光警告*/



#endif /* _WIN_UI_H_ */

