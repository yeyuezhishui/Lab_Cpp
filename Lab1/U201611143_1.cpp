#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>


struct STACK {
	int  *elems;	//申请内存用于存放栈的元素
	int   maxNum;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, STACK * const s); //用栈s初始化p指向的栈
int  sizeNum(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int *e); 	//出栈到e，并返回p
STACK *const assignValue(STACK*const p, STACK *const s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

FILE *fp;


int main(int argc, char * argv[])
{
	int err;
	if ((fp = fopen("U201611143_1.txt","w")) == 0) {
		printf("Cannot open file strike any key exit!");
		getchar();
	}

	if (argc == 1)
	{
		struct STACK *pStack = (struct STACK *)malloc(sizeof(struct STACK));
		struct STACK *sStack = (struct STACK *)malloc(sizeof(struct STACK));
		initSTACK(sStack, 5);
		push(sStack, 4);
		push(sStack, 7);
		push(sStack, 6);
		push(sStack, 1);
		push(sStack, 3);
		push(sStack, 4);

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
					initSTACK(pStack, maxNum);
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
					initSTACK(pStack, sStack);
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
					temp = sizeNum(pStack);
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
					temp = howMany(pStack);
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
					if (temp <= howMany(pStack))
					{
						temp = getelem(pStack, temp);
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
					push(pStack, e);
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
					pop(pStack, &e);
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
					assignValue(pStack, sStack);
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
					print(pStack);
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

		struct STACK *pStack = (struct STACK *)malloc(sizeof(struct STACK));
		struct STACK *sStack = (struct STACK *)malloc(sizeof(struct STACK));
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
					initSTACK(pStack, tempInt);            //新建栈
					fprintf(fp, "%d  ", tempInt);
					printf("%d  ", tempInt);
					ifInit = 1;  //栈新建后，修改为1
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
					int stackNum = howMany(pStack);
					int stackMax = sizeNum(pStack);

					if (stackNum == stackMax)
					{
						printf("E  ");
						fputs("E  ", fp);
						getchar();
						getchar();
						exit(1);
					}

					push(pStack, tempInt);     //入栈

				}
				print(pStack);
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
						if (tempInt > howMany(pStack))
						{
							printf("E  ");
							fputs("E  ", fp);
							break;
						}
						int j;
						for (j = 0; j < tempInt; j++)
						{
							pop(pStack, &e);
						}
					
						if(howMany(pStack)) print(pStack);

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
					fputs("A  ", fp);
					printf("A  ");
					//如果下一位是大于0小于9的数字
					if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
					{

						tempInt = atoi(argv[++i]);             //将字符串转化成数字
						initSTACK(sStack, tempInt);            //新建栈
						assignValue(sStack, pStack);
						if (howMany(pStack)) print(pStack);
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
					initSTACK(sStack, pStack);            //新建栈
					if (howMany(pStack)) print(pStack);

				}


				if (!strcmp(argv[i], "-N"))
				{
					fputs("N  ", fp);
					printf("N  ");
					//如果下一位是大于0小于9的数字
					int N = howMany(pStack);//新建栈
					fprintf(fp, "%d  ", N);
					printf("%d  ", N);
					getchar();
					getchar();
					fclose(fp);
					return 0;

				}


				if (!strcmp(argv[i], "-G"))
				{
					fputs("G  ", fp);
					printf("G  ", fp);
					//如果下一位是大于0小于9的数字
					tempInt = atoi(argv[i + 1]);
					if (tempInt >= howMany(pStack))
					{
						fputs("E  ", fp);
						printf("E  ");
						break;
					}
					else
					{
					int N = getelem(pStack, tempInt);//新建栈
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

void initSTACK(STACK *const p, int m)
{
	p->elems = (int*)malloc(sizeof(int)*m);
	p->maxNum = m;
	p->pos = 0;
}

void initSTACK(STACK *const p, STACK *const s)
{
	p->elems = (int*)malloc(sizeof(int)*s->maxNum);
	p->maxNum = s->maxNum;
	p->pos = s->pos;
	assignValue(p, s);
}

int  sizeNum(const STACK *const p)
{
	return p->maxNum;
}

int  howMany(const STACK *const p)
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)	//取下标x处的栈元素
{
	if (x > p->pos)
	{
		printf("超过了最大下标！\n");
		fputs("E ", fp);
		return 0;
	}
	return p->elems[x];
}

STACK *const push(STACK *const p, int e)
{
	if (p->pos == p->maxNum)
	{
		printf("堆栈已满，无法插入新元素");
		return p;
	}
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}

STACK *const pop(STACK *const p, int *e)
{
	if (p->pos != 0)
	{
		*e = p->elems[p->pos];
		p->pos--;
	}
	else
	{
		printf("E  ");
		fputs("E ", fp);
		return p;
	}
	return p;
}


STACK *const assignValue(STACK*const p, STACK *const s)
{
	int i;
	for (i = 0; i<s->pos && i<p->maxNum; i++)
	{
		p->elems[i] = s->elems[i];
	}
	p->pos = i;
	return p;
}

void print(const STACK*const p)
{
	int i;
	if (p->pos == 0)
	{
		printf("栈空!\n");
		fputs("E ", fp);
		return;
	}
	for (i = 0; i<p->pos; i++)
	{
		printf("%d  ", p->elems[i]);
		fprintf(fp, "%d  ", p->elems[i]);
	}
}

void destroySTACK(STACK*const p)
{
	free(p->elems);
}

