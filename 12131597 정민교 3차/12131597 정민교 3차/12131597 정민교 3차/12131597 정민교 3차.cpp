#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;

class node
{
public:
	int s_num;
	string name;
	string major;
	int grade;
	int height;
	node *left;
	node *right;
	node *parent;
	node();
};

node::node()
{
	s_num = 0;
	name = "";
	major = "";
	grade = 0;
	height = 1;
	left = NULL;
	right = NULL;
	parent = NULL;
}

class AVLTree
{
public:
	string Search(int);
	void Insert(int, string, string, int);
	node* compare(int, node *);
	node* restructure(node*);
	AVLTree();
	node *root;
	string Cinsert(int, string, string, int);
};

node* AVLTree::restructure(node* p1)
{
	node *z = p1->parent;
	node *y = p1;
	node *x = NULL;
	//x 지정
	if (p1->left == NULL)	//double rotation
	{
		x = p1->right;
	}
	else if (p1->right == NULL)	//single rotation
	{
		x = p1->left;
	}
	else if (p1->left->height > p1->right->height)
	{
		x = p1->left;
	}
	else if (p1->left->height < p1->right->height)
	{
		x = p1->right;
	}
	else if (p1->left->height == p1->right->height)	//single rotation
	{
		if (p1->parent->right == p1)	//single rotation
		{
			x = p1->right;
		}
		else if (p1->parent->left == p1)	//single rotation
		{
			x = p1->left;
		}
	}
	//rotation
	if (z->right ==y && y->right == x)
	{
		//single rotation
		if (z == root)
		{
			z->right = y->left;
			if(z->right != NULL)
			z->right->parent = z;
			y->left = z;
			z->parent = y;
			root = y;
			root->parent = NULL;
			z->height = y->height - 1;	
			node *temp = y;
			return temp;
		}
		else
		{
			if (z->parent->left == z)
				z->parent->left = y;
			else if (z->parent->right == z)
				z->parent->right = y;
			y->parent = z->parent;
			z->right = y->left;
			if (z->right != NULL)
			z->right->parent = z;
			z->parent = y;
			y->left = z;
			z->parent = y;
			z->height = y->height - 1;
			node *temp = y;
			return temp;
			
		}
	}
	else if (z->left== y && y->left == x)
	{
		//single rotation
		if (z == root)
		{
			z->left = y->right;
			if(z->left != NULL)
			z->left->parent = z;
			y->right = z;
			z->parent = y;
			root = y;
			root->parent = NULL;
			z->height = y->height - 1;
			node *temp = y;
			return temp;
		}
		else
		{
			if (z->parent->left == z)
				z->parent->left = y;
			else if (z->parent->right == z)
				z->parent->right = y;
			y->parent = z->parent;
			z->left = y->right;
			if(z->left != NULL)
			z->left->parent = z;
			y->right = z;
			z->parent = y;
			//높이변화
			z->height = y->height - 1;
			node *temp = y;
			return temp;
			
		}
	}
	else if (z->right == y && y->left == x)
	{
		//double rotation
		if (z == root)
		{
			z->right = x->left;
			if(z->right != NULL)
			z->right->parent = z;
			x->left = z;
			z->parent = x;
			y->left = x->right;
			if(y->left != NULL)
			y->left->parent = y;
			x->right = y;
			y->parent = x;
			root = x;
			root->parent = NULL;
			//높이변화
			x->height++;
			y->height = x->height - 1;
			z->height = x->height - 1;
			node *temp = x;
			return temp;
		}
		else
		{
			if (z->parent->right == z)
				z->parent->right = x;
			else if (z->parent->left == z)
				z->parent->left == x;
			x->parent = z->parent;
			z->right = x->left;
			if(z->right != NULL)
			z->right->parent = z;
			x->left = z;
			z->parent = x;
			y->left = x->right;
			if(y->left != NULL)
			y->left->parent = y;
			x->right = y;
			y->parent = x;
			// 높이 변화
			x->height++;
			y->height = x->height - 1;
			z->height = x->height - 1;
			node *temp = x;
			return temp;
			
		}

	}
	else if (z->left == y && y->right == x)
	{
		//double rotation
		if (z == root)
		{
			z->left = x->right;
			if(z->left != NULL)
			z->left->parent = z;
			x->right = z;
			z->parent = x;
			y->right = x->left;
			if(y->right != NULL)
			y->right->parent = y;
			x->left = y;
			y->parent = x;
			root = x;
			root->parent = NULL;
			//높이변화
			x->height++;
			y->height = x->height - 1;
			z->height = x->height - 1;
			node *temp = x;
			return temp;
		}
		else
		{
			if (z->parent->left == z)
				z->parent->left = x;
			else if (z->parent->right == z)
				z->parent->right = x;
			x->parent = z->parent;
			z->left = x->right;
			if(z->left != NULL)
			z->left->parent = z;
			x->right = z;
			z->parent = x;
			y->right = x->left;
			if(y->right != NULL)
			y->right->parent = y;
			x->left = y;
			y->parent = x;
			// 높이 변화
			x->height++;
			y->height = x->height - 1;
			z->height = x->height - 1;
			node *temp = x;
			return temp;
			
		}
	}

}


