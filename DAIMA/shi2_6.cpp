#include<malloc.h> 
#include<stdio.h> 
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT 10 // 存储空间分配增量

typedef int SElemType; // 定义栈元素类型
typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等

struct SqStack
{
     SElemType *base; // 在栈构造之前和销毁之后，base的值为NULL
     SElemType *top; // 栈顶指针
     int stacksize; // 当前已分配的存储空间，以元素为单位
}; // 顺序栈

Status InitStack(SqStack &S)       
{   
// 构造一个空栈S，该栈预定义大小为STACK_INIT_SIZE
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
     if(!S.base) return ERROR;
	 S.top=S.base;
	 S.stacksize=STACK_INIT_SIZE;
	 return OK;
}

Status Push(SqStack &S,SElemType e)   
{   
// 在栈S中插入元素e为新的栈顶元素
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) return ERROR;
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Pop(SqStack &S,SElemType &e)   
{   
// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
	if(S.top==S.base) return ERROR;
     e=*--S.top;
	 return OK;
}

Status GetTop(SqStack S,SElemType &e)   
{    
// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
	if(S.top==S.base) return ERROR;
    e=*(S.top-1);
	return OK;
}

int StackLength(SqStack S) 
{   
// 返回栈S的元素个数
	int i;
    i=S.top-S.base;
	return i;
}

Status StackTraverse(SqStack S)
{
// 从栈顶到栈底依次输出栈中的每个元素
	SElemType *p = (SElemType *)malloc(sizeof(SElemType)); 
	p = S.top;       
	if(S.top==S.base)printf("The Stack is Empty!");  
	else
	{
		printf("The Stack is: ");
		p--;
		while(p>=S.base)             
		{
			printf("%d ", *p);
			p--;               
		}
	}
	printf("\n");
	return OK;
}

// 判断c是否是运算符
int IsOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

// 判断运算符优先级
char Precede(char a, char b)
{
	// 返回'>'表示a优先级高于b，'<'表示a优先级低于b，'='表示相等
	switch(a)
	{
		case '+':
		case '-':
			if(b == '+' || b == '-' || b == ')') return '>';
			if(b == '*' || b == '/' || b == '(') return '<';
			break;
		case '*':
		case '/':
			if(b == '(') return '<';
			else return '>';
			break;
		case '(':
			if(b == ')') return '=';
			if(b == '=') return '>';
			else return '<';
			break;
		case ')':
			return '>';
		case '=':
			return '<';
	}
	return '<';
}

// 执行运算
int Operate(int a, char theta, int b)
{
	switch(theta)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
	return 0;
}

int EvaluateExpression()
{
	SqStack OPTR, OPND;  // OPTR为运算符栈，OPND为操作数栈
	char c;
	int a, b, num;
	char theta, x;
	
	InitStack(OPTR);
	InitStack(OPND);
	
	Push(OPTR, '=');  // 将'='压入运算符栈底
	
	scanf("%c", &c);
	
	while(c != '=' || *((char*)(OPTR.top-1)) != '=')
	{
		if(!IsOperator(c))  // 如果是数字
		{
			num = 0;
			while(c >= '0' && c <= '9')
			{
				num = num * 10 + (c - '0');
				scanf("%c", &c);
			}
			Push(OPND, num);
		}
		else  // 如果是运算符
		{
			char topOp = *((char*)(OPTR.top-1));
			
			if(Precede(topOp, c) == '<')
			{
				Push(OPTR, c);
				scanf("%c", &c);
			}
			else if(Precede(topOp, c) == '>')
			{
				theta = *((char*)(OPTR.top-1));
				OPTR.top--;
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
			}
			else  // 遇到匹配的括号
			{
				OPTR.top--;
				scanf("%c", &c);
			}
		}
	}
	
	GetTop(OPND, num);
	return num;
}

int main()
{
	int result = EvaluateExpression();
	printf("%d\n", result);
	return 0;
}