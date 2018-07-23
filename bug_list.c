/**
 * bug_list.c
 * ����:���ݴ洢�ļ����״�ʹ�ö�������������Ҫ�Ż�
 * ��Ҫ�Ż���:
 * 1:�û�����bug����Ӧ�÷ֿ����
 * 2:�洢�ı�����Ӧ�ú��������ֿ����
 * 3:user��bug�����ظ� ���迼�Ǽ�����
 * author:lyf 2015-05-28
 * version: 1.0
 * modify:
 */
 #include "bug_list.h"
extern int flag;
extern int user_flag;
extern FILE *fp;
extern FILE *fp1;
extern FILE *fp2;
extern FILE *fp3;
extern FILE *fp4;
extern FILE *fp5;
int rool1=0;

/*������������*/
b_tree add_bug(b_tree root){
       b_tree newnode;
       b_tree currentnode;
       b_tree parentnode;
       int node;
       newnode =(b_tree) malloc (sizeof(treenode));
/*�˴�Ϊ��ncurses������洢����*/       
	wmove(add_win,1,20);
       fflush(stdin);
	wscanw(add_win,"%d",&newnode->id);
       node= newnode->id;
	wmove(add_win,2,20);
	wgetstr(add_win,newnode->severity);
	wmove(add_win,3,20);
	wgetstr(add_win,newnode->type);
	wmove(add_win,4,20);
	wgetstr(add_win,newnode->data);
	wmove(add_win,5,20);
	wgetstr(add_win,newnode->introduce);
	newnode->left=NULL;
       newnode->right=NULL;
/*�жϱȽϣ�ȷ�����ݲ���λ��*/
       if(root==NULL)
        {   
            ko_win(add_win);
            return newnode;
        }
       else
        {
            currentnode=root;
            while( currentnode !=NULL)
                {
                    parentnode =currentnode;
                    if(currentnode->id >node)
                        currentnode=currentnode->left;
                    else
                        currentnode=currentnode->right;
                }
            if(parentnode->id>node)
                parentnode->left=newnode;
            else
                parentnode->right=newnode;
        }
       ko_win(add_win);
       return root;
}	
/*�������(���������������ݿɰ�˳�������ʾ�ڽ�����)*/
void inorder (b_tree point)
{
    if(point!=NULL)
        {
        
            inorder(point->left);
            mvwprintw(show_win,flag++,1,"%-10d%-12s%-15s%-15s  %s",point->id,point->severity,point->type,point->data,point->introduce);
            wmove(show_win,24,79);
            wrefresh(show_win); 
            inorder(point->right);
		
        }
}
/*�������(�˴���ʾ��pad�ṹ�崦)
*  ͨ�����¼����ӻ����rool1��ֵ
*  �Դﵽ������ʾ�Ĺ���
*/
void inorder_rool (b_tree point)
{
    if(point!=NULL)
        {
        
            inorder_rool(point->left);
            mvwprintw(pad,rool1++,1,"%-10d%-12s%-15s%-15s  %s",point->id,point->severity,point->type,point->data,point->introduce);
           // wmove(show_win,24,79);
            inorder_rool(point->right);
		
        }
}
/*���ַ�����
*  ����bug����
*  ͨ������bug��idֵ
*  ���ظ�bug�����������λ��*/
b_tree btree_traversal_search(b_tree point,int findnode)
{
    while(point!=NULL)
        {
            if(point->id==findnode)
                return point;
            else if(point->id>findnode)
                point=point->left;
            else
                point=point->right;
        }
    return NULL;
}
/*���ַ�����
*  �û����빦��
* ���Ҳ� ���
* ������������ͬ
* ���ɵ���*/
void u_btree_traversal_search(u_b_tree point)
{
       if(point!=NULL)
        {
            u_btree_traversal_search(point->left);
	     u_btree_traversal_search(point->right);
		 if(strcmp(point->name,user_defined)==0&&strcmp(point->passwd,passwd_defined)==0)
                     {              
                         wrong_time=0;
    		           show_message("Login successful!");
    	                      
		 	    password=1;
                     }
                else
                    login_success=1;
        }
}
/*bug��ʾ
* ��ʾ���ҵ�������
   �˴�������Ż�*/
void search_show(b_tree point){
    mvwprintw(search_win1,1,1,"%-10d%-12s%-15s%-15s  %s",point->id,point->severity,point->type,point->data,point->introduce);
    wmove(search_win1,24,79);
    wrefresh(search_win1);
}

