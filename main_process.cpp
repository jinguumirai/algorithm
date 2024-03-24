#include<iostream>
#include<cmath>
#include"my_fun.hpp"
#include<random>
#include<io.h>
#include<direct.h>
#include<iomanip>
#include<fstream>
#include"my_class.hpp"

using namespace std;


int main()
{
	AVLTree<double> tree(1.2);
	tree.assert(1.6);
	tree.assert(1.5);
	tree.assert(2.6);
	tree.assert(-1.2);
	tree.assert(-1.9);
	tree.assert(-3.5);
	tree.assert(3.72);
	tree.assert(-1.43);
	tree.delete_data(-1.2);
	cout << &tree;
	tree.save("AVLtree");
	AVLTree<double>* new_tree = load_avl<double>("AVLtree");
	cout << new_tree->get_height_tree()->get_root()->get_right_pointer()->get_data();
	return 0;
}