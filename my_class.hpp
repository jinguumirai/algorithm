#ifndef MY_CLASS_H_
#define MY_CLASS_H_

#include<fstream>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<sstream>

namespace tree
{
	const int left_flag = 0;
	const int right_flag = 1;
}

int string_length(const char* string);
char* string_cat(const char* str1, const char* str2);
double double_round(const double, const int);

template <class T>int get_cout_length(T cout_data, int accu=2)
{
	int minus_num = 0;
	if (cout_data < 0)
	{
		minus_num += 1;
	}
	double copy_data = cout_data;
	int char_len = 0;
	int i = 1;
	int k = 1;
	if (copy_data >= 10)
	{
		k = 10;
		while (copy_data >= k)
		{
			i++;
			k *= 10;
		}
		char_len = i + accu + 1 + minus_num;
	}
	else
	{
		char_len = accu + 2 + minus_num;
	}
	return char_len;
}

template <class T>void right_rotation(T rotation_point, T pre_point, int pre_flag)
{
	T left = rotation_point->get_left_pointer();
	T temp;
	rotation_point->set_left_point(left->get_right_pointer());
	left->set_right_point(rotation_point);
	if (pre_point != NULL)
	{
		if (pre_flag == tree::left_flag)
		{
			pre_point->set_left_point(left);
		}
		else
		{
			pre_point->set_right_point(left);
		}
	}
}

template <class T>void left_rotation(T rotation_point, T pre_point, int pre_flag)
{
	T right = rotation_point->get_right_pointer();
	T temp;
	rotation_point->set_right_point(right->get_left_pointer());
	right->set_left_point(rotation_point);
	if (pre_point != NULL)
	{
		if (pre_flag == tree::left_flag)
		{
			pre_point->set_left_point(right);
		}
		else
		{
			pre_point->set_right_point(right);
		}
	}
}

template <class T> void left_right_rotation(T rotation_point, T pre_point, int pre_flag)
{
	int left_pre_flag = tree::left_flag;
	T new_point = rotation_point->get_left_pointer();
	left_rotation(new_point, rotation_point, left_pre_flag);
	right_rotation(rotation_point, pre_point, pre_flag);
}

template <class T> void right_left_rotation(T rotation_point, T pre_point, int pre_flag)
{
	int right_pre_flag = tree::right_flag;
	T new_point = rotation_point->get_right_pointer();
	right_rotation(new_point, rotation_point, right_pre_flag);
	left_rotation(rotation_point, pre_point, pre_flag);
}

template <class T> char* data_to_chars(const T num_data, int accu=2)
{
	int i = 1;
	double k = 1;
	double copy_data = num_data;
	copy_data = double_round(copy_data, accu);
	char* char_data = NULL;
	int minus_num = 0;
	int char_len = 0;
	if (num_data < 0)
	{
		minus_num = 1;
	}
	if (copy_data >= 10)
	{
		k = 10;
		while (copy_data >= k)
		{
			i++;
			k *= 10;
		}
		char_len = i + accu + 2 + minus_num;
		char_data = new char[char_len];
	}
	else
	{
		char_len = accu + 3 + minus_num;
		char_data = new char[char_len];
	}
	i = 1;
	k = 10;
	while (accu >= k)
	{
		i++;
		k *= 10;
	}
	char* acc_str = new char[(long)i + 1];
	sprintf_s(acc_str, (long)i + 1, "%d", accu);
	char* out_format = string_cat("%.", acc_str);
	char* fin_out_mat = string_cat(out_format, "f");
	sprintf_s(char_data, char_len, fin_out_mat, copy_data);
	delete[] acc_str;
	delete[] out_format;
	delete[] fin_out_mat;
	return char_data;
}
template <class T> class LinkedPoint
{
private:
	T data;
	LinkedPoint* next_pointer;
public:
	LinkedPoint(T new_data)
	{
		this->data = new_data;
		this->next_pointer = NULL;
	}
	template <class T> friend std::ostream& operator << (std::ostream&, LinkedPoint<T>&);
	virtual void assert_next(LinkedPoint* next)
	{
		this->next_pointer = next;
	}
	void set_data(T new_data)
	{
		this->data = new_data;
	}
	void set_final()
	{
		this->next_pointer = NULL;
	}
	T get_data()
	{
		return this->data;
	}
	virtual LinkedPoint* get_next_pointer()
	{
		return this->next_pointer;
	}
	virtual ~LinkedPoint()
	{

	}
};

template <class T>
class LinkedList
{
private:
	LinkedPoint<T>* first_pointer;
	LinkedPoint<T>* final_pointer;
public:
	LinkedList(T data)
	{
		this->first_pointer = new LinkedPoint<T>(data);
		this->final_pointer = first_pointer;
		this->first_pointer->set_final();
	}
	LinkedList()
	{
		this->final_pointer = this->first_pointer = NULL;
	}
	void assert(LinkedPoint<T>* next)
	{
		this->final_pointer->assert_next(next);
		this->final_pointer = this->final_pointer->get_next_pointer();
		if (first_pointer == NULL)
		{
			first_pointer = final_pointer;
		}
	}
	void assert_data(T new_data)
	{
		LinkedPoint<T>* new_point = new LinkedPoint<T>(new_data);
		final_pointer->assert_next(new_point);
		final_pointer = new_point;
		if (first_pointer == NULL)
		{
			first_pointer = new_point;
		}
	}
	template <class T>friend std::ostream& operator << (std::ostream & out, LinkedList<T>& linked_list);

	LinkedPoint<T>* get_first_pointer()
	{
		return this->first_pointer;
	}
	LinkedPoint<T>* get_final_pointer()
	{
		return this->final_pointer;
	}

	~LinkedList()
	{
		LinkedPoint<T>* temp = this->first_pointer;
		LinkedPoint<T>* temp_next;
		while (temp != NULL)
		{
			temp_next = temp->get_next_pointer();
			delete temp;
			temp = temp_next;
		}
	}
};

template <class T> class TreePoint
{
private:
	T data;
	TreePoint<T>* left_pointer;
	TreePoint<T>* right_pointer;
public:
	template <class T> friend class BinarySearchTree;
	template <class T> friend std::ostream& operator << (std::ostream&, BinarySearchTree<T>*);
	template <class T> friend int tree_point_height(TreePoint<T>*);
	template <class T> friend int tree_point_width(TreePoint<T>*);
	TreePoint<T>* get_left_pointer()
	{
		return this->left_pointer;
	}
	TreePoint<T>* get_right_pointer()
	{
		return this->right_pointer;
	}
	void set_data(T new_data)
	{
		this->data = new_data;
	}
	T get_data()
	{
		return this->data;
	}
	TreePoint(T new_data)
	{
		this->data = new_data;
		this->left_pointer = NULL;
		this->right_pointer = NULL;
	}
	TreePoint()
	{
		this->data = 0;
		this->left_pointer = NULL;
		this->right_pointer = NULL;
	}
	void set_leaf()
	{
		this->left_pointer = NULL;
		this->right_pointer = NULL;
	}
	void set_left_point(TreePoint* tree_point)
	{
		this->left_pointer = tree_point;
	}
	void set_right_point(TreePoint* right_point)
	{
		this->right_pointer = right_point;
	}
	void assert_left_data(T new_data)
	{
		TreePoint<T>* new_point = new TreePoint<T>(new_data);
		this->left_pointer = new_point;
	}
	void assert_right_data(T new_data)
	{
		TreePoint<T>* new_point = new TreePoint<T>(new_data);
		this->right_pointer = new_point;
	}

	template <class T>friend std::ostream& operator << (std::ostream & out, TreePoint<T>& tree_point);
};

