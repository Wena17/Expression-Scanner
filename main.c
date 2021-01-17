#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>

struct node {
    char data;
    struct node *next;
};

struct queue {
    struct node *front;
    struct node *rear;
    int count;
};

struct queue *q;

struct queue *create_queue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

//Adding data to the queue
struct queue *enqueue(struct queue *q, char exp) {
    struct node *new_queue = malloc(sizeof(struct node));
    new_queue->data = exp;
    if(q->rear == NULL){
        q->front = q->rear = new_queue;
        q->front->next = q->rear->next = NULL;
    } else {
        q->rear->next = new_queue;
        q->rear = new_queue;
        q->rear->next = NULL;
    }
    q->count++;
    return q;
}

//Deleting data from the queue
struct queue *dequeue(struct queue *q) {
    if (q->front == NULL) {
        printf("\n!!! Queue is empty !!!");
    } else {
        struct node *ptr = q->front;
        q->front = ptr->next;
        if (ptr == q->rear) {
            q->rear = NULL;
        }
        free(ptr);
        q->count--;
    }
    return q;
}

void display(struct queue *q)
{
    struct node *ptr = q->front; // first node
    printf("\n");
    printf("expression: ");
    while (ptr != NULL)
    {
        printf("%c ", ptr->data);
        ptr = ptr->next;
    }
}

int calculate(char a, int b, int c)
{

    if(a=='+')
        return (b+c);

    else if(a=='-')
        return (b-c);
    else if(a=='*')
        return (b*c);
    else if(a=='/')
        return (b/c);
    else
        return -1;
}

int charToInt(char c){
	int num = 0;

	//Substract '0' from entered char to get
	//corresponding digit
	num = c - '0';

	return num;
}

int calculateExpression(struct queue *q) {
    char data, temp_opr, temp_op1, temp_op2;
    int operand1, operand2, value;

    while ((q->count != 1))
    {
        temp_opr = q->front->data;//we get the first data in the queue
        q = dequeue(q);//then remove in the queue
        if(ispunct(temp_opr))// if temp_opr is punctuation '+' or '_' or '*' or '/'
        {
            temp_op1 = q->front->data;//data pointer is pointing to the 2nd data in the queue
            //stringcopy(data1, dataptr); // copies the string pointed by dataptr to data1

            temp_op2= q->front->next->data;//data pointer is poiting to the 3rd data in the queue
            //stringcopy(data2,dataptr); // copies the string pointed by dataptr to data2
            if(!ispunct(temp_op1)&&!ispunct(temp_op2))
            {
                operand1 = charToInt(temp_op1);
                operand2 = charToInt(temp_op2);
                q = dequeue(q);
                q = dequeue(q);
                value = calculate(temp_opr, operand1, operand2);
                printf (" \n\nafter calculating %d %c %d = %d\n",operand1,temp_opr,operand2,value);
                data = (char)(value) + 0;
                //sprintf(data,"%d",value);
                q = enqueue(q, data);
                display(q);
            }
            else
            {
                q = enqueue(q, temp_opr);
                display(q);
            }
        }
        else
        {
            q = enqueue(q, temp_opr);
            display(q);
        }
    }
    q = dequeue(q);
    return atoi(data);
}

int main()
{
    char expr[128];
    q = create_queue();
    printf("!!!Do not forget spacing!!!");
    printf("\nEnter prefix expression: ");
    gets(expr);

    for(int i = 0; i < strlen(expr); i++){
            if(expr[i] != 32) {
                q = enqueue(q, expr[i]);
            }
    }
    int finalvalue = calculateExpression(q);
    printf("\n\n value of the expression %d", finalvalue);
}
