#include<stdio.h>
bool Find(int array[4][4],int row,int colu,int num)
{
	int i = 0;
	int j = colu -1;
	if(array == NULL || row < 0||colu < 0)
	{
		return false;

	}
	while(i < row && j >= 0)
	{
	     if(array[i][j] > num)
		   j--;
		 else if(array[i][j] < num)
			++i;
		 else return true;
	}
	return false;

}

int main()
{
	int array[4][4] = {
		{1,2,8,9},
		{2,4,9,12},
		{4,7,10,13},
		{6,8,11,15}};        
	int i = Find(array,4,4,3);
	printf("%d\n",i);
	return 0;
}