template <class T> class BinarySearchTree
{
private:
	TreePoint<T>* root;
public:
	template <class T> friend int tree_width(BinarySearchTree<T>*);
	template <class T> friend std::ostream& operator << (std::ostream&, BinarySearchTree<T>*);

	TreePoint<T>* get_root()
	{
		return root;
	}
	BinarySearchTree(T new_data)
	{
		TreePoint<T>* new_root = new TreePoint<T>(new_data);
		this->root = new_root;
	}
	BinarySearchTree()
	{
		this->root = NULL;
	}
	virtual void set_root(TreePoint<T>* tree_point_ptr)
	{
		this->root = tree_point_ptr;
	}
	virtual bool assert(T new_data)
	{
		TreePoint<T>* temp = this->root;
		while (temp != NULL)
		{
			if (temp->data == new_data)
			{
				return false;
			}
			else if (temp->data < new_data)
			{
				if (temp->right_pointer == NULL)
				{
					TreePoint<T>* new_right_point = new TreePoint<T>(new_data);
					temp->right_pointer = new_right_point;
					return true;
				}
				else
				{
					temp = temp->right_pointer;
				}
			}
			else
			{
				if (temp->left_pointer == NULL)
				{
					TreePoint<T>* new_left_point = new TreePoint<T>(new_data);
					temp->left_pointer = new_left_point;
					return true;
				}
				else
				{
					temp = temp->left_pointer;
				}
			}
		}
	}

	TreePoint<T>* search(T search_data)
	{
		TreePoint<T>* temp = this->root;
		while (temp != NULL)
		{
			if (temp->data == search_data)
			{
				return temp;
			}
			else if (temp->data < search_data)
			{
				temp = temp->right_pointer;
			}
			else
			{
				temp = temp->left_pointer;
			}
		}
		return NULL;
	}

	virtual void delete_point(TreePoint<T>* delete_root)
	{
		if (delete_root != NULL)
		{
			if (delete_root->get_left_pointer() != NULL)
			{
				delete_point(delete_root->get_left_pointer()); 
			}
			if (delete_root->get_right_pointer() != NULL) 
			{ 
				delete_point(delete_root->get_right_pointer()); 
			}
			delete delete_root;
		}
	}
	void delete_tree_point(TreePoint<T>* delete_root_pointer)
	{
		if (delete_root_pointer != NULL)
		{
			TreePoint<T>* left_point = delete_root_pointer->get_left_pointer();
			TreePoint<T>* right_point = delete_root_pointer->get_right_pointer();
			delete_tree_point(left_point);
			delete_tree_point(right_point);
			delete delete_root_pointer;
		}
	}
	
	~BinarySearchTree()
	{
		delete_tree_point(this->root);
	}

	int height()
	{
		TreePoint<T>* temp = root;
		return tree_point_height(temp);
	}

	int width()
	{
		TreePoint<T>* temp = root;
		return tree_point_width(temp);
	}

	virtual bool delete_data(T delete_data)
	{
		TreePoint<T>* temp_pre = NULL;
		TreePoint<T>* temp = this->root;
		while (temp != NULL)
		{
			T temp_data = temp->get_data();
			if (temp_data == delete_data)
			{
				if (temp->get_left_pointer() == NULL && temp->get_right_pointer() == NULL)
				{
					if (temp_pre != NULL)
					{
						if (temp_pre->get_left_pointer() == temp)
						{
							temp_pre->set_left_point(NULL);
						}
						else
						{
							temp_pre->set_right_point(NULL);
						}
					}
					else
					{
						this->root = NULL;
					}
					delete temp;
					return true;
				}
				else if (temp->get_left_pointer() == NULL)
				{
					if (temp_pre != NULL)
					{
						if (temp_pre->get_left_pointer() == temp)
						{
							temp_pre->set_left_point(temp->get_right_pointer());
						}
						else
						{
							temp_pre->set_right_point(temp->get_right_pointer());
						}
					}
					else
					{
						this->root = temp->get_right_pointer();
					}
					delete temp;
					return true;
				}
				else if (temp->get_right_pointer() == NULL)
				{
					if (temp_pre != NULL)
					{
						if (temp_pre->get_left_pointer() == temp)
						{
							temp_pre->set_left_point(temp->get_left_pointer());
						}
						else
						{
							temp_pre->set_right_point(temp->get_left_pointer());
						}
					}
					else
					{
						this->root = temp->get_left_pointer();
					}
					delete temp;
					return true;
				}
				else
				{
					TreePoint<T>* temp_right = temp->get_right_pointer();
					TreePoint<T>* min_left = temp_right->get_left_pointer();
					TreePoint<T>* min_left_pre = temp_right;
					if (min_left == NULL)
					{
						temp_right->set_left_point(temp->get_left_pointer());
						if (temp_pre != NULL)
						{
							if (temp_pre->get_left_pointer() == temp)
							{
								temp_pre->set_left_point(temp_right);
							}
							else
							{
								temp_pre->set_right_point(temp_right);
							}
						}
						else
						{
							this->root = temp_right;
						}
						delete temp;
						return true;
					}
					else
					{
						while (min_left->get_left_pointer() != NULL)
						{
							min_left_pre = min_left;
							min_left = min_left->get_left_pointer();
						}
						min_left_pre->set_left_point(min_left->get_right_pointer());
						T data_new = min_left->get_data();
						temp->set_data(data_new);
						delete min_left;
						return true;
					}
				}
			}
			else if (temp_data < delete_data)
			{
				temp_pre = temp;
				temp = temp->get_right_pointer();
			}
			else
			{
				temp_pre = temp;
				temp = temp->get_left_pointer();
			}
		}
		return false;
	}

	virtual void set_root(T new_data)
	{
		TreePoint<T>* new_root = new TreePoint<T>(new_data);
		TreePoint<T>* temp = this->root;
		this->root = new_root;
		if (temp != NULL)
		{
			delete temp;
		}
	}
	virtual void reset_root(TreePoint<T>* new_root)
	{
		this->root = new_root;
	}

	static void save_tree(std::ofstream* file, const TreePoint<T>* saved_root)
	{
		
		if (saved_root)
		{
			(*file) << '[';
			save_tree(file, saved_root->left_pointer);
			std::string str;
			std::stringstream ss;
			ss << saved_root->data;
			ss >> str;
			(*file) << str;
			save_tree(file, saved_root->right_pointer);
			(*file) << ']';
		}
	}
	
	virtual void save(const char* file_path)
	{
		std::ofstream save_file(file_path);
		this->save_tree(&save_file, root);
		save_file.close();
	}
};

