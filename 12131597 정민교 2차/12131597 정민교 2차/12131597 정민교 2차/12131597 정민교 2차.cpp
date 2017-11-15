#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class node
{
public:
	int s_num, grade;
	string name, major;
	bool flag;
	node();
};
node::node()
{
	grade = 0;
	s_num = 0;
	flag = 0;
}

class Hash
{
public:
	int s_num, grade, ind, ind2;
	string name, major;
	int size, p_num;
	node *arr;	
	void Insert(int s_num, string name, string major, int grade);
	string CInsert(int s_num, string name, string major, int grade);
	string Search(int);
	string Delete(int);
	void setinfo(int, string, string, int);
};

void Hash::setinfo(int, string, string, int)	//�����Ȱ�ü �迭�� �ʱ�ȭ
{
		s_num = 0;
		name = "";
		major = "";
		grade = 0;
}

string Hash::CInsert(int s_num, string name, string major, int grade)	//command ������ insert�Լ�
{
	int probe = 1;
	ind = s_num % size;
	ind2 = p_num - (s_num % p_num);
	int ind3 = ind2;

	if (arr[ind].s_num == s_num)	//���� ������ �߰� �� �� ����
	{
		string str = "�߰� �� �� ���� " + probe;
		return str;
	}

	else if (arr[ind].s_num == 0 && arr[ind].name == "" &&arr[ind].flag == 1)	// ���� �ٸ��� �� �ڸ��� �������� ������ �ִ� �ڸ��̸�
	{
		arr[ind].s_num = s_num;
		arr[ind].name = name;
		arr[ind].major = major;
		arr[ind].grade = grade;
		arr[ind].flag = 0;
		probe++;
		while (1)
		{
			int modind2 = (ind + ind2) % size;
			if (arr[modind2].s_num == 0 && arr[modind2].name == "" &&arr[modind2].flag == 0)	//���� probeȽ���� ã�� ����
			{
				string str = to_string(probe);
				return str;
				break;
			}
			else if (arr[modind2].s_num != 0 && arr[modind2].name != "")
			{
				ind2 = ind3 + ind2;
				probe++;
			}
			else if (arr[modind2].s_num == 0 && arr[modind2].name == "" &&arr[modind2].flag == 1)
			{
				ind2 = ind3 + ind2;
				probe++;
			}
		}
	}
	else if(arr[ind].s_num != s_num)	//���� ���� ���� ��� Ž��
	{
		while (1)
		{
			int modind2 = (ind + ind2) % size;

			if (arr[modind2].s_num == s_num)
			{
				probe++;
				string str = "�߰� �� �� ���� " + probe;
				return str;
				break;
			}
			else if (arr[modind2].s_num == 0 && arr[modind2].name == "")
			{
				probe++;
				string str = to_string(probe);
				arr[modind2].s_num = s_num;
				arr[modind2].name = name;
				arr[modind2].major = major;
				arr[modind2].grade = grade;
				arr[modind2].flag = 0;
				return str;
				break;
			}
			else
			{
				ind2 = ind3 + ind2;
				probe++;
			}
		}
	}
}

void Hash::Insert(int s_num, string name, string major, int grade)	//�ʱ� �Է¿����� insert�Լ�
{
	ind = s_num % size;
	ind2 = p_num - (s_num % p_num);
	int ind3 = ind2;
	
	if (arr[ind].s_num == 0 && arr[ind].name == "")
	{
		arr[ind].s_num = s_num;
		arr[ind].name = name;
		arr[ind].major = major;
		arr[ind].grade = grade;
		arr[ind].flag = 0;
	}
	else
	{
		while (1)
		{
			int modind2 = (ind + ind2) % size;

			if(arr[modind2].s_num == 0 && arr[modind2].name == "")
			{
				arr[modind2].s_num = s_num;
				arr[modind2].name = name;
				arr[modind2].major = major;
				arr[modind2].grade = grade;
				arr[modind2].flag = 0;
				break;
			}
			else
				ind2 = ind3 + ind2;
		}
	}
}


