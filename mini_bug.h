/**
 * mini_bug.h
 * 描述:公用变量 与结构体的文件
 * author:lyf 2015-05-28
 * version: 0.1
 * modify:
 */
#ifndef _MINI_BUG_H_ 
#define _MINI_BUG_H_
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <form.h>
#include <menu.h>
#include <panel.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
extern WINDOW *add_win;
extern WINDOW *show_win;
extern WINDOW *search_win;
extern WINDOW *search_win1;
extern WINDOW *search_win2;
extern WINDOW *del_bug_win;
extern WINDOW *user_add_win;
extern WINDOW *user_show_win;
extern WINDOW *del_user_win;
extern WINDOW *user_menu_win;
extern WINDOW *main_win;
extern WINDOW *warm_win;
extern WINDOW *menu_win1;
extern int password;
extern int wrong_time;
extern char user_defined[10];
extern char passwd_defined[8];
extern int login_success;
extern WINDOW *begin_win;
extern int quit;
extern WINDOW *pad;
extern int rool1;
extern int rool_page;
extern int highlight;
extern int warm;
extern int change_eye;

/*bug存储树*/
struct tree
{
	struct tree *left;
	int id;
	char severity[15];
	char type[128];
	char data[15];
	char introduce[256];
	struct tree *right;
};
typedef struct tree treenode;
typedef treenode *b_tree;

/*用户存储树*/
struct user
{  
	struct user *left;
    	int user_id;
       char name[15];   
       char passwd[15];
	char user_data[15];
       struct user *right;
};
typedef struct user u_treenode;
typedef u_treenode *u_b_tree;




#endif