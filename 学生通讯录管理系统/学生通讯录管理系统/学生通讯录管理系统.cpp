// 学生通讯录管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(LNode)
int seat;                 //全局变量，用于存放通讯录成员的序号

typedef struct LNode
{//用于通讯录节点
	int number;            //学号
	char name[20];         //姓名
	double telenum;        //电话
	struct LNode* next;
}LNode,*LinkList;

LinkList creatIncreLink()//1.创建列表
{//创建一个存放通讯录成员的非递减有序表，返回头结点地址
	LinkList p;
	int num = 1, number;
	double telenum;
	char name[20], temp;
	LinkList L, P;
	L = (LinkList)malloc(LEN);              //创建头结点
	L->next = NULL;
	printf("请输入学生学号、姓名、和电话号码，建立通讯录，以'-1'为输入结束标志\n");
	printf("请输入学号 %d：-->", num);
		scanf("%d", &number);
	printf("请输入姓名 %d：-->",num);
		temp = getchar();
		gets_s(name);
	printf("请输入电话号码 %d：-->", num);
		scanf("%lf", &telenum);
		while (number >= 0)
		{
			p = (LinkList)malloc(LEN);            //新分配节点
			p->number = number;
			p->telenum = telenum;
			strcpy(p->name, name);
			insertYouXu(L, p);               //有序的插入新结点
			num++;
			printf("请输入学号 %d：-->", num);
				scanf("%d", &number);
			printf("请输入姓名 %d：-->", num);
			temp = getchar();
			gets_s(name);
			printf("请输入电话号码 %d：-->", num);
				scanf("%lf", &telenum);
		}
		return L;
}//end


//2.在通讯录按序号删除第i个成员
void deleteElem(LinkList L, int i)
{
	LinkList p = L, q;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!(p->next))        //判断i是否合法，i不能大于元素的个数，也不能小于等于0
	{
		printf("第%d个元素删除失败\n", i);
		return;
	}
	q = p->next;
	p->next = q->next;
	free(q);           //释放删除的结点
}//end deleteElem


//按姓名删除通讯录成员
int delName(LinkList L, char n[])
{
	int flag = 0;                 //判断要删除的通讯录成员和通讯录中的姓名是否匹配
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL)
	{
		printf("该链表中没有元素，查找失败\n");
	}
	else
	{
		while (p != NULL)
		{
			if (!strcmp(p->name, n))         //比较输入的姓名和通讯录中的姓名
			{
				flag = 1;
				printf("%s ", p->name);
				p = p->next;
				deleteElem(L, seat);
			}
			else
			{
				p = p->next;
				seat++;
			}//输入姓名不匹配，指针移动到下一个通讯录成员
		}
		if (flag)
		{
			printf("被删除\n");
		}
	}
	return flag;
}

//按学号删除通讯录成员
int delNum(LinkList L, int n)
{
	int flag = 0;                  //判断要删除的通讯录成员和通讯录中的学号是否匹配
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL)
	{
		printf("该链表中没有元素，删除失败\n");
	}
	else
	{
		while (p != NULL)
		{
			if (p->number <= n)
			{
				if (p->number == n)
				{
					flag = 1;       //输入学号匹配
					printf("%d ", p->number);
					p = p->next;
					deleteElem(L, seat);
				}//endif
			}//endif
			else
			{
				p = p->next;
				seat++;
			}
		}//while
		printf("被删除\n");
	}//else
	return flag;
}//end delNum
//5.插入一条成员记录，使通讯录保持有序
void insertYouXu(LinkList L,LinkList Elem)
{
	LinkList p=L->next;
	while (p != NULL && Elem->number >= p->number)
	{
		if (p->number == Elem->number)
		{
			printf("重复输入！！！\n");
			return;
		}
		p = p->next;
	}
	if (p == NULL)   //确定 Elem 的插入位置
	{
		p = prior(L, p);
		Elem->next = NULL;
		p->next = Elem;
	}
	else
	{
		p = prior(L, p);
		Elem->next = p->next;
		p->next = Elem;
	}
}

//6.输出通讯录L的所有元素
void printList(LinkList L)
{//打印头结点地址为L的通讯录
	LinkList p = L;
	int n = 1;
	printf("\n                ---------------\n");
	printf("                   学号        姓名          电话号码\n");
	printf("\n                ---------------\n");
	if (L == NULL || L->next == NULL)//判断通讯录是否为空
	{
		printf("该通讯录中没有元素\n");
	}
	else
	{
		while (p->next != NULL)
		{
			printf("                   %2d        %-9d", n, p->next->number);
			printf("     %-5s    %.0f\n", p->next->name, p->next->telenum);
			p = p->next;
			n++;
		}
	}
	printf("\n                ---------------\n");
	return;
}//end

//7.找到当前地址元素的直接前驱元素的地址
LinkList prior(LinkList L, LinkList p)
{
	LinkList p_prior = L;
	if (L->next == NULL)
	{
		return (L);
	}
	while (p_prior->next != p)
	{
		p_prior = p_prior->next;
	}
	return (p_prior);
}

