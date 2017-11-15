#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class node
	{
	public:
		string name;
		int classnum;
		string rank;
		int ID;
		node* left;
		node* right;
		node* parent;
		int size;
		node();
		
};

node::node()
{
	this->parent =NULL;
	this->left = NULL;
	this->right = NULL;
	size = 0;
}
class tree
{
public:
	void createsibiling(node *p1,node* p2);
	void createchild(node *p1,node *p2);
	void printlistclass(node *p1,int);
	void printallnode(node *p1);
	void deletenode(node *p1);
	node* searchnode(node *p1,string);
};


void tree::createsibiling(node* root,node* p)	//������� ����, ����� �����ʿ� �ܴ�
{
	if(root->right==NULL)
	{
			root->right = p;
			p->parent = root;
			
	}
	else
		this->createsibiling(root->right,p);
}

void tree::createchild(node* root,node *p)		//�ڽ� ��� ���� �й��� ���� ��� �� �й��� ���ʿ� �Ŵܴ�
{

	if(p->classnum == root->classnum)
	{
		if(root->left==NULL)
		{
			root->left = p;	
			p->parent = root;
		}
		else
		{
			root->left->right = p;
		}
	}
	else
		createchild(root->right, p);
	

}


void tree::printlistclass(node* root,int num)	//�й��� ��� ������ ���
{
		if(root == NULL)
		{
			cout<<"����"<<endl;
			return;
		}
	
		if(root->classnum == num)
		{
			cout<<root->name<<root->classnum<<root->rank<<root->ID<<endl; //�й��� ������ ���� ���� ���
			cout<<root->left->name<<root->left->classnum<<root->left->rank<<root->left->ID<<endl;//�й��� ������ ���� ��� �� ������ 1�� ���
			node *p1 = root->left;
			while(p1->right != NULL)
			{
			cout<<p1->right->name<<p1->right->classnum<<p1->right->rank<<p1->right->ID<<endl;//2,3,....��° ������ ���
			p1 = p1->right;
			}
		}
		else if(root->classnum != num)
			printlistclass(root->right,num);
		
	
}

void tree::printallnode(node* root)	//��� ��带 ���
{
		if(root == NULL)
		{
			return;
		}
			cout<<root->name<<root->classnum<<root->rank<<root->ID<<endl;		//���Ǳ��� ���
			cout<<root->left->name<<root->left->classnum<<root->left->rank<<root->left->ID<<endl; //1��° ���������� ��� 
			node *p1 = root->left;
			while(p1->right != NULL)
			{
			cout<<p1->right->name<<p1->right->classnum<<p1->right->rank<<p1->right->ID<<endl;//2,3,....��° ������ ���
			p1 = p1->right;
			}
			printallnode(root->right);
}

node* tree::searchnode(node* root,string name)		//������ ã��. delete�ϱ� ���ؼ� ��� ������ Ȯ����
{
	node *temp = NULL;
	if(root->left != NULL)
		temp = searchnode(root->left,name);
	if(temp !=NULL)
		return temp;
	if(root->name == name)
		return root;
	if(root->right!= NULL)
		temp = searchnode(root->right,name);
	return temp;
}
void tree::deletenode(node* root)		//ã�� ������ ���ǿ� ���߾ ������Ŵ
{
	if(root == NULL)
		cout<<"���� �� �� ����"<<endl;
	else if(root->left != NULL)
		cout<<"���� �� �� ����"<<endl;
	else
		{
			node *u = root->parent;
			node *w = root->right;
			if(u->left == root)
			{
				u->left = w;
				if(w != NULL)
				w->parent = u;
				delete root;
			}
			else
			{
				u->right = w;
				if(w != NULL)
				w->parent = u;
				delete root;
			}
			
		
		}
}

