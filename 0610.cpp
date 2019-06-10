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
			cout << x << "�ڵ�" << mid + 1 << "��λ��" << endl;
			return;
		}
		else if (a[mid]>x)
			r = mid - 1;
		else l = mid + 1;
	}
	cout << "δ���ҵ�" << x << endl;
}
struct node
{
	int key;
	node *l, *r;
};
node* InsertBST(node *T, int key)///��������������ڵ�
{
	node *f = T, *p = T;
	while (p)
	{
		if (p->key == key) return T;
		f = p;//��f���²���·���ϵ����һ�����ʵĽڵ�
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
node *CreateBST(int n) ///��������������
{
	node *bt = NULL;            //��ʼʱbtΪ����
	for (int i = 0; i<n; i++)
		bt = InsertBST(bt, a[i]);     //���ؼ���A[i]�������������T��
	return bt;                  //���ؽ����Ķ����������ĸ�ָ��
}

void DelBST(node *T, int key)///����������ɾ���ڵ�
{
	node *p = T, *f = NULL, *q, *s;
	while (p)
	{
		if (p->key == key) break; //�ҵ��ؼ���Ϊkey�Ľ��
		f = p;//���¹ؼ���key�ڵ�ĸ��ڵ�
		p = (key<p->key) ? p->l : p->r;//�ֱ���*p�����������в���
	}
	if (!p) return;//�������������޹ؼ���Ϊkey�Ľ��
	if (p->l == NULL&&p->r == NULL) //pû����������
	{
		if (p == T) T = NULL;//ɾ�����Ǹ��ڵ�
		else if (p == f->l)
			f->l = NULL;
		else
			f->r = NULL;
		free(p);
	}
	else if (p->l == NULL&&p->r != NULL)//p����������������
	{
		if (f->l == p)
			f->l = p->r; //��p�����������ӵ��丸����������
		else
			f->r = p->r; //��p�����������ӵ��丸����������
		free(p);
	}
	else if (p->r == NULL&&p->l != NULL)//p����������������
	{
		if (f->l == p)
			f->l = p->l; //��p�����������ӵ��丸����������
		else
			f->r = p->l; //��p�����������ӵ��丸����������
		free(p);
	}
	else if (p->l != NULL&&p->r != NULL)//p��������������������
	{
		q = p;
		s = p->l;//ת��
		while (s->r) //Ȼ�����ҵ���ͷ
		{
			q = s;
			s = s->r;//sָ��ɾ�ڵ�ġ�ǰ����(����ǰ��)
		}
		p->key = s->key;//��p������ǰ�����s����p������s�����ݸ��Ƶ�p�У�
		if (q != p) q->r = s->l;//�ؽ�q��������
		else q->l = s->l;//�ؽ�q����������
		free(s);
	}
}

void midorder(node * T)///�ݹ�ʵ���������
{
	if (T != NULL)
	{
		midorder(T->l);
		printf("%d ", T->key);
		midorder(T->r);
	}
}

void menu()  // ��ӡ���˵����溯���Ķ���
{
	cout << "\t" << "\t" "1.���������ʹ����֪�ؼ��ֲ���" << endl << endl << "\t";
	cout << "\t2.����������������ɾ��ָ�����" << endl << endl << "\t";
	cout << "\t3.0�˳�ϵͳ" << endl << endl << "\t";
}

int main()
{
	menu();
	while (1)
	{
		int i = 0;
		cout << "�밴����������������Ӧ�����֣� ";
		cin >> i;
		if (i == 0)
			break;
		else{
			switch (i){
			case 1:
			int n;
			cout << "������n" << endl;
			cin >> n;
			cout << "������" << n << "���������" << endl;
			for (int i = 0; i < n; i++)
				cin >> a[i];
			int x;
			cout << "������Ҫ���ҵ���" << endl;
			cin >> x;
			erfen(n, x);
			break;

			case 2:

			cout << "������n" << endl;
			cin >> n;
			cout << "������" << n << "����" << endl;
			for (int i = 0; i < n; i++)
				cin >> a[i];
			node *bt;
			bt = CreateBST(n);
			cout << "�����������Ϊ��" << endl;
			midorder(bt);
			puts("");
			int num;
			cout << "������Ҫɾ���Ľڵ�" << endl;
			cin >> num;
			DelBST(bt, num);
			cout << "ɾ���ڵ�֮�������������Ϊ��" << endl;
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
