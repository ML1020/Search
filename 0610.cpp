#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
int a[100];
void erfen(int n, int x)
{
	int l = 0, r = n - 1, mid;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (a[mid] == x)
		{
			cout << x << "在第" << mid + 1 << "个位置" << endl;
			return;
		}
		else if (a[mid]>x)
			r = mid - 1;
		else l = mid + 1;
	}
	cout << "未能找到" << x << endl;
}
struct node
{
	int key;
	node *l, *r;
};
node* InsertBST(node *T, int key)///二叉排序树插入节点
{
	node *f = T, *p = T;
	while (p)
	{
		if (p->key == key) return T;
		f = p;//用f记下查找路径上的最后一个访问的节点
		p = (key<p->key) ? p->l : p->r;
	}
	p = (node*)malloc(sizeof(node));
	p->key = key;
	p->l = p->r = NULL;
	if (T == NULL)
		T = p;
	else if (key<f->key)
		f->l = p;
	else
		f->r = p;
	return T;
}
node *CreateBST(int n) ///建立二叉排序树
{
	node *bt = NULL;            //初始时bt为空树
	for (int i = 0; i<n; i++)
		bt = InsertBST(bt, a[i]);     //将关键字A[i]插入二叉排序树T中
	return bt;                  //返回建立的二叉排序树的根指针
}

void DelBST(node *T, int key)///二叉排序树删除节点
{
	node *p = T, *f = NULL, *q, *s;
	while (p)
	{
		if (p->key == key) break; //找到关键字为key的结点
		f = p;//记下关键字key节点的父节点
		p = (key<p->key) ? p->l : p->r;//分别在*p的左、右子树中查找
	}
	if (!p) return;//二叉排序树中无关键字为key的结点
	if (p->l == NULL&&p->r == NULL) //p没有左右子树
	{
		if (p == T) T = NULL;//删除的是根节点
		else if (p == f->l)
			f->l = NULL;
		else
			f->r = NULL;
		free(p);
	}
	else if (p->l == NULL&&p->r != NULL)//p无左子树有右子树
	{
		if (f->l == p)
			f->l = p->r; //将p的右子树链接到其父结点的左链上
		else
			f->r = p->r; //将p的右子树链接到其父结点的右链上
		free(p);
	}
	else if (p->r == NULL&&p->l != NULL)//p有左子树无右子树
	{
		if (f->l == p)
			f->l = p->l; //将p的左子树链接到其父结点的左链上
		else
			f->r = p->l; //将p的左子树链接到其父结点的右链上
		free(p);
	}
	else if (p->l != NULL&&p->r != NULL)//p既有左子树又有右子树
	{
		q = p;
		s = p->l;//转左
		while (s->r) //然后向右到尽头
		{
			q = s;
			s = s->r;//s指向被删节点的“前驱”(中序前驱)
		}
		p->key = s->key;//以p的中序前趋结点s代替p（即把s的数据复制到p中）
		if (q != p) q->r = s->l;//重接q的右子树
		else q->l = s->l;//重接q的左子树。
		free(s);
	}
}

void midorder(node * T)///递归实现中序遍历
{
	if (T != NULL)
	{
		midorder(T->l);
		printf("%d ", T->key);
		midorder(T->r);
	}
}

void menu()  // 打印主菜单界面函数的定义
{
	cout << "\t" << "\t" "1.建立有序表并使用已知关键字查找" << endl << endl << "\t";
	cout << "\t2.建立二叉排序树，删除指定结点" << endl << endl << "\t";
	cout << "\t3.0退出系统" << endl << endl << "\t";
}

int main()
{
	menu();
	while (1)
	{
		int i = 0;
		cout << "请按照您的需求输入相应的数字： ";
		cin >> i;
		if (i == 0)
			break;
		else{
			switch (i){
			case 1:
			int n;
			cout << "请输入n" << endl;
			cin >> n;
			cout << "请输入" << n << "个有序的数" << endl;
			for (int i = 0; i < n; i++)
				cin >> a[i];
			int x;
			cout << "请输入要查找的数" << endl;
			cin >> x;
			erfen(n, x);
			break;

			case 2:

			cout << "请输入n" << endl;
			cin >> n;
			cout << "请输入" << n << "个数" << endl;
			for (int i = 0; i < n; i++)
				cin >> a[i];
			node *bt;
			bt = CreateBST(n);
			cout << "中序遍历序列为：" << endl;
			midorder(bt);
			puts("");
			int num;
			cout << "请输入要删除的节点" << endl;
			cin >> num;
			DelBST(bt, num);
			cout << "删除节点之后中序遍历序列为：" << endl;
			midorder(bt);
			puts("");
			break;

			default:
				break;
			}
		}
	}
	system("pause");
	return 0;
}
