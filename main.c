/**
 * main.c
 * 描述:mini bug 管理系统是可以作为个人项目bug管理的小型
 * 系统,对于bug管理和个人项目经验累积很有帮组。
 * author:lyf 2015-06 
 * version: 1.0
 * modify:
 */
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "mini_bug.h"
#include "win_ui.h"
#include "bug_list.h"
int password = 0;/*登入密码的标志*/
int wrong_time=1; /*密码错误的标志*/
int choices;/*用户选择*/
int flag=2;/*bug使用标志*/
int user_flag=2;/*用户使用标志*/
int search_id;/*查找标志*/
int del_id;/*删除标志*/
int user_choices;/*用户选择标志*/
int del_user_id;/*删除标志*/
int user_back=0;/*返回标志*/
int login_success=0;/*登入用标志*/
char user_defined[10]={0};/*账户对比*/
char passwd_defined[8]={0};/*密码对比*/
int quit=3;/*退出标志*/
int goback=0;/*返回标志*/
int rool_page=0;/*bug滚动标志*/
int highlight=1;/*高亮标志*/
int warm=1;/*清空警告标志*/
int change_eye=1;/*登入警告标志*/

u_b_tree root_user =NULL;
u_b_tree point_user= NULL;
u_b_tree root_user_defined =NULL;
FILE *fp;
FILE *fp1;
FILE *fp2;
FILE *fp3;
FILE *fp4;
FILE *fp5;
FILE *fp9;
FILE *fp10;

void user_manage(int use_choices) /*用户界面*/
{
	
	switch(use_choices)
		{
		case 1:/*显示所有用户*/
			create_title_window("show user");			
			user_show_dos();/*显示屏幕*/
			user_inorder(root_user);/*中序遍历显示*/
			goback=go_back(user_show_win);/*判断返回*/
				while(1)
			 	{
			 	if(goback==1){
			 goback=0;
				break;
			 		}
			 	}
			fflush(stdin);
        		ko_win(user_show_win);/*关闭界面*/
			//ko_win(user_menu_win);
			user_flag=2;
	             break;
		case 2 :
			curs_set(1);/*关闭光标*/
			create_title_window("add user");
			user_add_dos();/*添加用户界面*/
			root_user=add_user(root_user);/*添加*/
			fp4=fopen("user.txt","w");/*加入文本*/
			save_user_inorder(root_user);
			fclose(fp4);
			ko_win(user_add_win);
			curs_set(0);
			//ko_win(user_menu_win);
			break;
		case 3 :
			curs_set(1);
			create_title_window("del user");
			del_user_dos();/*删除用户界面*/
			root_user=delete_user(root_user,del_user_id);/*删除用户操作*/
			fp5=fopen("user.txt","w");
			del_user_inorder(root_user);
			fclose(fp5);
			ko_win(del_user_win);
			curs_set(0);
			//ko_win(user_menu_win);
			break;
		case 4 :
			warm=warm_dos();/*清空警告界面*/
			if(warm==2)
			{
				fp10=fopen("user.txt","w");/*文本清空*/
				root_user=NULL;/*二叉树清空*/
				fclose(fp10);
				show_message("empty all users ");
				warm=1;
			}
			ko_win(warm_win);
			warm=1;
			break;
		case 5:
			user_back=1;/*返回*/
		default :
			break;
		}
		
}

