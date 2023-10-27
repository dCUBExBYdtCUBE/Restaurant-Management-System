#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct item
{
char name[100];
int price;
int time;
}ITEM;

typedef struct node
{
	int data;
	int occ;
	struct node *left, *right;
}NODE;

typedef struct btree
{
	NODE* root;
}BST;

void Default(BST* b)
{
	b->root=NULL;
}

NODE* init(int key)
{
	NODE* temp;
	temp=malloc(sizeof(NODE));
	temp->data=key;
	temp->occ=0;
	temp->left=NULL;
	temp->right=NULL;
}

void insert(BST *b, int key)
{
    NODE*temp=init(key);
	
    if(b->root==NULL)
        b->root=temp;
    else
    {
    NODE* befp=NULL;    
    NODE* p=b->root;
        while(p!=NULL)
        {
            if(p->data>=key)
            {
                befp=p;
                p=p->left;
            }
            else
            {
                befp=p;
                p=p->right;
            }
        }
        if(befp->data>key)
            befp->left=temp;
        else
            befp->right=temp;
    }
}


void inorder(NODE* p)
{
	if (p == NULL) {
        return;  
    }
	inorder(p->left);
	if(p->occ==0)
		printf("%d\n",p->data);
	inorder(p->right);
}

void occupied(NODE* p, int x)
{
    if (p==NULL)
	{
        return;
	}
    if((p)->data == x)
        (p)->occ=1;
    if((p)->data > x)
        occupied(p->left, x);
    else         
		occupied(p->right, x);
}



void vacant(NODE* p, int x)
{
    if (p==NULL)
	{
        return;
	}
    if((p)->data == x)
        (p)->occ=0;
    if((p)->data > x)
        vacant(p->left, x);
    else         
		vacant(p->right, x);
}


int main()
{
BST B;
int table,com,k;
int ch,x=1;
Default(&B);

ITEM a[10]= {{"tomato soup",90,20},{"sweet corn soup",90,20},{"gobi manchurian",130,25},{"paneer manchurian",140,25},{"dal tadka",120,25},{"paneer butter masala",150,30},{"butter kulcha",70,20},{"pulao",140,30},{"ghee rice",110,25},{"buttermilk",40,15}};
printf("MENU \n\n");
printf("NAME\t\t\t\t\tPrice\t\tTime\n");
for(int i=0;i<10;i++)
{
	
	printf("%s\t\t%d\t\t%d\n",a[i].name,a[i].price,a[i].time);
}
/*
printf("please place your order\n");
do
	{
		printf("\n 1-add item, 2-delete item, 3-empty 4-exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: 
					break;
			case 2:	
					break;
			case 3: 
					break;	
			case 4: exit(0);
			default: printf("enter valid option");
		}
	}while(ch!=0);
return 0;
}

*/

for(int i=0; i<15; i++)
{
	k= rand() % 100 + 1;
	insert(&B,k);
}

printf("get ready for voila experience!!");


while(x!=0)
{
printf("unoccupied tables: \n");
inorder(B.root);


printf("\nassign a table: ");
scanf("%d",&table);
vacant(B.root, table);
occupied(B.root, table);

scanf("%d",&x);
}

return 0;
}

