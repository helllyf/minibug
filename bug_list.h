#ifndef _BUG_LIST_H
#define _BUG_LIST_H

#include "mini_bug.h"
#include "win_ui.h"
b_tree add_bug(b_tree root);/*���bug*/
void inorder (b_tree point);/*����*/
b_tree btree_traversal_search(b_tree point,int findnode);/*����*/
void search_show(b_tree point);/*��ʾ��������*/
b_tree delete_bug(b_tree root,int node);/*ɾ��bug����*/
u_b_tree add_user(u_b_tree root);/*���user*/
void user_inorder (u_b_tree point);/*��ʾ����user*/
u_b_tree delete_user(u_b_tree root,int node);/*ɾ��user*/
/*�ı��ڵ�bug�浽����*/
b_tree  show_bug_text(b_tree root);
/*����ı��浽�ı���*/
void save_bug_inorder(b_tree point); 
/*ɾ����ı����ı�*/
void del_bug_inorder(b_tree point);
/*�ı��ڵ�user�浽����*/
u_b_tree  show_user_text(u_b_tree root);
/*����ı��浽�ı���*/
void save_user_inorder(u_b_tree point); 
/*ɾ����ı����ı�*/
void del_user_inorder(u_b_tree point);
/*�û�������*/
void u_btree_traversal_search(u_b_tree point);
/*������ʾ*/
void inorder_rool (b_tree point);
#endif