template <class T> TreePoint<T>* load_tree(std::ifstream* file)
{
	TreePoint<T>* new_point = new TreePoint<T>;
	char temp;
	char Num[350];
	int k = 0;
	(*file) >> temp;
	if (temp == '[')
	{
		new_point->set_left_point(load_tree<T>(file));
		(*file) >> temp;
	}

	if ((temp <= '9' && temp >= '0') || temp == '.' || temp == '-')
	{
		
		while ((temp <= '9' && temp >= '0' )|| temp == '.' || temp == '-')
		{
			Num[k] = temp;
			k++;
			(*file) >> temp;
		}
		Num[k] = '\0';
		std::string str(Num);
		new_point->set_data(std::stod(str));
	}

	if (temp == '[')
	{
		new_point->set_right_point(load_tree<T>(file));
	}
	if (temp != ']')
	{
		(*file) >> temp;
	}
	return new_point;
}

template <class T> BinarySearchTree<T>* load_BiSeTr(const char* file_path)
{
	std::ifstream load_file;
	load_file.open(file_path, std::ios::in);
	char temp;
	load_file >> temp;
	if (!load_file.eof())
	{
		BinarySearchTree<T>* new_tree = new BinarySearchTree<T>;
		new_tree->set_root(load_tree<T>(&load_file));
		load_file.close();
		return new_tree;
	}
	else
	{
		load_file.close();
		return NULL;
	}
}

template <class T> class BinaryTree
{
private:
	TreePoint<T>* root;
public:
	BinaryTree()
	{
		this->root = NULL;
	}
	BinaryTree(T new_data)
	{
		this->root = new TreePoint<T>(new_data);
	}
	void set_root(T new_data)
	{
		TreePoint<T>* temp = this->root;
		TreePoint<T>* new_root = new TreePoint<T>(new_data);
		this->root = new_root;
		if (temp != NULL)
		{
			delete temp;
		}
	}
	TreePoint<T>* get_root()
	{
		return this->root;
	}
	void reset_root(TreePoint<T>* new_root)
	{
		this->root = new_root;
	}
	void delete_all_tree(TreePoint<T>* root_point)
	{
		if (root_point != NULL)
		{
			TreePoint<T>* left = root_point->get_left_pointer();
			TreePoint<T>* right = root_point->get_right_pointer();
			if (left != NULL)
			{
				delete_all_tree(left);
			}
			if (right != NULL)
			{
				delete_all_tree(right);
			}
			delete root_point;
		}
	}
	~BinaryTree()
	{
		delete_all_tree(this->root);
	}
};

template <class T> class DoubleLinkedPoint : public LinkedPoint<T>
{
private:
	DoubleLinkedPoint<T>* pre_pointer;
public:
	DoubleLinkedPoint():
		LinkedPoint<T>()
	{
		pre_pointer = NULL;
	}
	DoubleLinkedPoint(T new_data):
		LinkedPoint<T>(new_data)
	{
		pre_pointer = NULL;
	}
	DoubleLinkedPoint<T>* get_next_pointer()
	{
		return (DoubleLinkedPoint<T>*)(LinkedPoint<T>::get_next_pointer());
	}
	DoubleLinkedPoint<T>* get_pre_pointer()
	{
		return pre_pointer;
	}
	T get_data()
	{
		return LinkedPoint<T>::get_data();
	}
	void assert_next(DoubleLinkedPoint<T>* new_pointer)
	{
		LinkedPoint<T>::assert_next(new_pointer);
		new_pointer->pre_pointer = this;
	}
	~DoubleLinkedPoint()
	{

	}
};

template <class T> class DoubleLinkedList
{
private:
	DoubleLinkedPoint<T>* start_point;
	DoubleLinkedPoint<T>* final_point;
public:
	template <class T> friend std::ostream& operator << (std::ostream&, const DoubleLinkedList<T>*);
	DoubleLinkedList()
	{
		start_point = final_point = NULL;
	}
	DoubleLinkedList(T new_data)
	{
		DoubleLinkedPoint<T>* new_point = new DoubleLinkedPoint<T>(new_data);
		start_point = final_point = new_point;
	}
	void assert(DoubleLinkedPoint<T>* new_point)
	{
		if (final_point != NULL)
		{
			final_point->assert_next(new_point);
		}
	}
	void assert_data(T new_data)
	{
		DoubleLinkedPoint<T>* new_point = new DoubleLinkedPoint<T>(new_data);
		if (final_point != NULL)
		{
			final_point->assert_next(new_point);
			final_point = new_point;
		}
		else
		{
			start_point = final_point = new_point;
		}
	}
	~DoubleLinkedList()
	{
		DoubleLinkedPoint<T>* temp_next;
		DoubleLinkedPoint<T>* temp = start_point;
		if (temp != NULL)
		{
			temp_next = (DoubleLinkedPoint<T>*)temp->get_next_pointer();
			delete temp;
			temp = temp_next;
		}
	}
	DoubleLinkedPoint<T>* get_first_pointer()
	{
		return this->start_point;
	}
	DoubleLinkedPoint<T>* get_final_pointer()
	{
		return final_point;
	}
};

