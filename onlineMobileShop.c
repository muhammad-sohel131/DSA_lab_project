#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

void owner();
void customer();
void orders();

int login(int pass);

void addProduct();
void displayProdcuts();
void deleteClient();
int existProduct(char name[]);


typedef struct Products product;
product *create_node();

struct Products
{
    int id;
    char name[50];
    char description[100];
    int price;
    product *next;
};

product *head = NULL;

int card[10];
int cardCounter = 0;
void sortCard(int arr[], int count);
int exitInCard(int arr[], int count, int id);
void myCard();

int main()
{
    int option;
    printf("--------------------\n");
    printf("The online Mobile Shop\n");
    printf("--------------------\n\n");

    srand(time(0));
    while(1)
    {
        printf("1. Are you a customer?\n");
        printf("2. Are you Owner of this shop?\n");
        printf("3. Exit\n");

        scanf("%d", &option);

        if(option == 1)
        {
            customer();
        }
        else if(option == 2)
        {
            owner();
        }
        else if(option == 3)
        {
            exit(1);
        }
        else
        {
            printf("Invalid Input! Please, input 1 or 2.\n");
        }
    }

    return 0;
}

int login(int pass){
    int myPass = 1100;
    if(myPass == pass){
        return 1;
    }
    return 0;
}

void owner(){
    int pass, islogin, choice;

    printf("------Login------\n");
    printf("Please, enter the your password: ");
    scanf("%d", &pass);

    islogin = login(pass);
    if(!islogin){
        printf("Incorrect Password!\n");
        owner();
    }else {
        printf("Welcome to Dashboard\n");

        do{
            printf("1. Add Product\n");
            printf("2. Display Products\n");
            printf("3. Orders\n");
            printf("4. Back to Previous Menu\n");

            scanf("%d", &choice);
            switch(choice){
            case 1:
                addProduct();
                break;
            case 2:
                displayProdcuts();
                break;
            case 3:
                orders();
                break;
            case 4:
                return ;
                break;
            default:
                printf("Invalid input!/n");
            }
        }while(1);
    }
}
void customer(){
    int choice;

    printf("Welcome to our shop\n");

    do {
        printf("1. Show All The Mobile Phones\n");
        printf("2. Search Phone by Name\n");
        printf("3. My Card\n");
        printf("4. Back to Previous Menu\n");

        scanf("%d", &choice);

        switch(choice){
        case 1:
            displayProdcuts();
            break;
        case 2:
            findByName();
            break;
        case 3:
            myCard();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("Invalid Input!");
        }
    }while(1);
}
product *create_node()
{
    product *newNode = malloc(sizeof(product));
    newNode -> next = NULL;
    newNode -> id = rand();

    return newNode;
}

void addProduct()
{
    int found;

    product *new_product = create_node();

    printf("Put details of product - \n");
    printf("--------------------\n\n");

    printf("Enter the name of the Mobile: ");
    scanf(" %[^\n]", new_product -> name);
    printf("Enter the price of the Mobile: ");
    scanf("%d", &new_product -> price);
    printf("Enter the a short description: ");
    scanf(" %[^\n]", new_product -> description);

    if(head == NULL)
    {
        head = new_product;
        printf("The mobile is uploaded!\n");
        return ;
    }

    found = existProduct(new_product -> name);

    if(found != 0)
    {
        printf("The phone is already registered!\n");
    }
    else
    {
        product *temp = head;
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = new_product;
        printf("The mobile is uploaded!\n");
        return ;
    }

}

void displayProdcuts()
{
    int i = 1;

    product *temp = head;

    printf("Product List: \n");
    printf("--------------------\n");

    if(head == NULL)
    {
        printf("There is no product!\n");
        return ;
    }
    while(temp != NULL)
    {
        printf("%d. Name: %s  Price: %d  description: %s\n",i++, temp -> name, temp -> price, temp -> description);
        temp = temp -> next;
    }

    printf("\n");
    return 0;
}



void findByName()
{
    int isExit, option;
    char name[20], savedName[20];
    product *temp = head;

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
        printf("Name: %s  \nPrice: %d  \nDescription: %s\n", temp -> name, temp -> price, temp -> description);

        while(1)
        {
            printf("1. Add to card\n");
            printf("2. Back to previous menu\n");

            scanf("%d", &option);

            if(option == 1)
            {
                if(cardCounter >= 2){
                    isExit = exitInCard(card, cardCounter, temp->id);
                    if(isExit == -1){
                        printf("The mobile is already in card!\n");
                        return ;
                    }
                }
                card[cardCounter++] = temp->id;

            }
            else if(option == 2)
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

int existProduct(char name[])
{
    int found = 0;
    product *temp = head;
    while(temp != NULL)
    {
        if(!strcmp(name, temp -> name))
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

void sortCard(int arr[], int count){
    //used bubble sort
    int i,j,temp;
    for(i = 0; i < count - 1; i++){
        for(j = 1; j < count - i; j++){
            if(arr[i] > arr[j]){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

}

int exitInCard(int arr[], int count, int id){
    //used binary search
     sortCard(arr, count);

     int start, end, mid;
     start = 0;
     end = count;
     while(start <= end){
        mid = (start + mid) / 2;
        if(card[mid] == id){
            return mid;
        }
        if(card[mid] > id){
            end = mid - 1;
        }else {
            start = mid + 1;
        }
     }
     return -1;

}

void myCard(){
    int i,j = 1;
    product *temp;
    if(cardCounter == 0){
        printf("The card is empty!\n");
    }else {
        temp = head;
        while(temp != NULL){
            for(i=0; i < cardCounter; i++){
                if(temp->id == card[i]){
                    printf("%d. Name: %s  Price: %d  Description: %s.\n", j++, temp->name, temp->price, temp->description);
                }
            }
            temp = temp -> next;
        }
    }
}
void orders(){

}
