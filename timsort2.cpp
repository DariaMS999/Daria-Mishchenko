#include<stdio.h>
#include <iostream>
#include<cstdio>
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW  -101


using namespace std; 

struct Node{
	struct Node *next;
	struct Node *prev;
	int data;
};


Node* SortInsert(Node **start,int size)
{
	struct Node *element,*NextElement,*PrevElement,*tmp;
	int k=1;
	element=(*start)->next;
	while (k<size&&element!=NULL)
	{
		NextElement=element->next;
		PrevElement=element->prev; 
		tmp=element->prev;
		while ((tmp!=(*start)->prev)&&(tmp->data > element->data))
		{
			tmp=tmp->prev;
		}
		
		if (tmp==(*start)->prev)  
		{
			element->next=(*start); 
			element->prev=(*start)->prev;
			if ((*start)->prev!=NULL)	(*start)->prev->next=element; 			
			(*start)->prev=element;
			(*start)=element;
			if (NextElement!=NULL) NextElement->prev=PrevElement;
			PrevElement->next=NextElement;
		}
		else
		{
		if (tmp->next!=element)
		{
		element->next = tmp->next;
		tmp->next->prev = element;			
		tmp->next = element;
		element->prev = tmp;
		if (NextElement!=NULL) NextElement->prev = PrevElement;
		PrevElement->next = NextElement;
	}
}
		element=NextElement; 
		k++;
	}
	return NextElement;
}


Node* sliv(Node *start1, Node *start2, int n1, int n2)  
{
	Node *tmp,*tmp1,*tmp2,*start;
	int i1=0,i2=0;
	if (start1->data<start2->data)
	{
	start=start1;
	tmp=start1;	
	tmp1=start1->next;
	tmp2=start2;
	i1++;	
}
else
{
	start=start2;
	tmp=start2;	
	tmp->prev=start1->prev;
	if (start1->prev!=NULL)
	start1->prev->next=tmp;
	tmp2=start2->next;
	tmp1=start1;
	i2++;	
}
while (i1<n1&&i2<n2)	
{ 
	if (tmp1->data<tmp2->data)
	{
		tmp->next=tmp1;
		tmp1->prev=tmp;
		tmp=tmp1;
		tmp1=tmp1->next;
		i1++;
	}
	else
	{
		tmp->next=tmp2;
		tmp2->prev=tmp;
		tmp=tmp2;
		tmp2=tmp2->next;
		i2++;
	}
}
if (i1==n1)	
{
 tmp->next=tmp2;
 tmp2->prev=tmp;	
}
else
{
 tmp->next=tmp1;
 tmp1->prev=tmp;
 i1++;
 while (i1<n1)
 {
 	tmp1=tmp1->next;
 	i1++;
 }
 tmp1->next=tmp2;
 if (tmp2!=NULL)
 tmp2->prev=tmp1;
}	
	
return start;
}


int OutArray(Node *start)
{
	Node *num;
	num=start;
	while (num!=NULL)
	{
		cout << num->data << "   ";
		num=num->next;
	}
	cout<<endl;
}

int GetMinrun(int n)
	{
	    int r = 0;           
	    while (n >= 64) 
		{
	        r |= n & 1;
	        n >>= 1;
	    }
	    return n + r;
	}



struct Array 
{
	int size;
	struct Node *start;
	struct Array *prev;
};


void push(Array **head, int size, Node *start) 
{
    Array *tmp = new struct Array;
if (tmp == NULL) {
        exit(STACK_OVERFLOW);
    }
    tmp->prev = *head;
    tmp->size = size;
    tmp->start = start;
    *head = tmp;
}


void pop(Array **head) 
{
    Array *out;
     if (*head == NULL) 
	{
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->prev;
    delete out;
}







int main ()
{
	
	struct Node *first=NULL,*tmp=NULL,*prev=NULL,*start=NULL,*tmpnext=NULL;
	struct Node *num=NULL;
	struct Array *head=NULL,*tmpdel=NULL;
	int n,minrun,remain,nnew;
    
  	first = new struct Node;	
    
 	first->next=NULL;
	first->prev=NULL;
	prev=first;
	n=1;
	int A,N, M;
	cout<<"Enter the size N:";
	cin>> N;
	int* mass= new int[N];
	srand(time(NULL));
	cout<<"Range of values from 0 to M. Enter the M:";
	cin>>M;
	for(int i=0; i<N; i++)
	{	
	   A=rand()%M;		
		mass[i]=A;
		
		tmp= new struct Node;
		tmp->data = A;
		tmp->prev = prev;
		prev->next = tmp;
		prev = tmp;	
		n++;
	} 
	
	tmp->next=NULL;
	
	minrun=GetMinrun(n);
	minrun=4;
	tmp=first;
	remain=n;
	do
	{
		if (remain<minrun)
		{
			minrun=remain;
		}
	tmpnext=SortInsert(&(tmp),minrun);
	if (remain==n) first=tmp;
	OutArray(first);
	push(&head,minrun,tmp);
	remain-=minrun;
	if (head->prev!=NULL && head->prev->prev!=NULL)
	{
	if (head->size <= head->prev->size + head->prev->prev->size || head->prev->size <= head->prev->prev->size) 
	{
		if(head->size < head->prev->prev->size)
		{
			tmp=sliv(head->prev->start, head->start,head->prev->size,head->size);
			nnew=head->size+head->prev->size;
			pop(&head);
			head->size=nnew;
			head->start=tmp;
		}
		else
		{
			tmp=sliv(head->prev->prev->start,head->prev->start,head->prev->prev->size, head->prev->size);
			nnew=head->prev->size+head->prev->prev->size;
			tmpdel=head->prev;
			head->prev=head->prev->prev;
			head->prev->size=nnew;
			head->prev->start=tmp;
			delete tmpdel;
		}
	if (head->prev->prev == NULL) first=head->prev->start;	
	}		
	}
	
	OutArray(first);	
	tmp=tmpnext;
	}
	while (remain>0);
	

while (head->prev!=NULL)
{
			tmp=sliv(head->prev->start, head->start,head->prev->size,head->size);
			nnew=head->size+head->prev->size;
			pop(&head);
			head->size=nnew;
			head->start=tmp;
}

OutArray(head->start);
	
	return 0;
}




