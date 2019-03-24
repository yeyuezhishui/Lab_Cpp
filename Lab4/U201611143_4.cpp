#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

FILE *fp;
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	virtual int  size() const;		//返回栈的最大元素个数max
	virtual  operator int() const	//返回栈的实际元素个数pos
	{
		return pos;
	}
	virtual int operator[] (int x) const;	//取下标x处的栈元素
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e); 	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;		//打印栈
	virtual ~STACK();				//销毁栈
};

//初始化栈
STACK::STACK(int m) :max(m), elems(new int[m]) {
	pos = 0;
}

//用栈s初始化p指向的栈

STACK::STACK(const STACK &s) : max(s.max), elems(new int[s.max]) {
	pos = s.pos;
	*this = s;
}

//返回栈的最大元素个数max
int  STACK::size() const {
	return max;
}


//取下标x处的栈元素
int  STACK::operator[](int x) const
{
	if (x > pos)
	{
		//printf("超过了最大下标！\n");
		fputs("E ", fp);
		return 0;
	}
	return elems[x];
}


//将e入栈,并返回栈
STACK& STACK::operator<<(int e)
{
	if (pos == max)
	{
		//printf("堆栈已满，无法插入新元素");
		return *this;
	}
	elems[pos] = e;
	pos++;
	return *this;
}

STACK& STACK::operator>> (int &e)
{
	if (pos != 0)
	{
		e = elems[pos - 1];
		pos--;
	}
	else
	{
		printf("E  ");
		fputs("E ", fp);
	}
	return *this;
}


STACK& STACK::operator=(const STACK&s)
{
	int i;
	for (i = 0; i<s.pos && i<this->max; i++)
	{
		elems[i] = s.elems[i];
	}
	pos = i;
	return *this;

}


void STACK::print() const
{
	int i;
	if (pos == 0)
	{
		fputs("E ", fp);
		return;
	}
	for (i = 0; i < pos; i++)
	{
		printf("%d  ", elems[i]);
		fprintf(fp, "%d  ", elems[i]);
	}

}

STACK::~STACK()
{
	delete elems;
}


class QUEUE: public STACK {
	STACK s2;
public:
	QUEUE(int m);		//初始化循环队列：elems有m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int() const {
		return s2 + STACK::operator int();
	}
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
	virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};

//初始化队列
QUEUE::QUEUE(int m) :STACK(m), s2(m) {
	return;
}

//用队列s初始化p指向的队列
QUEUE::QUEUE(const QUEUE &s) : STACK(s.STACK::size()), s2(s.s2.size()) {
	*this = s;
}

//判断队列是否满
int  QUEUE::full() const {
	if (s2 == s2.size() && STACK::operator int() == STACK::size())
	{
		return 1;
	}
	return 0;
}


//取下标x处的队列元素
int  QUEUE::operator[](int x) const
{
	if ((this->STACK::operator int() + s2 == 0) || (x > (s2.size() * 2 - 1)) ){
				printf("E  ");
				fputs("E  ",fp);
				exit(1);
	}
	
	if (s2 == 0)
	{
		return this->STACK::operator[](x);
	}
	else
	{
		if (x >= s2)
		{
			return this->STACK::operator[](x - s2);
		}
		else
		{
			return s2[s2 - 1 - x];
		}
	}
}


//将e入队,并返回队列
QUEUE& QUEUE::operator<<(int e)
{
	int k;
	//如果队列满了，那么返回错误
	if (full())
	{
		printf("E  ");
		fputs("E  ",fp);
		return *this;
	}

	//如果队列2不为0，且队列1满，那么错误。
	if (s2 != 0 && STACK::operator int() == this->STACK::size())
	{
		printf("E  ");
		fputs("E  ",fp);
		getchar();
		getchar();
		exit(1);
	}

	//如果队列1没有满，那么进入队列1
	if (STACK::operator int() <  this->STACK::size())
	{
		STACK::operator<<(e);
		return *this;
	}
	else
	{
		//如果队列1满了，将队列1的内容倒入队列2
		while (STACK::operator int() != 0)
		{
			STACK::operator>>(k);
			s2 << k;
		}
		STACK::operator<<(e);
	}

	return *this;
}

