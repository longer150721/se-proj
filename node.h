#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "std_lib_facilities.h"
using namespace std;

class Node
{
public:
	Node(string date,int lots,double price) :date(date),lots(lots),price(price),next(NULL) {};
	Node(string date) :date(date), next(NULL) {};
	Node(int lots) :lots(lots), next(NULL) {};
	Node(double price) :price(price), next(NULL) {};
	Node* next;
	string date;
	int lots;
	double price;
private:
};



class List
{
public:
	List::List(const vector<string>& v1, const vector<int>& v2, const vector<double>& v3);//使用vector初始化
	List(const vector<string>& v);//使用vector初始化
	List(const vector<int>& v);//使用vector初始化
	List(const vector<double>& v);//使用vector初始化
	List(int* array, int array_size);//使用大小确定的数组初始化
	int length();//返回长度
	bool List::insert(int pos, string date, int lots, double price);//在pos位置插入value
	int List::find(string date);//找到第一个出现的值为value的项并返回其位置
	int List::remove(string date);//清除所有值为value的项
	bool spilt(int pos, List& new_list);//从pos开始分离后部至new_list中
	void combine(List& append_list);//将append_list接到原list尾部
	void printALL();//格式化输出list
	~List();

private:
	Node* head;
	int size;
};

List::List(const vector<string>& v1, const vector<int>& v2, const vector<double>& v3)
{
	if ((v1.size() != v2.size())|| (v1.size() != v3.size()) || (v2.size() != v3.size()))
	{
		error("vector error.");
	}
	size = v1.size();
	Node* new_hode = new Node(v1[0],v2[0],v3[0]);
	head = new_hode;
	for (int i = 0; i < v1.size() - 1; i++)
	{
		new_hode->next = new Node(v1[i + 1], v2[i + 1], v3[i + 1]);
		new_hode = new_hode->next;
	}
};

List::List(const vector<string>& v)
{
	size = v.size();
	Node* new_hode = new Node(v[0]);
	head = new_hode;
	for (int i = 0; i < v.size() - 1; i++)
	{
		new_hode -> next = new Node(v[i + 1]);
		new_hode = new_hode -> next;
	}
};

List::List(const vector<int>& v)
{
	size = v.size();
	Node* new_hode = new Node(v[0]);
	head = new_hode;
	for (int i = 0; i < v.size() - 1; i++)
	{
		new_hode->next = new Node(v[i + 1]);
		new_hode = new_hode->next;
	}
};

List::List(const vector<double>& v)
{
	size = v.size();
	Node* new_hode = new Node(v[0]);
	head = new_hode;
	for (int i = 0; i < v.size() - 1; i++)
	{
		new_hode->next = new Node(v[i + 1]);
		new_hode = new_hode->next;
	}
};


int List::length()
{
	return size;
}

bool List::insert(int pos, string date, int lots, double price)
{
	if (pos == 0)
	{
		Node* new_hode = new Node(date, lots, price);
		new_hode -> next = head;
		head = new_hode;
		size++;
		return true;
	}
	else if (pos >  size || pos < 0)//pos输入检测，错误返回false
	{
		return false;
	}
	else
	{
		Node* next_hode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			next_hode = next_hode -> next;
		}
		Node* new_hode = new Node(date, lots, price);
		new_hode -> next = next_hode -> next;
		next_hode -> next = new_hode;
		size++;
		return true;
	}
}

int List::find(string date)
{

	Node* next_hode = head;
	int pos = 0;
	while (true)
	{
		if (next_hode -> date == date)
		{
			return pos;
		}
		else if (next_hode -> next == NULL)
		{
			return -1;
		}
		else
		{
			next_hode = next_hode -> next;
			pos++;
		}
	}
}

int List::remove(string date)
{
	int pos = 0;
	if (head -> date == date)
	{
		head = head -> next;
		pos++;
		size--;
	}
	else
	{
		Node* next_hode = head;
		while (next_hode -> next != NULL)
		{
			if (next_hode -> next -> date == date)
			{
				next_hode -> next = next_hode -> next -> next;
				pos++;
				size--;
			}
			else
			{
				next_hode = next_hode -> next;
			}
		}
	}
	return pos;
};

bool List::spilt(int pos, List& new_list)
{
	if (pos == 0)
	{
		new_list.head = head;
		head = NULL;
		new_list.size = size;
		return true;
	}
	else if (pos >  size || pos < 0)//pos输入检测，错误返回false
	{
		return false;
	}
	else
	{
		Node* next_hode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			next_hode = next_hode -> next;
		}
		new_list.head = next_hode -> next;
		next_hode -> next = NULL;
		new_list.size = size - pos;
		return true;
	}
}

void List::combine(List& append_list)
{
	Node* next_hode = head;
	while (next_hode -> next != NULL)
	{
		next_hode = next_hode -> next;
	}
	next_hode -> next = append_list.head;
	size = size + append_list.size;
	append_list.head = NULL;
}

void List::printALL()
{
	cout << "date:" << head -> date << '\t' << "lots:" << head -> lots << '\t' << "price:" << head -> price << endl;
	Node* next_hode = head -> next;
	while(next_hode != NULL)//输出直至为空指针
	{
		cout << "date:" << next_hode -> date << '\t' << "lots:" << next_hode -> lots << '\t' << "price:" << next_hode -> price << endl;
		next_hode = next_hode -> next;
	}
	cout << endl;
}

List::~List()
{
		Node *del = head;
		if (del == NULL)
		{
			delete del;
		}
		else
		{
			while (del -> next != NULL)
			{
				Node *copy = del;
				del = del -> next;
				delete copy;
			}
			delete del;
		}
}