int main(int argc, char **args)
{
		
    b_tree root;/*二叉树头结点*/
    root =NULL;
    b_tree point=NULL;/*二叉树结点*/
	pthread_t tid1;/*创建线程*/
	
setlocale (LC_ALL,"");
 
 time_t rawtime;
 
 struct tm * timeinfo;

  char buffer [80];

  struct lconv * lc;


  time ( &rawtime );

  timeinfo = localtime ( &rawtime );


  int twice=0;


  do {
    printf ("Locale is: %s\n", setlocale(LC_ALL,NULL) );


    strftime (buffer,80,"%c",timeinfo);
   
 printf("Date is: %s\n",buffer);

 
   lc = localeconv ();
  
  printf ("Currency symbol is: %s\n-\n",lc->currency_symbol);

    
//setlocale (LC_ALL,"");
 
 } while (!twice++);
 
    
        
    /* 初始化窗口 */
    init_win();
    /* 生成窗口边框 */
	curs_set(0);
	
	begin1_dos();/*欢迎界面*/
	while(quit!=2)
		{
	begin_dos();/*登入界面*/
		if(quit==1)
			{
				ko_win(begin_win);
				exit_win();
				return 0;
			}
		}
    create_frame();
    /* 生成消息区 */
    create_msg_zone();
    /* 生成标题窗口 */
    create_title_window("User Login");
    /* 生成登录提示界面 */
	curs_set(1);
	
   	root_user=show_user_text(root_user);/*文本导入用户树*/
   	 while(!password)
       	 {
           		 user_login();		/*登入界面*/
	    	 	 u_btree_traversal_search(root_user);/*遍历查找是否能登入*/
            		if(login_success==1)
               		 {
                			fflush(stdin);/*闪光警告程序*/
                			pthread_create(&tid1,NULL,(void*) thread1,NULL); 
                      		 wrong_time++;
                    		login_success=0;
                		}
            if(wrong_time>3)
             {
                 exit_win();
                 return 0;
             }
		if(wrong_time>2)
             {
                 pthread_cancel(tid1);//解决输入两次错误 会崩溃bug
             }
        }
	pthread_cancel(tid1);/*关闭线程*/
	ko_win(main_win);/*关闭登入界面*/
		 	
	curs_set(0);

	
    create_title_window("Menu List");
    menu_dos();/*菜单界面*/
    root=show_bug_text(root);/*文本导入bug*/
    while(1){
		curs_set(0);
    switch(choices)
    {
    case 1 :	
        		create_title_window("show bug");
			show_dos();/*bug 全部显示界面*/
			rooling();/*可滚动显示*/
			inorder_rool (root);/*中序显示*/
			rool1=0;
			while(1)
			 	{				
					prefresh(pad, rool_page ,0 , 5 ,2 , 15, 78) ;
					goback=rool_go_back(pad);/*返回菜单*/				
			 		if(goback==1){
						ko_win(pad);
			 			goback=0;
						break;
			 			}
			 	}
					
        		ko_win(show_win);
        		flag=2;
       		create_title_window("Menu List");/*重新显示*/
        		menu_dos();      
        		break;
   case 2 :
   			curs_set(1);	
    			create_title_window("add bug");
    			add_dos();/*添加bug*/
    			root=add_bug(root);
			fp1=fopen("bug.txt","w");
			save_bug_inorder(root);/*添加bug*/
			fclose(fp1);
       		create_title_window("Menu List");
       		menu_dos();
	   		curs_set(0);
   			break;
    case 3 :
			curs_set(1);
        		create_title_window("del bug");
       		del_dos();/*删除界面*/
        		root=delete_bug(root,del_id);/*删除树内的结点*/
			fp2=fopen("bug.txt","w");
			del_bug_inorder(root);
			fclose(fp2);
       		ko_win(del_bug_win);
        		create_title_window("Menu List");
        		menu_dos();  
        		curs_set(0);
        		break;
   case 4:
	 		curs_set(1);
        		search_dos();/*查询bug界面*/
        		create_title_window("search bug");
        		point=btree_traversal_search(root,search_id);/*遍历查询*/
        		if(point!=NULL)
           			{
                			search_dos_result1();
                			search_show(point);              
					while(1)
			 		{
			 	 		goback=go_back(search_win1);
			 			if(goback==1)
						{
			 				goback=0;
							break;
			 			}
			 		}
               	 ko_win(search_win1);
                	create_title_window("Menu List");
                	menu_dos();   
            			}
       		else
            		{
                		search_dos_result2();/*查询失败界面*/
                		sleep(2);
                		ko_win(search_win2);
                		create_title_window("Menu List");
                		menu_dos();
            		}
			curs_set(0);
        		break;
     case 5:
	 		while(1)
	 		{	 		
	 			if(user_back==1)
				break;
	 			create_title_window("user manage");
				user_menu_dos();/*进入用户界面*/
				user_manage(user_choices);
	 		}
			user_back=0;
			create_title_window("Menu List");
        		menu_dos();
       		break;
	case 6 :
			warm=warm_dos();/*清空bug*/
			if(warm==2)
			{
				fp9=fopen("bug.txt","w");
				root=NULL;
				fclose(fp9);
				warm=1;
				}
			ko_win(warm_win);
			create_title_window("Menu List");
               	menu_dos();
			warm=1;		
			break;
      case 7 :	 	
        		exit_win();	
        		return 0;/* 退出窗口 */   
    			default :break;
   		}
        }
    return 0;
}