QUEUE& QUEUE::operator>> (int &e)
{
	if (STACK::operator int() != 0 || s2 != 0)
	{
		if (s2 != 0)
		{
			s2 >> e;
			return *this;
		}
		else
		{
			int k;
			while (STACK::operator int() != 0)
			{
				STACK::operator>>(k);
				s2 << k;
			}
			s2 >> e;
			return *this;
		}
	}
	else
	{
		printf("E  ");
		fputs("E ", fp);
	}
	return *this;
}


QUEUE& QUEUE::operator=(const QUEUE&s)
{
	if (s.s2 != 0)
	{
		s2 = s.s2;
	}

	if (this->STACK::operator int() != 0)
	{
		STACK::operator=(s);
	}

	return *this;
}


void QUEUE::print() const
{
	int i;
	if (!(STACK::operator int() != 0 || s2 != 0))
	{
		//printf("队列空!\n");
		fputs("E ", fp);
		printf("E  ");
	}

	if (s2 != 0)
	{
		for (i = s2 - 1; i >= 0; i--)
		{
			printf("%d  ", s2[i]);
			fprintf(fp, "%d  ", s2[i]);
		}
	}

	if (STACK::operator int() != 0)
	{
		for (i = 0; i < STACK::operator int(); i++)
		{
			printf("%d  ", STACK::operator[](i));
			fprintf(fp, "%d  ", STACK::operator[](i));
		}
	}

}

QUEUE::~QUEUE()
{

}

