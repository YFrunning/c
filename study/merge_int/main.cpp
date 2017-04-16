#include<iostream>
using namespace std;
void merge1(int *str,int *str1,int len,int len1)
{
	if(str == NULL || str1 == NULL || len < 0|| len1  < 0) return ;
    int length = len + len1-1;
	int *string = new int[length]; 
	int i = 0;
	while(*str != 0 && *str1 != 0)
	{
          if(*str > *str1)
		  {
			  string[i++] = *str1++;
		  }
		  else 
		  {
			  string[i++] = *str++;
		  }
		  
	}
	while(*str != 0)
	{
		string[i++] = *str++;
	}
	while(*str1 != 0)
	{
		string[i++] = *str1++;
	}
	string[i] = 0;
	i = 0;
	while(string[i] != 0)
	{
         cout<<string[i]<<" ";
		 ++i;
	}
	
	delete [] string;
}
void merge2(int *str,int *str1)
{
	if(str == NULL || str1 == NULL) return ;
     int len  = 0;
	 int len1 = 0;
	int m = 0;
	while(str[m] != 0)
	{
		++len;
		m++;
	}
	m = 0;
	while(str1[m] != 0)
	{
		++len1;
		m++;
	}
	int length = len+len1;
	int i = len-1;
	int j = len1-1;
	int k = length-1;
	while(k >= 0 && k > i)
	{
		if(str[i] > str1[j])
		{
			str[k-- ] = str[i];
			i--;
		}
		else
		{
			str[k--] = str1[j];
			j--;
		}
	}
}
int main()
{
	int str[16] = {1,3,4,6,9};
	int str1[5] = {2,5,6};
	int len = sizeof(str)/sizeof(str[0]);
	int len1 = sizeof(str1)/sizeof(str1[0]);
	//merge(str,str1,len,len1);
	merge2(str,str1);
	int i = 0;
	while(str[i] != 0)
	{
		cout<<str[i]<<" ";
		++i;
	}
	return 0;
}
