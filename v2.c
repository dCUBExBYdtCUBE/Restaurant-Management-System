#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SEATS 5

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
    char item_name[100];
    int quantity;
    int cost;
    int time;
    int table_num;
    struct order* next;
} ORDER;

typedef struct queue1 {
    ORDER* front, * rear;
} QUEUE;

// occupied_table structure for the elements in the queue
typedef struct occupied_table {
    int data;
    int table_num;
    struct occupied_table* next;
} occupied_table;

// Queue_of_occupied_tables structure
typedef struct{
    occupied_table* front;
    occupied_table* rear;
} Queue_of_occupied_tables;

void init_bill(QUEUE* ord) {
    ord->front = NULL;
    ord->rear = NULL;
}

ORDER* create_node() {
    ORDER* temp = malloc(sizeof(ORDER));
    temp->next = NULL;
    return temp;
}

void insert_item(QUEUE* ord, char* item, int quantity, int orderTime, int seatNumber) {
    ORDER* temp = create_node();
    strcpy(temp->item_name, item);
    temp->quantity = quantity;
    temp->time = orderTime;  // Set order time
    temp->table_num = seatNumber;  // Set seat number

    for (int i = 0; i < 10; i++) {
        if (strcmp(menu[i].name, item) == 0) {
            temp->cost = menu[i].price * quantity;
            break;
        }
    }

    // Insert into the linked list maintaining ascending order based on time
    if (ord->front == NULL) {
        ord->front = temp;
        ord->rear = temp;
    } else {
        ORDER* current = ord->front;
        ORDER* prev = NULL;

        while (current != NULL && current->time < temp->time) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            // Insert at the beginning
            temp->next = ord->front;
            ord->front = temp;
        } else {
            // Insert in the middle or at the end
            prev->next = temp;
            temp->next = current;

            if (current == NULL) {
                ord->rear = temp;  // Update rear if inserted at the end
            }
        }
    }
}


void disp_menu() {
    printf("MENU \n\n");
    printf("Serial No.\tNAME\t\t\tPrice\t\tTime\n");

    for (int i = 0; i < 10; i++) {
        printf("%d\t\t%-20s\tRs.%d\t\t%d\n", i + 1, menu[i].name, menu[i].price, menu[i].time);
    }
}

void disp_order(QUEUE* ord) {
    printf("The Order List is:\n");
    ORDER* l = ord->front;
    while (l != NULL) {
        printf("%-15s  %d  %d\n", l->item_name, l->quantity, l->cost);
        l = l->next;
    }
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
    char name[50];
    char phone[12];
    char email[50];
    int t_cost;
    int tableNumber;
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

void clear_orders(QUEUE* ord) {
    ORDER* current = ord->front;
    ORDER* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    ord->front = NULL;
    ord->rear = NULL;
}


void insert_pd(QUEUE_DETAILS* det,int tableNumber) {
    DETAILS* temp = create_details_node();
    printf("Enter the details\n");
    printf("Enter name: ");
    scanf("%99s", temp->name);
    printf("Enter mobile number: ");
    scanf("%10s", temp->phone);
    printf("Enter email: ");
    scanf("%99s", temp->email);
    temp->t_cost = 0;
    temp->tableNumber = tableNumber;  // Store the table number

    if (det->front == NULL && det->rear == NULL) {
        det->front = temp;
        det->rear = temp;
    } else {
        det->rear->next = temp;
        temp->prev = det->rear;
        det->rear = temp;
    }
}

void display(QUEUE_DETAILS* det) {
    printf("The Queue_of_occupied_tables is: \n");
    DETAILS* l = det->front;
    if (det->front == NULL) {
        printf("Empty Queue_of_occupied_tables\n");
    } else {
        while (l != det->rear) {
            printf("%s  %s  %s  %d \n", l->name, l->phone, l->email, l->t_cost);
            l = l->next;
        }
        printf("%s  %s  %s  %d\n", l->name, l->phone, l->email, l->t_cost);
    }
}

void prepare_orders(ORDER orders[], int orderCount) {
    printf("PREPARATION COUNTER \n\n");
    printf("Serial No.\tStatus\n");

    // Simulating order preparation (set all orders as prepared in this example)
    for (int i = 0; i < orderCount; i++) {
        printf("%d\t%-15s\t%d\t%s\n",i+1, orders[i].item_name,orders[i].quantity, "Prepared");
    }
}

//code for the binary tree operations
typedef struct TreeNode {
    int seatNumber;
    Queue_of_occupied_tables* ordersQueue;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int seatNumber) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    newNode->seatNumber = seatNumber;
    newNode->ordersQueue = NULL;
    newNode->left = newNode->right = NULL;

    return newNode;
}

// Function to insert a node into the binary tree
TreeNode* insert(TreeNode* root, int seatNumber) {
    if (root == NULL) {
        return createNode(seatNumber);
    }

    if (seatNumber < root->seatNumber) {
        root->left = insert(root->left, seatNumber);
    } else if (seatNumber > root->seatNumber) {
        root->right = insert(root->right, seatNumber);
    }

    return root;
}