/*������ѯ �������жϲ��ҵ�bug��λ��
* ������һ��ɾ�������Ĳ���
* ����鼮
*/
b_tree binary_search(b_tree point,int node,int *position)  /*���ҽ���Ƿ�������*/
{
    b_tree parent;
    parent=point;/*����ָ���ֵ*/
    *position=0;/*����λ�ó�ֵ*/
    while(point!=NULL)
        {
            if(point->id==node)
                return parent;/*�ҵ��Ľ��*/
            else
                {
                    parent=point;
                    if(point->id>node)
                        {
                            point=point->left;
                            *position=-1;/*��������Ϊ-1*/
                        }
                    else
                        {
                            point=point->right;
                            *position=1;/*��������Ϊ1*/
                        }
                }
        }
    return NULL;
}
/*ɾ��bug
* ͨ����һ�������ҵ���λ��
* ɾ�����ڽ��
*/
b_tree delete_bug(b_tree root,int node){
    b_tree parent;
    b_tree point;
    b_tree child;
    int position;
    parent = binary_search(root, node, &position);
    if(parent==NULL)
        return root;
    else
        {
            switch(position)/*�ж�ɾ��λ��*/
                {
                    case -1 :point=parent->left;break;
                    case   1 :point=parent->right;break;
                    case   0 :point=parent;break;
                }
            /*-----û��������Ҳû������-----*/
            if(point->left==NULL&&point->right==NULL)
                {
                    switch(position)
                        {
                            case -1 :parent->left=NULL;break;
                            case   1 :parent->right=NULL;break;
                            case   0 :root=NULL;break;                           
                        }
                    return root;
                 }
          /*-----û��������-----*/
          if(point->left==NULL&&point->right!=NULL)
            {
                if(parent!=point)
                    parent->right=point->right;
                else
                    root=root->right;
                free(point);
                return root;
            }
          /*-----û��������-----*/
          else if(point->right==NULL&&point->left!=NULL)
            {
                if(parent!=point)
                    parent->left=point->left;
                else
                    root=root->left;
                free(point);
                return root;
            }
          /*��������Ҳ��������*/
          else   //if(point->right!=NULL&&point->left!=NULL)
            {
                parent=point;   /*�����ڵ�ָ��Ŀǰ���*/
                child=point->left;/*�����ӽڵ�*/
                while(child->right!=NULL)/*�ҵ������������ұߵ�Ҷ�ӵ�*/
                    {
                        parent=child;
                        child=child->right;
                    }
				/*�������������ұߵĽ���滻��Ҫɾ���Ľ��*/
                point->id=child->id;
                strcpy(point->severity,child->severity);
                strcpy(point->type,child->type);
                strcpy(point->data,child->data);
                strcpy(point->introduce,child->introduce);
                if(parent->left==child)
                    parent->left=child->left;
                else
                    parent->right=child->right;
				/*ɾ�������������ұߵĽ��*/
                free(child);
                return root;               
            }
        }
}
/*����û�*/
/*������*/
u_b_tree add_user(u_b_tree root){
       u_b_tree newnode;
       u_b_tree currentnode;
       u_b_tree parentnode;
       int node;
       newnode =(u_b_tree) malloc (sizeof(u_treenode));
       /*��ncurses��Ļ�������û�*/
	wmove(user_add_win,1,25);
       fflush(stdin);
	wscanw(user_add_win,"%d",&newnode->user_id);
	//wgetstr(add_win,newnode->id);
       node= newnode->user_id;
	wmove(user_add_win,2,25);
	wgetstr(user_add_win,newnode->name);
	wmove(user_add_win,3,25);
	wgetstr(user_add_win,newnode->passwd);
	wmove(user_add_win,4,25);
	wgetstr(user_add_win,newnode->user_data);
	newnode->left=NULL;
       newnode->right=NULL;
	/*�жϲ���λ��*/
       if(root==NULL)
        {   
            return newnode;
        }
       else
        {
            currentnode=root;
            while( currentnode !=NULL)
                {
                    parentnode =currentnode;
                    if(currentnode->user_id >node)
                        currentnode=currentnode->left;
                    else
                        currentnode=currentnode->right;
                }
            if(parentnode->user_id>node)
                parentnode->left=newnode;
            else
                parentnode->right=newnode;
        }
       return root;
}	
/*�������*/
void user_inorder (u_b_tree point)
{
    if(point!=NULL)
        {
            
            user_inorder(point->left);
            mvwprintw(user_show_win,user_flag++,1,"%-10d%-12s%-15s%-15s",point->user_id,point->name,point->passwd,point->user_data);
            wmove(user_show_win,24,79);
            wrefresh(user_show_win); 
            user_inorder(point->right);
        }
}


/*user�����е�λ�ò�ѯ*/