template <class T> class AVLTree : public BinarySearchTree<T>
{
private:
	BinaryTree<int>* height_tree;
public:
	AVLTree() :
		BinarySearchTree<T>()
	{
		height_tree = new BinaryTree<int>;
	}
	AVLTree(T new_data) :
		BinarySearchTree<T>(new_data)
	{
		height_tree = new BinaryTree<int>(1);
	}
	bool assert(T new_data)
	{
		if (this->get_root() == NULL)
		{
			TreePoint<T>* new_root = new TreePoint<T>(new_data);
			this->set_root(new_root);
			height_tree->get_root()->set_data(1);
			return true;
		}
		DoubleLinkedList<TreePoint<T>*>* trace_list = new DoubleLinkedList<TreePoint<T>*>;
		DoubleLinkedList<TreePoint<int>*>* height_trace_list = new DoubleLinkedList<TreePoint<int>*>;
		TreePoint<T>* temp = this->get_root();
		TreePoint<int>* h_temp = height_tree->get_root();
		int fin_flag = -1;
		while (temp != NULL)
		{
			T temp_data = temp->get_data();
			if (temp_data == new_data)
			{
				delete trace_list;
				delete height_trace_list;
				return false;
			}
			else if (temp_data < new_data)
			{
				height_trace_list->assert_data(h_temp);
				trace_list->assert_data(temp);
				temp = temp->get_right_pointer();
				h_temp = h_temp->get_right_pointer();
				fin_flag = tree::right_flag;
			}
			else
			{
				height_trace_list->assert_data(h_temp);
				trace_list->assert_data(temp);
				temp = temp->get_left_pointer();
				h_temp = h_temp->get_left_pointer();
				fin_flag = tree::left_flag;
			}
		}
		TreePoint<T>* final_tree_point = trace_list->get_final_pointer()->get_data();
		TreePoint<T>* new_pointer = NULL;
		TreePoint<int>* new_height_pointer = NULL;
		if (fin_flag == tree::right_flag)
		{
			final_tree_point->assert_right_data(new_data);
			new_pointer = final_tree_point->get_right_pointer();
		}
		else
		{
			final_tree_point->assert_left_data(new_data);
			new_pointer = final_tree_point->get_left_pointer();
		}
		DoubleLinkedPoint<TreePoint<int>*>* height_trace = height_trace_list->get_final_pointer();
		TreePoint<int>* height_temp = height_trace_list->get_final_pointer()->get_data();
		bool height_change = false;
		if (fin_flag == tree::left_flag)
		{
			height_temp->assert_left_data(1);
			if (height_temp->get_data() == 1)
			{
				height_temp->set_data(2);
				height_change = true;
			}
			new_height_pointer = height_temp->get_left_pointer();
		}
		else
		{
			height_temp->assert_right_data(1);
			if (height_temp->get_data() == 1)
			{
				height_temp->set_data(2);
				height_change = true;
			}
			new_height_pointer = height_temp->get_right_pointer();
		}
		DoubleLinkedPoint<TreePoint<int>*>* pre_height_trace = height_trace->get_pre_pointer();
		TreePoint<int>* another_tree;
		trace_list->assert_data(new_pointer);
		height_trace_list->assert_data(new_height_pointer);
		if (height_change)
		{
			while (pre_height_trace != NULL)
			{
				int another_height;
				if (pre_height_trace != NULL)
				{
					if (pre_height_trace->get_data()->get_left_pointer() == height_trace->get_data())
					{
						another_tree = pre_height_trace->get_data()->get_right_pointer();
						if (another_tree != NULL)
						{
							another_height = another_tree->get_data();
						}
						else
						{
							another_height = 0;
						}
					}
					else
					{
						another_tree = pre_height_trace->get_data()->get_left_pointer();
						if (another_tree != NULL)
						{
							another_height = another_tree->get_data();
						}
						else
						{
							another_height = 0;
						}
					}
					if (another_height < height_trace->get_data()->get_data())
					{
						pre_height_trace->get_data()->set_data(height_trace->get_data()->get_data() + 1);
					}
					else
					{
						break;
					}
				}
				height_trace = pre_height_trace;
				pre_height_trace = height_trace->get_pre_pointer();
			}
		}
		else
		{
			delete trace_list;
			delete height_trace_list;
			return true;
		}
		DoubleLinkedPoint<TreePoint<T>*>* temp_trace = trace_list->get_final_pointer()->get_pre_pointer();
		height_trace = height_trace_list->get_final_pointer()->get_pre_pointer();
		int left_height, right_height;
		TreePoint<int>* left_height_tree = NULL;
		TreePoint<int>* right_height_tree = NULL;
		TreePoint<int>* pre_height_pointer = NULL;
		TreePoint<T>* pre_tree_pointer = NULL;
		while (temp_trace != NULL)
		{
			temp = temp_trace->get_data();
			height_temp = height_trace->get_data();
			left_height_tree = height_trace->get_data()->get_left_pointer();
			if (left_height_tree != NULL)
			{
				left_height = left_height_tree->get_data();
			}
			else
			{
				left_height = 0;
			}
			right_height_tree = height_trace->get_data()->get_right_pointer();
			if (right_height_tree != NULL)
			{
				right_height = right_height_tree->get_data();
			}
			else
			{
				right_height = 0;
			}
			int left_right = left_height - right_height;
			if (left_right > 1)
			{
				if (temp_trace->get_pre_pointer() != NULL)
				{
					pre_tree_pointer = temp_trace->get_pre_pointer()->get_data();
					pre_height_pointer = height_trace->get_pre_pointer()->get_data();
				}
				else
				{
					pre_height_pointer = NULL;
					pre_tree_pointer = NULL;
				}
				bool rotation_flag = false;
				if (temp_trace->get_next_pointer()->get_next_pointer()->get_data() ==
					temp_trace->get_next_pointer()->get_data()->get_left_pointer())
				{
					rotation_flag = true;
				}
				if (rotation_flag)
				{
					if (pre_tree_pointer != NULL)
					{
						if (pre_tree_pointer->get_left_pointer() == temp_trace->get_data())
						{
							right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::left_flag);
							right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::left_flag);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
						else
						{
							right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::right_flag);
							right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::right_flag);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
					}
					else
					{
						this->reset_root(this->get_root()->get_left_pointer());
						height_tree->reset_root(height_tree->get_root()->get_left_pointer());
						right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer, -1);
						right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer, -1);
						height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
						delete trace_list;
						delete height_trace_list;
						return true;
					}
				}
				else
				{
					TreePoint<T>* left_right_point = temp_trace->get_data()->get_left_pointer()->get_right_pointer();
					TreePoint<T>* left_left_point = temp_trace->get_data()->get_left_pointer();
					if (pre_tree_pointer != NULL)
					{
						if (pre_tree_pointer->get_left_pointer() == temp_trace->get_data())
						{
							left_right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::left_flag);
							left_right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::left_flag);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
							left_right_point->set_data(left_right_point->get_data() + 1);
							left_left_point->set_data(left_left_point->get_data() - 1);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
						else
						{
							left_right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::right_flag);
							left_right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::right_flag);
							left_right_point->set_data(left_right_point->get_data() + 1);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
							left_left_point->set_data(left_left_point->get_data() - 1);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
					}
					else
					{
						this->reset_root(this->get_root()->get_left_pointer()->get_right_pointer());
						height_tree->reset_root(height_tree->get_root()->get_left_pointer()->get_right_pointer());
						left_right_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
							-1);
						left_right_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
							-1);
						left_right_point->set_data(left_right_point->get_data() + 1);
						height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 2);
						left_left_point->set_data(left_left_point->get_data() - 1);
						delete trace_list;
						delete height_trace_list;
						return true;
					}
				}
			}
			else if (left_right < -1)
			{
			
				bool rotation_flag = true;
				if (temp_trace->get_next_pointer()->get_next_pointer()->get_data() ==
					temp_trace->get_next_pointer()->get_data()->get_right_pointer())
				{
					rotation_flag = false;
				}
				if (temp_trace->get_pre_pointer() != NULL)
				{
					pre_tree_pointer = temp_trace->get_pre_pointer()->get_data();
					pre_height_pointer = height_trace->get_pre_pointer()->get_data();
				}
				else
				{
					pre_height_pointer = NULL;
					pre_tree_pointer = NULL;
				}
				if (rotation_flag)
				{
					
					TreePoint<int>* right_left = height_trace->get_data()->get_right_pointer()->get_left_pointer();
					TreePoint<int>* right_right = height_trace->get_data()->get_right_pointer();
					if (pre_tree_pointer != NULL)
					{
						if (pre_tree_pointer->get_left_pointer() == temp_trace->get_data())
						{
							right_left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::left_flag);
							right_left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::left_flag);
							height_temp->set_data(height_temp->get_data() - 2);
							right_left->set_data(right_left->get_data() + 1);
							right_right->set_data(right_right->get_data() - 1);
							return true;
						}
						else
						{
							right_left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::right_flag);
							right_left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::right_flag);
							height_temp->set_data(height_temp->get_data() - 2);
							right_left->set_data(right_left->get_data() + 1);
							right_right->set_data(right_right->get_data() - 1);
							return true;
						}
					}
					else
					{
						this->reset_root(temp_trace->get_data()->get_right_pointer()->get_left_pointer());
						height_tree->reset_root(height_trace->get_data()->get_right_pointer()->get_left_pointer());
						right_left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer, -1);
						right_left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer, -1);
						height_temp->set_data(height_temp->get_data() - 2);
						right_left->set_data(right_left->get_data() + 1);
						right_right->set_data(right_right->get_data() - 1);
						delete trace_list;
						delete height_trace_list;
						return true;
					}
				}
				else
				{
					if (pre_tree_pointer != NULL)
					{
						if (pre_tree_pointer->get_left_pointer() == temp_trace->get_data())
						{
							left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::left_flag);
							left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::left_flag);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 1);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
						else
						{
							left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
								tree::right_flag);
							left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
								tree::right_flag);
							height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 1);
							delete trace_list;
							delete height_trace_list;
							return true;
						}
					}
					else
					{
						this->reset_root(this->get_root()->get_right_pointer());
						height_tree->reset_root(height_tree->get_root()->get_right_pointer());
						left_rotation<TreePoint<T>*>(temp_trace->get_data(), pre_tree_pointer,
							-1);
						left_rotation<TreePoint<int>*>(height_trace->get_data(), pre_height_pointer,
							-1);
						height_trace->get_data()->set_data(height_trace->get_data()->get_data() - 1);
						delete trace_list;
						delete height_trace;
						return true;
					}
				}
			}
			temp_trace = temp_trace->get_pre_pointer();
			height_trace = height_trace->get_pre_pointer();

		}
	}

	bool delete_data(T dele_data)
	{
		DoubleLinkedList<TreePoint<T>*> trace_list;
		DoubleLinkedList<TreePoint<int>*> height_trace_list;
		TreePoint<T>* temp = this->get_root();
		TreePoint<int>* height_temp = height_tree->get_root();
		bool has_data = false;
		if (temp == NULL)
		{
			return false;
		}
		while (temp != NULL)
		{
			if (temp->get_data() == dele_data)
			{
				has_data = true;
				trace_list.assert_data(temp);
				height_trace_list.assert_data(height_temp);
				break;
			}
			else if (temp->get_data() < dele_data)
			{
				trace_list.assert_data(temp);
				height_trace_list.assert_data(height_temp);
				temp = temp->get_right_pointer();
				height_temp = height_temp->get_right_pointer();
			}
			else
			{
				trace_list.assert_data(temp);
				height_trace_list.assert_data(height_temp);
				temp = temp->get_left_pointer();
				height_temp = height_temp->get_left_pointer();
			}
		}
		if (!has_data)
		{
			return false;
		}
		TreePoint<T>* selected_point = trace_list.get_final_pointer()->get_data();
		bool change_height = false, height_change=false;
		temp = selected_point;
		height_temp = height_trace_list.get_final_pointer()->get_data();
		DoubleLinkedPoint<TreePoint<T>*>* trace_temp = trace_list.get_final_pointer();
		DoubleLinkedPoint<TreePoint<int>*>* height_trace_temp = height_trace_list.get_final_pointer();
		TreePoint<T>* pre_temp = NULL;
		TreePoint<int>* pre_height_temp = NULL;
		DoubleLinkedPoint<TreePoint<T>*>* pre_trace_temp = trace_list.get_final_pointer()->get_pre_pointer();
		DoubleLinkedPoint<TreePoint<int>*>* pre_height_trace_temp = height_trace_list.get_final_pointer()->get_pre_pointer();
		int another_height;
		int right_left_delta;
		int fin_flag;
		bool not_delete = true;
		if (temp->get_left_pointer() && temp->get_right_pointer())
		{
			TreePoint<T>* switch_temp = temp;
			temp = temp->get_right_pointer();
			height_temp = height_temp->get_right_pointer();
			while (temp)
			{
				trace_list.assert_data(temp);
				height_trace_list.assert_data(height_temp);
				temp = temp->get_left_pointer();
				height_temp = height_temp->get_left_pointer();
			}
			trace_temp = trace_list.get_final_pointer();
			pre_trace_temp = trace_temp->get_pre_pointer();
			pre_height_trace_temp = height_trace_temp->get_pre_pointer();
			height_trace_temp = height_trace_list.get_final_pointer();
			temp = trace_list.get_final_pointer()->get_data();
			T switch_data = switch_temp->get_data();
			height_temp = height_trace_list.get_final_pointer()->get_data();
			switch_temp->set_data(temp->get_data());
			temp->set_data(switch_data);
		}
		if (temp->get_left_pointer() != NULL && temp->get_right_pointer() == NULL)
		{
			if (trace_temp->get_pre_pointer())
			{
				pre_temp = trace_temp->get_pre_pointer()->get_data();
				if (pre_temp->get_right_pointer() == temp)
				{
					pre_temp->set_right_point(temp->get_left_pointer());
					pre_height_temp->set_right_point(height_temp->get_left_pointer());
					TreePoint<int>* pre_temp_left_height = pre_height_temp->get_left_pointer();
					if (pre_temp_left_height)
					{
						if (pre_temp_left_height->get_data() <= pre_height_temp->get_right_pointer()->get_data())
						{
							pre_height_temp->set_data(pre_height_temp->get_right_pointer()->get_data() + 1);
							height_change = true;
						}
						else
						{
							pre_height_temp->set_data(pre_temp_left_height->get_data() + 1);
						}
					}
					else
					{
						pre_height_temp->set_data(pre_height_temp->get_right_pointer()->get_data() + 1);
					}
				}
				else
				{
					pre_temp->set_left_point(temp->get_left_pointer());
					pre_height_temp->set_left_point(height_temp->get_left_pointer());
					TreePoint<int>* pre_temp_right_height = pre_height_temp->get_right_pointer();
					if (pre_temp_right_height)
					{
						if (pre_temp_right_height->get_data() < pre_height_temp->get_left_pointer()->get_data())
						{
							pre_height_temp->set_data(pre_height_temp->get_left_pointer()->get_data() + 1);
						}
						else
						{
							pre_height_temp->set_data(pre_temp_right_height->get_data() + 1);
						}
					}
					else
					{
						pre_height_temp->set_data(pre_height_temp->get_left_pointer()->get_data() + 1);
					}
				}
			}
			else
			{
				this->reset_root(temp->get_left_pointer());
				height_tree->reset_root(height_temp->get_left_pointer());
				delete temp;
				delete height_temp;
				return true;
			}
			delete temp;
			delete height_temp;
			not_delete = false;
		}
		else if (temp->get_right_pointer() != NULL && temp->get_left_pointer() == NULL)
		{
			if (pre_trace_temp->get_pre_pointer())
			{
				pre_temp = trace_temp->get_pre_pointer()->get_data();
				pre_height_temp = height_trace_temp->get_pre_pointer()->get_data();
				if (pre_temp->get_right_pointer() == temp)
				{
					pre_temp->set_right_point(temp->get_right_pointer());
					pre_height_temp->set_right_point(height_temp->get_right_pointer());
					TreePoint<int>* pre_temp_left_height = pre_height_temp->get_left_pointer();
					if (pre_temp_left_height)
					{
						if (pre_temp_left_height->get_data() <= pre_height_temp->get_right_pointer()->get_data())
						{
							pre_height_temp->set_data(pre_height_temp->get_right_pointer()->get_data() + 1);
							height_change = true;
						}
						else
						{
							pre_height_temp->set_data(pre_temp_left_height->get_data() + 1);
						}
					}
					else
					{
						pre_height_temp->set_data(pre_height_temp->get_right_pointer()->get_data() + 1);
					}
				}
				else
				{
					pre_temp->set_left_point(temp->get_right_pointer());
					pre_height_temp->set_left_point(height_temp->get_right_pointer());
					TreePoint<int>* pre_temp_right_height = pre_height_temp->get_right_pointer();
					if (pre_temp_right_height)
					{
						if (pre_temp_right_height->get_data() < pre_height_temp->get_left_pointer()->get_data())
						{
							pre_height_temp->set_data(pre_height_temp->get_left_pointer()->get_data() + 1);
						}
						else
						{
							pre_height_temp->set_data(pre_temp_right_height->get_data() + 1);
						}
					}
					else
					{
						pre_height_temp->set_data(pre_height_temp->get_left_pointer()->get_data() + 1);
					}
				}
			}
			else
			{
				this->reset_root(temp->get_right_pointer());
				height_tree->reset_root(height_temp->get_right_pointer());
				delete temp;
				delete height_temp;
				return true;
			}
			delete temp;
			delete height_temp;
			temp = pre_trace_temp->get_data();
			height_temp = pre_height_trace_temp->get_data();
			trace_temp = pre_trace_temp;
			height_trace_temp = pre_height_trace_temp;
			not_delete = false;
		}
		if (temp->get_left_pointer() == NULL && temp->get_right_pointer() == NULL)
		{
			if (not_delete)
			{
				trace_temp = trace_list.get_final_pointer();
				height_trace_temp = height_trace_list.get_final_pointer();
				pre_trace_temp = trace_temp->get_pre_pointer();
				pre_height_trace_temp = height_trace_temp->get_pre_pointer();
				if (pre_trace_temp != NULL)
				{
					pre_temp = pre_trace_temp->get_data();
					pre_height_temp = pre_height_trace_temp->get_data();
					if (pre_temp->get_left_pointer() == temp)
					{
						if (pre_height_temp->get_right_pointer() != NULL)
						{
							another_height = pre_height_temp->get_right_pointer()->get_data();
						}
						else
						{
							another_height = 0;
						}
						pre_height_temp->set_left_point(NULL);
						delete height_temp;
						delete temp;
						pre_temp->set_left_point(NULL);
						if (another_height == 2)
						{
							right_left_delta = 2;
						}
						else if (another_height == 0)
						{
							pre_height_temp->set_data(1);
							height_change = true;
						}
					}
					else
					{
						if (pre_height_temp->get_left_pointer() != NULL)
						{
							another_height = pre_height_temp->get_left_pointer()->get_data();
						}
						else
						{
							another_height = 0;
						}
						pre_height_temp->set_right_point(NULL);
						delete height_temp;
						delete temp;
						pre_temp->set_right_point(NULL);
						if (another_height == 2)
						{
							right_left_delta = -2;
						}
						else if (another_height == 0)
						{
							pre_height_temp->set_data(1);
							height_change = true;
						}
					}
				}
				else
				{
					this->reset_root(NULL);
					this->height_tree->reset_root(NULL);
					delete temp;
					delete height_temp;
					return true;
				}
				trace_temp = trace_temp->get_pre_pointer();
				temp = trace_temp->get_data();
				height_temp = height_trace_temp->get_data();
				height_trace_temp = height_trace_temp->get_pre_pointer();
				pre_trace_temp = trace_temp->get_pre_pointer();
			}
			else
			{
				temp = pre_temp;
				height_temp = pre_height_temp;
				trace_temp = trace_temp->get_pre_pointer();
				height_trace_temp = height_trace_temp->get_pre_pointer();
			}
			TreePoint<T>* final_change_pointer = NULL;
			if (trace_temp->get_pre_pointer())
			{
				if (trace_temp->get_pre_pointer()->get_pre_pointer())
				{
					final_change_pointer = trace_temp->get_pre_pointer()->get_pre_pointer()->get_data();
				}
			}
			
			for (;
				height_change && trace_temp != NULL; 
				trace_temp = trace_temp->get_pre_pointer(), height_trace_temp = height_trace_temp->get_pre_pointer())
			{
				height_change = false;
				temp = trace_temp->get_data();
				height_temp = height_trace_temp->get_data();
				pre_trace_temp = trace_temp->get_pre_pointer();
				pre_height_trace_temp = height_trace_temp->get_pre_pointer();
				if (pre_trace_temp != NULL)
				{
					if (pre_trace_temp->get_data()->get_left_pointer() == temp)
					{
						if (pre_height_trace_temp->get_data()->get_right_pointer())
						{
							another_height = pre_height_trace_temp->get_data()->get_right_pointer()->get_data();
						}
						else
						{
							another_height = 0;
						}
					}
					else
					{
						if (pre_height_trace_temp->get_data()->get_left_pointer())
						{
							another_height = pre_height_trace_temp->get_data()->get_left_pointer()->get_data();
						}
						else
						{
							another_height = 0;
						}
					}
					if (height_temp->get_data() >= another_height)
					{
						pre_height_trace_temp->get_data()->set_data(pre_height_trace_temp->get_data()->get_data() - 1);
						height_change = true;
						if (pre_trace_temp->get_pre_pointer())
						{
							if (pre_trace_temp->get_pre_pointer()->get_pre_pointer())
							{
								final_change_pointer = pre_trace_temp->get_pre_pointer()->get_pre_pointer()->get_data();
							}
							else
							{
								final_change_pointer = NULL;
							}
						}
						else
						{
							final_change_pointer = NULL;
						}

					}
				}
			}
			trace_temp = trace_list.get_final_pointer()->get_pre_pointer();
			height_trace_temp = height_trace_list.get_final_pointer()->get_pre_pointer();
			bool next_change = false;
			bool use_final = false;

			while ((temp != final_change_pointer || use_final) && trace_temp != NULL)
			{
				temp = trace_temp->get_data();
				height_temp = height_trace_temp->get_data();
				int left_height;
				if (height_temp->get_left_pointer())
				{
					left_height = height_temp->get_left_pointer()->get_data();
				}
				else
				{
					left_height = 0;
				}
				int right_height;
				if (height_temp->get_right_pointer())
				{
					right_height = height_temp->get_right_pointer()->get_data();
				}
				else
				{
					right_height = 0;
				}
				right_left_delta = right_height - left_height;
				DoubleLinkedPoint<TreePoint<T>*>* pre_trace_temp = trace_temp->get_pre_pointer();
				TreePoint<T>* pre_temp = NULL;
				TreePoint<int>* height_pre_temp = NULL;
				bool not_root_flag = false;
				if (pre_trace_temp != NULL)
				{
					pre_temp = pre_trace_temp->get_data();
					height_pre_temp = height_trace_temp->get_pre_pointer()->get_data();
					not_root_flag = true;
				}
				bool pre_temp_flag = tree::left_flag;
				if (not_root_flag)
				{
					if (pre_temp->get_right_pointer() == temp)
					{
						pre_temp_flag = tree::right_flag;
					}
				}

				if (right_left_delta > 1)
				{
					TreePoint<T>* right_temp = temp->get_right_pointer();
					int left_right_height;
					if (height_temp->get_right_pointer()->get_left_pointer() != NULL)
					{
						left_right_height = height_temp->get_right_pointer()->get_left_pointer()->get_data();
					}
					else
					{
						left_right_height = 0;
					}

					int right_right_height;
					if (height_temp->get_right_pointer()->get_right_pointer() != NULL)
					{
						right_right_height = height_temp->get_right_pointer()->get_right_pointer()->get_data();
					}
					else
					{
						right_right_height = 0;
					}
					
					if (right_right_height >= left_right_height)
					{
						TreePoint<int>* height_right_temp = height_temp->get_right_pointer();
						TreePoint<T>* right_temp = temp->get_right_pointer();
						left_rotation(height_temp, height_pre_temp, pre_temp_flag);
						left_rotation(temp, pre_temp, pre_temp_flag);
						if (right_right_height == left_right_height)
						{
							height_temp->set_data(height_temp->get_data() - 1);
							height_right_temp->set_data(height_right_temp->get_data() + 1);
							if (!not_root_flag)
							{
								this->reset_root(right_temp);
								height_tree->reset_root(height_right_temp);
							}
							return true;
						}
						else
						{
							height_temp->set_data(height_temp->get_data() - 2);
							use_final = true;
						}
						if (!not_root_flag)
						{
							this->reset_root(right_temp);
							height_tree->reset_root(height_right_temp);
							return true;
						}
					}
					else
					{
						TreePoint<int>* height_temp_right_left = height_temp->get_right_pointer()->get_left_pointer();
						TreePoint<int>* height_temp_right = height_temp->get_right_pointer();
						TreePoint<T>* temp_right_left = temp->get_right_pointer()->get_left_pointer();
						right_left_rotation(height_temp, pre_height_temp, pre_temp_flag);
						right_left_rotation(temp, pre_temp, pre_temp_flag);
						height_temp->set_data(height_temp->get_data() - 2);
						height_temp_right_left->set_data(height_temp_right_left->get_data() + 1);
						height_temp_right->set_data(height_temp_right->get_data() - 1);
						if (!not_root_flag)
						{
							this->reset_root(temp_right_left);
							height_tree->reset_root(height_temp_right_left);
							return true;
						}
						use_final = true;
					}
				}
				else if (right_left_delta < - 1)
				{
					TreePoint<T>* left_temp = temp->get_left_pointer();
					int left_right_height;
					if (height_temp->get_left_pointer()->get_right_pointer() != NULL)
					{
						left_right_height = height_temp->get_left_pointer()->get_right_pointer()->get_data();
					}
					else
					{
						left_right_height = 0;
					}
					int left_left_height;
					if (height_temp->get_left_pointer()->get_left_pointer() != NULL)
					{
						left_left_height = height_temp->get_left_pointer()->get_left_pointer()->get_data();
					}
					else
					{
						left_left_height = 0;
					}
					if (left_left_height >= left_right_height)
					{
						TreePoint<int>* height_left_temp = height_temp->get_left_pointer();
						TreePoint<T>* left_temp = temp->get_left_pointer();

						right_rotation(height_temp, height_pre_temp, pre_temp_flag);
						right_rotation(temp, pre_temp, pre_temp_flag);
						if (left_left_height == left_right_height)
						{
							height_temp->set_data(height_temp->get_data() - 1);
							height_left_temp->set_data(height_left_temp->get_data() + 1);
							if (!not_root_flag)
							{
								
								this->reset_root(left_temp);
								height_tree->reset_root(height_left_temp);
							}
							return true;
						}
						else
						{
							height_temp->set_data(height_temp->get_data() - 2);
							use_final = true;
						}
						if (!not_root_flag)
						{
							this->reset_root(left_temp);
							height_tree->reset_root(height_left_temp);
							return true;
						}
					}
					else
					{
						
						TreePoint<int>* height_temp_left_right = height_temp->get_left_pointer()->get_right_pointer();
						TreePoint<int>* height_temp_left = height_temp->get_left_pointer();
						TreePoint<T>* temp_left_right = temp->get_left_pointer()->get_right_pointer();
						right_left_rotation(height_temp, pre_height_temp, pre_temp_flag);
						right_left_rotation(temp, pre_temp, pre_temp_flag);
						height_temp->set_data(height_temp->get_data() - 2);
						height_temp_left_right->set_data(height_temp_left_right->get_data() + 1);
						height_temp_left->set_data(height_temp_left->get_data() - 1);
						if (!not_root_flag)
						{
							this->reset_root(temp_left_right);
							height_tree->reset_root(height_temp_left_right);
							return true;
						}
						use_final = true;
					}
				}
				trace_temp = trace_temp->get_pre_pointer();
				height_trace_temp = height_trace_temp->get_pre_pointer();
				if (trace_temp)
				{
					temp = trace_temp->get_data();
				}
				else
				{
					temp = NULL;
				}
			}
		}
	}

	virtual void save(const char* file_path)
	{
		std::string str1(file_path);
		std::string str2(file_path);
		str1 = str1 + "_1";
		str2 = str2 + "_2";
		std::ofstream file1(str1);
		std::ofstream file2(str2);
		BinarySearchTree<T>::save_tree(&file1, this->get_root());
		BinarySearchTree<int>::save_tree(&file2, this->height_tree->get_root());
		file1.close();
		file2.close();
	}

	BinaryTree<int>* get_height_tree()
	{
		return this->height_tree;
	}

	~AVLTree()
	{
		delete height_tree;
	}
};

