#include<iostream>
#include"common_func.hpp"

int get_length(const char* str)
{
	int len = 0;
	char x = str[len];
	while (x != '\0')
	{
		len += 1;
		x = str[len];
	}
	return len;
}

void str_cat(const char* str1, const char* str2, char* const str)
{
	int len1 = get_length(str1);
	int len2 = get_length(str2);
	int i, j;
	j = 0;
	for (i = 0; i < len1; i++, j++)
	{
		str[j] = str1[i];
	}
	for (i = 0; i < len2; i++, j++)
	{
		str[j] = str2[i];
	}
	str[j] = '\0';
}