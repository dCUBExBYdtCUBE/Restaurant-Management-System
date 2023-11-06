#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct item {
    char name[100];
    int price;
    int time;
} ITEM;

ITEM menu[10] = {
    {"tomato soup", 90, 20},
    {"sweet corn soup", 90, 20},
    {"gobi manchurian", 130, 25},
    {"paneer manchurian", 140, 25},
    {"dal tadka", 120, 25},
    {"paneer butter masala", 150, 30},
    {"butter kulcha", 70, 20},
    {"pulao", 140, 30},
    {"ghee rice", 110, 25},
    {"buttermilk", 40, 15}
};

typedef struct order {
    char f_name[100];
    int quantity;
    int cost;
    struct order* prev, * next;
} ORDER;


typedef struct queue1 {
    ORDER* front, * rear;
} QUEUE;


void init(QUEUE* ord) {
    ord->front = NULL;
    ord->rear = NULL;
}


ORDER* create_node() {
    ORDER* temp = malloc(sizeof(ORDER));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

char* addtime() {
    time_t rawtime;
    struct tm* timeinfo;
    char* buffer = (char*)malloc(30);

    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}


void insert_item(QUEUE* ord, char* item, int quantity) {
    ORDER* temp = create_node();
    strcpy(temp->f_name, item);
    temp->quantity = quantity;


    for (int i = 0; i < 10; i++) {
        if (strcmp(menu[i].name, item) == 0) {
            temp->cost = menu[i].price * quantity;
            break;
        }
    }

    if (ord->front == NULL && ord->rear == NULL) {
        ord->front = temp;
        ord->rear = temp;
    } else {
        ord->rear->next = temp;
        temp->prev = ord->rear;
        ord->rear = temp;
    }
}


void remove_item(QUEUE* ord, char* item) {
    ORDER* f;
    if (ord->front == NULL && ord->rear == NULL) {
        printf("Order List is Empty\n");
    } else if (strcmp(ord->front->f_name, item) == 0) {
        f = ord->front;
        ord->front = ord->front->next;
        if (ord->front != NULL) {
            ord->front->prev = NULL;
        } else {
            ord->rear = NULL;
        }
        free(f);
    } else if (strcmp(ord->rear->f_name, item) == 0) {
        f = ord->rear;
        ord->rear = ord->rear->prev;
        if (ord->rear != NULL) {
            ord->rear->next = NULL;
        } else {
            ord->front = NULL;
        }
        free(f);
    } else {
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


void disp_menu() {
    printf("MENU \n\n");
    printf("Serial No.\tNAME\t\t\t\tPrice\t\tTime\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\t\t%s\t\t%d\t\t%d\n", i + 1, menu[i].name, menu[i].price, menu[i].time);
    }
}


void disp_order(QUEUE* ord) {
    printf("The Order List is:\n");
    ORDER* l = ord->front;
    while (l != ord->rear) {
        printf("%s  %d  %d\n", l->f_name, l->quantity, l->cost);
        l = l->next;
    }
    printf("%s  %d  %d\n", l->f_name, l->quantity, l->cost);
}


int total_bill(QUEUE* ord) {
    ORDER* l = ord->front;
    int sum = 0;

    while (l != NULL) {
        sum += l->cost;
        l = l->next;
    }

    return sum;
}



typedef struct p_details {
    char name[100];
    char phone[100];
    char email[100];
    char time[30];
    int t_cost;
    struct p_details* next, * prev;
} DETAILS;


typedef struct queue {
    DETAILS* front, * rear;
} QUEUE_DETAILS;


void init1(QUEUE_DETAILS* det) {
    det->front = NULL;
    det->rear = NULL;
}


DETAILS* create_details_node() {
    DETAILS* temp = malloc(sizeof(DETAILS));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}


void insert_pd(QUEUE_DETAILS* det) {
    DETAILS* temp = create_details_node();
    printf("Enter the details\n");
    printf("Enter name: ");
    scanf("%99s", temp->name);
    printf("Enter mobile number: ");
    scanf("%10s", temp->phone);
    printf("Enter email: ");
    scanf("%99s", temp->email);
    temp->t_cost = 0;

    // Get and set the current time
    char* timestamp = addtime();
    strcpy(temp->time, timestamp);

    if (det->front == NULL && det->rear == NULL) {
        det->front = temp;
        det->rear = temp;
    } else {
        det->rear->next = temp;
        temp->prev = det->rear;
        det->rear = temp;
    }
}


int delete_pd(QUEUE_DETAILS* det) {
    DETAILS* l;
    if (det->front == NULL) {
        printf("The Queue is empty\n");
        return 0;
    } else if (det->front == det->rear) {
        l = det->front;
        det->front = NULL;
        det->rear = NULL;
    } else {
        l = det->front;
        det->front = det->front->next;
        det->front->prev = NULL;
    }

    printf("Customer %s deleted.\n", l->name);
    int totalCost = l->t_cost;
    free(l);
    return totalCost;
}


void display(QUEUE_DETAILS* det) {
    printf("The Queue is: \n");
    DETAILS* l = det->front;
    if (det->front == NULL) {
        printf("Empty Queue\n");
    } else {
        while (l != det->rear) {
            printf("%s  %s  %s  %s  %d \n", l->name, l->phone, l->email, l->time, l->t_cost);
            l = l->next;
        }
        printf("%s  %s  %s  %s  %d\n", l->name, l->phone, l->email, l->time, l->t_cost);
    }
}




int main() {
    
    QUEUE_DETAILS det;
    DETAILS* l;
    init1(&det);

    int choice;
    int customerId = 1; 

    do {
        printf("Press 1 to add new customer, Press 2 to delete customer, Press 3 to view customer list, and Press 0 to exit: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert_pd(&det);
                printf("Customer %d added.\n", customerId);
                customerId++;
                break;
            case 2:
                if (det.front != NULL) {
                    int totalCost = delete_pd(&det);
                    printf("Total bill for the customer: %d\n", totalCost);
                } else {
                    printf("No customers to delete.\n");
                }
                break;
            case 3:
                display(&det);
                break;
        }
    } while (choice != 0);

    printf("\nCustomer Orders Management:\n");

    while (1) {
        int orderChoice;
        printf("Enter the customer ID (1-%d) or 0 to exit: ", customerId - 1);
        scanf("%d", &orderChoice);

        if (orderChoice == 0) {
            break;
        } else if (orderChoice < 1 || orderChoice >= customerId) {
            printf("Invalid customer ID. Please enter a valid customer ID.\n");
        } else {
            printf("Customer %d, give your order:\n", orderChoice);

            QUEUE ord;
            init(&ord);
            int totalCost = 0;

            disp_menu();
            while (1) {
                int menuChoice;
                
                printf("Enter the serial number of the item you want to order (1-10) or 0 to finish your order: ");
                scanf("%d", &menuChoice);

                if (menuChoice == 0) {
                    break;
                } else if (menuChoice < 1 || menuChoice > 10) {
                    printf("Invalid menu item. Please enter a valid serial number.\n");
                } else {
                    int quantity;
                    printf("Enter the quantity: ");
                    scanf("%d", &quantity);
                    int itemIndex = menuChoice - 1;
                    insert_item(&ord, menu[itemIndex].name, quantity);
                    totalCost += (menu[itemIndex].price * quantity);
                    printf("Order added to your bill.\n");
                }
            }

            totalCost += total_bill(&ord);
            l = det.front;

            while (l != det.rear && strcmp(l->name, "Customer") != 0) {
                l = l->next;
            }
            l->t_cost = totalCost;

            printf("Your order:\n");
            disp_order(&ord);
            printf("Total bill for the customer: %d\n", totalCost/2);
        }
    }

    return 0;
}