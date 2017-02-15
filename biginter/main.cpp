#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

class BigInteger
{
public:
	BigInteger(string &number):_number(number){}
private:
	string &_number;
	friend BigInteger operator+(const BigInteger &left, const BigInteger &right);
	friend BigInteger operator-(const BigInteger &left, const BigInteger &right);
	friend ostream & operator<<(ostream &out,const BigInteger &src);
};
BigInteger operator+(const BigInteger &left, const BigInteger &right)
{
	
	int len1 = left._number.length();
	int len2 = right._number.length();
	stack<char> res;
	int num = 0;
	int flag = 0 ;
    if(len1 == len2)
	{
		for(int i = len1-1; i >= 0; --i)
		{
			num = left._number[i]-'0'+right._number[i]- '0'+ flag;
			if(num >= 10 )
			{
				res.push( num - 10 + '0');
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0');
			}
		}
	}
	else
	{
		int j = len1-1;
		int i = len2-1;
		for( i = len1-1,j = len2-1; i >= 0 && j >= 0; --i,--j)
		{
			num = left._number[i]-'0'+right._number[j]- '0'+ flag;
			if(num >= 10 )
			{
				res.push( num - 10 + '0');
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0');
			}
		}
		while(i <j) //right元素多
		{
			num = right._number[j]- '0'+ flag;
			if(num >= 10 )
			{
				res.push( num - 10 + '0');
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0');
			}
			j --;
		}
		while(i >j)
		{
			num = left._number[i]- '0'+ flag;
			if(num >= 10 )
			{
				res.push( num - 10 + '0');
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0');
			}
			i --;
		}

	}
	static string sr;
	if(flag == 1)
	{
		sr.push_back(flag+'0');
	}
	while(!res.empty())
	{
		sr.push_back(res.top());
		res.pop();
	}
	return BigInteger(sr);
	
}
BigInteger operator-(const BigInteger &left, const BigInteger &right)
{
	int len1 = left._number.length();
	int len2 = right._number.length();
	stack<char> res;
	int num = 0;
	int flag = 0;
	int f = 0;
	if(len1 == len2 )
	{
		int i = len1-1;
		while(i >= 0&&left._number[i] == right._number[i]   )
		{
			 i --;
		}
		if(i < 0)
		{
			return BigInteger(string("0"));
		}
		else  
		{
			if(left._number[i] < right._number[i])
			{
				f = -1;
				string tmp = left._number;
				left._number = right._number;
				right._number  = tmp;
				int ltmp = len1;
				len1 = len2;
				len2 = ltmp;
			}
			
		}
		for( i = len1-1; i >= 0; --i)
		{
			int num1 = left._number[i]-'0';
			int num2  = right._number[i]- '0';
			num = num1-num2- flag;
			if(num < 0 )
			{
				res.push( 10+left._number[i]-'0' - right._number[i]);
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0');
			}
		}
	}
	else
	{
		if(len1 < len2)
		{
			 f = -1;
			 string tmp = left._number;
			 left._number = right._number;
			 right._number  = tmp;
			 int ltmp = len1;
			 len1 = len2;
			 len2 = ltmp;
		}
		int j = 0;
		int i = 0;
		for(i = len1-1,j = len2-1; i >= 0 &&j >= 0; --i,--j)
		{
			int num1 = left._number[i]-'0';
			int num2  = right._number[j]- '0';
			num = num1- num2 - flag;
			if(num < 0 )
			{
				res.push( 10+num1 - num2 - flag +'0');
				flag = 1;
			}
			else
			{
				flag = 0;
				res.push(num+'0'-flag);
			}
		}
		while(i >= 0)
		{
			int num = left._number[i]-flag-'0';
			if(num < 0 )
			{
				if(left._number[i]-'0'==0)
				{
					res.push( 10+'0'-flag);
					flag = 1;
				}
				else
				{
					res.push( 10+'0'-flag);
					flag = 1;
				}	
			}
			else
			{
				flag = 0;
				res.push(num+'0'-flag);
			}
			--i;
		}
	}
	static string sr;
	int iszero = 0;
	if(f == -1)
	{
        sr.push_back('-');
	}
	while(!res.empty())
	{
		int no = res.top();
		if(no == '0' && iszero == 0)
		{
		    res.pop();
		}
		else
		{
			iszero ++;
            sr.push_back(res.top());
		    res.pop();
		}
	}
	return BigInteger(sr);

}
ostream & operator<<(ostream &out,const BigInteger &src)
{
	out<<src._number<<endl;
	return out;
}
int main()
{
	/*
	连续借位：10000-9= 9991；
	连续进位：9999+1= 10000;
	大数加法：23761798265789632409851927836478916279384+6756857986094375190283749126412347861297834=
	          6780619784360164822693601054248826777577218
	大数减法：7892136478712036589789347438971627836487125478-907987897213894782174234=
	          7892136478712036589788439451074413941704951244
	*/
	string le = "7892136478712036589789347438971627836487125478";
	string ri = "907987897213894782174234";
	BigInteger left(le);
	BigInteger right(ri);
	BigInteger res = left+right;
	BigInteger resl = left-right;
	cout<<res<<endl;
	cout<<resl<<endl;
    return 0;
}