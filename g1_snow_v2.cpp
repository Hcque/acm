//Memory  Time 
//16696K 3766MS 

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int prime=999983;  // 10n内最大的素数（本题n=10W）

class
{
public:
	int len[6];  //6瓣叶子的长度
}leaf[1000010];

typedef class HashTable
{
public:
	int len[6];   //记录6瓣叶子的长度信息
	HashTable* next;  //用于冲突时开放寻址

	HashTable()  //Initial
	{
        fill(len,len+6,0);
		next=0;
	}
}Hashtable;

Hashtable _hash[prime+1];

/*计算第k个雪花的关键字key*/

int compute_key(int k)
{
	int key=0;
	for(int i=0;i<6;i++)
	{
		key+=(leaf[k].len[i]) % prime;
		key%=prime;   //利用同余模定理计算key，避免出现大数
	}

	return ++key;  //键值后移1位，把key的范围从0~999982变为 1~999983
}

/*从顺时针方向判断两片雪花是否相同*/

bool clockwise(Hashtable* p,int k)
{
	for(int j=0;j<6;j++)  //顺时针转动j格
	{
		bool flag=true;
		for(int i=0;i<6;i++)
			if(leaf[k].len[i] != p->len[(i+j)%6])
			{
				flag=false;
				break;
			}
		if(flag)
			return true;
	}
	return false;
}

/*从逆时针方向判断两片雪花是否相同*/

bool counterclockwise(Hashtable* p,int k)
{
	for(int j=0;j<6;j++)  //逆时针转动j格
	{
		bool flag=true;
		for(int i=0;i<6;i++)
			if(leaf[k].len[i] != p->len[(5-i-j+6)%6])
			{
				flag=false;
				break;
			}
		if(flag)
			return true;
	}
	return false;
}

/*把第k个雪花信息插入HashTable*/
/*当插入的位置已存在其他雪花信息时，顺便比较*/

bool insert(int k)
{
	int key=compute_key(k);

	if(_hash[key].len[0]==0)
	{
		for(int i=0;i<6;i++)
			_hash[key].len[i]=leaf[k].len[i];

	}
	else  //地址冲突,开放寻址,顺便比较
	{
		Hashtable* temp=&_hash[key];

		if(clockwise(temp,k) || counterclockwise(temp,k))  //检查雪花是否相同
			return true;

		while(temp->next)    //寻址
		{
			temp=temp->next;

			if(clockwise(temp,k) || counterclockwise(temp,k))  //检查雪花是否相同
				return true;
		}

		temp->next=new Hashtable;    //申请空间，保存新雪花信息
		for(int i=0;i<6;i++)
			temp->next->len[i]=leaf[k].len[i];
	}
	return false;
}

int main(int i,int j)
{
	int n;  //雪花数
	while(cin>>n)
	{
		/*Initial*/

		memset(_hash,0,sizeof(_hash));  // 0 <-> NULL

		/*Input*/

		bool flag=false;  //记录输入过程中是否出现了相同的雪花
		for(i=1;i<=n;i++)
		{
			for(j=0;j<6;j++)
				scanf("%d",&leaf[i].len[j]);

			/*Hash*/

			if(!flag)    //当前还没有出现相同的雪花
				flag=insert(i);
			             //若出现相同的雪花，则还需后续输入，但不再处理
		}

		/*Output*/

		if(flag)
			cout<<"Twin snowflakes found."<<endl;
		else
			cout<<"No two snowflakes are alike."<<endl;

	}
	return 0;
}
