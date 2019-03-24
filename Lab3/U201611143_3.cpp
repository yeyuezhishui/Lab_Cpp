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
	virtual  operator int () const	//返回栈的实际元素个数pos
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
		printf("堆栈已满，无法插入新元素");
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
		e = elems[pos];
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
		//printf("栈空!\n");
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


int main(int argc, char * argv[])
{
	if ((fp = fopen("U201611143_3.txt", "w")) == 0) {
		printf("Cannot open file strike any key exit!");
		getchar();
	}

	if (argc == 1)
	{
		class STACK *pStack = (class STACK *)malloc(sizeof(class STACK));
		class STACK *sStack = new STACK(6);
		*sStack << 4;
		*sStack << 7;
		*sStack << 6;
		*sStack << 1;
		*sStack << 3;
		*sStack << 4;

		int operate = 1;  //操作序号 在0-12之间
		int isInitial = 0; //判断栈是否存在
		int maxNum;
		int e;
		int temp;
		int input;
		while (operate) {
			system("cls");
			printf("\n\n");
			printf("-------------------Welcome---------------\n");
			printf("1. 初始化栈P         ||7. 将一个数出栈到e\n");
			printf("2. 从栈S初始化栈P    ||8. 赋s给p指向的栈\n");
			printf("3. 栈元素的最大个数  ||9. 打印p指向的栈 \n");
			printf("4. 栈中实际元素个数  ||10. 销毁p指向的栈\n");
			printf("5. 取下标为x的栈元素 ||0. 退出           \n");
			printf("6.  输入一个数并入栈\n");
			printf("-------------------------------------------------\n");
			printf("请选择你的操作:");
			scanf("%d", &operate);
			switch (operate)
			{
			case 1:
				//InitStack
				if (isInitial == 0)
				{
					printf("\n\t请输入栈的大小:");
					scanf("%d", &maxNum);
					pStack = new STACK(maxNum);
					isInitial = 1;
					printf("\n\t新建栈成功，栈的大小为%d\n", maxNum);
				}
				else
				{
					printf("\n\t栈已经被创建\n");
				}

				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 2:
				//initSTACK：S-P
				if (isInitial)printf("\n\t栈p已经初始化！");
				else
				{
					pStack = new STACK(*sStack);
					printf("\n\t成功从栈s新建栈p");
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 3:
				//sizeNum
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					temp = pStack->size();
					printf("\n\t该栈的最大容量是%d", temp);
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 4:
				//howMany
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					temp = *pStack;
					printf("\n\t该栈中目前有%d个元素", temp);
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 5:
				//getelem
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					printf("\n\t请输入你要查找的数据下标:\n");
					scanf("%d", &temp);
					if (temp <= *pStack)
					{
						STACK aStack = *pStack;
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
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					printf("\n\t请输入你需要入栈的元素:");
					scanf("%d", &e);
					*pStack << e;
					printf("\n\t成功入栈！\n");
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 7:
				//LocateElem
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					*pStack>>e;
					printf("\n\t出栈的数据为%d", e);
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 8:
				//PriorElem
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					*pStack = *sStack;
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 9:
				//NextElem
				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					printf("\n\t该栈的内容为：\n");
					pStack->print();
				}
				getchar();
				printf("\n\t\t（按任意键继续……）\n");
				getchar();
				break;
			case 10:

				if (!isInitial)printf("\n\t栈p不存在！");
				else
				{
					printf("\n\t成功销毁该栈！\n");
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
	else {

		class STACK *pStack = (class STACK *)malloc(sizeof(class STACK));
		class STACK *sStack = (class STACK *)malloc(sizeof(class STACK));
		int tempInt; // 临时使用的整型

		int ifInit = 0;
		int ifNew = 0; //判断是否对新栈操作

		int i;
		int e;

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
					pStack = new STACK(tempInt);           //新建栈
					fprintf(fp, "%d  ", tempInt);
					printf("%d  ", tempInt);
					ifInit = 1;                            //栈新建后，修改为1
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
					int stackNum = *pStack;
					int stackMax = pStack->size();

					if (stackNum == stackMax)
					{
						printf("E  ");
						fputs("E  ", fp);
						getchar();
						getchar();
						exit(1);
					}

					*pStack<<tempInt;     //入栈

				}
				pStack->print();
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
						if (tempInt > *pStack)
						{
							printf("E  ");
							fputs("E  ", fp);
							return 0;
						}
						int j;
						
						for (j = 0; j < tempInt; j++)
						{
							*pStack >> e;
						}

						if (*pStack) pStack->print();
						i--;
					}
					else
					{

						printf("E  ");
						fputs("E ", fp);
						break;
					}
				}

				//检测到一个新栈的建立
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
						sStack = new STACK(tempInt);            //新建栈
						*sStack = *pStack;
						if (ifLast == 0)
						{
							if (sStack) sStack->print();
						}
						else
						{
							pStack->print();
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
					sStack = new STACK(*pStack);
					if (sStack) sStack->print();

				}


				if (!strcmp(argv[i], "-N"))
				{
					fputs("N  ", fp);
					printf("N  ");
					//如果下一位是大于0小于9的数字
					int N = *pStack;//新建栈
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
					if (tempInt >= *pStack)
					{
						fputs("E  ", fp);
						printf("E  ");
						break;
					}
					else
					{
						STACK aStack = *pStack;
						int N = aStack[tempInt];
						fprintf(fp, "%d  ", N);
						printf("%d  ", N);
					}

				}

			}

		}

		fclose(fp);
		getchar();
		getchar();
	}
	return 0;

}

