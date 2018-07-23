/**
 * win_ui.c
 * ÃèÊö:ncurses Ž°ÌåœÓ¿ÚÎÄŒþ
 * ÐèÒªÓÅ»¯µã
 * 1:Ž°¿ÚÉêÇëºÜ¶à£¬¿ÉÒÔ³¢ÊÔÊ¹ÓÃpadœá¹¹Ìå£¬
 *    Ò»ŽÎ»­³öËùÓÐŽ°¿ÚÄÚÈÝ£¬
 *    ÔÙÍš¹ýÑ¡ÔñÏÔÊŸ¡£
 * 2:ÊýŸÝŽŠÀíÄÜÁŠÂýµÄµçÄÔÏÔÊŸ»á³öÏÖÎÊÌâ£¬×ÔŒºµçÄÔ²»»á
 * 3:žÃÎÄ±ŸÄÚŽúÂëŸùÎŽŒì²éŽúÂëŒòœà³Ì¶È£¬ÐèÒªÓÅ»¯
 * 4:Êó±êÓëŒüÅÌ²Ù×÷ÓŠžÃÖØ¿ªÒ»žöÎÄŒþ
 * author:lyf 2015-05-28
 * version: 1.0
 * modify:
 */
#include "win_ui.h"

extern int choices;
extern int wrong_time;
extern int search_id;
extern int del_id;
extern int user_choices;
extern int del_user_id;
extern int goback;
int x, y, i; 
/*œçÃæŽ°¿Ú*/
static WINDOW *win=NULL;               /* ¿òŒÜŽ°¿Ú */
static WINDOW *title_win=NULL;         /* ±êÌâŽ°¿Ú */
         WINDOW *main_win=NULL;          /* Ö÷Ž°¿Ú   */
static WINDOW *message_win=NULL;       /* ÏûÏ¢Ž°¿Ú */
         WINDOW *menu_win1=NULL; 					/*menuŽ°¿Ú*/
         WINDOW *add_win=NULL;           /*ÌíŒÓbugŽ°¿Ú*/
         WINDOW *show_win=NULL;         /*ÏÔÊŸËùÓÐbugŽ°¿Ú*/
         WINDOW *search_win=NULL;      /*²éÕÒbug Ž°¿Ú*/
         WINDOW *search_win1=NULL;/*²éÕÒbugœá¹û1*/
         WINDOW *search_win2=NULL;/*²éÕÒbugœá¹û2*/
         WINDOW *del_bug_win=NULL;/*ÉŸ³ýbug*/
         WINDOW *user_menu_win=NULL; /*user¹ÜÀíœçÃæ*/
	  WINDOW *user_add_win=NULL;           /*ÌíŒÓuserŽ°¿Ú*/
         WINDOW *user_show_win=NULL;         /*ÏÔÊŸËùÓÐuserŽ°¿Ú*/
         WINDOW *del_user_win=NULL;/*ÉŸ³ýuser*/
	   WINDOW *begin_win=NULL;
static WINDOW *first_win=NULL; 
int signal = 0;
	WINDOW *pad=NULL;
	WINDOW *warm_win=NULL;
char *menu_choices[] = {
"[   显示   ]",
"[   添加  ]",
"[   删除  ]",
"[   查询 ]",
"[  USER  ]",
"[  EMPTY ]",
"[  EXIT  ]",
};
int m_choices = sizeof(menu_choices) / sizeof(char *);
char *user_menu_choices[] = {
"[ SHOW  ]",
"[  ADD  ]",
"[  DEL  ]",
"[ EMPTY ]",
"[  EXIT ]",
};
int user_m_choices = sizeof(user_menu_choices) / sizeof(char *);

void init_win(void)
{
	setlocale (LC_ALL,"");
	//locale loc( "chs" );
    /* ³õÊŒ»¯ÐéÄâŽ°¿ÚœøÈëncursesÄ£Êœ */
    initscr();

    /*µ±cbreakÄ£Êœ±»¿ªÆôáá£¬³ýÁËDELETE»òCTRL
µÈÈÔ±»ÊÓÎªÌØÊâ¿ØÖÆ×ÖÔªÍâÒ»ÇÐÊäÈëµÄ×ÖÔªœ«Á¢¿Ì±»Ò»Ò»¶ÁÈ¡¡£*/
    cbreak();
    //noecho(); /*¹Ø±Õ»ØÏÔ*/
    start_color();
       init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(6,COLOR_CYAN,COLOR_BLACK);
	init_pair(7,COLOR_RED,COLOR_BLACK);
}

/*ÑÓÊ±º¯Êý1£¬¿ÉÒÔ¶àŽÎµ÷ÓÃ*/
void delay(void){	
	int count = 0,count2 = 0;
	while(count < 999)	{		
		count2 = 0;		
		while(count2 < 9999){			
			count2++;		
			}		
			count++;	
			}
}
/*ÑÓÊ±º¯Êý2£¬¿ÉÒÔ¶àŽÎµ÷ÓÃ*/
void delay2(void){	
	int count = 0,count2 = 0;		
	while(count < 3999)	{		
		count2 = 0;		
		while(count2 < 9999){			
			count2++;		
			}		
			count++;	
			}

}

/*³õÊŒÏÔÊŸœçÃæ
*  ÏÔÊŸ³õŒ¶Á÷Ë®µÆ
* ÏÔÊŸœçÃæ¿ÉÒÔÃÀ»¯
*/

