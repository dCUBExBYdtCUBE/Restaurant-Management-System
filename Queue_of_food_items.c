#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct order{
    char f_name[100];
    struct order*prev,*next;
    int cost;
    int num;

}ORDER;

typedef struct queue1{
    ORDER*front,*rear;
}QUEUE;


void init(QUEUE*ord)
{
    ord->front=NULL;
    ord->rear=NULL;
}

ORDER* create_node()
{
    ORDER*temp=malloc(sizeof(ORDER));
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

void insert_item(QUEUE*ord)
{
    ORDER*temp=create_node();
    printf("Enter your Order List\n");
    printf("Enter the item: ");
    scanf("%99s",&temp->f_name);
    printf("Enter the cost: ");
    scanf("%d",&temp->cost);
    printf("Enter number of times: ");
    scanf("%d",&temp->num);

    if(ord->front==NULL && ord->rear==NULL)
    {
        ord->front=temp;
        ord->rear=temp;
    }
    else
    {
        ord->rear->next=temp;
        temp->prev=ord->rear;
        ord->rear=temp;
    }
}

void remove_item(QUEUE* ord, char* item) {
    ORDER* f;
    if (ord->front == NULL && ord->rear == NULL) {
        printf("Order List is Empty\n");
    } 
    else if (strcmp(ord->front->f_name, item) == 0) {
        f = ord->front;
        ord->front = ord->front->next;
        if (ord->front != NULL) {
            ord->front->prev = NULL;
        } else {
            ord->rear = NULL;
        }
        free(f);
    } 
    else if (strcmp(ord->rear->f_name, item) == 0) {
        f = ord->rear;
        ord->rear = ord->rear->prev;
        if (ord->rear != NULL) {
            ord->rear->next = NULL;
        } else {
            ord->front = NULL;
        }
        free(f);
    } 
    else {
        f = ord->front;
        while (f != NULL && strcmp(f->f_name, item) != 0) {
            f = f->next;
        }
        if (f == NULL) {
            printf("Item not Found\n");
        } else {
            f->prev->next = f->next;
            if (f->next != NULL) {
                f->next->prev = f->prev;
            } else {
                ord->rear = f->prev;
            }
            free(f);
        }
    }
}


void disp_menu()
{
    printf("The menu is empty as of now\n");
}

void disp_order(QUEUE*ord)
{
    printf("The Order List is:\n");
    ORDER*l=ord->front;
    while(l!=ord->rear)
    {
        printf("%s  %d  %d\n",l->f_name,l->cost,l->num);
        l=l->next;
    }
    printf("%s  %d  %d\n",l->f_name,l->cost,l->num);
}

void total_bill(QUEUE*ord)
{
    ORDER*l=ord->front;
    int sum=0;
    int choice,tip_choice;
    while(l!=ord->rear)
    {
        sum=sum+(l->cost*l->num);
        l=l->next;
    }
    sum=sum+(l->cost*l->num);
    printf("Would you like to add a tip?: ");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("Enter the tip amount: ");
        scanf("%d",&tip_choice);
    }
    printf("Your total bill is: \n");
    printf("%d",sum+tip_choice);
}



int main()
{
    QUEUE*ord;
    ORDER*l;
    char item[100];
    init(ord);
    int n;
    do{
        printf("Press 1 to add new item, Press 2 to delete item, Press 3 to display menu, Press 4 to display items and Press 0 to confirm order\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:insert_item(ord);break;
            case 2:printf("Enter the item name to be removed: ");
                    scanf("%99s",item);
                    remove_item(ord,item);break;
            case 3:disp_menu();break;
            case 4:disp_order(ord);break;
        }
    }while(n!=0);
    total_bill(ord);
}