#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "products.h"
#include "file.h"

typedef void (*MenuFunction)();

void displayMenu()
{
    Food *temp;
    int found;

    printf("\n========================================================\n");
    printf("                  CAFETERIA MENU\n");
    printf("========================================================\n");

    printf("\n--------------------- DISCOUNT -------------------------\n");
    printf("Subtotal below Rs.500   : 0%% discount\n");
    printf("Subtotal Rs.500-Rs.999  : 5%% discount\n");
    printf("Subtotal Rs.1000+       : 10%% discount\n");
    printf("--------------------------------------------------------\n");

    printf("\n------------------- BEVERAGES --------------------------\n");
    printf("%-10s %-20s %-15s %-10s %-10s\n",
           "Food ID", "Food Name", "Category", "Price", "Quantity");
    printf("--------------------------------------------------------\n");

    found = 0;
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->category, "Beverages") == 0 ||
            strcmp(temp->category, "Beverage") == 0)
        {
            printf("%-10d %-20s %-15s %-10.2f %-10d\n",
                   temp->foodId,
                   temp->foodName,
                   temp->category,
                   temp->price,
                   temp->quantity);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No food items available.\n");

    printf("\n--------------------- SNACKS ---------------------------\n");
    printf("%-10s %-20s %-15s %-10s %-10s\n",
           "Food ID", "Food Name", "Category", "Price", "Quantity");
    printf("--------------------------------------------------------\n");

    found = 0;
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->category, "Snacks") == 0 ||
            strcmp(temp->category, "Snack") == 0)
        {
            printf("%-10d %-20s %-15s %-10.2f %-10d\n",
                   temp->foodId,
                   temp->foodName,
                   temp->category,
                   temp->price,
                   temp->quantity);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No food items available.\n");

    printf("\n------------------- FAST FOOD --------------------------\n");
    printf("%-10s %-20s %-15s %-10s %-10s\n",
           "Food ID", "Food Name", "Category", "Price", "Quantity");
    printf("--------------------------------------------------------\n");

    found = 0;
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->category, "Fast Food") == 0)
        {
            printf("%-10d %-20s %-15s %-10.2f %-10d\n",
                   temp->foodId,
                   temp->foodName,
                   temp->category,
                   temp->price,
                   temp->quantity);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No food items available.\n");

    printf("\n-------------------- DESSERTS --------------------------\n");
    printf("%-10s %-20s %-15s %-10s %-10s\n",
           "Food ID", "Food Name", "Category", "Price", "Quantity");
    printf("--------------------------------------------------------\n");

    found = 0;
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->category, "Desserts") == 0 ||
            strcmp(temp->category, "Dessert") == 0)
        {
            printf("%-10d %-20s %-15s %-10.2f %-10d\n",
                   temp->foodId,
                   temp->foodName,
                   temp->category,
                   temp->price,
                   temp->quantity);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No food items available.\n");

    printf("\n========================================================\n");
}

void loadDefaultItems()
{
    Food *newFood;
    Food *temp;

    temp = head;

    while (temp != NULL)
    {
        if (temp->foodId == 101 ||
            temp->foodId == 102 ||
            temp->foodId == 103 ||
            temp->foodId == 201 ||
            temp->foodId == 202 ||
            temp->foodId == 203 ||
            temp->foodId == 301 ||
            temp->foodId == 302 ||
            temp->foodId == 303)
        {
            printf("\nDefault food items already loaded.\n");
            return;
        }

        temp = temp->next;
    }

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 101;
    strcpy(newFood->foodName, "Tea");
    strcpy(newFood->category, "Beverages");
    newFood->price = 15;
    newFood->quantity = 20;
    newFood->next = NULL;

    head = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 102;
    strcpy(newFood->foodName, "Coffee");
    strcpy(newFood->category, "Beverages");
    newFood->price = 25;
    newFood->quantity = 15;
    newFood->next = NULL;

    head->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 103;
    strcpy(newFood->foodName, "Fresh Juice");
    strcpy(newFood->category, "Beverages");
    newFood->price = 50;
    newFood->quantity = 10;
    newFood->next = NULL;

    head->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 201;
    strcpy(newFood->foodName, "Samosa");
    strcpy(newFood->category, "Snacks");
    newFood->price = 20;
    newFood->quantity = 20;
    newFood->next = NULL;

    head->next->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 202;
    strcpy(newFood->foodName, "Sandwich");
    strcpy(newFood->category, "Snacks");
    newFood->price = 60;
    newFood->quantity = 15;
    newFood->next = NULL;

    head->next->next->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 203;
    strcpy(newFood->foodName, "French Fries");
    strcpy(newFood->category, "Snacks");
    newFood->price = 80;
    newFood->quantity = 10;
    newFood->next = NULL;

    head->next->next->next->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 301;
    strcpy(newFood->foodName, "Burger");
    strcpy(newFood->category, "Fast Food");
    newFood->price = 100;
    newFood->quantity = 10;
    newFood->next = NULL;

    head->next->next->next->next->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 302;
    strcpy(newFood->foodName, "Pizza");
    strcpy(newFood->category, "Fast Food");
    newFood->price = 150;
    newFood->quantity = 8;
    newFood->next = NULL;

    head->next->next->next->next->next->next->next = newFood;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
        return;

    newFood->foodId = 303;
    strcpy(newFood->foodName, "Noodles");
    strcpy(newFood->category, "Fast Food");
    newFood->price = 120;
    newFood->quantity = 12;
    newFood->next = NULL;

    head->next->next->next->next->next->next->next->next = newFood;

    saveProducts();

    printf("\nDefault food items loaded successfully.\n");
}


void adminMenu()
{
    int adminChoice;

    MenuFunction adminFunctions[] =
    {
        updateFood,
        addFood,
        cancelBill,
        generateSalesReport,
        loadDefaultItems
    };

    printf("\n========================================\n");
    printf("            ADMIN LOGIN\n");
    printf("========================================\n");

    if (!adminLogin())
    {
        printf("\nInvalid User ID or Password.\n");
        printf("Access denied.\n");
        return;
    }

    printf("\nLogin successful.\n");

    do
    {
        printf("\n========================================\n");
        printf("              ADMIN MENU\n");
        printf("========================================\n");

        printf("1. Update Food Quantity\n");
        printf("2. Add New Food Item\n");
        printf("3. Cancel Bill\n");
        printf("4. Daily Sales Report\n");
        printf("5. Load Default Food Items\n");
        printf("6. Back to Main Menu\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &adminChoice);


        if (adminChoice >= 1 && adminChoice <= 5)
        {
            adminFunctions[adminChoice - 1]();
        }
        else if (adminChoice == 6)
        {
            printf("\nReturning to main menu...\n");
        }
        else
        {
            printf("\nInvalid Admin choice.\n");
            printf("Please select a choice from 1 to 6.\n");
        }

    } while (adminChoice != 6);
}


int main()
{
    int choice;

    MenuFunction menuFunctions[] =
    {
        orderFood,
        adminMenu
    };

    loadProducts();

    do
    {
        displayMenu();

        printf("\n========================================\n");
        printf("       CAFETERIA MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Order\n");
        printf("2. Admin\n");
        printf("3. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 2)
        {
            menuFunctions[choice - 1]();
        }
        else if (choice == 3)
        {
            printf("\nThank you for using Cafeteria Management System.\n");
        }
        else
        {
            printf("\nInvalid choice.\n");
            printf("Please select a choice from 1 to 3.\n");
        }

    } while (choice != 3);

    return 0;
}