TreePoint<int>* load_height_point(std::ifstream* file);

template <class T> AVLTree<T>* load_avl(const char* path)
{
	std::string str1(path);
	std::string str2(path);
	str1 = str1 + "_1";
	str2 = str2 + "_2";
	std::ifstream file1(str1);
	std::ifstream file2(str2);
	char temp1, temp2;
	file1 >> temp1;
	file2 >> temp2;
	if (!file1.eof())
	{
		AVLTree<T>* new_tree = new AVLTree<T>;
		new_tree->set_root(load_tree<T>(&file1));
		(new_tree->get_height_tree())->reset_root(load_height_point(&file2));
		file1.close();
		file2.close();
		return new_tree;
	}
	else
	{
		return NULL;
	}
}

template <class T> int tree_point_height(TreePoint<T>* point_ptr)
{
	if (point_ptr == NULL)
	{
		return 0;
	}
	int left_height, right_height;
	left_height = tree_point_height(point_ptr->left_pointer);
	right_height = tree_point_height(point_ptr->right_pointer);
	int local_height = left_height >= right_height ? left_height : right_height;
	return local_height + 1;
}

template <class T> class MyQueue
{
private:
	LinkedPoint<T>* start_point;
	LinkedPoint<T>* final_point;
public:
	MyQueue(const T new_data)
	{
		LinkedPoint<T>* new_start_point = new LinkedPoint<T>(new_data);
		start_point = final_point = new_start_point;
	}
	bool push(T push_data)
	{
		LinkedPoint<T>* push_point = new LinkedPoint<T>(push_data);
		if (final_point != NULL)
		{
			final_point->assert_next(push_point);
			final_point = push_point;
			return true;
		}
		else
		{
			final_point = push_point;
			start_point = final_point;
			return true;
		}
	}
	T pop()
	{
		if (start_point != NULL)
		{
			T pop_data = start_point->get_data();
			LinkedPoint<T> temp = start_point;
			start_point = start_point->get_next_pointer();
			delete temp;
			return pop_data;
		}
		else
		{
			return NULL;
		}
	}
	~MyQueue()
	{
		LinkedPoint<T>* temp = this->first_pointer;
		LinkedPoint<T>* temp_next;
		while (temp != NULL)
		{
			temp_next = temp->get_next_pointer();
			delete temp;
			temp = temp_next;
		}
		std::cout << "~MyQueue end" << std::endl;
	}
};