u_b_tree user_binary_search(u_b_tree point,int node,int *position)  /*���ҽ���Ƿ�������*/
{
    u_b_tree parent;
    parent=point;/*����ָ���ֵ*/
    *position=0;/*����λ�ó�ֵ*/
    while(point!=NULL)
        {
            if((point->user_id)==node)
                return parent;/*�ҵ��Ľ��*/
            else
                {
                    parent=point;
                    if(point->user_id>node)
                        {
                            point=point->left;
                            *position=-1;/*��������Ϊ-1*/
                        }
                    else
                        {
                            point=point->right;
                            *position=1;/*��������Ϊ1*/
                        }
                }
        }
    return NULL;
}
/*ɾ�����е��û�*/
u_b_tree delete_user(u_b_tree root,int node){
    u_b_tree parent;
    u_b_tree point;
    u_b_tree child;
    int position;
    parent = user_binary_search(root, node, &position);
    if(parent==NULL)
        return root;
    else
        {
            switch(position)/*�ж�ɾ��λ��*/
                {
                    case -1 :point=parent->left;break;
                    case   1 :point=parent->right;break;
                    case   0 :point=parent;break;
                }
            /*-----û��������Ҳû������-----*/
            if(point->left==NULL&&point->right==NULL)
                {
                    switch(position)
                        {
                            case -1 :parent->left=NULL;break;
                            case   1 :parent->right=NULL;break;
                            case   0 :root=NULL;break;                           
                        }
                    return root;
                 }
          /*-----û��������-----*/
          if(point->left==NULL&&point->right!=NULL)
            {
                if(parent!=point)
                    parent->right=point->right;
                else
                    root=root->right;
                free(point);
                return root;
            }
          /*-----û��������-----*/
          else if(point->right==NULL&&point->left!=NULL)
            {
                if(parent!=point)
                    parent->left=point->left;
                else
                    root=root->left;
                free(point);
                return root;
            }
          /*��������Ҳ��������*/
          else    //if(point->right!=NULL&&point->left!=NULL)/*��б��û��warming*/
            {
                parent=point;   /*�����ڵ�ָ��Ŀǰ���*/
                child=point->left;/*�����ӽڵ�*/
                while(child->right!=NULL)/*�ҵ������������ұߵ�Ҷ�ӵ�*/
                    {
                        parent=child;
                        child=child->right;
                    }
                point->user_id=child->user_id;
                strcpy(point->name,child->name);
                strcpy(point->passwd,child->passwd);
                strcpy(point->user_data,child->user_data);
                if(parent->left==child)
                    parent->left=child->left;
                else
                    parent->right=child->right;
                free(child);
                return root;               
            }
        }/*��ɾ���Ľ�㻻�����������ұߵ�ֵ*/
}
/*bug���ı�����*/
b_tree  show_bug_text(b_tree root){
      
        fp=fopen("bug.txt","a+");
		if(fp==0)
			exit(0);
	fseek(fp,0l,2);

	if(ftell(fp)==0){
		return root;
	}
	else
	{	
		fseek(fp,0l,0);
		b_tree newnode=NULL;
      	       b_tree currentnode=NULL;
              b_tree parentnode=NULL;
              int node;
              
	/*�ı������ݶ�������*/	
	while(!feof(fp)){
		newnode =(b_tree) malloc (sizeof(treenode));
		fscanf(fp,"%d %s %s %s %s ",&newnode->id,newnode->severity,newnode->type,newnode->data,newnode->introduce);
		node= newnode->id;
		newnode->left=NULL;
      		newnode->right=NULL;
		/*�ж϶���λ��*/
			if(root==NULL)
        		{   
           			root=newnode;
     			   }
       		else
              	{
           			 currentnode=root;
            			while( currentnode !=NULL)
                			{
                  		 		 parentnode =currentnode;
                    			if(currentnode->id >node)
                      				  currentnode=currentnode->left;
                   				 else
                        					currentnode=currentnode->right;
                			}
						//parentnode->left=NULL;
      						//parentnode->right=NULL;
          				  if(parentnode->id>node)
             					   {
             					   	parentnode->left=newnode;
          				  	   }
            				else
              			      { 
              					parentnode->right=newnode;
            					}
							
							
							//newnode->left=NULL;
      							//newnode->right=NULL;
       		 }
			//newnode->left=NULL;
      			//newnode->right=NULL;
					}		
	}	
       fclose(fp);
	return root;
}

/*�����ӡ���ı���*/
void save_bug_inorder(b_tree point) 
{
	if(point!=NULL)
        {
            
            save_bug_inorder(point->left);
	     fprintf(fp1,"%d %s %s %s %s ",point->id,point->severity,point->type,point->data,point->introduce);
            save_bug_inorder(point->right);
	}

}

