#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct p_details{
    char name[100];
    char phone[100];
    char email[100];
    char time[30];
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

char*addtime()
{
    time_t rawtime;
    struct tm *timeinfo;
    static char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
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
    strcpy(temp->time,addtime());


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

DETAILS*delete_pd(QUEUE*det)
{
    DETAILS*l;
    if(det->front==NULL)
    {
        printf("The Queue is empty\n");
    }
    else if(det->front==det->rear)
    {
        l=det->front;
        det->front=NULL;
        det->rear=NULL;
    }
    else
    {
        l=det->front;
        det->front=det->front->next;
        det->front->prev=NULL;
        
    }
    return l;
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
            printf("%s  %s  %s  %s  %d \n",l->name,l->phone,l->email,l->time,l->t_cost);
            l=l->next;
        }
        printf("%s  %s  %s  %s  %d\n",l->name,l->phone,l->email,l->time,l->t_cost);
    }

}



int main()
{
    QUEUE*det=malloc(sizeof(QUEUE));
    DETAILS*l;
    init1(det);
    int n;
    insert_pd(det);
    do
    {
        printf("Press 1 to add new dude, Press 2 to delete first dude and Press 3 to view the Queue and 0 to exit: ");
        scanf("%d",&n);
        switch(n)
        {
        case 1:insert_pd(det);break;
        case 2:l=delete_pd(det);
                    printf("%s  %s  %s  %s  %d\n",l->name,l->phone,l->email,l->time,l->t_cost);
                    free(l);break;
        case 3:display(det);break;
        }
    }while(n!=0);
}