void begin_add(WINDOW *a)
{
	int iii=0;
	int jjj=0;
	while(1)
		{
			for(change_eye=1;change_eye<3;change_eye++)
				{
				wattron(a,COLOR_PAIR(change_eye));
				if(iii==0)
				mvwprintw(a, iii, jjj++, "..");
				if(jjj==80)
				mvwprintw(a, iii++, jjj-1, ".");
				if(iii==24)
				mvwprintw(a, iii-1, jjj--, "..");
				if(jjj==-1)
				mvwprintw(a, iii--, jjj+1, ".");
				wrefresh(a);
				//wclear(a);
				delay();
				wattroff(a,COLOR_PAIR(change_eye));
				}
		}
}
/*×Ö·ûÏÔÊŸœçÃæ
* ÏÔÊŸœçÃæ¿ÉÃÀ»¯
*/
void begin1_dos(void)
{
	pthread_t tid4;
	first_win=newwin(24, 80, 0, 0);         /* ¿òŒÜŽ°¿Ú */
	pthread_create(&tid4,NULL,(void*)begin_add,first_win); 
	int i = 1;
	char str11[]="Mini BUG 管理系统";
	char str12[]="日了够了";
	char str13[]="欢迎";
	char str14[]="                   ";
	char str15[]=" 逼逼男人设计  ";
	char tmp[30] = {0};
	
if(signal == 0)
{
	signal++;
	for(i = 1; i <= strlen(str11); ++i)
	{
		memset(tmp,0,30);
		strncpy(tmp,str11,i);
		wattron(first_win,COLOR_PAIR(2)|A_BOLD|A_BLINK);
    	mvwprintw(first_win, 6, 17, tmp);
		wattroff(first_win,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		wrefresh(first_win);
		delay();
	}
	
	for(i = 1; i <= strlen(str12); ++i)
	{
		memset(tmp,0,30);
		strncpy(tmp,str12,i);
		wattron(first_win,COLOR_PAIR(6)|A_BOLD|A_BLINK);
	    mvwprintw(first_win, 8, 29, tmp);
		wattroff(first_win,COLOR_PAIR(6)|A_BOLD|A_BLINK);
		wrefresh(first_win);
		delay();
	}
	sleep(1);
	/*ÏûÈ¥×Ö·ûŽ®*/
	for(i = 1; i <= strlen(str14); ++i)
	{
		memset(tmp,0,30);
		strncpy(tmp,str14,i);
		wattron(first_win,COLOR_PAIR(2)|A_BOLD|A_BLINK);
    	mvwprintw(first_win, 6, 17, tmp);
		wattroff(first_win,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		wrefresh(first_win);
		delay();
	}
	
	for(i = 1; i <= strlen(str15); ++i)
	{
		memset(tmp,0,30);
		strncpy(tmp,str15,i);
		wattron(first_win,COLOR_PAIR(4)|A_BOLD|A_BLINK);
	    mvwprintw(first_win, 8, 29, tmp);
		wattroff(first_win,COLOR_PAIR(4)|A_BOLD|A_BLINK);
		wrefresh(first_win);
		delay();
	}
	
	/*ÏÔÊŸMiniBUG Management Systems*/
	
	for(i = 2; i < 6; i++)
	{
		wattron(first_win,COLOR_PAIR(1)|A_BOLD|A_BLINK);
		mvwprintw(first_win, 8, 29, str15);
		wattroff(first_win,COLOR_PAIR(1)|A_BOLD|A_BLINK);

		mvwprintw(first_win, i-1, 25, "                              ");
		wattron(first_win,COLOR_PAIR(1)|A_BOLD|A_BLINK);
    	mvwprintw(first_win, i, 25, "MiniBUG Management Systems");
		wattroff(first_win,COLOR_PAIR(1)|A_BOLD|A_BLINK);
		wrefresh(first_win);
		//refresh();
		delay2();
	}
	
	/*ÏÔÊŸwelcome*/
	
	for(i = 1; i <= strlen(str13); ++i)
	{
		memset(tmp,0,30);
		strncpy(tmp,str13,i);
		wattron(first_win,COLOR_PAIR(i)|A_BOLD);
		mvwprintw(first_win,15, 33, tmp);
		wattroff(first_win,COLOR_PAIR(i)|A_BOLD);
		wrefresh(first_win);
		delay2();
	}
		wattron(first_win,COLOR_PAIR(1)|A_BOLD);
		mvwprintw(first_win,15, 33, tmp);
		wattroff(first_win,COLOR_PAIR(1)|A_BOLD);
		wrefresh(first_win);

	/*ÏÔÊŸ...*/
	
	for(i = 0; i <= 3; i++)
	{
		if(i == 0)
		{
			wattron(first_win,COLOR_PAIR(1)|A_BOLD);
			mvwprintw(first_win,16, 35, ".");
			wattroff(first_win,COLOR_PAIR(1)|A_BOLD);
		}
		else if(i == 1)
		{
			wattron(first_win,COLOR_PAIR(1)|A_BOLD);
			mvwprintw(first_win,16, 35, "..");
			wattroff(first_win,COLOR_PAIR(1)|A_BOLD);
		}
		else if(i == 2)
		{
			wattron(first_win,COLOR_PAIR(1)|A_BOLD);
			mvwprintw(first_win,16, 35, "...");
			wattroff(first_win,COLOR_PAIR(1)|A_BOLD);
		}
		else
		{
			wattron(first_win,COLOR_PAIR(1)|A_BOLD);
			mvwprintw(first_win,16, 35, "   ");
			wattroff(first_win,COLOR_PAIR(1)|A_BOLD);
		}
	    wrefresh(first_win);
		sleep(1);
	}
}
	pthread_cancel(tid4);
    ko_win(first_win);
}
/*ÍË³öº¯Êý*/
void exit_win(void)
{
    endwin();
}
/*clear win*/
 void ko_win(WINDOW *koo_win)
{
	wclear(koo_win);
        wrefresh(koo_win);
        delwin(koo_win); 
}
/* ÌáÊŸÐÅÏ¢Ž°¿Ú */
void create_msg_zone(void)
{
    message_win=newwin(4, 78, 19, 1); /* ÌáÊŸÐÅÏ¢Ž°¿Ú */
    keypad(message_win, true);
    wrefresh(win);
}

/**
 * function£º»æÖÆÖ÷¿òŒÜœçÃæ          
 * parmater£ºÎÞ
 * return  £ºÎÞ
 */
void create_frame(void)
{   
        wattron(win,COLOR_PAIR(1));
    win=newwin(24, 80, 0, 0);  
    wbkgd(win,COLOR_PAIR(1));/* ¿òŒÜŽ°¿Ú */

    box(win,0,ACS_CKBOARD);    /* »­Žó¿òŒÜ±ß¿ò */
    /* ÐŽÈëÈíŒþÏµÍ³Ãû */
    mvwprintw(win, 0, 25, "Mini BUG Management Systems");

    /* »­±ß¿òºáÏß */
    mvwaddch(win, 18, 0, ACS_LTEE);
    mvwhline(win, 18, 1, 0, 78);
    mvwaddch(win, 18, 79, ACS_RTEE);
    mvwprintw(win, 18, 36, "Message");
    
    wrefresh(win);
    wattroff(win,COLOR_PAIR(1));
}

/**
 * function£º»æÖÆ±êÌâŽ°¿Ú          
 * parmater£ºs£º±êÌâŽ°¿ÚµÄÃû×Ö
 * return£ºÎÞ
 */
void create_title_window(char *s)
{
	
    title_win=newwin(3, 20, 1, 28);   /* ±êÌâŽ°¿Ú */
	wattron(title_win,A_BOLD);
    wclear(title_win);
    box(title_win,0,0);
    mvwprintw(title_win,1,5,s);
	wattroff(title_win,A_BOLD);
    wrefresh(title_win); 
}

/**
 * function£ºÔÚÏûÏ¢Ž°¿ÚÏÔÊŸÌáÊŸ»òŸ¯žæÏûÏ¢
 * parmater£ºs£ºËùÒªÏÔÊŸµÄÐÅÏ¢µÄÄÚÈÝ
 * return£ºÎÞ
 */
void show_message(char *s)
{   
   
    wclear(message_win);
    mvwprintw(message_win,0,0,s);
    if(wrong_time>1)
    	mvwprintw(message_win,2,0,"account or password is wrong %d times!",wrong_time-1);
    	if(wrong_time==0)
        {   
    		wclear(message_win);
    		mvwprintw(message_win,0,0,s);
           }
  	        wrefresh(message_win);
           
}
 
 

/**
 * function£ºµÇÂŒÌáÊŸœçÃæ       
 * parmater£ºÎÞ
 * return£ºÎÞ
 * žÃº¯Êý¿ÉÒÔÓÅ»¯
 */

void begin_dos(void)
{
	MEVENT mouse;
	raw();
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);	
	int key;
	begin_win=newwin(24, 80, 0, 0);
	box(begin_win,0,0);  
	keypad(begin_win, true);
	if(quit==3)
		wattron(begin_win,COLOR_PAIR(1));
	if(quit==4)
		wattron(begin_win,COLOR_PAIR(6));
	if(quit==5)
		wattron(begin_win,COLOR_PAIR(5));
	if(quit==6)
		wattron(begin_win,COLOR_PAIR(4));
	if(quit==7)
		wattron(begin_win,COLOR_PAIR(3));
	if(quit==8)
		wattron(begin_win,COLOR_PAIR(2));
	if(quit==9)
		wattron(begin_win,COLOR_PAIR(7));

	wattron(begin_win,A_REVERSE);/*ÏÔÊŸminibug*/
	mvwprintw(begin_win,1,78,"X");
	mvwprintw(begin_win,3,44,"  ");
	mvwprintw(begin_win,3,64,"      ");
	mvwprintw(begin_win,4,44,"  ");
	mvwprintw(begin_win,4,64,"  ");
	mvwprintw(begin_win,4,68,"  ");
	mvwprintw(begin_win,5,44,"  ");
	mvwprintw(begin_win,5,64,"      ");
	mvwprintw(begin_win,6,6, "          ");
	mvwprintw(begin_win,6,20,"   ");
	mvwprintw(begin_win,6,27,"      ");
	mvwprintw(begin_win,6,37,"   ");
	mvwprintw(begin_win,6,44,"      ");
	mvwprintw(begin_win,6,54,"  ");
	mvwprintw(begin_win,6,58,"  ");
	mvwprintw(begin_win,6,68,"  ");
	mvwprintw(begin_win,7,6,"  ");
	mvwprintw(begin_win,7,10,"  ");
	mvwprintw(begin_win,7,14,"  ");
	mvwprintw(begin_win,7,20,"   ");
	mvwprintw(begin_win,7,27,"  ");
	mvwprintw(begin_win,7,31,"  ");
	mvwprintw(begin_win,7,37,"   ");
	mvwprintw(begin_win,7,44,"  ");
	mvwprintw(begin_win,7,48,"  ");
	mvwprintw(begin_win,7,54,"  ");
	mvwprintw(begin_win,7,58,"  ");
	mvwprintw(begin_win,7,68,"  ");
	mvwprintw(begin_win,8,6,"  ");
	mvwprintw(begin_win,8,10,"  ");
	mvwprintw(begin_win,8,14,"  ");
	mvwprintw(begin_win,8,20,"   ");
	mvwprintw(begin_win,8,27,"  ");
	mvwprintw(begin_win,8,31,"  ");
	mvwprintw(begin_win,8,37,"   ");
	mvwprintw(begin_win,8,44,"      ");
	mvwprintw(begin_win,8,54,"      ");

	mvwprintw(begin_win,8,64,"      ");
	mvwprintw(begin_win,11,4,"                                                                    ");
	mvwprintw(begin_win,13,4,"                                                                    ");
	
	//wattron(begin_win,COLOR_PAIR(6));
	wattron(begin_win,A_STANDOUT);
	mvwprintw(begin_win,18,17,"    LOGIN    ");
	mvwprintw(begin_win,18,51,"    COLOR    ");
	wattroff(begin_win,A_STANDOUT);
	//wattroff(begin_win,COLOR_PAIR(6));
	wattroff(begin_win,A_REVERSE);
	//wattron(begin_win,COLOR_PAIR(6));
	mvwprintw(begin_win,22,65,"DATE:2015.5");
	wmove(begin_win,1,78);
	
	wrefresh(begin_win);
	if(quit==3)
		wattroff(begin_win,COLOR_PAIR(1)); 
	if(quit==4)
		wattroff(begin_win,COLOR_PAIR(6));
	if(quit==5)
		wattroff(begin_win,COLOR_PAIR(5));
	if(quit==6)
		wattroff(begin_win,COLOR_PAIR(4));
	if(quit==7)
		wattroff(begin_win,COLOR_PAIR(3));
	if(quit==8)
		wattroff(begin_win,COLOR_PAIR(2));
	if(quit==9)
		wattroff(begin_win,COLOR_PAIR(7));
	
	key = wgetch(begin_win);
	switch(key)
		{
			case KEY_MOUSE : 
				getmouse(&mouse); /*get mouse action*/

				if (!wenclose(begin_win, mouse.y, mouse.x)) 
				break; /*do nothing if not in window*/

			wmouse_trafo(begin_win, &mouse.y, &mouse.x, FALSE);

		if ((18 <= mouse.x && mouse.x <= 30) && ( mouse.y ==18))
				quit=2;
		if ((52 <= mouse.x && mouse.x <= 64) && ( mouse.y ==18))
			{
				quit++;
				if(quit==10)
					quit=3;
			}

			if (1 == mouse.y && 78 == mouse.x) /*Clicked 'X'*/
					quit = 1;

					break;
			case 'q' :
					quit = 1;
					break;
			case 'l' :
					quit =2;
					break;
			default :
					break;
}
	
}
/*1ŽÎŽíÎóÏÔÊŸÑÛŸŠ²ÊµÆ 2ŽÎŽíÎóÏÔÊŸžÐÌŸºÅ*/
void *thread1(void *arg)
{	
      int yellow=1;
	while(1)
		{
			curs_set(0);
			for(change_eye=1;change_eye<8;change_eye++)
				{

					mvwprintw(main_win,6,38,"                                   ");
					mvwprintw(main_win,7,38,"                                    ");
 					mvwprintw(main_win,8,38,"                                    ");
 					mvwprintw(main_win,10,38,"                                   ");
					if((change_eye%2)==0)
						yellow=1;
					else
						yellow=4;
					wattron(main_win,COLOR_PAIR(change_eye)|A_REVERSE);
					mvwprintw(main_win,7,16,"O");
					mvwprintw(main_win,7,24,"O");
					wattroff(main_win,COLOR_PAIR(change_eye)|A_REVERSE);
					wattron(main_win,COLOR_PAIR(yellow)|A_REVERSE);
					if(wrong_time>2)
						{
						mvwprintw(main_win,6,46-change_eye,"    ");
						mvwprintw(main_win,6,56-change_eye,"    ");
						mvwprintw(main_win,6,66-change_eye,"    ");
						mvwprintw(main_win,7,46-change_eye,"    ");
						mvwprintw(main_win,7,56-change_eye,"    ");
						mvwprintw(main_win,7,66-change_eye,"    ");
						mvwprintw(main_win,8,46-change_eye,"    ");
						mvwprintw(main_win,8,56-change_eye,"    ");
						mvwprintw(main_win,8,66-change_eye,"    ");
						mvwprintw(main_win,10,46-change_eye,"    ");
						mvwprintw(main_win,10,56-change_eye,"    ");
						mvwprintw(main_win,10,66-change_eye,"    ");
						}
					wattroff(main_win,COLOR_PAIR(yellow)|A_REVERSE);
					wrefresh(main_win);
					delay2();
				}
	
		}
}

/*ÓÃ»§µÇÈëº¯Êý*/
void user_login(void)
{
        
        main_win=newwin(14, 78, 4, 1);
        /* Ö÷œçÃæŽ°¿Ú */
       wattron(main_win,COLOR_PAIR(1));
    /* µ±¿ªÆôkeypadáá£¬¿ÉÒÔÊ¹ÓÃŒüÅÌÉÏµÄÒ»Ð©ÌØÊâ×ÖÔª£¬ÈçÉÏÏÂ×óÓÒµÈ·œÏòŒü*/
       keypad(main_win, true);
       char str1[10];
       char str2[8];
       wrefresh(main_win);
       mvwprintw(main_win,1,13,"UserName:");
       mvwprintw(main_win,1,40,"[The max length of username is 10]");
       mvwprintw(main_win,3,13,"Password:");
       mvwprintw(main_win,3,40,"[The  length of password is 8]");
	wattron(main_win,COLOR_PAIR(1)|A_REVERSE);/*ÏÔÊŸ°×*/
	mvwprintw(main_win,6,10,"                     ");	
	wattron(main_win,COLOR_PAIR(change_eye));
	mvwprintw(main_win,7,16,"O");
	mvwprintw(main_win,7,24,"O");
	wattroff(main_win,COLOR_PAIR(change_eye));
	
	mvwprintw(main_win,7,10,"      ");
	mvwprintw(main_win,7,17,"       ");
	mvwprintw(main_win,7,25,"      ");
	
	mvwprintw(main_win,8,10,"                     ");
	mvwprintw(main_win,9,10,"         ---         ");
	mvwprintw(main_win,10,10,"                     ");
	wattroff(main_win,COLOR_PAIR(1)|A_REVERSE);
    
    show_message("Please input username!you have 3 times!");
    wmove(main_win,1,22);
    wrefresh(main_win); 
	
 	noecho();
	fflush(stdin); 
   int k=0;
   int e=0;/*ÅÐ¶ÏÕËºÅÊäÈë ¿ÉÍËžñ*/
   while((str1[k++]=wgetch(main_win))!='\n')
		{	
			if(str1[k-1]==(char)KEY_BACKSPACE)
				{
				str1[--k]='\0';
				str1[--k]='\0';
				if(k<0)
					k=0;
				for(e=0;e<k;e++)
				mvwaddch(main_win,1,22+e,str1[e]);
				mvwprintw(main_win,1,22+e,"        ");
				wmove(main_win,1,22+e);
				}
			else
			mvwaddch(main_win,1,21+k,str1[k-1]);
			wrefresh(main_win);
			fflush(stdin);
			
				
		}
	str1[k]='\0';
	str1[k+1]='\0';
	str1[k-1]='\0';
    wmove(main_win,3,22);
	 k=0;
    fflush(stdin);
	noecho();
	/*ÅÐ¶ÏÃÜÂëÊäÈë ¿ÉÍËžñ*/
	while((str2[k++]=wgetch(main_win))!='\n')
		{	
				if(str2[k-1]==(char)KEY_BACKSPACE)
				{
				str2[--k]='\0';
				str2[--k]='\0';
				if(k<0)
					k=0;
				for(e=0;e<k;e++)
				mvwaddch(main_win,3,22+e,'*');
				mvwprintw(main_win,3,22+e,"        ");
				wmove(main_win,3,22+e);
				}
			else
			mvwprintw(main_win,3,21+k,"*");
			wrefresh(main_win);
			fflush(stdin);
				
		}
	str2[k]='\0';
	str2[k+1]='\0';
	str2[k-1]='\0';
	 strcpy(user_defined,str1);
	 strcpy(passwd_defined,str2);
 if(strcmp(str1,"admin")==0&&strcmp(str2,"123456")==0)
    	{
    		wrong_time=0;
    		show_message("Login successful!");
    		
    		password=1; 
    		}
 else
    login_success=1;

        wattroff(main_win,COLOR_PAIR(1));
}

/*bug²Ëµ¥œçÃæ*/
void menu_dos(void)
{

	MEVENT mouse1;
	int key1;
	raw();
	 menu_win1=newwin(14, 78, 4, 1);   
	  wattron(menu_win1,COLOR_PAIR(2));/* Ö÷œçÃæŽ°¿Ú */
		//int hh,jj;
    /* µ±¿ªÆôkeypadáá£¬¿ÉÒÔÊ¹ÓÃŒüÅÌÉÏµÄÒ»Ð©ÌØÊâ×ÖÔª£¬ÈçÉÏÏÂ×óÓÒµÈ·œÏòŒü*/
	/*ŽËŽŠÎªÊó±ê*/
    keypad(menu_win1, true);
    mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);	
    wattron(menu_win1,A_REVERSE);
    mvwprintw(menu_win1,1,4,"         ");
    mvwprintw(menu_win1,2,4,"SHOW BUGS");
    mvwprintw(menu_win1,3,4,"         ");
    wattroff	(menu_win1,COLOR_PAIR(2));
    wattron	(menu_win1,COLOR_PAIR(4));
    mvwprintw(menu_win1,1,16,"         ");
    mvwprintw(menu_win1,2,16,"ADD A BUG");
    mvwprintw(menu_win1,3,16,"         ");
    wattroff	(menu_win1,COLOR_PAIR(4));
    wattron	(menu_win1,COLOR_PAIR(3));
    mvwprintw(menu_win1,1,28,"         ");
    mvwprintw(menu_win1,2,28,"DEL A BUG");
    mvwprintw(menu_win1,3,28,"         ");
    wattroff	(menu_win1,COLOR_PAIR(3));
	wattron	(menu_win1,COLOR_PAIR(6));
	mvwprintw(menu_win1,1,40,"          ");
    mvwprintw(menu_win1,2,40,"SEARCH BUG");
	mvwprintw(menu_win1,3,40,"          ");
	wattroff	(menu_win1,COLOR_PAIR(6));
	wattron	(menu_win1,COLOR_PAIR(5));
	mvwprintw(menu_win1,1,53,"               ");
    mvwprintw(menu_win1,2,53,"USER MANAGEMENT");
	mvwprintw(menu_win1,3,53,"               ");
	wattroff	(menu_win1,COLOR_PAIR(5));
	wattron	(menu_win1,COLOR_PAIR(7));
	mvwprintw(menu_win1,1,71,"    ");
    mvwprintw(menu_win1,2,71,"EXIT");
	mvwprintw(menu_win1,3,71,"    ");
	wattroff	(menu_win1,COLOR_PAIR(7));
    show_message("welcome to mini bug management system");

	wattron	(menu_win1,COLOR_PAIR(1));
	mvwprintw(menu_win1,9,67,"     ");
    mvwprintw(menu_win1,10,67,"EMPTY");
	mvwprintw(menu_win1,11,67,"     ");
	wattroff	(menu_win1,COLOR_PAIR(1));
    
	 wattroff(menu_win1,A_REVERSE);
	 mvwprintw(menu_win1,5,2,"<The above is with the mouse||Following with the keyboard>");
	wrefresh(menu_win1);
/*ŽËŽŠÎªŒüÅÌ*/
	x = 2;
	y = 6;

	for(i = 0;i < m_choices;++i)
		{
		if(highlight == i + 1) /* Ê¹Ñ¡ÔñµÄ×Ö·ûŽ®žßÁÁÏÔÊŸ*/
			{
			if(highlight==1){		
			wattron(menu_win1,COLOR_PAIR(2)|A_BOLD|A_DIM);
			mvwprintw(menu_win1, y, x, "Show all bugs in history.");
			wattroff(menu_win1,COLOR_PAIR(2)|A_BOLD|A_DIM);
				  }
			if(highlight==2){
				wattron(menu_win1,COLOR_PAIR(4)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "Add a bug in MiniBug.");
				wattroff(menu_win1,COLOR_PAIR(4)|A_BOLD|A_DIM);
				  }
			if(highlight==3){
				wattron(menu_win1,COLOR_PAIR(3)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "Del a bug in MiniBug.");
				wattroff(menu_win1,COLOR_PAIR(3)|A_BOLD|A_DIM);
				  }
			if(highlight==4){
				wattron(menu_win1,COLOR_PAIR(6)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "Search a record in histroy.");
				wattroff(menu_win1,COLOR_PAIR(6)|A_BOLD|A_DIM);
				  }
			if(highlight==5){
				wattron(menu_win1,COLOR_PAIR(5)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "Enter users management.");
				wattroff(menu_win1,COLOR_PAIR(5)|A_BOLD|A_DIM);
				  }
			if(highlight==6){
				wattron(menu_win1,COLOR_PAIR(7)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "Empty all history.");
				wattroff(menu_win1,COLOR_PAIR(7)|A_BOLD|A_DIM);
				  }
			if(highlight==7){
				wattron(menu_win1,COLOR_PAIR(1)|A_BOLD|A_DIM);
				mvwprintw(menu_win1, y, x, "EXIT MiniBug.");
				wattroff(menu_win1,COLOR_PAIR(1)|A_BOLD|A_DIM);
				  }
}
else
	{
	
	wrefresh(menu_win1);
	wattron(menu_win1,COLOR_PAIR(1));
	mvwprintw(menu_win1, y, x, "%s", menu_choices[i]);
	wattroff(menu_win1,COLOR_PAIR(1));
	}
++y;
}
wrefresh(menu_win1);

    choices=8;
    while(choices>7){
    wmove(menu_win1,25,80);
    wrefresh(menu_win1);
    echo();
    //wscanw(menu_win1,"%d",&choices);
    key1 = wgetch(menu_win1);
		switch(key1)
			{
				case KEY_MOUSE : 
					getmouse(&mouse1); /*get mouse action*/

					if (!wenclose(menu_win1, mouse1.y, mouse1.x)) 
					break; /*do nothing if not in window*/

					wmouse_trafo(menu_win1, &mouse1.y, &mouse1.x, FALSE);

				if ((4 <= mouse1.x && mouse1.x <= 13) && (1<= mouse1.y && mouse1.y <= 3))
					choices=1;

				if ((16 <= mouse1.x && mouse1.x <= 25) && (1<= mouse1.y && mouse1.y <= 3))
					choices=2;
				if ((28 <= mouse1.x && mouse1.x <= 37) && (1<= mouse1.y && mouse1.y <= 3))
					choices=3;
				if ((40 <= mouse1.x && mouse1.x <= 50) && (1<= mouse1.y && mouse1.y <= 3))
					choices=4;
				if ((53 <= mouse1.x && mouse1.x <= 68) && (1<= mouse1.y && mouse1.y <= 3))
					choices=5;
				if ((71 <= mouse1.x && mouse1.x <= 75) && (1<= mouse1.y && mouse1.y <= 3))
					choices=7;
				if ((67 <= mouse1.x && mouse1.x <= 72) && (9<= mouse1.y && mouse1.y <= 11))
					choices=6;
						break;
				case 'q' :
						choices=7;
						break;
				case KEY_UP:
					if(highlight == 1)
						highlight = m_choices;
						else
						--highlight;
						break;
				case KEY_DOWN:
					if(highlight == m_choices)
						highlight = 1;
					else
					++highlight;
					break;
				case 10:
				choices = highlight;
					break;
					
						default :
						break;
				}
x = 2;
y = 6;
/*ŒüÅÌÈ·¶šÑ¡ÔñœçÃæ*/
for(i = 0;i < m_choices;++i)
{
if(highlight == i + 1) /* Ê¹Ñ¡ÔñµÄ×Ö·ûŽ®žßÁÁÏÔÊŸ*/
{
	if(highlight==1){		
		wattron(menu_win1,COLOR_PAIR(2)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Show all bugs in history.");
		wattroff(menu_win1,COLOR_PAIR(2)|A_BOLD|A_DIM);
				  }
	if(highlight==2){
		wattron(menu_win1,COLOR_PAIR(4)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Add a bug in MiniBug.");
		wattroff(menu_win1,COLOR_PAIR(4)|A_BOLD|A_DIM);
				  }
	if(highlight==3){
		wattron(menu_win1,COLOR_PAIR(3)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Del a bug in MiniBug.");
		wattroff(menu_win1,COLOR_PAIR(3)|A_BOLD|A_DIM);
				  }
	if(highlight==4){
		wattron(menu_win1,COLOR_PAIR(6)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Search a record in histroy.");
		wattroff(menu_win1,COLOR_PAIR(6)|A_BOLD|A_DIM);
				  }
	if(highlight==5){
		wattron(menu_win1,COLOR_PAIR(5)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Enter users management.");
		wattroff(menu_win1,COLOR_PAIR(5)|A_BOLD|A_DIM);
				  }
	if(highlight==6){
		wattron(menu_win1,COLOR_PAIR(1)|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "Empty all history.");
		wattroff(menu_win1,COLOR_PAIR(1)|A_BOLD|A_DIM);
				  }
	if(highlight==7){
		wattron(menu_win1,COLOR_PAIR(7)|A_BOLD|A_DIM|A_BOLD|A_DIM);
		mvwprintw(menu_win1, y, x, "EXIT MiniBug.");
		wattroff(menu_win1,COLOR_PAIR(7)|A_BOLD|A_DIM);
				  }
}
else
	{
	wattron(menu_win1,COLOR_PAIR(1));
	mvwprintw(menu_win1, y, x, "%s                           ", menu_choices[i]);
	wattroff(menu_win1,COLOR_PAIR(1));
	}
++y;
}
wrefresh(menu_win1);
   }
   ko_win(menu_win1);
}

/*ÌíŒÓbugœçÃæ*/
void add_dos(void){

	add_win=newwin(14,78,4,1);
	wrefresh(add_win);
	mvwprintw(add_win,1,10,"   BUG ID:");
	mvwprintw(add_win,1,50,"MAX LEAGTH IS 5");
	mvwprintw(add_win,2,10," SEVERITY:");
	mvwprintw(add_win,2,50,"NORMAL/MAJOR/BLOCKER");
	mvwprintw(add_win,3,10,"     TYPE:");
	mvwprintw(add_win,3,50,"MAX LEAGTH IS 128");
	mvwprintw(add_win,4,10,"     DATA:");
	mvwprintw(add_win,4,50,"EG 2015/2/30");
	mvwprintw(add_win,5,10,"INTRODUCE:");
	mvwprintw(add_win,7,50,"MAX LEAGTH IS 256");
	show_message("Please input bug ");
	wmove(add_win,1,20);
	wrefresh(add_win);
}
/*ÏÔÊŸbugÀàÐÍ*/
void show_dos(void)
{	
	show_win=newwin(1,78,4,1); 
	wattron(show_win,COLOR_PAIR(2));
	mvwprintw(show_win,0,1,"BUG ID:  SEVERITY:   TYPE :         DATA:          INTRODUCE:");
	wattroff(show_win,COLOR_PAIR(2));
 	show_message("click on the back to menu||You can use the up and down keys");
 	wrefresh(show_win);				
}
/*ÏÔÊŸ²éÕÒœçÃæ*/
void search_dos(void){
    search_win=newwin(14,78,4,1);
    mvwprintw(search_win,5,25,"please input bug id(search):");
    show_message("bug id search");
    wmove(search_win,14,51);
    wrefresh(search_win);
    echo();
    fflush(stdin);
    wscanw(search_win,"%d",&search_id);
}
/*²éÕÒœá¹û1*/
void search_dos_result1(void){
    search_win1=newwin(14,78,4,1);
    mvwprintw(search_win1,0,1,"BUG ID:  SEVERITY:   TYPE :         DATA:          INTRODUCE:");
    wattron(search_win1,A_REVERSE);
    mvwprintw(search_win1,0,70,"BACK");
    wattroff(search_win1,A_REVERSE);
    show_message("show bugs||click on the back to menu");
    wmove(search_win1,24,79);
    wrefresh(search_win1);
}
/*²éÕÒœá¹û2*/
void search_dos_result2(void){
    search_win2=newwin(14,78,4,1);
    mvwprintw(search_win2,3,20,"no such bug id");
    show_message("wait 2 seconds");
    wmove(search_win2,24,79);
    wrefresh(search_win2);
}
/*ÉŸ³ýbug*/
void del_dos(void){
    del_bug_win=newwin(14,78,4,1);
    mvwprintw(del_bug_win,5,25,"please input bug id(delete) :");
    show_message("bug id delete(if id is not at here,back to menu)");
    wmove(del_bug_win,14,51);
    wrefresh(del_bug_win);
    echo();
    fflush(stdin);
    wscanw(del_bug_win,"%d",&del_id);
}
/*ÓÃ»§œçÃæ*/
void user_menu_dos(void)
{	

	MEVENT mouse2;
	int key2;
	raw();
       user_menu_win=newwin(14, 78, 4, 1);    /* Ö÷œçÃæŽ°¿Ú */
	wattron(user_menu_win,COLOR_PAIR(4));
    	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);
    /* µ±¿ªÆôkeypadáá£¬¿ÉÒÔÊ¹ÓÃŒüÅÌÉÏµÄÒ»Ð©ÌØÊâ×ÖÔª£¬ÈçÉÏÏÂ×óÓÒµÈ·œÏòŒü*/
    	keypad(user_menu_win, true);
    	wattron(user_menu_win,A_REVERSE);
    	mvwprintw(user_menu_win,1,4,"	           ");
    	mvwprintw(user_menu_win,2,4,"   SHOW USERS  ");
    	mvwprintw(user_menu_win,3,4,"               ");	
	mvwprintw(user_menu_win,1,21,"                ");
    	mvwprintw(user_menu_win,2,21,"    ADD USERS   ");
	mvwprintw(user_menu_win,3,21,"                ");
	mvwprintw(user_menu_win,1,39,"                ");
  	mvwprintw(user_menu_win,3,39,"                ");
 	mvwprintw(user_menu_win,2,39,"    DEL USERS   ");
 	mvwprintw(user_menu_win,1,57,"                  ");
  	mvwprintw(user_menu_win,3,57,"                  ");
      mvwprintw(user_menu_win,2,57," BACK TO BUG MENU ");
      show_message("welcome to account management");
	wattroff	(user_menu_win,COLOR_PAIR(4));
	wattron	(user_menu_win,COLOR_PAIR(1));
	mvwprintw(user_menu_win,9,67,"     ");
  	mvwprintw(user_menu_win,10,67,"EMPTY");
	mvwprintw(user_menu_win,11,67,"     ");
	wattroff	(user_menu_win,COLOR_PAIR(1));
	wattroff(user_menu_win,A_REVERSE);
      mvwprintw(user_menu_win,5,2,"<The above is with the mouse||Following with the keyboard>");
	wrefresh(user_menu_win);
	x = 2;
	y = 7;
	for(i = 0;i < user_m_choices;++i)
	{
	if(highlight == i + 1) /* Ê¹Ñ¡ÔñµÄ×Ö·ûŽ®žßÁÁÏÔÊŸ*/
		{
		wattron(user_menu_win,COLOR_PAIR(1)|A_BOLD|A_DIM);
		if(highlight==1)	
			mvwprintw(user_menu_win, y, x, "Show all users in history.");
		if(highlight==2)
			mvwprintw(user_menu_win, y, x, "Add a user in MiniBug.");
		if(highlight==3)
			mvwprintw(user_menu_win, y, x, "Del a user in MiniBug.");
		if(highlight==4)
			mvwprintw(user_menu_win, y, x, "Empty all users.");
		if(highlight==5)
			mvwprintw(user_menu_win, y, x, "Back to bug menu.");
		wattroff(user_menu_win,COLOR_PAIR(1)|A_BOLD|A_DIM);
	}
	else
		{	
		wrefresh(user_menu_win);
		wattron(user_menu_win,COLOR_PAIR(4));
		mvwprintw(user_menu_win, y, x, "%s", user_menu_choices[i]);
		wattroff(user_menu_win,COLOR_PAIR(4));
	}
	++y;
}
	wrefresh(menu_win1);
    user_choices=6;
    while(user_choices>5){
    wmove(user_menu_win,7,48);
    wrefresh(user_menu_win);
    echo();
    //wscanw(user_menu_win,"%d",&user_choices);
    key2 = wgetch(user_menu_win);
		switch(key2)
			{
				case KEY_MOUSE : 
					getmouse(&mouse2); /*get mouse action*/

					if (!wenclose(user_menu_win, mouse2.y, mouse2.x)) 
					break; /*do nothing if not in window*/

					wmouse_trafo(user_menu_win, &mouse2.y, &mouse2.x, FALSE);

				if ((4 <= mouse2.x && mouse2.x <= 19) && (1<= mouse2.y && mouse2.y <= 3))
					user_choices=1;

				if ((21 <= mouse2.x && mouse2.x <= 37) && (1<= mouse2.y && mouse2.y <= 3))
					user_choices=2;
				if ((39 <= mouse2.x && mouse2.x <= 55) && (1<= mouse2.y && mouse2.y <= 3))
					user_choices=3;
				if ((57 <= mouse2.x && mouse2.x <= 76) && (1<= mouse2.y && mouse2.y <= 3))
					user_choices=5;
				if ((67 <= mouse2.x && mouse2.x <= 72) && (9<= mouse2.y && mouse2.y <= 11))
					user_choices=4;

						break;
						case 'q' :
						user_choices=5;
						break;
						case KEY_UP:
					if(highlight == 1)
						highlight = user_m_choices;
						else
						--highlight;
						break;
				case KEY_DOWN:
					if(highlight == user_m_choices)
						highlight = 1;
					else
					++highlight;
					break;
				case 10:
				user_choices = highlight;
					break;
						default :
						break;
			}
    	x = 2;
	y = 7;

	for(i = 0;i < user_m_choices;++i)
	{
	if(highlight == i + 1) /* Ê¹Ñ¡ÔñµÄ×Ö·ûŽ®žßÁÁÏÔÊŸ*/
	{
			wattron(user_menu_win,COLOR_PAIR(1)|A_BOLD|A_DIM);
			if(highlight==1)	
				mvwprintw(user_menu_win, y, x, "Show all users in history.");
			if(highlight==2)
				mvwprintw(user_menu_win, y, x, "Add a user in MiniBug.");	  
			if(highlight==3)
				mvwprintw(user_menu_win, y, x, "Del a user in MiniBug.");
			if(highlight==4)
				mvwprintw(user_menu_win, y, x, "Empty all users.");
			if(highlight==5)
				mvwprintw(user_menu_win, y, x, "Back to bug menu.");		
			wattroff(user_menu_win,COLOR_PAIR(1)|A_BOLD|A_DIM);
	}
	else
	{	
	wrefresh(user_menu_win);
	wattron(user_menu_win,COLOR_PAIR(4));
	mvwprintw(user_menu_win, y, x, "%s                                ", user_menu_choices[i]);
	wattroff(user_menu_win,COLOR_PAIR(4));
	}
	++y;
}
	wrefresh(menu_win1);
   }
   ko_win(user_menu_win);
}
/*ÓÃ»§ÏÔÊŸ*/
void user_show_dos(void)
{
    user_show_win=newwin(14,78,4,1);
    mvwprintw(user_show_win,1,1,"USER ID:  NAME:   PASSWORD:         DATA:");
    show_message("show users||click on the back to menu");
    wmove(user_show_win,24,79);
    wattron(user_show_win,A_REVERSE);
    mvwprintw(user_show_win,0,70,"BACK");
    wattroff(user_show_win,A_REVERSE);
    wrefresh(user_show_win);
}
/*ÓÃ»§ÌíŒÓ*/
void user_add_dos(void){
	user_add_win=newwin(14,78,4,1);
	wrefresh(user_add_win);
	mvwprintw(user_add_win,1,12,"     USER ID:");
	mvwprintw(user_add_win,1,50,"MAX LEAGTH IS 5");
	mvwprintw(user_add_win,2,12,"        NAME:");
	mvwprintw(user_add_win,2,50,"MAX LEAGTH IS 15");
	mvwprintw(user_add_win,3,12,"    PASSWORD:");
	mvwprintw(user_add_win,3,50,"MAX LEAGTH IS 15");
	mvwprintw(user_add_win,4,12,"        DATA:");
	mvwprintw(user_add_win,4,50,"EG 2015/2/30");
	show_message("Please input user ");
	wmove(user_add_win,1,25);
	wrefresh(user_add_win);
}
/*ÓÃ»§ÉŸ³ý*/
void del_user_dos(void){
    del_user_win=newwin(14,78,4,1);
    mvwprintw(del_user_win,5,25,"please input user id(delete) :");
    show_message("user id delete(if id is not at here,back to menu)");
    wmove(del_user_win,14,51);
    wrefresh(del_user_win);
    echo();
    fflush(stdin);
    wscanw(del_user_win,"%d",&del_user_id);
}
/*·µ»Ø°ŽŒü¹«ÓÃº¯Êý*/
int go_back(WINDOW *goback_win)
{
	MEVENT mouse1;
	int key1;
	 
	raw();
       keypad(goback_win, true);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);
	key1 = wgetch(goback_win);
		switch(key1)
			{
				case KEY_MOUSE : 
					getmouse(&mouse1); /*get mouse action*/

					if (!wenclose(goback_win, mouse1.y, mouse1.x)) 
					break; /*do nothing if not in window*/

					wmouse_trafo(goback_win, &mouse1.y, &mouse1.x, FALSE);

				if ((70 <= mouse1.x && mouse1.x <= 74) &&  mouse1.y ==  0)
					goback=1;
						break;
						case 'q' :
						goback=1;
						break;
						default :
						break;
				}
		return goback;
		
}

/*padÏÔÊŸ¹ö¶¯œçÃæ*/
void rooling(void)
{
	pad=newpad(80,128);
	wattron(pad,A_REVERSE);
	mvwprintw(pad,0,70,"BACK");
	wattroff(pad,A_REVERSE);
}
/*Íš¹ýÉÏÏÂŒü»¬¶¯*/
int rool_go_back(WINDOW *goback_win)
{
	MEVENT mouse2;
	int key2;
	 

	raw();
       keypad(goback_win, true);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);

	key2 = wgetch(goback_win);
		switch(key2)
			{
				case KEY_MOUSE : 
					getmouse(&mouse2); /*get mouse action*/
					if (!wenclose(goback_win, mouse2.y, mouse2.x)) 
					break; /*do nothing if not in window*/
					wmouse_trafo(goback_win, &mouse2.y, &mouse2.x, FALSE);

				if ((70 <= mouse2.x && mouse2.x <= 74) &&  mouse2.y ==  0)
					goback=1;
						break;
				case KEY_UP:
					if(rool_page==0)
						break;
					else
					rool_page=rool_page-1;
					break;

				case  KEY_DOWN:

					if(rool_page==76)
						break;
					else
						rool_page=rool_page+1;
					break;
						case 'q' :
						goback=1;
						break;
						default :
						break;
				
		}
		return goback;		
}
/*Ÿ¯žæœçÃæ*/
int warm_dos(void)
{
	MEVENT mouse3;
	int key3;
	 warm_win=newwin(7,22,8,30);
	raw();
       keypad(warm_win, true);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);
	
	box(warm_win,0,0);
	wattron(warm_win,COLOR_PAIR(1));
	mvwprintw(warm_win,1,20,"X");
	mvwprintw(warm_win,2,4,"(O_O) Really?");
	mvwprintw(warm_win,4,4,"yes");
	mvwprintw(warm_win,4,16,"no");
	
	wrefresh(warm_win);
	wattroff(warm_win,COLOR_PAIR(1));
	while(warm!=0&&warm!=2){
		//fflush(stdin);
	key3 = wgetch(warm_win);
		switch(key3)
			{
				case KEY_MOUSE : 
					getmouse(&mouse3); /*get mouse action*/

					if (!wenclose(warm_win, mouse3.y, mouse3.x)) 
					break; /*do nothing if not in window*/

					wmouse_trafo(warm_win, &mouse3.y, &mouse3.x, FALSE);

				if ((20<= mouse3.x && mouse3.x <= 21) &&  mouse3.y ==  1)
					warm=0;
				
				if ((4<= mouse3.x && mouse3.x <= 7) &&  mouse3.y ==  4)
					warm=2;
				
					if ((16<= mouse3.x && mouse3.x <= 18) &&  mouse3.y ==  4)
						warm=0;
					break;
					case 'n' :
						warm=0;
						break;
					case 'y' :
						warm=2;
						break;
						default :
						break;

		}
	}	
	return warm;
}
