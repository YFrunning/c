#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include <windows.h>
using namespace std;

#define  MAX 100

class MyTimer
{
public:
	MyTimer()
	{
		QueryPerformanceFrequency(&_freq);
		costTime=0.0;
	}
	void Start()
	{
		for(int i=0; i<EN_NUMER; ++i)
		{
			QueryPerformanceCounter(&_array[i]._begin);	
		}
	}
	void Stop()
	{
		for(int i=0; i<EN_NUMER; ++i)
		{
			QueryPerformanceCounter(&_array[i]._end);	
		}
	}
	void Reset()
	{
		costTime=0.0;
	}
	void showTime()
	{
		double allTime=0.0;
		for(int i=0; i<EN_NUMER; ++i)
		{
			allTime+=(((double)_array[i]._end.QuadPart-(double)_array[i]._begin.QuadPart)/(double)_freq.QuadPart);
		}
		costTime=allTime/EN_NUMER;
		costTime*=1000000;

		if((((int)costTime)/1000000) > 0)
		{
			cout<<costTime/1000000<<" s"<<endl;
		}
		else if(((int)costTime)/1000 > 0)
		{
			cout<<costTime/1000<<" ms"<<endl;
		}
		else
		{
			cout<<costTime<<" us"<<endl;
		}
	}
private:
	class Array
	{
	public:
		LARGE_INTEGER _begin;
		LARGE_INTEGER _end;
	};
	enum{EN_NUMER=5};
	LARGE_INTEGER _freq;
	double costTime;
	Array _array[EN_NUMER];
};


struct matchsucess
{
	int maleid;
	int femaleid;
};

class Person
{
public:
	Person(int id=0,int a=0,int b=0,int c=0,int d=0,int e=0,int f=0,int g=0):_id(id),_money(a),_beauity(b),
		_equaity(c),_nemoney(d),_nebeauity(e),_neequaity(f),_satisfy(g){}
	Person(const Person &src,int sa):_id(src._id),_money(src._money),_beauity(src._beauity),_equaity(src._equaity)
		,_nemoney(src._nemoney),_nebeauity(src._nebeauity),_neequaity(src._neequaity),_satisfy(sa){}

	void operator=(const Person &src)
	{
		_id = src._id;
		_money = src._money;
		_beauity= src._beauity;
		_equaity = src._equaity;
		_nemoney = src._nemoney;
		_nebeauity= src._nebeauity;
		_neequaity = src._neequaity;
		_satisfy = src._satisfy;
	}
	int _id;
	int _money;
	int _beauity;
	int _equaity;
	int _nemoney;
	int _nebeauity;
	int _neequaity;
	int _satisfy;
};

class Male;
class Cmatch;

//struct satisfypeople
//{
//	satisfypeople(Person src,int val):single(src),satisfy(val){}
//	void setval(Person src,int val)
//	{
//		single = src;
//		satisfy = val;
//	}
//	void operator=(const satisfypeople &src)
//	{
//		single = src.single;
//		satisfy = src.satisfy;
//	}
//	Person single;
//	int satisfy;
//};
class Female:public Person
{
public:
	Female(int id = 0,int a = 0,int b = 0,int c = 0,int d = 0,int e = 0,int f = 0,int g =0):Person(id,a,b,c,d,e,f,g){}
	Female(const Female &src,int sa):Person(src,sa){}
	int  calsatisfy()//计算每一个的满意度
	{
		vector<Person>::iterator it = invite.begin();
		while(it != invite.end())
		{
			int s = it->_money * _nemoney + it->_beauity * _nebeauity + it->_equaity * _neequaity;
			//msatify.push_back(Person(it->_id,it->_money,it->_beauity,it->_equaity,it->_nemoney,it->_nebeauity,it->_neequaity,s));
			msatify.push_back(Person(*it,s));
			it++;
		}
		vector<Person>::iterator it1 = msatify.begin();
		if(it1 != msatify.end())//判断该女的是否一个都没人选
		{
			int maxsatisfy = it1->_money + it1->_beauity + it1->_equaity;//自身三个属性
			int maxs = it1->_satisfy;
			 minid = it1->_id;
			it1 ++;
		    while(it1 != msatify.end())
			{
				
				if(it1->_satisfy > maxs)
				{
					maxs = it1->_satisfy;
					minid = it1->_id;
				}
				else if(it1->_satisfy == maxs) //找到满意度高的女性（可能重复）
				{
					int satify = it1->_money + it1->_beauity + it1->_equaity;//计算自身的三个属性和最大
					if(satify > maxsatisfy)//比较自身属性和id小的
					{
						maxsatisfy = satify;
						minid = it1->_id;
					}
					else if(satify == maxsatisfy)
					{
						if(it1->_id < minid)
						{
							minid = it1->_id;
						}
	
					}
				}
				it1 ++;
			}
			return minid;
		}
		return -2;
	}
	
private:
    int minid;
	vector<Person> invite; //满意数组存放的是发送邀请的男性id
	vector<Person> msatify;//自己满意的男生
	friend class Cmatch;
};

