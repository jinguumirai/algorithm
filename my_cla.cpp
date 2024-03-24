#include<iostream>
#include<cmath>
#include"my_class.hpp"

using namespace std;

double double_round(const double double_value, const int acc)
{
	int factor;
	if (double_value >= 0)
	{
		factor = 1;
	}
	else
	{
		factor = -1;
	}
	int k = 1;
	int i;
	for (i = 0; i < acc; i++)
	{
		k *= 10;
	}
	double copy_value = abs(double_value * k);
	int x = (int)copy_value;
	if (copy_value - x >= 0.5)
	{
		x += 1;
	}
	double return_value = double(x) / k;
	return return_value * factor;
}

int string_length(const char* string)
{
	int k = 0;
	while (string[k] != '\0')
	{
		k++;
	}
	return k;
}

char* string_cat(const char* str1, const char* str2)
{
	int str1_len = string_length(str1);
	int str2_len = string_length(str2);
	char* cat_str = new char[str1_len + str2_len + 1];
	int i;
	int k = 0;
	for (i = 0; i < str1_len; i++, k++)
	{
		cat_str[k] = str1[i];
	}
	for (i = 0; i < str2_len; i++, k++)
	{
		cat_str[k] = str2[i];
	}
	cat_str[k] = '\0';
	return cat_str;
}

TreePoint<int>* load_height_point(std::ifstream* file)
{
	TreePoint<int>* new_point = new TreePoint<int>;
	char temp;
	char Num[350];
	int k = 0;
	(*file) >> temp;
	if (temp == '[')
	{
		new_point->set_left_point(load_height_point(file));
		(*file) >> temp;
	}

	if ((temp <= '9' && temp >= '0') || temp == '.' || temp == '-')
	{

		while ((temp <= '9' && temp >= '0') || temp == '.' || temp == '-')
		{
			Num[k] = temp;
			k++;
			(*file) >> temp;
		}
		Num[k] = '\0';
		std::string str(Num);
		new_point->set_data(std::stoi(str));
	}

	if (temp == '[')
	{
		new_point->set_right_point(load_height_point(file));
	}
	if (temp != ']')
	{
		(*file) >> temp;
	}
	return new_point;
}