TreeNode* search(TreeNode* root, int seatNumber) {
    if (root == NULL || root->seatNumber == seatNumber) {
        return root;
    }

    if (seatNumber < root->seatNumber) {
        return search(root->left, seatNumber);
    } else {
        return search(root->right, seatNumber);
    }
}

void updateOccupancy(TreeNode* root, int seatNumber, Queue_of_occupied_tables* ordersQueue) {
    TreeNode* seatNode = search(root, seatNumber);
    if (seatNode != NULL) {
        enqueue(ordersQueue, seatNode,seatNumber);
    } else {
        printf("Seat number %d not found.\n", seatNumber);
    }
}
// Function to display the occupancy status of all seat numbers (in-order traversal)
void displayOccupancy(TreeNode* root) {
    if (root != NULL) {
        displayOccupancy(root->left);

        if (root->ordersQueue != NULL) {
            printf("Seat Number: %d, Occupied: Yes\n", root->seatNumber);
        } else {
            printf("Seat Number: %d, Occupied: No\n", root->seatNumber);
        }

        displayOccupancy(root->right);
    }
}

int areAllTablesOccupied(TreeNode* seatTree) {
    if (seatTree == NULL) {
        // Tree is empty, so technically all tables are occupied
        return 1;
    }

    // Check each node for occupancy
    while (seatTree != NULL) {
        if (seatTree->ordersQueue == NULL) {
            // If any table is unoccupied, return false
            return 0;
        }
        seatTree = seatTree->right;
    }

    // If all tables are occupied, return true
    return 1;
}


