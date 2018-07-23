/**
 * main.c
 * ����:mini bug ����ϵͳ�ǿ�����Ϊ������Ŀbug�����С��
 * ϵͳ,����bug����͸�����Ŀ�����ۻ����а��顣
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
int password = 0;/*��������ı�־*/
int wrong_time=1; /*�������ı�־*/
int choices;/*�û�ѡ��*/
int flag=2;/*bugʹ�ñ�־*/
int user_flag=2;/*�û�ʹ�ñ�־*/
int search_id;/*���ұ�־*/
int del_id;/*ɾ����־*/
int user_choices;/*�û�ѡ���־*/
int del_user_id;/*ɾ����־*/
int user_back=0;/*���ر�־*/
int login_success=0;/*�����ñ�־*/
char user_defined[10]={0};/*�˻��Ա�*/
char passwd_defined[8]={0};/*����Ա�*/
int quit=3;/*�˳���־*/
int goback=0;/*���ر�־*/
int rool_page=0;/*bug������־*/
int highlight=1;/*������־*/
int warm=1;/*��վ����־*/
int change_eye=1;/*���뾯���־*/

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

void user_manage(int use_choices) /*�û�����*/
{
	
	switch(use_choices)
		{
		case 1:/*��ʾ�����û�*/
			create_title_window("show user");			
			user_show_dos();/*��ʾ��Ļ*/
			user_inorder(root_user);/*���������ʾ*/
			goback=go_back(user_show_win);/*�жϷ���*/
				while(1)
			 	{
			 	if(goback==1){
			 goback=0;
				break;
			 		}
			 	}
			fflush(stdin);
        		ko_win(user_show_win);/*�رս���*/
			//ko_win(user_menu_win);
			user_flag=2;
	             break;
		case 2 :
			curs_set(1);/*�رչ��*/
			create_title_window("add user");
			user_add_dos();/*����û�����*/
			root_user=add_user(root_user);/*���*/
			fp4=fopen("user.txt","w");/*�����ı�*/
			save_user_inorder(root_user);
			fclose(fp4);
			ko_win(user_add_win);
			curs_set(0);
			//ko_win(user_menu_win);
			break;
		case 3 :
			curs_set(1);
			create_title_window("del user");
			del_user_dos();/*ɾ���û�����*/
			root_user=delete_user(root_user,del_user_id);/*ɾ���û�����*/
			fp5=fopen("user.txt","w");
			del_user_inorder(root_user);
			fclose(fp5);
			ko_win(del_user_win);
			curs_set(0);
			//ko_win(user_menu_win);
			break;
		case 4 :
			warm=warm_dos();/*��վ������*/
			if(warm==2)
			{
				fp10=fopen("user.txt","w");/*�ı����*/
				root_user=NULL;/*���������*/
				fclose(fp10);
				show_message("empty all users ");
				warm=1;
			}
			ko_win(warm_win);
			warm=1;
			break;
		case 5:
			user_back=1;/*����*/
		default :
			break;
		}
		
}

int main(int argc, char **args)
{
		
    b_tree root;/*������ͷ���*/
    root =NULL;
    b_tree point=NULL;/*���������*/
	pthread_t tid1;/*�����߳�*/
	
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
 
    
        
    /* ��ʼ������ */
    init_win();
    /* ���ɴ��ڱ߿� */
	curs_set(0);
	
	begin1_dos();/*��ӭ����*/
	while(quit!=2)
		{
	begin_dos();/*�������*/
		if(quit==1)
			{
				ko_win(begin_win);
				exit_win();
				return 0;
			}
		}
    create_frame();
    /* ������Ϣ�� */
    create_msg_zone();
    /* ���ɱ��ⴰ�� */
    create_title_window("User Login");
    /* ���ɵ�¼��ʾ���� */
	curs_set(1);
	
   	root_user=show_user_text(root_user);/*�ı������û���*/
   	 while(!password)
       	 {
           		 user_login();		/*�������*/
	    	 	 u_btree_traversal_search(root_user);/*���������Ƿ��ܵ���*/
            		if(login_success==1)
               		 {
                			fflush(stdin);/*���⾯�����*/
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
                 pthread_cancel(tid1);//����������δ��� �����bug
             }
        }
	pthread_cancel(tid1);/*�ر��߳�*/
	ko_win(main_win);/*�رյ������*/
		 	
	curs_set(0);

	
    create_title_window("Menu List");
    menu_dos();/*�˵�����*/
    root=show_bug_text(root);/*�ı�����bug*/
    while(1){
		curs_set(0);
    switch(choices)
    {
    case 1 :	
        		create_title_window("show bug");
			show_dos();/*bug ȫ����ʾ����*/
			rooling();/*�ɹ�����ʾ*/
			inorder_rool (root);/*������ʾ*/
			rool1=0;
			while(1)
			 	{				
					prefresh(pad, rool_page ,0 , 5 ,2 , 15, 78) ;
					goback=rool_go_back(pad);/*���ز˵�*/				
			 		if(goback==1){
						ko_win(pad);
			 			goback=0;
						break;
			 			}
			 	}
					
        		ko_win(show_win);
        		flag=2;
       		create_title_window("Menu List");/*������ʾ*/
        		menu_dos();      
        		break;
   case 2 :
   			curs_set(1);	
    			create_title_window("add bug");
    			add_dos();/*���bug*/
    			root=add_bug(root);
			fp1=fopen("bug.txt","w");
			save_bug_inorder(root);/*���bug*/
			fclose(fp1);
       		create_title_window("Menu List");
       		menu_dos();
	   		curs_set(0);
   			break;
    case 3 :
			curs_set(1);
        		create_title_window("del bug");
       		del_dos();/*ɾ������*/
        		root=delete_bug(root,del_id);/*ɾ�����ڵĽ��*/
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
        		search_dos();/*��ѯbug����*/
        		create_title_window("search bug");
        		point=btree_traversal_search(root,search_id);/*������ѯ*/
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
                		search_dos_result2();/*��ѯʧ�ܽ���*/
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
				user_menu_dos();/*�����û�����*/
				user_manage(user_choices);
	 		}
			user_back=0;
			create_title_window("Menu List");
        		menu_dos();
       		break;
	case 6 :
			warm=warm_dos();/*���bug*/
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
        		return 0;/* �˳����� */   
    			default :break;
   		}
        }
    return 0;
}