AVLTree::AVLTree()
{
	root = NULL;
}
string AVLTree::Search(int s_num)
{
	int probe = 1;
	node *p1 = root;
	while (1)
	{
		if (p1->s_num == s_num)
		{
			string str = to_string(p1->s_num)+ " " + p1->name +" "+ p1->major +" "+ to_string(p1->grade) + " " + to_string(probe);
			return str;
			break;
		}
		else if (p1->s_num > s_num)
		{
			if (p1->left == NULL)
			{
				string str = "없음 " + to_string(probe);
				return str;
				break;
			}
			p1 = p1->left;
			probe++;
			continue;
		}
		else if (p1->s_num < s_num)
		{
			if (p1->right == NULL)
			{
				string str = "없음 " + to_string(probe);
				return str;
				break;
			}
			p1 = p1->right;
			probe++;
			continue;
		}
	}
}

node* AVLTree::compare(int s_num, node *p1)
{
	while (1)
	{
		if (p1->s_num > s_num)
		{
			if (p1->left == NULL)
			{
				return p1;
			}
			else
			{
				p1 =  p1->left;
				continue;
			}
		}
		else if (p1->s_num < s_num)
		{
			if (p1->right == NULL)
			{
				return p1;
			}
			else
			{
				p1 = p1->right;
				continue;
			}
		}
	}
}

string AVLTree::Cinsert(int s_num, string name, string major, int grade)
{
	node *temp = root;
	int probe = 1;
	while (1)
	{
		if (s_num == temp->s_num)
		{
			string str = "추가 할 수 없음 " + to_string(probe);
			return str;
		}
		else
		{
			if (s_num > temp->s_num)
			{
				if (temp->right == NULL)
					break;
				temp = temp->right;
				probe++;
				continue;
			}
			else if(s_num < temp->s_num)
			{
				if (temp->left == NULL)
					break;
				temp = temp->left;
				probe++;
				continue;
			}
		}
	}


	Insert(s_num, name, major, grade);
	string str = to_string(probe);
	return str;

}

void AVLTree::Insert(int s_num, string name, string major, int grade)
{
	node *p = new node();
	p->s_num = s_num;
	p->name = name;
	p->major = major;
	p->grade = grade;

	if (root == NULL)
	{
		root = p;
	}
	else
	{
		node *p2 = compare(s_num, root);
		if (s_num < p2->s_num)
		{
			p2->left = p;
			p->parent = p2;
		}
		else if (s_num > p2->s_num)
		{
			p2->right = p;
			p->parent = p2;
		}
	}
	node *p1 = p->parent;
	if (p1 == NULL)
	{
		return;
	}

	//추가된 노드들의 높이를 증가
	int i = 3;
	node *tmp = NULL;
	if (p1->left == NULL || p1->right == NULL)
	{
		p1->height++;
		p1 = p1->parent;
		while (p1 != NULL)
		{

			if (p1->height == i)
			{
				i++;
				tmp = p1;
			}
			else
			{
				p1->height++;
				i++;
			}
			p1 = p1->parent;
		}
	}

	p1 = p;
	while (p1 != root)		//재구조 코드
	{
		if (p1->parent->right == NULL)
		{
			if (p1->parent->left->height == 1)
			{
				p1 = p1->parent;
				continue;
			}
			else
			{
				node* temp =restructure(p1);
				while(1)
				{
					if (tmp == NULL)
					{
						while (temp->parent != tmp)
						{
							temp->parent->height--;
							temp = temp->parent;
						}
						break;
					}
						
					else
					{
						while (temp->parent != tmp)
						{
							temp->parent->height--;
							temp = temp->parent;
						}
						break;
					}
				}
				
			}
		}
		else if (p1->parent->left == NULL)
		{
			if (p1->parent->right->height == 1)
			{
				p1 = p1->parent;
				continue;
			}
			else
			{
				node* temp = restructure(p1);
				while (1)
				{
					if (tmp == NULL)
					{
						while (temp->parent != tmp)
						{
							temp->parent->height--;
							temp = temp->parent;
						}
						break;
					}
						
					else
					{
						while (temp->parent != tmp)
						{
							temp->parent->height--;
							temp = temp->parent;
						}
					}
				}
				break;
			}
		}
		else if ((p1->parent->left->height) - (p1->parent->right->height) > 1 || (p1->parent->right->height)- (p1->parent->left->height) >1)
		{
			node *temp = restructure(p1);
			while (1)
			{
				if (tmp == NULL)
				{
					while (temp->parent != tmp)
					{
						temp->parent->height--;
						temp = temp->parent;
					}
					break;
				}
				else
				{
					while (temp->parent != tmp)
					{
						temp->parent->height--;
						temp = temp->parent;
					}
				}
			}
			break;
		}
		p1 = p1->parent;
	}
}
int main()
{
	int s_num,grade;
	string name,major;
	string file,alpha,file2,result;
	AVLTree avltree;
	cout << "초기 입력 파일명 : ";
	cin >> file;
	ifstream fin;
	fin.open(file);
	while (!fin.eof())
	{
		fin >> s_num >> name >> major >> grade;
		avltree.Insert(s_num, name, major, grade);
	}
	fin.close();

	cout << "질의 입력 파일명 : ";
	cin >> file;
	cout << "출력 파일명 : ";
	cin >> file2;
	ofstream out(file2);
	ifstream finn;
	finn.open(file);
	while (!finn.eof())
	{
		finn >> alpha;
		if (alpha == "s")
		{
			finn >> s_num;
			result = avltree.Search(s_num);
			out << result << endl;
		}
		else if (alpha == "i")
		{
			finn >> s_num >> name >> major >> grade;
			result = avltree.Cinsert(s_num, name, major, grade);
			out << result << endl;
		}
	}
	finn.close();
}