template <class T> std::ostream& operator << (std::ostream& out, LinkedPoint<T>& linked_point)
{
	std::cout << linked_point.data << std::endl;
	return std::cout;
}

template <class T> std::ostream& operator << (std::ostream& out, LinkedList<T>& linked_list)
{
	LinkedPoint<T>* temp = linked_list.first_pointer;
	while (temp != NULL)
	{
		std::cout << *temp;
		temp = temp->get_next_pointer();
	}
	return std::cout;
}

template <class T>std::ostream& operator << (std::ostream& out, TreePoint<T>& linked_list)
{
	out << linked_list.data << std::endl;
	return out;
}

template <class T> void tree_to_mat(TreePoint<T>* tree_point, char** char_mat, int h, int col_start_point,
	int col_final_point)
{
	if (tree_point != NULL)
	{
		int k, j;
		int left_start_point = -1, left_final_point = -1, right_start_point = -1, right_final_point = -1;
		TreePoint<T>* const temp = tree_point;
		T temp_data = tree_point->get_data();
		char* char_data = data_to_chars(temp_data, 2);
		for (k = col_start_point, j = 0; k <= col_final_point; k++, j++)
		{
			char_mat[h][k] = char_data[j];
		}
		delete[] char_data;
		if (temp->get_left_pointer() != NULL)
		{
			TreePoint<T>* left_temp = temp->get_left_pointer();
			T left_data = left_temp->get_data();
			if (left_temp->get_right_pointer() != NULL)
			{
				TreePoint<T>* left_right_pointer = left_temp->get_right_pointer();
				int left_right_width = tree_point_width(left_right_pointer) + 1;
				left_right_width += 1;
				left_final_point = col_start_point - 1 - left_right_width;
				left_start_point = left_final_point - get_cout_length(left_data) + 1;
				char_mat[h + 1][left_final_point + 1] = '/';
				int n;
				for (n = left_final_point + 2; n < col_start_point; n++)
				{
					char_mat[h][n] = '*';
				}
			}
			else
			{
				left_final_point = col_start_point - 2;
				char_mat[h + 1][col_start_point - 1] = '/';
				left_start_point = left_final_point - get_cout_length(left_data) + 1;
			}
		}

		if (temp->get_right_pointer() != NULL)
		{
			TreePoint<T>* right_temp = temp->get_right_pointer();
			T right_data = right_temp->get_data();
			if (right_temp->get_left_pointer() != NULL)
			{
				TreePoint<T>* right_left_pointer = right_temp->get_left_pointer();
				int right_left_width = tree_point_width(right_left_pointer) + 1;
				right_left_width += 1;
				right_start_point = col_final_point + 1 + right_left_width;
				right_final_point = right_start_point + get_cout_length(right_data) - 1;
				char_mat[h + 1][right_start_point - 1] = '\\';
				int n;
				for (n = col_final_point + 1; n < right_start_point - 1; n++)
				{
					char_mat[h][n] = '*';
				}
			}
			else
			{
				char_mat[h + 1][col_final_point + 1] = '\\';
				right_start_point = col_final_point + 2;
				right_final_point = right_start_point + get_cout_length(right_data) - 1;
			}
		}

		tree_to_mat(temp->get_left_pointer(), char_mat, h + 2, left_start_point, left_final_point);
		tree_to_mat(temp->get_right_pointer(), char_mat, h + 2, right_start_point, right_final_point);
	}
}