int isPrime(int num)
{
	int i;
	int flag = 1;
	for (i = 2; i<num/2;i++)
	{
		if (num%i == 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}


int main(int argc, char * argv[])
{
	int err;
	if ((fp = fopen("U201611143_4.txt", "w")) == 0) {
		printf("Cannot open file");
		getchar();
	}

	if (argc == 1)
	{
		using namespace std;
		int conti = 1;
		cout << "是否进行舞伴测试？(输入1是，任意键跳入主菜单）" << endl;
		int  wuban;
		cin >> wuban;
		if (wuban == 1)
		{
			int M, F;
			int m, f;
			cout << "请输入男生队列的人数M,确保M是素数:";
			cin >> M;
			while (!isPrime(M))
			{
				cout << "请重新输入男生队列的人数M,确保M是素数:";
				cin >> M;
			}

			cout << "请输入女生队列的人数F，确保F是素数且不等于M:";
			cin >> F;
			while (!isPrime(F) && F != M)
			{
				cout << "请重新输入女生队列的人数F,确保F是素数，且不等于M:";
				cin >> F;
			}

			cout << "请输入该男士站的位置确保m不超过M:";
			cin >> m;
			while (m > M)
			{
				cout << "请重新输入该男士站的确保m不超过M:";
				cin >> m;
			}

			cout << "请输入该女士站的位置确保f不超过F:";
			cin >> f;
			while (f > F)
			{
				cout << "请重新输入该男士站的确保f不超过F:";
				cin >> f;
			}

			class QUEUE *mQueue = new QUEUE(M);
			class QUEUE *fQueue = new QUEUE(F);

			int i;
			for (i = 1; i <= M; i++)
			{
				if (i != m) {
					*mQueue << 1;
				}
				else
				{
					*mQueue << 0;
				}
			}

			for (i = 1; i <= F; i++)
			{
				if (i != f) {
					*fQueue << 1;
				}
				else
				{
					*fQueue << 0;
				}
			}

			int mOut =1, fOut =1;
			int count = 0;
			while (mOut == 1 || fOut ==1) {
				*mQueue >> mOut;
				*mQueue << mOut;
				*fQueue >> fOut;
				*fQueue << fOut;
				count++;
			}
			delete mQueue;
			delete fQueue;

			cout << "结果：m男士在第【" << count << "】支舞时,可以和f女士共舞蹈" << endl;
			getchar();
			cout << "退出输入1";
			int out;
			cin >> out;
			if (out == 1)
			{
				return 0;
			}
		}
		else
		{

			class QUEUE *pQueue = (class QUEUE *)malloc(sizeof(class QUEUE));
			class QUEUE *sQueue = new QUEUE(6);
			*sQueue << 4;
			*sQueue << 7;
			*sQueue << 6;
			*sQueue << 1;
			*sQueue << 3;
			*sQueue << 4;

			int operate = 1;  //操作序号 在0-12之间
			int isInitial = 0; //判断队列是否存在
			int maxNum;
			int e;
			int temp;
			//int input;
			while (operate) {
				system("cls");
				printf("\n\n");
				printf("--------------------Welcome------------------\n");
				printf("-------------------------------------------------\n");
				printf("1. 初始化队列P        ||7. 将一个数出队列到e\n");
				printf("2. 从队列S初始化队列P ||8. 赋s给p指向的队列\n");
				printf("3. 队列元素的最大个数 ||9. 打印p指向的队列 \n");
				printf("4. 队列中实际元素个数 ||10. 销毁p指向的队列\n");
				printf("5. 取下标为x的队列元素||6.  输入一个数并入队列 \n");
				printf("0. 退出        \n");
				printf("-------------------------------------------------\n");
				printf("请选择你的操作:");
				scanf("%d", &operate);
				switch (operate)
				{
				case 1:
					//InitQueue
					if (isInitial == 0)
					{
						printf("\n\t请输入队列的大小:");
						scanf("%d", &maxNum);
						pQueue = new QUEUE(maxNum);
						isInitial = 1;
						printf("\n\t新建队列成功，队列的大小为%d\n", maxNum);
					}
					else
					{
						printf("\n\t队列已经被创建\n");
					}

					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 2:
					//initSTACK：S-P
					if (isInitial)printf("\n\t队列p已经初始化！");
					else
					{
						pQueue = new QUEUE(*sQueue);
						printf("\n\t成功从队列s新建队列p");
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 3:
					//sizeNum
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						temp = pQueue->size() ;
						printf("\n\t该队列的最大容量是%d", temp);
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 4:
					//howMany
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						temp = *pQueue;
						printf("\n\t该队列中目前有%d个元素", temp);
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 5:
					//getelem
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						printf("\n\t请输入你要查找的数据下标:\n");
						scanf("%d", &temp);
						if (temp <= *pQueue)
						{
							QUEUE aStack = *pQueue;
							temp = aStack[temp];
							printf("\n\t你要查找的数据为%d\n", temp);
						}
						else
						{
							printf("\n\t超出范围！\n");
						}

					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 6:
					//push
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						printf("\n\t请输入你需要入队列的元素:");
						scanf("%d", &e);
						*pQueue << e;
						printf("\n\t成功入队列！\n");
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 7:
					//LocateElem
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						*pQueue >> e;
						printf("\n\t出队列的数据为%d", e);
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 8:
					//PriorElem
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						*pQueue = *sQueue;
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 9:
					//NextElem
					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						printf("\n\t该队列的内容为：\n");
						pQueue->print();
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;
				case 10:

					if (!isInitial)printf("\n\t队列p不存在！");
					else
					{
						printf("\n\t成功销毁该队列！\n");
					}
					getchar();
					printf("\n\t\t（按任意键继续……）\n");
					getchar();
					break;

				case 0:
					break;
				}//end of switch
			}//end of while
			printf("欢迎下次再使用本系统！\n");
			return 0;
		}
		
	}
	else {

		class QUEUE *pQueue = (class QUEUE *)malloc(sizeof(class QUEUE));
		class QUEUE *sQueue = (class QUEUE *)malloc(sizeof(class QUEUE));
		int tempInt; // 临时使用的整型

		int ifInit = 0;
		int ifNew = 0; //判断是否对新队列操作

		int i;
		int e;
		int m;

		for (i = 1; i<argc; i++)
		{
			//当遇见-S
			if (!strcmp(argv[i], "-S"))
			{
				printf("S  ");
				fputs("S  ", fp);


				if (ifInit == 1)
				{
					printf("E "); //那么报错，并跳出循环
					fputs("E  ", fp);
					break;
				}

				//如果下一位是大于0小于9的数字
				if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
				{

					tempInt = atoi(argv[++i]);             //将字符串转化成数字
					pQueue = new QUEUE(tempInt);           //新建队列
					m = tempInt;
					fprintf(fp, "%d  ", tempInt);
					printf("%d  ", tempInt);
					ifInit = 1;                            //队列新建后，修改为1
				}
				else
				{
					printf("E  ");
					fputs("E  ", fp);
					break;
				}
			}

			//当遇见-I，开始加入元素
			if (!strcmp(argv[i], "-I"))
			{
				fputs("I  ", fp);
				printf("I  ");

				int ifLast = 0; // 判断是不是最后一个字母
				int k = i + 1;
				for (; k < argc; k++)
				{
					ifLast = 1;
					if (!strcmp(argv[k], "-I") || !strcmp(argv[k], "-O") || !strcmp(argv[k], "-N") || !strcmp(argv[k], "-G"))
					{
						ifLast = 0;
						break;
					}
				}

				 
				//如果还没有新建，那么就报错
				if (ifInit == 0)
				{
					printf("E  ");
					fputs("E  ", fp);
					exit(1);
				}

				i++;

				for (; (i < argc) && (argv[i][0] >= '0') && (argv[i][0] <= '9'); i++)
				{
					tempInt = atoi(argv[i]);   //将字符串转化成数字'

					if (pQueue->full())
					{
						fputs("E  ", fp);
						printf("E  ");	
						getchar();
						getchar();
						exit(1);
					}

					*pQueue << tempInt;     //入队列

				}
				pQueue->print();
				i--;
			}


			if (i < argc)
			{
				if (!strcmp(argv[i], "-O"))
				{
					fputs("O  ", fp);
					printf("O  ");


					if (ifInit == 0)
					{
						printf("E  "); //那么报错，并跳出循环
						fputs("E ", fp);
						break;
					}
					//如果下一位是大于0小于9的数字
					if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
					{
						tempInt = atoi(argv[++i]);
						if (tempInt > *pQueue)
						{
							printf("E  ");
							fputs("E  ", fp);
							return 0;
						}
						int j;

						for (j = 0; j < tempInt; j++)
						{
							*pQueue >> e;
						}

						if (*pQueue) pQueue->print();
						i--;
					}
					else
					{

						printf("E  ");
						fputs("E ", fp);
						return 0;
					}
				}

				//检测到一个新队列的建立
				if (!strcmp(argv[i], "-A"))
				{
					int ifLast = 0; // 判断是不是最后一个字母
					int k = i + 1;
					for (; k < argc; k++)
					{
						ifLast = 1;
						if (!strcmp(argv[k], "-I") || !strcmp(argv[k], "-O") || !strcmp(argv[k], "-N") || !strcmp(argv[k], "-G"))
						{
							ifLast = 0;
							break;
						}
					}

					fputs("A  ", fp);
					printf("A  ");
					//如果下一位是大于0小于9的数字
					if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
					{

						tempInt = atoi(argv[++i]);             //将字符串转化成数字
						sQueue = new QUEUE(tempInt);            //新建队列
						*sQueue = *pQueue;
						if (ifLast == 0)
						{
							if (sQueue) sQueue->print();
						}
						else
						{
							pQueue->print();
						}

					}
					else
					{
						printf("E  ");
						fputs("E ", fp);
						break;
					}

				}

				//深度拷贝
				if (!strcmp(argv[i], "-C"))
				{
					fputs("C  ", fp);
					printf("C  ");

					QUEUE *newQueue;
					newQueue = new QUEUE(*pQueue);
					if (newQueue) newQueue->print();
					delete newQueue;
				}


				if (!strcmp(argv[i], "-N"))
				{
					fputs("N  ", fp);
					printf("N  ");
					//如果下一位是大于0小于9的数字
					int N = *pQueue;//新建队列
					fprintf(fp, "%d  ", N);
					printf("%d  ", N);
					fclose(fp);
					return 0;

				}


				if (!strcmp(argv[i], "-G"))
				{
					fputs("G  ", fp);
					printf("G  ");
					//如果下一位是大于0小于9的数字
					tempInt = atoi(argv[i + 1]);
					if (tempInt >= *pQueue)
					{
						fputs("E  ", fp);
						printf("E  ");
						break;
					}
					else
					{
						int N = (*pQueue)[tempInt];
						fprintf(fp, "%d  ", N);
						printf("%d  ", N);
					}

				}

			}

		}
		fclose(fp);
	}
	getchar();
	getchar();
	return 0;

}

