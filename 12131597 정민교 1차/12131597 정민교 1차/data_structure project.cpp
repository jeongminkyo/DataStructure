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


void tree::createsibiling(node* root,node* p)	//형제노드 생성, 노드의 오른쪽에 단다
{
	if(root->right==NULL)
	{
			root->right = p;
			p->parent = root;
			
	}
	else
		this->createsibiling(root->right,p);
}

void tree::createchild(node* root,node *p)		//자식 노드 생성 분반이 같은 경우 그 분반의 왼쪽에 매단다
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


void tree::printlistclass(node* root,int num)	//분반의 모든 노드들을 출력
{
		if(root == NULL)
		{
			cout<<"없음"<<endl;
			return;
		}
	
		if(root->classnum == num)
		{
			cout<<root->name<<root->classnum<<root->rank<<root->ID<<endl; //분반이 같으면 먼저 교수 출력
			cout<<root->left->name<<root->left->classnum<<root->left->rank<<root->left->ID<<endl;//분반이 같으면 교수 출력 후 수강생 1번 출력
			node *p1 = root->left;
			while(p1->right != NULL)
			{
			cout<<p1->right->name<<p1->right->classnum<<p1->right->rank<<p1->right->ID<<endl;//2,3,....번째 수강생 출력
			p1 = p1->right;
			}
		}
		else if(root->classnum != num)
			printlistclass(root->right,num);
		
	
}

void tree::printallnode(node* root)	//모든 노드를 출력
{
		if(root == NULL)
		{
			return;
		}
			cout<<root->name<<root->classnum<<root->rank<<root->ID<<endl;		//강의교수 출력
			cout<<root->left->name<<root->left->classnum<<root->left->rank<<root->left->ID<<endl; //1번째 수강생부터 출력 
			node *p1 = root->left;
			while(p1->right != NULL)
			{
			cout<<p1->right->name<<p1->right->classnum<<p1->right->rank<<p1->right->ID<<endl;//2,3,....번째 수강생 출력
			p1 = p1->right;
			}
			printallnode(root->right);
}

node* tree::searchnode(node* root,string name)		//노드들을 찾음. delete하기 위해서 모든 조건을 확인함
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
void tree::deletenode(node* root)		//찾은 노드들을 조건에 맞추어서 삭제시킴
{
	if(root == NULL)
		cout<<"삭제 할 수 없음"<<endl;
	else if(root->left != NULL)
		cout<<"삭제 할 수 없음"<<endl;
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
	fin.open("input.txt");		//input.txt 입력
	fin>>root.name>>root.classnum>>root.rank>>root.ID;

	node *p = new node;			//생성자 노드를 이용해서 책임교수 생성
	fin>>p->name>>p->classnum>>p->rank>>p->ID;
	root.left = p;				//첫번째 강의교수를 입력 
	p->parent = &root;
	
	while(!fin.eof())
	{
		node *p = new node; 
		fin>>p->name>>p->classnum>>p->rank>>p->ID;			//inputtxt 파일을 입력받아서 한줄씩 읽음 rank가 강의교수이면 오른쪽에
															// rank가 수강생이면 왼쪽에 단다.
		if(p->rank=="강의교수")
		{
			tree.createsibiling(root.left,p);
		}
		else if(p->rank=="수강생")
		{	
			tree.createchild(root.left,p);
		}
	}
	fin.close();	//input.txt 닫음

	ifstream finn;
	finn.open("command.txt");
	
	while(!finn.eof())
	{
		stop:
		finn>>a;
		if(a=="s" || a=="d")
		finn>>b;
		else	
		finn>>b>>c>>d>>e;				//입력이 i,d,s인 경우 달리 받는다.
	
		if(a=="s")		//s인 경우 분반에 맞는 수강생이랑 강의교수 출력
		{
			classnum1 = atoi(b.c_str());
			if(classnum1==0)
				{
					cout<<root.name<<root.classnum<<root.rank<<root.ID<<endl;
					tree.printallnode(root.left);
				}
			else //0분반이 아니면 printlistclass 출력 루트 노드의 왼쪽부터 시작
			tree.printlistclass(root.left,classnum1);	
		}
		
		else if(a=="i")			//강의생을 각 분반에 맞게 입력함. 입력값이 30개가 넘어가면 예외처리
		{
			node *p1 = root.left;
			node *p2 = p1->left;
			change_classnum = atoi(c.c_str());
			change_ID = atoi(e.c_str());
			if(d=="강의교수")					//직위가 강의교수일경우
			{
				while(p1->right != NULL)
				{
					if(change_classnum != p1->right->classnum)
						{
							p1 = p1->right;
						}
					else if(change_classnum == p1->right->classnum)
							{
								cout<<"추가할 수 없음"<<endl;
								break;
							}
				}
				if(p1->right == NULL)
				{
					node *p = new node;				//새로운 노드 할당
					p->name = b;
					p->classnum = change_classnum;
					p->rank = d;
					p->ID = change_ID;	//노드에 값을 입력
					p1->right = p; 
				}	
			}

			if(d=="수강생")			//수강생인 경우 
			{
				if(count>30)		//수강생이 30명이 넘을 경우 예외처리
				{
					cout<<"추가할 수 없음"<<endl;
					goto stop;
				}
						
						while(1)
						{
							p1 = p1->right;				
							if(change_classnum == p1->classnum)		
								break;
							if(p1->right==NULL)
							{
								cout<<"추가할 수 없음"<<endl;
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
								
							}									//분반이 같을때까지 계속해서 찾음 찾으면 새로운 노드에 할당
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
			tree.deletenode(tree.searchnode(root.left,b));			//강의교수나 수강생을 삭제 
		}
	
	}
	finn.close();

	
}