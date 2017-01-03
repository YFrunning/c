#include<iostream>
using namespace std;

#define MAX_ALLOC 128

template<typename T>
class Queue
{
public:
	Queue()
	{
		_prear = _pfirst = new QueueItem();
	}
	~Queue()
	{
		QueueItem  * pcur = _pfirst;
		while (_pfirst != _prear)
		{
			_pfirst = _pfirst->_pnext;
			delete   pcur;
			pcur = _pfirst;
		}
		delete _pfirst;
	}
	void addQue(const T &val);
	void delQue();
	T top();
	bool empty()const;
	void show()
	{
		if (empty())
		{
			cout<<"is empty"<<endl;
			return ;
		}
     QueueItem *p = _pfirst;
	 while(p != _prear)
	 {
		 cout<<p->_data<<" ";
		 p = p->_pnext;
	 }
	 cout<<p->_data<<endl;
	}
private:
	// new QueueItem   delete QueueItem    new int delete int
	class QueueItem
	{
	public:
		QueueItem(T data=T()):_data(data),_pnext(NULL){};
		~QueueItem(){}

		//所以，这两个函数编译器默认就处理成static函数 对象不存在
		void* operator new(size_t size)
		{
			int alloc_size = MAX_ALLOC *size;
			QueueItem *pcur = _pfreelist;
			if(_pfreelist == NULL)
			{
				_pfreelist = (QueueItem *)new char[alloc_size];
				for(pcur = _pfreelist;pcur< _pfreelist+MAX_ALLOC-1;++pcur)
				{
					pcur->_pnext = pcur+1;
				}
				pcur = NULL;
			}
			pcur = _pfreelist;
			_pfreelist = _pfreelist->_pnext;
			return pcur;
		}
		void operator delete(void *ptr)
		{
			if(ptr == NULL)
			   return ;
			QueueItem *pcur = (QueueItem *)ptr;
			pcur->_pnext = _pfreelist;
			_pfreelist = pcur;
		}

		T _data;
		QueueItem *_pnext;
		static QueueItem *_pfreelist; //共有 类外初始化
	};
	QueueItem *_pfirst;
	QueueItem *_prear;
};

template<typename T>
typename Queue<T>::QueueItem  *Queue<T>::QueueItem::_pfreelist = NULL ;
template<typename T>
void Queue<T> ::addQue(const T &val)
{
	QueueItem *p = new QueueItem(val);  // QueueItem()
	if (_prear == NULL)
	{   
		_prear = p;
		_pfirst = p;
		
		return ;
	}
	_prear ->_pnext = p;
	_prear = p;

}
template<typename T>
void Queue<T> :: delQue()
{
	if (_prear == _pfirst)
	{
		delete _pfirst;
		_pfirst = NULL;
		_prear = NULL;
		return ;
	}
    QueueItem *p = _pfirst;
	_pfirst = _pfirst->_pnext;
	delete p;  // ~QueueItem
}
template<typename T>
T Queue<T>::top()
{
	/*if (empty())
	{
		return 
	}*/
	return _pfirst->_data;
}
template<typename T>
bool Queue<T>::empty()const
{
    if (_pfirst == NULL || _prear == NULL)
    {
		return true;
    }
	return false;
}
int main()
{
	//  100000QueueItem的节点
    Queue<int> queue;
	queue.addQue(10);
    queue.addQue(20);
	queue.addQue(30);
	queue.addQue(40);   // malloc   free
	queue.delQue();
    queue.delQue();
	queue.delQue();
	queue.delQue();
	queue.show();
	return 0;
}