template <class T>std::ostream& operator << (std::ostream& out, BinarySearchTree<T>* tree_root)
{
	TreePoint<T>* temp = tree_root->get_root();
	if (tree_root->root == NULL)
	{
		return out;
	}
	int tree_h = tree_root->height();
	int mat_w = tree_root->width();
	int mat_h = 2 * tree_h - 1;
	char** cout_mat = new char* [mat_h];
	int i, j;
	for (i = 0; i < mat_h; i++)
	{
		cout_mat[i] = new char[mat_w];
		for (j = 0; j < mat_w; j++)
		{
			cout_mat[i][j] = ' ';
		}
	}
	int start_point, final_point;
	if (temp != NULL)
	{
		TreePoint<T>* temp_left = temp->get_left_pointer();
		if (temp_left != NULL)
		{
			start_point = tree_point_width(temp_left) + 1;
		}
		else
		{
			start_point = 0;
		}
	}
	final_point = start_point + get_cout_length(temp->get_data()) - 1;
	tree_to_mat(temp, cout_mat, 0, start_point, final_point);
	for (i = 0; i < mat_h; i++)
	{
		for (j = 0; j < mat_w; j++)
		{
			out << cout_mat[i][j];
		}
		out << std::endl;
	}
	for (i = 0; i < mat_h; i++)
	{
		delete[] cout_mat[i];
	}
	delete[] cout_mat;
	return out;
}

template <class T> int tree_width(BinarySearchTree<T>* tree_root)
{
	return tree_point_width(tree_root->root);
}

template <class T> int tree_point_width(TreePoint<T>* tree_point)
{
	if (tree_point == NULL)
	{
		return 0;
	}
	int left_width;
	int right_width;
	left_width = tree_point_width(tree_point->left_pointer);
	right_width = tree_point_width(tree_point->right_pointer);
	int num = 2;
	if (tree_point->get_left_pointer() == NULL)
	{
		num -= 1;
	}
	if (tree_point->get_right_pointer() == NULL)
	{
		num -= 1;
	}
	int local_width = left_width + right_width + num + get_cout_length(tree_point->get_data());
	return local_width;
}

template <class T> std::ostream& operator << (std::ostream& out, const DoubleLinkedList<T>* double_list)
{
	DoubleLinkedPoint<T>* temp = double_list->start_point;
	while (temp != NULL)
	{
		out << temp->get_data() << std::endl;
		temp = (DoubleLinkedPoint<T>*)temp->get_next_pointer();
	}
	return out;
}
#endif