/*ɾ�����bug����ӡ���ı���*/
void del_bug_inorder(b_tree point) //���浽bug.txt
{
	if(point!=NULL)
        {
            
            del_bug_inorder(point->left);
	     fprintf(fp2,"%d %s %s %s %s ",point->id,point->severity,point->type,point->data,point->introduce);
            del_bug_inorder(point->right);
	}

}
/*�˻��������*/
void change(char *a)
	{if((*a>='A'&&*a<'W')||(*a>='a'&&*a<'w'))
		*a=*a+4;
	else if(*a=='W')
		*a='A';
	else if(*a=='w')
		*a='a';
	else if(*a=='X')
		*a='B';
	else if(*a=='x')
		*a='b';
	else if(*a=='Y')
		*a='C';
	else if(*a=='y')
		*a='c';
	else if(*a=='Z')
		*a='D';
	else if(*a=='z')
		*a='d';
}
/*�˻��������*/
void b_change(char *a)
	{if((*a>='E'&&*a<'Z')||(*a>='e'&&*a<'z'))
		*a=*a-4;
	else if(*a=='A')
		*a='W';
	else if(*a=='a')
		*a='w';
	else if(*a=='B')
		*a='X';
	else if(*a=='b')
		*a='x';
	else if(*a=='C')
		*a='Y';
	else if(*a=='c')
		*a='y';
	else if(*a=='D')
		*a='Z';
	else if(*a=='d')
		*a='z';
}

/*user ���ı�����*/


u_b_tree  show_user_text(u_b_tree root){
      
        fp3=fopen("user.txt","a+");
		if(fp3==0)
			exit(0);
	fseek(fp3,0l,2);

	if(ftell(fp3)==0){
		return root;
	}
	else
	{	
		fseek(fp3,0l,0);
		u_b_tree newnode=NULL;
      	       u_b_tree currentnode=NULL;
              u_b_tree parentnode=NULL;
              int node;
              
		char name_user[15]={0};
		char passwd_user[15]={0};
		int i,j;
		
	while(!feof(fp3)){
		newnode =(u_b_tree) malloc (sizeof(u_treenode));
		fscanf(fp3,"%d %s %s %s ",&newnode->user_id,name_user,passwd_user,newnode->user_data);
		for(i=0;i<15;i++)
	{   b_change(&name_user[i]);
		
	if(name_user[i]=='\0')
		break;
				}
			for(j=0;j<15;j++)
	{   b_change(&passwd_user[j]);
		
	if(passwd_user[j]=='\0')
		break;
				}
			strcpy(newnode->name,name_user);
			strcpy(newnode->passwd,passwd_user);
			
		node= newnode->user_id;
		newnode->left=NULL;
      		newnode->right=NULL;
		
			if(root==NULL)
        		{   
           			root=newnode;
     			   }
       		else
              	{
           			 currentnode=root;
            			while( currentnode !=NULL)
                			{
                  		 		 parentnode =currentnode;
                    			if(currentnode->user_id >node)
                      				  currentnode=currentnode->left;
                   				 else
                        					currentnode=currentnode->right;
                			}
						//parentnode->left=NULL;
      						//parentnode->right=NULL;
          				  if(parentnode->user_id>node)
             					   {
             					   	parentnode->left=newnode;
          				  	   }
            				else
              			      { 
              					parentnode->right=newnode;
            					}
							
							
							//newnode->left=NULL;
      							//newnode->right=NULL;
       		 }
			//newnode->left=NULL;
      			//newnode->right=NULL;
					}		
	}	
       fclose(fp3);
	return root;
}
/*�û����浽�ı�*/
void save_user_inorder(u_b_tree point)
{
	if(point!=NULL)
        {
            
            save_user_inorder(point->left);
			char name_user[15]={0};
			char passwd_user[15]={0};
			int i,j;
			strcpy(name_user,point->name);
			strcpy(passwd_user,point->passwd);
			
			for(i=0;i<15;i++)
	{   change(&name_user[i]);
		
	if(name_user[i]=='\0')
		break;
				}
			for(j=0;j<15;j++)
	{   change(&passwd_user[j]);
		
	if(passwd_user[j]=='\0')
		break;
				}
	     fprintf(fp4,"%d %s %s %s ",point->user_id,name_user,passwd_user,point->user_data);
            save_user_inorder(point->right);
	}

}

/*ɾ���û����������浽�ı�*/
void del_user_inorder(u_b_tree point) 
{
	if(point!=NULL)
        {
            
            del_user_inorder(point->left);
			char name_user[15]={0};
			char passwd_user[15]={0};
			int i,j;
			strcpy(name_user,point->name);
			strcpy(passwd_user,point->passwd);
			
			for(i=0;i<15;i++)
	{   change(&name_user[i]);
		
	if(name_user[i]=='\0')
		break;
				}
			for(j=0;j<15;j++)
	{   change(&passwd_user[j]);
		
	if(passwd_user[j]=='\0')
		break;
				}
	     fprintf(fp5,"%d %s %s %s ",point->user_id,name_user,passwd_user,point->user_data);
            del_user_inorder(point->right);
	}

}
