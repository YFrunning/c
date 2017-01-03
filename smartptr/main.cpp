#include<iostream>
#include<vector>
#include<functional>
#include <algorithm>
using namespace std;

class CHeapManager
{
public:
	static CHeapManager &getIntance()
	{
		 static CHeapManager cm;
		 return cm;
	}
	void addRef(void *ptr)
	{
		vector<ResItem>::iterator it = find(_vec.begin(),_vec.end(),ptr);
		if(it == _vec.end())
		{
			_vec.push_back(ptr);
			cout<<"new res addr:"<<ptr<<" ref:"<<1<<endl;
		}
		else
		{
			it->_refcount++;
			cout<<"add res addr:"<<ptr<<" ref:"<<it->_refcount<<endl;
		}
		/*int flag = 0;
		vector<ResItem>::iterator it = _vec.begin();
		while(it != _vec.end())
		{
			if(it->_paddr == ptr)
			{
				flag = 1;
				it->_refcount++;
				cout<<"add res addr"<<ptr<<"  ref:"<<it->_refcount<<endl;
			}
			++it;
		}
		if(flag == 0)
		{
			_vec.push_back(ptr);
			cout<<"new res addr"<<ptr<<" ref"<<1<<endl;
		}*/
		
	}

	void delRef(void *ptr)
	{
		vector<ResItem> ::iterator it = find(_vec.begin(),_vec.end(),ptr);
		if(it != _vec.end())
		{
             it->_refcount--;
			 cout<<"delete res addr:"<<ptr<<" ref:"<<it->_refcount<<endl;
		}
		/*vector<ResItem>::iterator it = _vec.begin();
		while(it != _vec.end())
		{
			if(it->_paddr == ptr)
			{
				it->_refcount --;
				cout<<"delet res addr"<<ptr<<" ref:"<<it->_refcount<<endl;
			}
			++it;
		}*/
	}
	int getRef(void *ptr)
	{
		vector<ResItem>::iterator it = find(_vec.begin(),_vec.end(),ptr);
		if(it == _vec.end())
		{
			return -1;
		}
		else
		{
			return it->_refcount;
		}
		/*vector<ResItem>::iterator it = _vec.begin();   
		while(it != _vec.end())
		{
			if(it->_paddr == ptr)
			{
				return it->_refcount;
			}
			++it;
		}
		return -1;*/
	}
private:
    CHeapManager(){}
	struct ResItem
	{
		ResItem(void *paddr = NULL):_paddr(paddr),_refcount(0)
		{
			if(_paddr != NULL)
			{
				_refcount = 1;
			}
		}
		bool operator==(const ResItem &src)
		{
			return _paddr == src._paddr;
		}
		void *_paddr;
		int _refcount;
	};
	vector<ResItem> _vec;
};


class test
{
public:
	test(){cout<<"test()"<<endl;}
	~test(){cout<<"~test()"<<endl;}
	void func(){cout<<"call fun"<<endl;}
};
template<typename T>
class CSmartptr
{
public:
	CSmartptr(T *ptr = NULL):_ptr(ptr)//,owns(true){}
	{
		if(ptr != NULL)
		addRef();
	}
	~CSmartptr()
	{
		//if(owns)
		delRef();
		if(getRef() == 0)
			delete _ptr;
	}
	T &operator*(){return *_ptr;}
	const T &operator*()const{return *_ptr;}
	T* operator->(){return _ptr;}
	const T* operator->()const{return _ptr;}
	CSmartptr(const CSmartptr<T> &src):_ptr (src._ptr)
	{
		if(_ptr != NULL)
		addRef();
		
	}
	CSmartptr<T> &operator=(const CSmartptr &src)
	{
		if(this == &src )
			return *this;
		delRef();
		if(getRef() == 0)
			delete _ptr;
		_ptr = src._ptr;
	}
	void addRef()
	{
	    _heapManager.addRef(_ptr);
	}
	void delRef()
	{
	    _heapManager.delRef(_ptr);
	}
	int getRef()
	{
       return  _heapManager.getRef(_ptr);	
	}
    //   void release()const
	 //{
		// //((CSmartptr<T> *)this)->owns = false;
	 //}
private:
	//bool owns;
	T *_ptr;//auto
	static CHeapManager &_heapManager;
};
template<typename T>
CHeapManager& CSmartptr<T>::_heapManager = CHeapManager::getIntance();
int main()
{
	int *p = new int;
	CSmartptr<int> p1(p);
	CSmartptr<char> p2((char*)p);
	
	CSmartptr<double> p3((double *)p);
	//CSmartptr<int> p1(new int);//站上对象，出了函数作用域就自动析构的特点，智能指针不能出现在堆上。（智能能指针都是站上的）
	////*p1 = 100;
	//CSmartptr<test> p2(new test);
	////p2->func();
	//CSmartptr<int> p3(p1);
	return 0;
}