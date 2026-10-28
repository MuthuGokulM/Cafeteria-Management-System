#ifndef PRODUCTS_H
#define PRODUCTS_H

#define MAX_NAME 50
#define MAX_CATEGORY 30

typedef struct Food
{
    int foodId;
    char foodName[MAX_NAME];
    char category[MAX_CATEGORY];
    float price;
    int quantity;

    struct Food *next;

} Food;

extern Food *head;

void displayMenu();
void orderFood();
void updateFood();
void addFood();

int adminLogin();
void adminMenu();
void loadDefaultItems();

#endif