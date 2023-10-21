#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct p_details{
    char name[100];
    char phone[100];
    char email[100];
    int t_cost;
    struct p_details*next,*prev;
}DETAILS;


typedef struct queue{
    DETAILS*front,*rear;
}QUEUE;


void init1(QUEUE*det)
{
    det->front=NULL;
    det->rear=NULL;
}

DETAILS*create()
{
    DETAILS*temp=malloc(sizeof(DETAILS));
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

DETAILS*insert_pd(QUEUE*det)
{
    DETAILS*temp=create();
    printf("Enter the details\n");
    printf("Enter name: ");
    scanf("%99s",temp->name);
    printf("Enter mobile number: ");
    scanf("%10s",temp->phone);
    printf("Enter email: ");
    scanf("%99s",temp->email);
    temp->t_cost=0; 


    if(det->rear==NULL && det->front==NULL)
    {
        det->front=temp;
        det->rear=temp;
    }
    else
    {
        det->rear->next=temp;
        temp->prev=det->rear;
        det->rear=temp;
    }
    return temp;  
}



void display(QUEUE*det)
{
    printf("The Queue is: \n");
    DETAILS*l=det->front;
    if(det->front==NULL)
    {
        printf("Empty Queue\n");
    }
    else
    {
        while(l!=det->rear){
            printf("%s  %s  %s  %d\n",l->name,l->phone,l->email,l->t_cost);
            l=l->next;
        }
        printf("%s  %s  %s  %d\n",l->name,l->phone,l->email,l->t_cost);
    }

}



int main()
{
    QUEUE*det=malloc(sizeof(QUEUE));
    init1(det);
    int n;
    do
    {
        insert_pd(det);
        printf("Press 1 to add new dude and 0 to exit: ");
        scanf("%d",&n);
    }while(n!=0);
    display(det);
}



