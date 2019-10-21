#include<stdio.h>
#include <iostream>
#include<cstdio>
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW  -101


using namespace std; 
//элемент массива
struct Node{
	struct Node *next;
	struct Node *prev;
	int data;
};


Node* SortInsert(Node **start,int size)//сортировка вставками части массива длины size элементов, начиная с элемента *start
{
	struct Node *element,*NextElement,*PrevElement,*tmp;
	int k=1;
	element=(*start)->next;
	while (k<size&&element!=NULL)//начиная со второго друг за другом перебираем элементы element подмассива, и каждый вставляем на свое место
	{
		NextElement=element->next;
		PrevElement=element->prev;//надо запомнить начальных соседей, чтобы после изъятия element замкнуть их друг на друга 
		tmp=element->prev;
		while ((tmp!=(*start)->prev)&&(tmp->data > element->data))//идем от начального  полжения element до начала подмассива, пока не найдем подходящее место
		{
			tmp=tmp->prev;
		}
		//место найдено - надо воткнуть element перед tmp
		if (tmp==(*start)->prev) //если мы дошли до начала подмассива, то есть element оказался минимальным 
		{
			element->next=(*start); //устанавливаем новые связи
			element->prev=(*start)->prev;
			if ((*start)->prev!=NULL)	(*start)->prev->next=element; //если это не самое начало массива			
			(*start)->prev=element;
			(*start)=element;//тогда новым начальным элементом подмассива становится element
			if (NextElement!=NULL) NextElement->prev=PrevElement;//перезамыкаем друг на друга старых соседей
			PrevElement->next=NextElement;
		}
		else
		{
		if (tmp->next!=element)//если element должен переместиться куда-то не в начало подмассива
		{
		element->next = tmp->next;
		tmp->next->prev = element;			
		tmp->next = element;
		element->prev = tmp;
		if (NextElement!=NULL) NextElement->prev = PrevElement;//может оказаться, что element изначально находился в конце большого массива
		PrevElement->next = NextElement;
	}
}
		element=NextElement; //переходим к следующему element
		k++;
	}
	return NextElement;//возвращаем элемент, следующий после подмассива
}

//сливает вместе два соседних упорядоченных подмассива
Node* sliv(Node *start1, Node *start2, int n1, int n2)  
{
	Node *tmp,*tmp1,*tmp2,*start;
	int i1=0,i2=0;
	if (start1->data<start2->data)
	{
	start=start1;
	tmp=start1;//tmp - последний установленный элемент слитого подмассива	
	tmp1=start1->next;//tmp1 - текущий элемент первого подмассива, tmp2- второго, на первое место ставим меньший них
	tmp2=start2;
	i1++;	
}
else
{
	start=start2;
	tmp=start2;	
	tmp->prev=start1->prev;//зацепили с предыдущим массивом
	if (start1->prev!=NULL)
	start1->prev->next=tmp;
	tmp2=start2->next;
	tmp1=start1;
	i2++;	
}
while (i1<n1&&i2<n2)//пока не достигнем конца одного из подмассивов	
{ //меньший из текущих элементов двух подмассивов записываем в слитый подмассив, и в этом из двух подмассивов переходим к следующему элементу
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
if (i1==n1)	//дозаливаем оставшийся подмассив
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
	
return start;//возвращаем ссылку на начальный элемент слитого подмассива	
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


//стек подмассивов
struct Array 
{
	int size;
	struct Node *start;//начальная позиция в массиве
	struct Array *prev;//число элементов
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
	int a;
	int symbol;
	struct Node *first=NULL,*tmp=NULL,*prev=NULL,*start=NULL,*tmpnext=NULL;
	struct Node *num=NULL;
	struct Array *head=NULL,*tmpdel=NULL;
	int t,n,minrun,remain,nnew;
    //FILE * fo = fopen("1.txt","r");
  	first = new struct Node;	
    //fscanf(fo,"%d",&(first->data));
 	first->next=NULL;
	first->prev=NULL;
	prev=first;
	n=1;
	while (symbol != 0)
	{
		cout<< "Enter a number: ";
		cin >> symbol;
		tmp= new struct Node;
		tmp->data = symbol;
		tmp->prev = prev;
		prev->next = tmp;
		prev = tmp;
		n++;
	}
	//fclose(fo);
	tmp->next=NULL;
	
	minrun=GetMinrun(n);
	minrun=4;//на подмассивы какого размера делим большой массив - надо эту строку удалить
	tmp=first;
	remain=n;//n-сколько элементов в массиве, remain - сколько еще осталось
	do
	{
		if (remain<minrun)
		{
			minrun=remain;//так-то все подмассивы имеют размер Minrun, но на последний может не хватить элементов
		}
	tmpnext=SortInsert(&(tmp),minrun);//сортируем вставками очередной подмассив, получаем первый элемент следующего
	if (remain==n) first=tmp;//может оказаться так, что первый элемент массива изменится в результате соритровки
	OutArray(first);
	push(&head,minrun,tmp);
	remain-=minrun;
	if (head->prev!=NULL && head->prev->prev!=NULL)//если в стеке уже есть три подмассива - попытаемся слить два из них
	{
	if (head->size <= head->prev->size + head->prev->prev->size || head->prev->size <= head->prev->prev->size) //взято с сайта для оптимизации алгоритма
	{
		if(head->size < head->prev->prev->size)//сливаем ближайший к вершине стека массив с тем из его соседей, у которого меньше размер
		{
			tmp=sliv(head->prev->start, head->start,head->prev->size,head->size);
			nnew=head->size+head->prev->size;//новый размер слитого подмассива
			pop(&head);//из стека удаляем один из двух слитых подмассивов
			head->size=nnew;//а на место другого записываем данные слитого подмассива
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
	if (head->prev->prev == NULL) first=head->prev->start;//меняем первй элемент массива, если это необходимо	
	}		
	}
	
	OutArray(first);	
	tmp=tmpnext;
	}
	while (remain>0);
	
//в стеке осталось несколько подмассивов - их тоже сливаем
while (head->prev!=NULL)
{
			tmp=sliv(head->prev->start, head->start,head->prev->size,head->size);
			nnew=head->size+head->prev->size;
			pop(&head);
			head->size=nnew;
			head->start=tmp;
}
cout >> 
OutArray(head->start);
	
	return 0;
}


