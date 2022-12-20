#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void registerClient();
void showAllClient();
void deleteClient();
int existClient(char phone[]);


typedef struct Clients client;
client *create_node();

struct Clients
{
    char name[50];
    char phone[20];
    int totalBill;
    int totalPaid;
    client *next;
};

client *head = NULL;

int main()
{
    int option;
    printf("--------------------\n");
    printf("Client Management\n");
    printf("--------------------\n\n");


    while(1)
    {
        printf("1. Register a Client\n");
        printf("2. List of all Clients\n");
        printf("3. Search By Name \n");
        printf("4. Search By Phone Number \n");
        printf("5. Exit\n");

        scanf("%d", &option);

        if(option == 1)
        {
            registerClient();
        }
        else if(option == 2)
        {
            showAllClient();
        }
        else if(option == 3)
        {
            findByName();
        }
        else if(option == 4)
        {
            findByPhone();
        }
        else if(option == 5)
        {
            exit(1);
        }
        else
        {
            printf("Invalid Input\n");
        }
    }

    return 0;
}

client *create_node()
{
    client *newNode = malloc(sizeof(client));
    newNode -> totalBill = 0;
    newNode -> totalPaid = 0;
    newNode -> next = NULL;

    return newNode;
}

void registerClient()
{
    int found;

    client *new_client = create_node();

    printf("You are going to register a client - \n");
    printf("--------------------\n\n");

    printf("Enter the name of the client: ");
    scanf(" %[^\n]", new_client -> name);
    printf("Enter the phone number of the client: ");
    scanf(" %[^\n]", new_client -> phone);

    if(head == NULL)
    {
        head = new_client;
        printf("The client is registered!\n");
        return ;
    }

    found = existClient(new_client -> phone);

    if(found != 0)
    {
        printf("The phone is already registered!\n");
    }
    else
    {
        client *temp = head;
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = new_client;
        printf("The client is registered!\n");
        return ;
    }

}

void showAllClient()
{
    int total, i = 1;

    client *temp = head;

    printf("List of all clients: \n");
    printf("--------------------\n");

    if(head == NULL)
    {
        printf("There is no client!\n");
        return ;
    }
    while(temp != NULL)
    {
        total = temp -> totalBill - temp -> totalPaid;
        printf("%d. Name: %s  Phone: %s  Due: %d\n",i++, temp -> name, temp -> phone, total);
        temp = temp -> next;
    }

    printf("\n");
    return 0;
}

void findByPhone()
{
    char phone[20];
    client *temp = head;
    int bill, paid, total, option;

    printf("Please enter phone number: ");
    scanf("%s", phone);


    while(temp != NULL)
    {
        if(!strcmp(temp -> phone, phone))
        {
            break;
        }
        temp = temp -> next;
    }

    if(temp != NULL)
    {
        total = temp -> totalBill - temp -> totalPaid;
        printf("Name: %s  \nPhone: %s  \nDue: %d\n", temp -> name, temp -> phone, total);

        while(1)
        {
            printf("1. Add Bill\n");
            printf("2. Add Diposit\n");
            printf("3. Delete Account \n");
            printf("4. Back to Main Menu \n");

            scanf("%d", &option);

            if(option == 1)
            {
                printf("Please, enter the bill: ");
                scanf("%d", &bill);
                temp -> totalBill += bill;
                printf("The bill is added!\nYour current due is %d", temp -> totalBill - temp -> totalPaid);
            }
            else if(option == 2)
            {

            }
            else if(option == 3)
            {

            }
            else if(option == 4)
            {
                return ;
            }
            else
            {
                printf("Invalid Input\n");
            }
        }
    }

    printf("Not found!\n");

    return 0;

}

void findByName()
{
    int total, option;
    char name[20], savedName[20];
    client *temp = head;

    printf("Please Enter Name: ");
    scanf(" %[^\n]", name);


    while(temp != NULL)
    {
        strcpy(savedName, temp -> name);
        if(!strcmp(strlwr(savedName), strlwr(name)))
        {
            break;
        }
        temp = temp -> next;
    }

    if(temp != NULL)
    {
        total = temp -> totalBill - temp -> totalPaid;
        printf("Name: %s  \nPhone: %s  \nDue: %d\n", temp -> name, temp -> phone, total);

        while(1)
        {
            printf("1. Add Bill\n");
            printf("2. Add Diposit\n");
            printf("3. Delete Account \n");
            printf("4. Back to Main Menu \n");

            scanf("%d", &option);

            if(option == 1)
            {

            }
            else if(option == 2)
            {

            }
            else if(option == 3)
            {

            }
            else if(option == 4)
            {
                return ;
            }
            else
            {
                printf("Invalid Input\n");
            }
        }
    }

    printf("Not found!\n");

}

void deleteClient()
{

}

int existClient(char phone[])
{
    int found = 0;
    client *temp = head;
    while(temp != NULL)
    {
        if(!strcmp(phone, temp -> phone))
        {
            found = 1;
            break;
        }
        temp = temp -> next;
    }

    if(found == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
