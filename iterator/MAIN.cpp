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
		bool operator==(const Iterator &src)
		{
			return ptr == src.ptr;
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
template <typename T>
class Mygreat
{
public:
	bool operator()(T a,T b)
	{
		return a>b;
	}
};
template <typename T>
class Myless
{
public:
	bool operator()(T a,T b)
	{
		return a<b;
	}
};
//======================�����㷨��ð������===========================
template <typename Iputiterator,typename Compare>
void sort(Iputiterator first,Iputiterator last,Compare comp)
{
	int n = last - first;
	for(int i = 0; i< n-1;++i)
	{
		for(int j  = 0; j < n-1-i;++j)
		{
			if(comp(first[j] , first[j+1]))
			{
				Iputiterator ::value_type tmp = first[j];
				first[j] = first[j+1];
				first[j+1] = tmp;
			}
		}
	}
}

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
//==================������ʹ��=====================================

//�󶨵�һ������
template<typename Compare,typename T>
class _blidlst
{
public:
	typedef T value_type;
	_blidlst(Compare &cp,T a):comp(cp),mval(a){}
	bool operator()(T val)
	{
		return comp(val,mval);
	}
private:
	Compare &comp;
	T mval;
};
template<typename Compare,typename T>
_blidlst<Compare ,T> blindlst(Compare &comp,const T &val)
{
     return _blidlst<Compare, T>(comp,val);
}
//�󶨵ڶ�������
template<typename Compare,typename T>
class _blid2nd
{
public:
	_blid2nd(Compare &cp,T a):comp(cp),mval(a){}
	bool operator()(T val)
	{
		return comp(mval,val);
	}
private:
	Compare &comp;
	T mval;
};
template<typename Compare,typename T>
_blid2nd<Compare ,T> blind2nd(Compare &comp,const T &val)
{
	return _blid2nd<Compare, T>(comp,val);
}

//һԪ����ȡ����
template<typename Compare>
class _not1
{
public:
	typedef typename Compare:: value_type  T;
	_not1(Compare &cp):comp(cp){}
	bool operator()(T val)
	{
		return  !comp(val);
	}
private:
	Compare &comp;
};
template<typename Compare>
_not1<Compare> not1(Compare &comp)
{	
	return _not1<Compare>(comp);
}
//======================�����㷨find_if(������Ѱ��)===========================
template <typename IputIterator,typename Compare>
IputIterator find_if(IputIterator first,IputIterator last,Compare comp)
{
	while(first != last)
	{
		if(comp(*first))
		   return first;
		++first ;
	}
	return last;
}
//======================�����㷨find��Ѱ��ĳֵ��===========================
template <typename IputIterator,typename T>
IputIterator find(IputIterator first,IputIterator last,const T &val)
{
	/*int n = last - first;
	for(int i = 0;i < n; ++i)
	{
		if(val == *first)
		{
			return first;
		}
		first ++;
	}*/
	while(first != last)
	{
		if(val == *first)
		   return first;
		++first ;
	}
	return last;
}
template <typename Contener>
void show(Contener &con)
{
	Vector<int>::Iterator it = con.begin();
	for(; it != con.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
//struct Node
//{
//	Node* prv;
//	Node* next;
//	int data;
//
//	Node(const int d = 0):prv(0),next(0),data(d){}
//};

int main()
{
	/*Vector<Node> v;
	v.push_back(Node(1));
	v.push_back(Node(2));
	v.push_back(Node(3));

	Vector<Node>::reserve_iterator it1 = v.rbegin();
	
	while(it1 != v.rend())
	{
		cout<<it1->data<<" ";
		++it1;
	}*/
	Vector<int> vec;
	for(int i = 0;i<10;++i)
	{
		vec.push_back(rand()%100);
	}
	cout<<vec<<endl;

	Vector<int>::Iterator it = vec.begin();
	show(vec);
	//���������д�С��������
	sort(vec.begin(),vec.end());
	//���������  ��С����
	show(vec);
	Vector<int>::reserve_iterator rit = vec.rbegin();
	while(rit != vec.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
	cout<<"====================�����㷨 find========================="<<endl;
	Vector<int>::Iterator it1 =  find(vec.begin(),vec.end(),34);
	if(it1 == vec.end())
	{
		cout<<"not find "<<endl;
	}
	else
	{
		cout<<"find val:"<<*it1<<endl;
	}
    cout<<"=================�����㷨�� sort����������==========================="<<endl;
	Mygreat<int> mg;
	sort(vec.begin(),vec.end(),mg);
	show(vec);
	Myless<int> ml;
	sort(vec.begin(),vec.end(),ml);
	show(vec);

	cout<<"================�����㷨find_if��ʵ�ְ��������ң�==========================="<<endl;
    //bindlst �󶨵�һ�����������ڶ�������
    //bind2nnd �󶨵ڶ�������������һ������
	show(vec);
	Vector<int>::Iterator it2 =  find_if(vec.begin(),vec.end(),blindlst(Myless<int>(),60));
	cout<<*it2<<endl;
	
	it2 =  find_if(vec.begin(),vec.end(),blind2nd(Mygreat<int>(),60));
	cout<<*it2<<endl;
    cout<<"=========ȡ����==============="<<endl;
	it2 =  find_if(vec.begin(),vec.end(),not1(blindlst(Myless<int>(),60)));
	cout<<*it2<<endl;
	return 0;
}
