#include<iostream>
using namespace std;

void ReplaceBlack(char *str,char *res)//str 是原来的字符串，res是再空格处添加的字符串
{
	int alllenth = 0;//空格加字符串的总数量
	int black = 0;//空格的数量
	int i = 0;
	while(str[i] != 0)
	{
		alllenth ++;
		if(str[i] == ' ')
		{
			++ black;
		}
		++i;
	}
	int reslenth = alllenth + black*2;//变换以后的总长度
	int len = 0;
	i = 0;
	while(res[i] != 0)
	{
		len++;
		++i;
	}
	while(alllenth >= 0 &&  reslenth > alllenth)
	{
		if(str[alllenth] == ' ')
		{
			i = len-1;
			while(i >= 0)
			{
				str[reslenth--] = res[i];
				--i;
			}
		}
		else
		{
			str[reslenth--] = str[alllenth];
		}
		alllenth --;
	}

}
void ReplaceBlack2(char *str) //用%20来替换空格
{
	if(str ==  NULL ) return ;
	int length = 0;//总长度
	int black = 0;//空格的数量
	int i = 0;
	while(str[i] != 0)
	{
		++length;
		if(str[i] == ' ')
			++black;
		++i;
	}
	int newlength = length + black * 2;
	char *newstr = new char[newlength];
	i = 0;
	int j = 0;
	while(str[i])
	{
		if(str[i] == ' ')
		{
			newstr[j++] = '%';
			newstr[j++] = '2';
			newstr[j++] = '0';
		}
		else
		{
			newstr[j++] = str[i];
		}
		++i;
	}
	newstr[j]= 0;
	cout<<newstr<<endl;
	delete[] newstr;
}
int main()
{
	char str[100] = "We are hanppy";
	char res[] = "%20";
	ReplaceBlack(str,res);
	cout<<str<<endl;
	ReplaceBlack2(str);
	return 0;
}