class Player:public Person
{
public:
	Player(int id,int a,int b,int c,int d,int e,int f):Person(id,a,b,c,d,e,f){}
private:
	int sex;
};
//struct satisfyval
//{
//	satisfyval(Female src,int val):single(src),satisfy(val){}
//	void setval(Female src,int val)
//	{
//		single = src;
//		satisfy = val;
//	}
//	void operator=(const satisfyval &src)
//	{
//		single = src.single;
//		satisfy = src.satisfy;
//	}
//	Female single;
//	int satisfy;
//};
class Male:public Person
{
public:
	Male(int id = 0,int a = 0,int b = 0,int c = 0,int d =0,int e =0,int f =0,int g = 0 ):Person(id,a,b,c,d,e,f,g){}
	Male(const Male &src,int sa):Person(src,sa){}
	void  calsatisfy(const Female &src)
	{
		int satisfy = src._money * _nemoney + src._beauity * _nebeauity + src._equaity * _neequaity;
		msatifmale.push_back(Female(src,satisfy));
	}
	Female& sendInvite()
	{
		vector<Female>::iterator it = msatifmale.begin();
		vector<Female>::iterator last = msatifmale.end();
		//sortbysatify();
		int msatify = msatifmale[0]._money + msatifmale[0]._beauity + msatifmale[0]._equaity;
		int minid = msatifmale[0]._id;
		int maxsa = msatifmale[0]._satisfy;
		recvInvite = msatifmale[0];//保存最终发送邀请女的信息	
		while(it != last)
		{
			if(it->_satisfy > maxsa)
			{
				maxsa = it->_satisfy;
				minid = it->_id;
				recvInvite = *it;
			}
			if(it->_satisfy == maxsa) //找到满意度高的女性（可能重复）
			{
				int satify = it->_money + it->_beauity + it->_equaity;//计算自身的三个属性和最大
				if(satify > msatify)//比较自身属性和id小的
				{
					msatify = satify;
					minid = it->_id;
					recvInvite = *it;
				}
				else if(satify == msatify)
				{
					if(it->_id < minid)
					{
                        minid = it->_id;
                       recvInvite = *it;
					}

				}
			}
			it++;
		}
	   return recvInvite;
	}
private:
	vector<Female>  msatifmale; //存放对所有女性的满意度
	Female recvInvite;
};



class Cmatch
{
public:
	void loadMaledata()
	{
		int id ,a,b,c,d,e,f;
		FILE *fr = fopen("f:\\male.txt","r");
		if(fr == NULL)
		{
			cout<<"file open error"<<endl;
			return ;
		}
		for(int i = 0;i < 100 ;++i)
		{
			fscanf(fr,"%d,%d,%d,%d,%d,%d,%d",&id,&a,&b,&c,&d,&e,&f);
			malesVec.push_back(Male(id,a,b,c,d,e,f));
		}
	}
	void loadFemaledata()
	{
		int id ,a,b,c,d,e,f;
		FILE *fr = fopen("f:\\female.txt","r");
		if(fr == NULL)
		{
			cout<<"file open error"<<endl;
			return ;
		}
		for(int i = 0;i < MAX ;++i)
		{
			fscanf(fr,"%d,%d,%d,%d,%d,%d,%d",&id,&a,&b,&c,&d,&e,&f);
			femalesVec.push_back(Female(id,a,b,c,d,e,f));
		}
	}
	void loadPlayerdata()
	{
		int id ,a,b,c,d,e,f;
		FILE *fr = fopen("f:\\players.txt","r");
		if(fr == NULL)
		{
			cout<<"file open error"<<endl;
			return ;
		}
		for(int i = 0;i < MAX ;++i)
		{
			fscanf(fr,"%d,%d,%d,%d,%d,%d,%d",&id,&a,&b,&c,&d,&e,&f);
			playersVec.push_back(Player(id,a,b,c,d,e,f));
		}
	}
	void storefemale(const Female &src,const Male &sc)
	{
		vector<Female>::iterator it = femalesVec.begin();
		while(it != femalesVec.end())
		{
			if(src._id == it->_id)
			{
				it->invite.push_back(Person(sc,0));
				break;
			}
			it ++;
		}
	}
	//针对与提出后的，那些选择该踢出女性的男性重新计算满意度
	void kickandagin()//提出样本
	{
		vector<Male>::iterator it = malesVec.begin();
		int male =  it->_id;
        while(it != malesVec.end())//在所有男子中找到已匹配男子，并且删除
		{
			if((*it)._id == ch.maleid)
			{
				male = it->_id;
				malesVec.erase(it);
		        break;
			}
			it ++;
		}
		vector<Female>::iterator it1 = femalesVec.begin();
		vector<Male> inv;
		while(it1 != femalesVec.end())//在所有女子中找到已匹配女子，并且删除
		{
			if((*it1)._id == ch.femaleid)
			{
				vector<Person>::iterator it3 = (*it1).invite.begin();
				while(it3 != (*it1).invite.end())
				{
					if(it3->_id == male)
					{
						it3++;
						continue;
					}
					inv.push_back(Male(it3->_id,it3->_money,it3->_beauity,it3->_equaity,
						it3->_nemoney,it3->_nebeauity,it3->_neequaity));
					it3 ++;
				}
				femalesVec.erase(it1);
				break;
			}
			it1 ++;
		}
		if(malesVec.size()<= 0 || femalesVec.size()<= 0)
		{
			cout<<endl;
			return ;
		}
		vector<Male>::iterator it2 = inv.begin();
		while(it2 != inv.end())
		{
			vector<Female>::iterator it3 = femalesVec.begin();
			while(it3 != femalesVec.end())
			{
				(*it2).calsatisfy(*it3);
				it3 ++;
			}

			Female recvInvite = (*it2).sendInvite(); 
			storefemale(recvInvite,*it2);
			it2 ++;
		}
	}
	
