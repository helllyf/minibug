#ifndef _WIN_UI_H_ 
#define _WIN_UI_H_ 

#include "mini_bug.h"


/* ��ʼ������ */
void init_win(void);
void ko_win(WINDOW *koo_win);

/* �˳����� */
void exit_win(void);
/* ��������ܽ���  */
void create_frame(void);
/* ������Ϣ�� */
void create_msg_zone(void);
/* ���Ʊ��ⴰ��  */
void create_title_window(char *s);
/* ��¼��ʾ���� */
void user_login(void);
/*�˵�����*/
void menu_dos(void);
/*bug��ӽ���*/
void add_dos(void);
/*����bug��ʾ����*/
void show_dos(void); 
/*����bug����*/
void search_dos(void);
/*���ҽ��1Ϊ�ҵ�����ʾ��2Ϊδ�ҵ�*/
void search_dos_result1(void);
void search_dos_result2(void);
void del_dos(void);/*ɾ��bug����*/
void user_menu_dos(void);/*�û��������*/
void user_show_dos(void);/*�û���ʾ����*/
void user_add_dos(void);/*�û����*/
void del_user_dos(void);/*�û�ɾ��*/
void show_message(char * s);/*������ʾ����*/
void begin_dos(void);/*��ʼ����*/
int go_back(WINDOW *goback_win);
void begin1_dos(void);/*��ʼ����*/
void rooling(void);/*����*/
int rool_go_back(WINDOW *goback_win);/*������ʾ*/
int  warm_dos(void); /*��վ���*/
void *thread1(void *arg);/*��ʾ���⾯��*/



#endif /* _WIN_UI_H_ */