void initQueue(Queue_of_occupied_tables* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueue(Queue_of_occupied_tables* queue, TreeNode* seatNode, int tableNumber) {
    occupied_table* newOccupiedTable = (occupied_table*)malloc(sizeof(occupied_table));
    if (newOccupiedTable == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    newOccupiedTable->data = seatNode->seatNumber;
    newOccupiedTable->table_num = tableNumber;  // Set the table number
    newOccupiedTable->next = NULL;

    // Update the ordersQueue in the TreeNode structure
    seatNode->ordersQueue = queue;

    if (queue->rear == NULL) {
        queue->front = newOccupiedTable;
        queue->rear = newOccupiedTable;
    } else {
        queue->rear->next = newOccupiedTable;
        queue->rear = newOccupiedTable;
    }
}

int delete_pd(QUEUE_DETAILS* det, TreeNode* seatTree) {
    DETAILS* l;
    int totalCost=0;
    if (det->front == NULL) {
        printf("The queue is empty\n");
        return totalCost;
    } else if (det->front == det->rear) {
        l = det->front;
        det->front = NULL;
        det->rear = NULL;
    } else {
        l = det->front;
        det->front = det->front->next;
        if (det->front != NULL) {
            det->front->prev = NULL;
        }
    }

    printf("Customer %s deleted from table %d.\n", l->name, l->tableNumber);

    // Reset the information associated with the corresponding seat node
    int tableNumber = l->tableNumber;
    totalCost=l->t_cost;
    // Check if seatTree is not NULL before calling search
    if (seatTree != NULL) {
        TreeNode* seatNode = search(seatTree, tableNumber);
        if (seatNode != NULL) {
            // Clear the ordersQueue for the seatNode
            initQueue(seatNode->ordersQueue);
            printf("Table %d is now unoccupied.\n", tableNumber);
        } else {
            printf("Error: Corresponding seat node not found for table %d.\n", tableNumber);
        }
    } else {
        printf("Error: seatTree is NULL\n");
    }

    free(l);

    return totalCost;
}



void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int seat_customer(TreeNode* seatTree, Queue_of_occupied_tables* servingQueue, int seatNumber) {
    int check = areAllTablesOccupied(seatTree);
    if (check == 1) {
        return -1;
    }

    // Validate seat number
    if (seatNumber > MAX_SEATS || seatNumber <= 0) {
        printf("Invalid table number\n");
        return 0;
    }

    TreeNode* seatNode = search(seatTree, seatNumber);
    if (seatNode != NULL) {
        // Check if the seat is already occupied
        if (seatNode->ordersQueue != NULL) {
            printf("The table is already occupied.\n");
            return 0;
        } else {
            enqueue(servingQueue, seatNode, seatNumber);
            printf("Customer seated at table number %d.\n", seatNumber);
            return 1;
        }
    } else {
        printf("Invalid seat number. Please enter a valid seat number.\n");
        return 0;
    }
}


void displayAvailableSeats(TreeNode* seatTree) {
    printf("Available Seats:\n");
    displayOccupancy(seatTree);
}

void add_customer_and_order(TreeNode* seatTree, Queue_of_occupied_tables* servingQueue, QUEUE_DETAILS* det, QUEUE* ord, int* customerId, ORDER orders[], int* orderCount) {

    // Check for available seats and update the binary tree
    int seatNumber;

    // Display available seats
    displayAvailableSeats(seatTree);

    printf("Enter seat number to seat the customer: ");
    if (scanf("%d", &seatNumber) != 1) {
        // Handle invalid input
        printf("Invalid input. Please enter a valid seat number.\n");
        return;
    }

    // Step 1: Seat the customer
    int seatResult = seat_customer(seatTree, servingQueue, seatNumber);

    if (seatResult == 1) {
        // Step 2: Insert customer details
        insert_pd(det,seatNumber);

        // Set the customer's name
        sprintf(orders[*orderCount].item_name, "Customer %d", *customerId);
        (*customerId)++;

        int totalCost = 0;
        clear_orders(ord);

        // Display the menu and take orders
        int menuChoice;

        while (1) {
            disp_menu();
            printf("Enter the serial number of the item you want to order (1-10) or 0 to finish your order: ");
            if (scanf("%d", &menuChoice) != 1) {
                // Handle invalid input
                printf("Invalid input. Please enter a valid menu item.\n");
                break;
            }

            if (menuChoice == 0) {
                break;
            } else if (menuChoice < 1 || menuChoice > 10) {
                printf("Invalid menu item. Please enter a valid serial number.\n");
            } else if (*orderCount < 100) {
                int quantity;
                printf("Enter the quantity: ");
                if (scanf("%d", &quantity) != 1) {
                    // Handle invalid input
                    printf("Invalid input. Please enter a valid quantity.\n");
                    break;
                }

                int itemIndex = menuChoice - 1;
                insert_item(ord, menu[itemIndex].name, quantity, menu[itemIndex].time, seatNumber);

                // Store details for the current item
                strcpy(orders[*orderCount].item_name, menu[itemIndex].name);
                orders[*orderCount].quantity = quantity;
                orders[*orderCount].cost = menu[itemIndex].price * quantity;
                orders[*orderCount].time = menu[itemIndex].time;
                (*orderCount)++;
                totalCost += (menu[itemIndex].price * quantity);
                printf("Order added to your bill.\n");
            }
        }

        totalCost += total_bill(ord);

        // Update the total cost for the customer
        DETAILS* l = det->front;
        while (l != NULL && strcmp(l->name, orders[*orderCount].item_name) != 0) {
            l = l->next;
        }

        if (l != NULL) {
            l->t_cost = totalCost;
        }

        // Display the order and total bill for the customer
        printf("Your order:\n");
        disp_order(ord);
        printf("Total bill for the customer: %d\n", totalCost);
    } else if (seatResult == 0) {
        printf("The table is already occupied. Please choose another table.\n");
    } else if (seatResult == -1) {
        printf("We're sorry, but the restaurant is currently full. \nPlease wait for a table to become available or visit us at a later time.\n Thank you for your understanding.");
    }
}



int main() {
    QUEUE_DETAILS det;
    DETAILS* l;
    init1(&det);

    TreeNode* seatTree = NULL;
    Queue_of_occupied_tables servingQueue;
    initQueue(&servingQueue);

    int choice = 1;
    int customerId = 1;
    QUEUE ord;
    init_bill(&ord);
    ORDER orders[100];  // Assuming a maximum of 100 orders
    int orderCount = 0;

    for (int i = 1; i <= MAX_SEATS; i++) {
        seatTree = insert(seatTree, i);
    }

    do {
        int totalCost = 0;
        printf("\nPress 1 to add new customer, Press 2 to delete customer, Press 3 to view customer list, Press 4 to Prepare order, and Press 0 to exit: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_customer_and_order(seatTree, &servingQueue, &det, &ord, &customerId, orders, &orderCount);
                break;
            case 2:
                if (det.front != NULL) {
                    int totalCost = delete_pd(&det,seatTree);
                    // printf("Total bill for the customer: Rs.%d.00\n", totalCost);
                } else {
                    printf("No customers to delete.\n");
                }
                break;
            case 3:
                display(&det);
                break;
            case 4:
                // Assuming you want to mark specific orders as prepared
                printf("Enter the serial number of the order you want to mark as prepared: ");
                int orderNumber;
                scanf("%d", &orderNumber);

                // Validate the order number
                if (orderNumber >= 1 && orderNumber <= orderCount) {
                    // Mark the selected order as prepared
                    printf("Order %d (%s) is marked as prepared.\n", orderNumber, orders[orderNumber - 1].item_name);
                    // Additional logic if needed
                } else {
                    printf("Invalid order number. Please enter a valid order number.\n");
                }
                break;

            // case 5:
            //     seat_customer(seatTree, &servingQueue);
            //     break;

            case 0:
                printf("Exiting the program. Thank you!\n");
                break;
            }
        }while(choice);

        freeTree(seatTree);

    return 0;
}  