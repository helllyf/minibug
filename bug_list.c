/**
 * bug_list.c
 * 描述:数据存储文件，首次使用二叉树，程序需要优化
 * 需要优化点:
 * 1:用户树与bug、树应该分开存放
 * 2:存储文本操作应该和树操作分开存放
 * 3:user和bug代码重复 ，需考虑简洁代码
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

/*插入二叉树结点*/
b_tree add_bug(b_tree root){
       b_tree newnode;
       b_tree currentnode;
       b_tree parentnode;
       int node;
       newnode =(b_tree) malloc (sizeof(treenode));
/*此处为在ncurses上输入存储内容*/       
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
/*判断比较，确定数据插入位置*/
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
/*中序遍历(中序遍历输出，数据可按顺序输出显示在界面上)*/
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
/*中序遍历(此处显示在pad结构体处)
*  通过上下键增加或减少rool1的值
*  以达到滚动显示的功能
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
/*二分法查找
*  查找bug功能
*  通过查找bug的id值
*  返回该bug结点所在树内位置*/
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
/*二分法查找
*  用户登入功能
* 查找并 配对
* 与树内数据相同
* 即可登入*/
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
/*bug显示
* 显示查找到的内容
   此处程序可优化*/
void search_show(b_tree point){
    mvwprintw(search_win1,1,1,"%-10d%-12s%-15s%-15s  %s",point->id,point->severity,point->type,point->data,point->introduce);
    wmove(search_win1,24,79);
    wrefresh(search_win1);
}

/*遍历查询 ，用于判断查找的bug的位置
* 用于下一个删除函数的操作
* 借鉴书籍
*/
b_tree binary_search(b_tree point,int node,int *position)  /*查找结点是否在树中*/
{
    b_tree parent;
    parent=point;/*设置指针初值*/
    *position=0;/*设置位置初值*/
    while(point!=NULL)
        {
            if(point->id==node)
                return parent;/*找到改结点*/
            else
                {
                    parent=point;
                    if(point->id>node)
                        {
                            point=point->left;
                            *position=-1;/*设左子树为-1*/
                        }
                    else
                        {
                            point=point->right;
                            *position=1;/*设右子树为1*/
                        }
                }
        }
    return NULL;
}
/*删除bug
* 通过上一个函数找到的位置
* 删除树内结点
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
            switch(position)/*判断删除位置*/
                {
                    case -1 :point=parent->left;break;
                    case   1 :point=parent->right;break;
                    case   0 :point=parent;break;
                }
            /*-----没有左子树也没有右子-----*/
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
          /*-----没有左子树-----*/
          if(point->left==NULL&&point->right!=NULL)
            {
                if(parent!=point)
                    parent->right=point->right;
                else
                    root=root->right;
                free(point);
                return root;
            }
          /*-----没有右子树-----*/
          else if(point->right==NULL&&point->left!=NULL)
            {
                if(parent!=point)
                    parent->left=point->left;
                else
                    root=root->left;
                free(point);
                return root;
            }
          /*有左子树也有右子树*/
          else   //if(point->right!=NULL&&point->left!=NULL)
            {
                parent=point;   /*将父节点指向目前结点*/
                child=point->left;/*设置子节点*/
                while(child->right!=NULL)/*找到左子树中最右边的叶子点*/
                    {
                        parent=child;
                        child=child->right;
                    }
				/*将其左子树最右边的结点替换到要删除的结点*/
                point->id=child->id;
                strcpy(point->severity,child->severity);
                strcpy(point->type,child->type);
                strcpy(point->data,child->data);
                strcpy(point->introduce,child->introduce);
                if(parent->left==child)
                    parent->left=child->left;
                else
                    parent->right=child->right;
				/*删除其左子树最右边的结点*/
                free(child);
                return root;               
            }
        }
}
/*添加用户*/
/*插入结点*/
u_b_tree add_user(u_b_tree root){
       u_b_tree newnode;
       u_b_tree currentnode;
       u_b_tree parentnode;
       int node;
       newnode =(u_b_tree) malloc (sizeof(u_treenode));
       /*在ncurses屏幕上输入用户*/
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
	/*判断插入位置*/
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
/*中序遍历*/
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


/*user在树中的位置查询*/

u_b_tree user_binary_search(u_b_tree point,int node,int *position)  /*查找结点是否在树中*/
{
    u_b_tree parent;
    parent=point;/*设置指针初值*/
    *position=0;/*设置位置初值*/
    while(point!=NULL)
        {
            if((point->user_id)==node)
                return parent;/*找到改结点*/
            else
                {
                    parent=point;
                    if(point->user_id>node)
                        {
                            point=point->left;
                            *position=-1;/*设左子树为-1*/
                        }
                    else
                        {
                            point=point->right;
                            *position=1;/*设右子树为1*/
                        }
                }
        }
    return NULL;
}
/*删除树中的用户*/
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
            switch(position)/*判断删除位置*/
                {
                    case -1 :point=parent->left;break;
                    case   1 :point=parent->right;break;
                    case   0 :point=parent;break;
                }
            /*-----没有左子树也没有右子-----*/
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
          /*-----没有左子树-----*/
          if(point->left==NULL&&point->right!=NULL)
            {
                if(parent!=point)
                    parent->right=point->right;
                else
                    root=root->right;
                free(point);
                return root;
            }
          /*-----没有右子树-----*/
          else if(point->right==NULL&&point->left!=NULL)
            {
                if(parent!=point)
                    parent->left=point->left;
                else
                    root=root->left;
                free(point);
                return root;
            }
          /*有左子树也有右子树*/
          else    //if(point->right!=NULL&&point->left!=NULL)/*加斜杆没有warming*/
            {
                parent=point;   /*将父节点指向目前结点*/
                child=point->left;/*设置子节点*/
                while(child->right!=NULL)/*找到左子树中最右边的叶子点*/
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
        }/*将删除的结点换成左子树最右边的值*/
}
/*bug的文本操作*/
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
              
	/*文本内数据读到树内*/	
	while(!feof(fp)){
		newnode =(b_tree) malloc (sizeof(treenode));
		fscanf(fp,"%d %s %s %s %s ",&newnode->id,newnode->severity,newnode->type,newnode->data,newnode->introduce);
		node= newnode->id;
		newnode->left=NULL;
      		newnode->right=NULL;
		/*判断读入位置*/
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

/*中序打印到文本内*/
void save_bug_inorder(b_tree point) 
{
	if(point!=NULL)
        {
            
            save_bug_inorder(point->left);
	     fprintf(fp1,"%d %s %s %s %s ",point->id,point->severity,point->type,point->data,point->introduce);
            save_bug_inorder(point->right);
	}

}

/*删除后的bug树打印到文本内*/
void del_bug_inorder(b_tree point) //保存到bug.txt
{
	if(point!=NULL)
        {
            
            del_bug_inorder(point->left);
	     fprintf(fp2,"%d %s %s %s %s ",point->id,point->severity,point->type,point->data,point->introduce);
            del_bug_inorder(point->right);
	}

}
/*账户密码加密*/
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
/*账户密码解密*/
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

/*user 的文本操作*/


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
/*用户保存到文本*/
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

/*删除用户操作并保存到文本*/
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