int main()
{	
	tree tree;
	node root;
	ifstream fin;
	string a,b,c,d,e;
	int classnum1;
	int change_ID;
	int change_classnum;
	int count =1;
	int size = 0;
	fin.open("input.txt");		//input.txt �Է�
	fin>>root.name>>root.classnum>>root.rank>>root.ID;

	node *p = new node;			//������ ��带 �̿��ؼ� å�ӱ��� ����
	fin>>p->name>>p->classnum>>p->rank>>p->ID;
	root.left = p;				//ù��° ���Ǳ����� �Է� 
	p->parent = &root;
	
	while(!fin.eof())
	{
		node *p = new node; 
		fin>>p->name>>p->classnum>>p->rank>>p->ID;			//inputtxt ������ �Է¹޾Ƽ� ���پ� ���� rank�� ���Ǳ����̸� �����ʿ�
															// rank�� �������̸� ���ʿ� �ܴ�.
		if(p->rank=="���Ǳ���")
		{
			tree.createsibiling(root.left,p);
		}
		else if(p->rank=="������")
		{	
			tree.createchild(root.left,p);
		}
	}
	fin.close();	//input.txt ����

	ifstream finn;
	finn.open("command.txt");
	
	while(!finn.eof())
	{
		stop:
		finn>>a;
		if(a=="s" || a=="d")
		finn>>b;
		else	
		finn>>b>>c>>d>>e;				//�Է��� i,d,s�� ��� �޸� �޴´�.
	
		if(a=="s")		//s�� ��� �йݿ� �´� �������̶� ���Ǳ��� ���
		{
			classnum1 = atoi(b.c_str());
			if(classnum1==0)
				{
					cout<<root.name<<root.classnum<<root.rank<<root.ID<<endl;
					tree.printallnode(root.left);
				}
			else //0�й��� �ƴϸ� printlistclass ��� ��Ʈ ����� ���ʺ��� ����
			tree.printlistclass(root.left,classnum1);	
		}
		
		else if(a=="i")			//���ǻ��� �� �йݿ� �°� �Է���. �Է°��� 30���� �Ѿ�� ����ó��
		{
			node *p1 = root.left;
			node *p2 = p1->left;
			change_classnum = atoi(c.c_str());
			change_ID = atoi(e.c_str());
			if(d=="���Ǳ���")					//������ ���Ǳ����ϰ��
			{
				while(p1->right != NULL)
				{
					if(change_classnum != p1->right->classnum)
						{
							p1 = p1->right;
						}
					else if(change_classnum == p1->right->classnum)
							{
								cout<<"�߰��� �� ����"<<endl;
								break;
							}
				}
				if(p1->right == NULL)
				{
					node *p = new node;				//���ο� ��� �Ҵ�
					p->name = b;
					p->classnum = change_classnum;
					p->rank = d;
					p->ID = change_ID;	//��忡 ���� �Է�
					p1->right = p; 
				}	
			}

			if(d=="������")			//�������� ��� 
			{
				if(count>30)		//�������� 30���� ���� ��� ����ó��
				{
					cout<<"�߰��� �� ����"<<endl;
					goto stop;
				}
						
						while(1)
						{
							p1 = p1->right;				
							if(change_classnum == p1->classnum)		
								break;
							if(p1->right==NULL)
							{
								cout<<"�߰��� �� ����"<<endl;
								break;
							}
						}
						if(change_classnum == p1->classnum)
						{
							node* p0 = p1;
							while(1)
							{
								if(p0->left ==NULL)
									break;
								if(p0->left->right == NULL)
									break;
								else
								p0->left = p0->left->right;
								
							}									//�й��� ���������� ����ؼ� ã�� ã���� ���ο� ��忡 �Ҵ�
							node *p = new node;
							p->name = b;
							p->classnum = change_classnum;
							p->rank = d;
							p->ID = change_ID;
							count++;
							tree.createchild(p1,p);
						}
				}
		}
		
		else if(a=="d")
		{
			tree.deletenode(tree.searchnode(root.left,b));			//���Ǳ����� �������� ���� 
		}
	
	}
	finn.close();

	
}