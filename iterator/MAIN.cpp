#include<iostream>
#include<vld.h>
using namespace std;

template <typename iterator>
class reserve_iterator
{
public:
	reserve_iterator(iterator p = iterator()):it(p){}
	bool operator!= (const reserve_iterator &src)//vec.rend();
	{
		return it  != src.it;
	}
	typename iterator::value_type &operator*()
	{
		return *it;
	}
	typename iterator::value_type* operator->()
	{
		return &(*it);//it
	}
	reserve_iterator &operator++()
	{
		--it;
		return *this;
	}
	typename iterator::value_type& operator[](int i)
	{
		return it[i];
	}
	reserve_iterator& operator--()
	{
		++it;
		return *this;
	}

private:
	iterator it;
};
template <typename T>
class Vector
{
public:
	
	Vector()
	{
		mfirst = NULL;
		mend = 0;
		mlast = 0;
	}
	Vector(int num,T value = T())
	{
		mfirst = new T[num];
		mend = mlast = num;
		for(int i= 0;i < num; ++i)
		{
			mfirst[i] = value;
		}
	}
	~Vector(){delete []mfirst;mfirst = NULL;}
	void push_back(const T &val)
	{
		if(mend == mlast)
			resize();
		mfirst[mlast++] = val;
	}
	void pop_back()
	{
		if(mlast == 0)
			return ;
		--mlast;
	}
	
	class Iterator
	{
	public:
		typedef T value_type;
		Iterator(T *p = NULL):ptr(p){}
		bool operator!= (const Iterator &it)
		{
			return ptr != it.ptr;
		}
		Iterator& operator++()
		{
			++ptr;
			return *this;
		}
		Iterator& operator--()
		{
			--ptr;
			return *this;
		}
		int  operator-(const Iterator &src)
		{
			return ptr - src.ptr;
		}
		T& operator*()
		{
			return *ptr;
		}
		T& operator[](int i)
		{
			return ptr[i];
		}
		T* operator->()
		{
			return ptr;
		}
	protected:
		T *ptr;
	};
	typedef reserve_iterator<Iterator>  reserve_iterator;
	reserve_iterator rbegin()
	{
		return --end();
	}
	reserve_iterator rend()
	{

		return --begin();
	}
	Iterator begin()
	{
		return mfirst;
	}
	Iterator end()
	{
		return Iterator(mfirst+mlast);
	}
private:
	void resize()
	{
		if(mfirst == NULL)
		{
			mfirst = new T[1];
			mend = 1;
			mlast = 0;
		}
		else
		{
			mend *= 2;
			T *p = new T[mend];
			memcpy(p,mfirst,sizeof(T)*mend);
			delete []mfirst;
			mfirst = p;
		}
	}
	T *mfirst;
	int mend;
	int mlast;
    
	friend  ostream & operator<<<T>(ostream &out,const Vector<T> &src);
};
template <typename Iputiterator>
void sort(Iputiterator first,Iputiterator last)
{
	int n = last - first;
	for(int i = 0; i< n-1;++i)
	{
		for(int j  = 0; j < n-1-i;++j)
		{
            if(first[j] < first[j+1])
			{
				Iputiterator ::value_type tmp = first[j];
				first[j] = first[j+1];
				first[j+1] = tmp;
			}
		}
	}
}
template <typename T>
ostream & operator<<(ostream &out,const Vector<T> &src)
{
	for(int i = 0;i < src.mlast;++i)
	{
		out<<src.mfirst[i]<<" ";
	}
	return out;
}

struct Node
{
	Node* prv;
	Node* next;
	int data;

	Node(const int d = 0):prv(0),next(0),data(d){}
};

int main()
{
	Vector<Node> v;
	v.push_back(Node(1));
	v.push_back(Node(2));
	v.push_back(Node(3));

	Vector<Node>::reserve_iterator it1 = v.rbegin();
	
	while(it1 != v.rend())
	{
		cout<<it1->data<<" ";
		++it1;
	}
	Vector<int> vec;
	for(int i = 0;i<10;++i)
	{
		vec.push_back(rand()%100);
	}
	cout<<vec<<endl;

	Vector<int>::Iterator it = vec.begin();
	for(; it != vec.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	//对容器进行从小到大排序
	sort(vec.begin(),vec.end());
	//正向迭代器  从小到大
	for(it = vec.begin(); it != vec.end(); ++it)
	{
		cout<<*it<<" ";  //it->length();
	}
	cout<<endl;
	Vector<int>::reserve_iterator rit = vec.rbegin();
	while(rit != vec.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
	return 0;
}