string Hash::Search(int s_num)	//search �Լ�
{
	ind = s_num % size;
	ind2 = p_num - (s_num % p_num);
	int ind3 = ind2;
	int probe=1;
	if (arr[ind].s_num == s_num && arr[ind].name !="")
	{
		string str = to_string(arr[ind].s_num)+" "+arr[ind].name+" "+arr[ind].major+" "+to_string(arr[ind].grade)+ " "+to_string(probe);
		return str;
	}
	else
	{
		while (1)
		{
			int modind2 = (ind + ind2) % size;
			if (arr[modind2].s_num == s_num)
			{
				probe++;
				string str = to_string(arr[modind2].s_num) + " " + arr[modind2].name + " " + arr[modind2].major + " " + to_string(arr[modind2].grade) + " " + to_string(probe);
				return str;
				break;
			}
			else if (arr[modind2].s_num == 0 && arr[modind2].flag ==0 && arr[modind2].name =="")
			{
				probe++;
				string str = "���� " + to_string(probe);
				return str;
				break;
			}
			else
			{
				ind2 = ind3 + ind2;
				probe++;
			}
		}
	}

}

string Hash::Delete(int s_num)		//delete �Լ� ������ �ڸ���flag���� 1�� �ٲ�
{
	int probe = 1;
	ind = s_num % size;
	ind2 = p_num - (s_num % p_num);
	int ind3 = ind2;

	if (arr[ind].s_num == s_num && arr[ind].flag==0 && arr[ind].name != "")
	{
		string str = to_string(probe);
		arr[ind].s_num = 0;
		arr[ind].name = "";
		arr[ind].major = "";
		arr[ind].grade = 0;
		arr[ind].flag = 1;
		return str;
	}

	else 
	{
		while (1)
		{
			int modind2 = (ind + ind2) % size;
			if (arr[modind2].s_num == 0 && arr[modind2].flag == 0 && arr[modind2].name == "")
			{
				probe++;
				string str = "���� �� �� ���� " + to_string(probe);
				return str;
				break;
			}
			if (arr[modind2].s_num == s_num)
			{
				probe++;
				string str = to_string(probe);
				arr[modind2].s_num = 0;
				arr[modind2].name = "";
				arr[modind2].major = "";
				arr[modind2].grade = 0;
				arr[modind2].flag = 1;
				return str;
				break;
			}
			else
			{
				ind2 = ind3 + ind2;
				probe++;
			}
		}
	}
}

int main()
{
	
	int s_num, grade;
	string name, major;
	int size, p_num;
	string file,alpha,file2,result;
	Hash hash;
	
	
	cout << "�ʱ� �Է� ���ϸ� : ";
	cin >> file;
	ifstream fin;
	fin.open(file);
	fin >> size >> p_num;
	hash.size = size;
	hash.p_num = p_num;
	hash.arr = new node[size];	//�迭 �����Ҵ�
	for (int i = 0; i < size; i++)
	{
		hash.setinfo(hash.arr[i].s_num, hash.arr[i].name, hash.arr[i].major, hash.arr[i].grade);
	}
	while (!fin.eof())
	{
		fin >> s_num >> name >> major >> grade;
		hash.Insert(s_num, name, major, grade);
	}
	fin.close();

	cout << "���� �Է� ���ϸ� : ";
	cin >> file;
	cout << "��� ���ϸ� : ";
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
			result = hash.Search(s_num);
			out << result << endl;
		}
		else if (alpha == "i")
		{
			finn >> s_num >> name >> major >> grade;
			result = hash.CInsert(s_num, name, major, grade);
			out << result << endl;
		}
		else if (alpha == "d")
		{
			finn >> s_num;
			result = hash.Delete(s_num);
			out << result << endl;
	
		}
	}
	finn.close();
	return 0;
}