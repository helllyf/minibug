#ifndef _BUG_LIST_H
#define _BUG_LIST_H

#include "mini_bug.h"
#include "win_ui.h"
b_tree add_bug(b_tree root);/*添加bug*/
void inorder (b_tree point);/*中序*/
b_tree btree_traversal_search(b_tree point,int findnode);/*查找*/
void search_show(b_tree point);/*显示查找内容*/
b_tree delete_bug(b_tree root,int node);/*删除bug函数*/
u_b_tree add_user(u_b_tree root);/*添加user*/
void user_inorder (u_b_tree point);/*显示所有user*/
u_b_tree delete_user(u_b_tree root,int node);/*删除user*/
/*文本内的bug存到树里*/
b_tree  show_bug_text(b_tree root);
/*树里的保存到文本内*/
void save_bug_inorder(b_tree point); 
/*删除后的保存文本*/
void del_bug_inorder(b_tree point);
/*文本内的user存到树里*/
u_b_tree  show_user_text(u_b_tree root);
/*树里的保存到文本内*/
void save_user_inorder(u_b_tree point); 
/*删除后的保存文本*/
void del_user_inorder(u_b_tree point);
/*用户树遍历*/
void u_btree_traversal_search(u_b_tree point);
/*滚动显示*/
void inorder_rool (b_tree point);
#endif