	void finalmaitch( int maleid,int femaleid) //只找到一个自己最满意的,并保存信息
	{
		ch.maleid =maleid;
		ch.femaleid = femaleid;
	}
	bool isplayer()//已经选择了自己满意的男性，看看是否是主角
	{
		return ch.maleid == -1 || ch.femaleid == -1;
	      
	}
	
	void beginmatch()
	{
		vector<Male>::iterator it = malesVec.begin();
		
		while(it != malesVec.end())//1.遍历所有男士，查看他们每一个人的心动女孩
		{
			vector<Female>::iterator it1 = femalesVec.begin();
			while(it1 != femalesVec.end())//所有男士向所有女士计算满意度
			{
                 (*it).calsatisfy(*it1);
				 it1 ++;
			}
			Female recvInvite = (*it).sendInvite(); //针对于每一个男子，遍历完所有女性后，根据满意度发送邀请
			 storefemale(recvInvite,*it);
			it++;
		}
		
		Female maless;
		//2.女性开始对向自己发起邀请的男士，开始计算满意度，选择自己满意的
		vector<Female>::iterator it1 = femalesVec.begin();
		
		
		while( it1 != femalesVec.end())//每一个女性的邀请数组(遍历数组找到自己最满意的那个男性)
		{
			int i = 0;
			int maxInvite = 0;
			vector<Female>::iterator it2 = femalesVec.begin();
			while(it2 != femalesVec.end())
			{
				int mi = (*it2).invite.size();
				if(mi >maxInvite)
				{
					maxInvite = mi;
					maless = *it2;
				}

				it2 ++;
			}
            int minid = maless.calsatisfy(); //女性已选择自己最满意的男子,已经匹配，存在匹配数组
			finalmaitch(minid,maless._id);
            bool f = isplayer();//已经选择了自己满意的男性，看看是否是主角
			if(f) //是主角匹配完成
			{
				cout<<ch.maleid<<":"<<ch.femaleid<<endl;
				break;
			}
			else
			{
				kickandagin();//提出样本,加一个操作选择该女性的男性重新选择心动女孩
				if(malesVec.size()<= 0 || femalesVec.size()<= 0)
				{
					break ;
				}
			}
			it1 = femalesVec.begin();
		}
		
	}
	void match()
	{
		vector<Player>::iterator it = playersVec.begin();
		int i = 0;
		while(it != playersVec.end()) //把每一个主角都要加进去
		{
			i++;
			cout<<"第"<<i<<"个主角加入";
			if((*it)._id == 0)//女性主角
			{
				femalesVec.push_back(Female(-1,it->_money,it->_beauity,it->_equaity,it->_nemoney,it->_nebeauity,it->_neequaity));
			     //femalesVec.push_back(Female(*it,0));
			}
			else
			{
				
				malesVec.push_back(Male(-1,it->_money,it->_beauity,it->_equaity,it->_nemoney,it->_nebeauity,it->_neequaity));
			    //malesVec.push_back(*it);
			}
			beginmatch();
			malesVec.clear();
			femalesVec.clear();
			loadMaledata();
			loadFemaledata();
			it ++;
		}
	}
private:
	vector<Male> malesVec;//Male
	vector<Female> femalesVec;//Female
	vector<Player> playersVec;//Player
	 matchsucess ch;
	friend class Male;

};

int main()
{
	MyTimer timer;
	timer.Start();
	///////////////////////////////
	Cmatch matchmember;
	matchmember.loadMaledata();
	matchmember.loadFemaledata();
	matchmember.loadPlayerdata();

	matchmember.match(); 
	/////////////////////////////////
	timer.Stop();
	timer.showTime();

	
	return 0;
}