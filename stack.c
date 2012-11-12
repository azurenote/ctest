#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "compile.h"

#ifdef COMPILE_5_1

typedef struct StackNode_t
{
	int element;
	struct StackNode_t* link;
} StackNode;

typedef struct Stack_t
{
	StackNode* top;
} Stack;


void stack_init(Stack* s)
{
	s->top = NULL;
}

int is_empty(Stack* s)
{
	return s->top == NULL;
}



void stack_push(Stack* s, int data)
{
	StackNode* temp = (StackNode*) malloc(sizeof(StackNode));

	if (temp == NULL)
	{
		return;
	}

	temp->element = data;
	temp->link = s->top;

	s->top = temp;
}

int stack_pop(Stack* s)
{
	StackNode* node;
	int data;

	if (is_empty(s))
	{
		exit(1);
		return -1;
	}

	node = s->top;

	data = node->element;

	s->top = node->link;

	free(node);

	return data;
}

void stack_destroy(Stack* s)
{
	while (!is_empty(s))
		stack_pop(s);

	stack_init(s);
}


int stack_peek(Stack* s)
{
	if (is_empty(s))
		return -1;

	return s->top->element;
}


int get_operend_priority(char op)
{
	switch(op)
	{
	case '(':case')':
		return 0;
	case '+':case'-':
		return 1;
	case '*':case'/':
		return 2;
	default:
		return -1;
	}
}

int is_operend(char c)
{
	return get_operend_priority(c) == -1 ? 0 : 1;
}

int is_space(char c)
{
	return c == ' ' || c == '\t';
}

void infix_to_postfix(char exp[])
{
	Stack s;

	int i, n, strlength;

	char* newstr;
	
	strlength = strlen(exp);

	newstr = (char*) malloc(strlength);

	stack_init(&s);

	n = 0;

	for (i = 0; i < strlength; ++i)
	{
		char temp = exp[i];

		if (temp == '(')
			stack_push(&s, temp);
		else if (temp == ')')
		{
			char topOp = (char) stack_pop(&s);

			while (topOp != '(')
			{
				newstr[n++] = topOp;
				topOp = (char) stack_pop(&s);
			}
		}
		else if (is_operend(temp))
		{
			char topOp = (char)stack_peek(&s);

			while (!is_empty(&s) && get_operend_priority(topOp) >= get_operend_priority(temp))
			{
				newstr[n++] = (char) stack_pop(&s);
				topOp = (char)stack_peek(&s);
			}

			stack_push(&s, temp);
		}
		else
		{
			newstr[n++] = exp[i];
		}
		//next
	}


	while (!is_empty(&s))
	{
		newstr[n++] = (char) stack_pop(&s);
	}

	memset(exp, 0, strlength);

	for (i = 0; i < n; ++i)
	{
		exp[i] = newstr[i];
	}

	stack_destroy(&s);
	free(newstr);
}

int eval(char exp[])
{
	Stack s;

	int i, strlength, result;

	stack_init(&s);

	strlength = strlen(exp);

	for (i = 0; i < strlength; ++i)
	{
		char c = exp[i];

		if (is_operend(c))
		{
			int a, b, temp;

			b = stack_pop(&s);
			a = stack_pop(&s);

			switch(c)
			{
			case '+':
				temp = a + b;
				break;
			case '-':
				temp = a - b;
				break;
			case '*':
				temp = a * b;
				break;
			case '/':
				temp = a / b;
				break;
			}

			stack_push(&s, temp);
		}
		else
			stack_push(&s, c - '0');
	}

	result = stack_pop(&s);

	stack_destroy(&s);

	return result;
}


int main()
{
	char string[50] = {0};
	int str_length;
	int i;

	puts("--Exercise 5.1 : numerical expression calculator----------");
	puts("examples)");
	puts(" * 3*4");
	puts(" * 9+2-5");
	puts(" * (5*4)/2");
	puts(" * (1+2+3)*(4+5)");

	while (1)
	{
		puts("Enter 'q' if you want to exit.");
		printf("input: ");
		scanf("%s", string);
		fflush(stdin);

		if (string[0] == 'q')
			break;

		infix_to_postfix(string);

		printf("in postfix: %s\n", string);

		printf("result: %d\n\n", eval(string));
	}
	return 0;
}


#endif