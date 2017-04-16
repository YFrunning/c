#include<iostream>
using namespace std;


二维数组查找
bool Find(int arr[4][4],int row,int colum,int number)
{
	if(arr == NULL || row < 0|| colum < 0) return false ;
	int i = 0;
	int j = colum-1;
	while(i < row && j >= 0)
	{
		if(arr[i][j] == number)
			return true;
		if(arr[i][j] < number)
			++i;
		if(arr[i][j] > number)
			--j;
	}
	return false;
}
int main()
{
	int arr[4][4] = 
	{
		{1,2,8,9},
		{2,4,9,12},
		{4,7,10,13},
		{6,8,11,15},
	};
	int colum = sizeof(arr[0])/sizeof(arr[0][0]);
	int  row= sizeof(arr)/sizeof(arr[0]);
    int ch = 0;
	while(1)
	{
	    cin>>ch;
        bool i = Find(arr,row,colum,ch);
		cout<<i<<endl;
	}
	
	
	return 0;
}
