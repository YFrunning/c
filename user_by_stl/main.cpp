#include<iostream>
#include<string.h>
#include<functional>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace  std;

template <typename Container>
void show(Container &cop)
{
	Container::iterator it = cop.begin();
	for(;it != cop.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
template <typename Container>
void show_reverse(Container &cop)
{
	Container::reverse_iterator rit = cop.rbegin();
	for(;rit != cop.rend();++rit)
	{
		cout<<*rit<<" ";
	}
	cout<<endl;
}
int main()
{
	vector<int> vec;
	for(int i = 0;i < 10;++i)
	{
		vec.push_back(rand() %100);
	}
	show(vec);
	show_reverse(vec);
	vector<int>::iterator it = vec.begin();
	vector<int>::iterator re = find(it,vec.end(),64);
    if(re == vec.end())
	{
		cout<<"find not it "<<endl;
	}
	else
	{
		cout<<"find  it"<<*re<<endl;
	}
	sort(vec.begin(),vec.end());//默认从小到大
	show(vec);
	sort(vec.begin(),vec.end(),greater <int>()); //根据第三个参数，将序列从大到小排序
	show(vec);
	vector<int>::iterator rea = find_if(vec.begin(),vec.end(),bind1st(greater<int>(),50)); //找到第一个小于50的数
	if(rea == vec.end())
	{
		cout<<"find not it "<<endl;
	}
	else
	{
		cout<<"find  it "<<*rea<<endl;
		vec.insert(rea,50);
		show(vec);
	}
	cout<<"==================="<<endl;
	vector<int>::iterator rea1 = find_if(vec.begin(),vec.end(),not1(bind1st(greater<int>(),50)));
	cout<<*rea1<<endl;
	cout<<"=================="<<endl;
	vector<int> vec1;
	copy(vec.rbegin(),vec.rend(),back_inserter(vec1));
	show(vec1);

	rea = find_if(vec1.begin(),vec1.end(),bind1st(less<int>(),40));
	if(rea == vec1.end())
	{
		cout<<"find not it "<<endl;
	}
	else
	{
		cout<<"find  it"<<*rea<<endl;
        vec1.erase(rea);
		show(vec1);
	}
	rea = find_if(vec1.begin(),vec1.end(),bind1st(less_equal<int>(),20));
	re = find_if(vec1.begin(),vec1.end(),bind1st(less_equal<int>(),60));
	vec1.erase(rea,re);
	show(vec1);
	vector<int> vec2;
	for(int i = 0;i < 100;++i)
	{
		vec2.push_back(rand()%10);
	}
	show(vec2);
	cout<<endl;
	vector<int> ::iterator it1 = vec2.begin();
	while(it1!=vec2.end())
	{
		re = find(it1,vec2.end(),9);
		if(re != vec2.end())
		{
			vec2.erase(re);
		}
	    ++it1; 
	}
	show(vec2);
	return 0;
	
}