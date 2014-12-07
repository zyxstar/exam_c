 /*==================================================================*/
 /*=== �������ƣ� Stack_03.c                    =====*/
 /*=== ����Ŀ�ģ� ����������ʽ����ջӦ�ã�            =====*/
 /*==================================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#define MAXSIZE 10


typedef  struct
  {char  data[MAXSIZE];
   int  top;
  }SeqStack;


SeqStack  *Init_SeqStack()  /*�ÿ�ջ*/
{
  SeqStack  *s;
  s=malloc(sizeof(SeqStack));
  s->top=0;  return s;
}

 /*------------------------------------------------------------------*/
 /* �����ջ����                             */
 /*------------------------------------------------------------------*/
int Push_SeqStack (SeqStack *s, char  x)    /* ��ջ*/
{
  if (s->top==MAXSIZE-1)  return 0; /*ջ��������ջ*/
  s->data[s->top]=x;
  s->top++;

  return 1;

}


 /*------------------------------------------------------------------*/
 /* �Ӷ�ջ��ȡ������                         */
 /*------------------------------------------------------------------*/
int  Pop_SeqStack(SeqStack *s, char *x)
{  if  (Empty_SeqStack ( s ) )  return 0; /*ջ�ղ��ܳ�ջ */
   else  {
          s->top--;
          *x=s->data[s->top];

          return 1; }        /*ջ��Ԫ�ش���*x������*/
}

 /*------------------------------------------------------------------*/
 /* ����ջ�Ƿ�Ϊ��                         */
 /*------------------------------------------------------------------*/
int Empty_SeqStack(SeqStack *s) /*�п�ջ*/
{
   if (s->top==0)  return 1;
   else  return 0;
}
 /*------------------------------------------------------------------*/
 /* �ж��Ƿ�Ϊ�����                         */
 /*------------------------------------------------------------------*/
int is_operator(char operator)
{
    switch(operator)
    {
        case '+': case '-': case '*': case '/':return 1; /*�ǲ�����*/
        default: return 0; /*���ǲ�����*/
    }
}

 /*------------------------------------------------------------------*/
 /* �ж������������Ȩ                       */
 /*------------------------------------------------------------------*/
int priority(char o)
{
    switch(o)
    {
        case '+': case '-': return 1; /*"��"��"��"�����������ȨֵΪ1*/
        case '*': case '/': return 2; /*"*"��"/"�����������ȨֵΪ2*/
        default: return 0;
    }
}

 /*------------------------------------------------------------------*/
 /* ������������������ֵ                         */
 /*------------------------------------------------------------------*/
int two_result(int operator, int operand1, int operand2)
{
    switch(operator)
    {
        case '+': return(operand2 + operand1);
        case '-': return(operand2 - operand1);
        case '*': return(operand2 * operand1);
        case '/': return(operand2 / operand1);
    }
}

 /*------------------------------------------------------------------*/
 /* �����򣺿����������ջ���ݣ��������ջ����           */
 /*------------------------------------------------------------------*/
void main()
{
    SeqStack *s_operand,*s_operator;
    char expression[50]; /*�������ʽ�ַ�������*/
    int position = 0; /*���ʽ��Ԫ��λ��*/
    int op = 0; /*�����*/
    int operand1 = 0; /*ǰ������*/
    int operand2 = 0; /*�������*/
    int evaluate = 0; /*������*/

    s_operand=Init_SeqStack();
    s_operator=Init_SeqStack();

    printf("\nplease input the inorder expression:");
    gets(expression);

    while(expression[position]!='\0'&& expression[position]!='\n')
    {
        if(is_operator(expression[position]))
        {
            if(!Empty_SeqStack(s_operator))
        	{
                while(!Empty_SeqStack(s_operator)&&priority(expression[position]) <= priority(s_operator->data[s_operator->top]))
            	{
                    /*�Ӷ�ջ��ȡ��������������һ�������*/
                    Pop_SeqStack(s_operand, &operand1);
                    Pop_SeqStack(s_operand, &operand2);
                    Pop_SeqStack(s_operator, &op);
                    Push_SeqStack (s_operand, two_result(op,operand1,operand2));
            	}
        	}
            /*��ǰԪ�ش����������ջ*/
            Push_SeqStack (s_operator,expression[position]);


        }
        else/*�����������ջ��������Ascii��ת��*/
            Push_SeqStack (s_operand,expression[position]-48);


        position++;/*���ʽ����һ��Ԫ��*/
    }

    /*ȡ���������ջ������*/
    while(!Empty_SeqStack(s_operator))
    {
        Pop_SeqStack(s_operator, &op);
        Pop_SeqStack(s_operand, &operand1);
        Pop_SeqStack(s_operand, &operand2);
        /*����󽫽�������ջ*/
        Push_SeqStack (s_operand,two_result(op,operand1,operand2));

    }
    /*ȡ�����ʽ���ս��*/
    Pop_SeqStack(s_operand, &evaluate);
    printf("The expression [%s] result is '%d'",expression,evaluate);
    getch();
}