//按姓名查找通讯录成员
int searchName(LinkList L, char n[])
{
	int flag = 0;           //标志要查找的通讯录成员和通讯录中的姓名是否匹配
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL || L == NULL)
	{
		printf("该通讯录中没有元素，查找失败\n");
	}
	else
	{
		while (p != NULL)
		{
			if (!strcmp(p->name, n))   //比较要查找的姓名是否和当前通讯录所指姓名匹配
			{
				flag = 1;          //输入姓名的匹配，查找成功
				printf("要查找的是第%d位通讯录成员：", seat);
				printf(" Number: %d    Name: %s     TeleNo.: %.0f\n", p->number, p->name, p->telenum);
			}//endif
			p = p->next;
			seat++;          //!!!!
		}//while
	}//else
	return flag;
}//searchName

//按学号查找通讯录成员
int searchNum(LinkList L, int n)
{
	int flag = 0;          //标志要查找的通讯录成员和通讯录中的学号是否匹配
	LinkList p = L->next;
	seat = 1;
	if (L->next == NULL)
	{
		printf("该链表中没有元素，查找失败\n");
	}
	else
	{
		while (p != NULL)
		{
			if (p->number <= n)
			{
				if (p->number == n)
				{
					flag = 1;       //输入的学号匹配，查找成功
					printf("要查找的是第%d位通讯录成员：", seat);
					printf(" Number: %d    Name: %s     TeleNo.: %.0f\n", p->number, p->name, p->telenum);
				}
				p = p->next;
				seat++;
			}
		}
	}
	return flag;
}
//void main()//主函数
int main()
{
	LinkList L = NULL;
	int flag = 0;         //标志变量。标记通讯录是否建立
	int menu;             //菜单选项
	char temp;
	LinkList p = L;
	system("color 1f");              //设置界面颜色
	printf("\n    *****************^@^欢迎使用通讯录系统*******************\n");
	printf("            *           1 通讯录的建立                         *\n");
	printf("            *           2 插入通讯记录                         *\n");
	printf("            *           3 查询通讯记录                         *\n");
	printf("            *           4 删除通讯记录                         *\n");
	printf("            *           5 显示通讯录信息                        *\n");
	printf("            *           0 退出管理系统                          *\n");
	printf("      *****************^@^欢迎使用通讯录系统*******************\n");
	printf("请选择0-5：-->");
		scanf("%d", &menu);
	while (menu != 0)
	{
		switch (menu)
		{
		case 1:
			L = creatIncreLink();  //用于函数实现通讯录的建立
			printf("建立通讯录：-->");
			printList(L);
			flag = 1;
			break;

		case 2:

			if (1 == flag)
			{
				int number, telenum;

				//char name[20], temp;
				char name[20];
				printf("请输入通讯录成员的学号和姓名：\n");
				printf("请输入学号：-->");
				scanf("%d", &number);
				printf("请输入姓名：-->");
				temp = getchar();
				gets_s(name);
				printf("请输入电话号码：-->");
				scanf("%d", &telenum);
				p = (LinkList)malloc(LEN);    //分配新结点
				p->number = number;
				strcpy(p->name, name);
				p->telenum = telenum;
				insertYouXu(L, p);           //插入新结点
				printf("插入后：-->");
				printList(L);
			}
			else
			{
				printf("\nERROR：通讯录还没有建立，请先建立通讯录\n");
				break;
			}

		case 3:
			int way, n, s;          //查找方式
			//char na[20], temp;
			char na[20];
			if (L != NULL)
			{
				if (flag)
				{
					printf("选择查找方式：\n");
					printf("        1.按学号      2.按姓名");
					scanf("%d", &way);
					if (1 == way)
					{
						printf("\n请输入学号：-->");
						scanf("%d", &n);
						s = searchNum(L, n);      //查找通讯录成员
						if (0 == s)
						{
							printf("无此通讯录成员，查找失败！\n");
						}
					}
					else if (2 == way)
					{
						printf("\n请输入姓名：-->");
						temp = getchar();
						gets_s(na);
						s = searchName(L, na);
						if (0 == s)
						{
							printf("无此通讯录成员，查找失败！\n");
						}
					}
					else
					{
						printf("通讯录中无记录！\n");
					}//
				}//结束endif(flag)
				break;
			}//endif(L!=NULL)
			else
			{
				printf("无此通讯录成员，查找失败！\n");
			}
			break;
		case 4:
			int way1;           //删除方式
			//char temp;
			printf("选择删除方式：  1.按序号    2.按学号    3.按姓名    \n");
				scanf("%d", &way1);
			if (1 == way1)
			{
				int n;
				printf("请输入通讯录序号：-->");
				scanf("%d", &n);
				printf("删除后：\n");
				deleteElem(L, n);
				printList(L);
			}
			else if (2 == way1)
			{
				int n, f;
				printf("请输入学号：-->");
				scanf("%d", &n);
				f = delNum(L, n);     //按学号删除
				if (f != 0)
				{
					printf("删除后：\n");
					printList(L);
				}
				else
				{
					printf("无该学号，删除失败!\n");
				}
			}
			else if (3 == way1)
			{
				char na[20], temp;
				int f;
				printf("\n请输入姓名：-->");
				temp = getchar();
				gets_s(na);
				f = delName(L, na);              //按姓名删除
				if (f != 0)
				{
					printf("删除后：\n");
					printList(L);
				}
				else
				{
					printf("无该学号，删除失败!\n");
				}
			}
			else
			{
				printf("ERROR!!!\n");
			}
			break;

		case 5:
			printf("当前通讯录内容如下： \n");
			printList(L);      //打印通讯录
			break;

		case 0:
			exit(0);

		default:
			printf("\n没得此功能，重新输入吧孩子\n");
		}//end switch
		printf("选择功能：-->");
		scanf("%d", &menu);
	}//end while
}//end main