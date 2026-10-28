#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "products.h"
#include "file.h"
#include <time.h>

Food *head = NULL;

int adminLogin()
{
char userId[30];
    char password[30];

    printf("Enter User ID: ");
    scanf("%29s", userId);

    printf("Enter Password: ");
    scanf("%29s", password);

    if (strcmp(userId, "admin") == 0 &&
        strcmp(password, "1234") == 0)
    {
        printf("\nLogin successful.\n");
        return 1;
    }

    return 0;
}

void orderFood()
{
    Bill bill;
    Food *food;

    int foodId;
    int quantity;
    int found;
    int choice;
    int i;

    float subtotal;
    float discount;
    float finalAmount;

    bill.itemCount = 0;
    bill.status = 1;

    while (1)
    {
        displayMenu();

        printf("\nEnter Food ID (0 to finish): ");
        scanf("%d", &foodId);

        if (foodId == 0)
        {
            break;
        }

        food = head;
        found = 0;

        while (food != NULL)
        {
            if (food->foodId == foodId)
            {
                found = 1;
                break;
            }

            food = food->next;
        }

        if (!found)
        {
            printf("\nFood ID not found.\n");
            printf("Please enter a valid Food ID.\n");
            continue;
        }

        for (i = 0; i < bill.itemCount; i++)
        {
            if (bill.items[i].foodId == foodId)
            {
                printf("\nThis item is already in your bill.\n");
                printf("Use Change Quantity option to modify it.\n");
                found = 0;
                break;
            }
        }

        if (!found && i < bill.itemCount)
        {
            continue;
        }

        printf("\nFood Name : %s\n", food->foodName);
        printf("Price     : %.2f\n", food->price);
        printf("Available : %d\n", food->quantity);

        printf("Enter Quantity: ");
        scanf("%d", &quantity);

        if (quantity <= 0)
        {
            printf("\nInvalid quantity.\n");
            continue;
        }

        if (quantity > food->quantity)
        {
            printf("\nInsufficient quantity available.\n");
            continue;
        }

        if (bill.itemCount >= MAX_BILL_ITEMS)
        {
            printf("\nMaximum number of items reached.\n");
            break;
        }

        bill.items[bill.itemCount].foodId = food->foodId;

        strcpy(bill.items[bill.itemCount].foodName,
               food->foodName);

        strcpy(bill.items[bill.itemCount].category,
               food->category);

        bill.items[bill.itemCount].price = food->price;

        bill.items[bill.itemCount].quantity = quantity;

        bill.itemCount++;

        printf("\nItem added successfully.\n");

        printf("\nDo you want to add more items? (Y/N): ");

        char more;
        scanf(" %c", &more);

        if (more != 'Y' && more != 'y')
        {
            break;
        }
    }

    if (bill.itemCount == 0)
    {
        printf("\nNo items selected.\n");
        printf("Returning to main menu...\n");
        return;
    }

    while (1)
    {
        subtotal = 0;

        for (i = 0; i < bill.itemCount; i++)
        {
            subtotal +=
                bill.items[i].price *
                bill.items[i].quantity;
        }

        if (subtotal >= 1000)
        {
            discount = subtotal * 0.10;
        }
        else if (subtotal >= 500)
        {
            discount = subtotal * 0.05;
        }
        else
        {
            discount = 0;
        }

        finalAmount = subtotal - discount;

        printf("\n========================================================\n");
        printf("                    BILL PREVIEW\n");
        printf("========================================================\n");

        printf("%-10s %-20s %-8s %-10s %-10s\n",
               "Food ID",
               "Food Name",
               "Qty",
               "Price",
               "Total");

        printf("--------------------------------------------------------\n");

        for (i = 0; i < bill.itemCount; i++)
        {
            printf("%-10d %-20s %-8d %-10.2f %-10.2f\n",
                   bill.items[i].foodId,
                   bill.items[i].foodName,
                   bill.items[i].quantity,
                   bill.items[i].price,
                   bill.items[i].price *
                   bill.items[i].quantity);
        }

        printf("--------------------------------------------------------\n");

        printf("Subtotal     : %.2f\n", subtotal);

        if (subtotal >= 1000)
        {
            printf("Discount     : 10%% (%.2f)\n",
                   discount);
        }
        else if (subtotal >= 500)
        {
            printf("Discount     : 5%% (%.2f)\n",
                   discount);
        }
        else
        {
            printf("Discount     : 0%% (%.2f)\n",
                   discount);
        }

        printf("Final Amount : %.2f\n", finalAmount);

        printf("========================================================\n");

        printf("\n1. Change Quantity\n");
        printf("2. Remove Item\n");
        printf("3. Add More Items\n");
        printf("4. Confirm Bill\n");
        printf("5. Cancel Order\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\nEnter Food ID: ");
            scanf("%d", &foodId);

            found = 0;

            for (i = 0; i < bill.itemCount; i++)
            {
                if (bill.items[i].foodId == foodId)
                {
                    found = 1;

                    food = head;

                    while (food != NULL)
                    {
                        if (food->foodId == foodId)
                        {
                            printf("Available Quantity: %d\n",
                                   food->quantity);

                            printf("Current Quantity: %d\n",
                                   bill.items[i].quantity);

                            printf("Enter New Quantity: ");
                            scanf("%d", &quantity);

                            if (quantity <= 0)
                            {
                                printf("\nInvalid quantity.\n");
                            }
                            else if (quantity > food->quantity)
                            {
                                printf("\nInsufficient quantity available.\n");
                            }
                            else
                            {
                                bill.items[i].quantity = quantity;

                                printf("\nQuantity updated successfully.\n");
                            }

                            break;
                        }

                        food = food->next;
                    }

                    break;
                }
            }

            if (!found)
            {
                printf("\nFood ID is not in your bill.\n");
            }
        }

        else if (choice == 2)
        {
            printf("\nEnter Food ID to remove: ");
            scanf("%d", &foodId);

            found = 0;

            for (i = 0; i < bill.itemCount; i++)
            {
                if (bill.items[i].foodId == foodId)
                {
                    found = 1;

                    for (int j = i;
                         j < bill.itemCount - 1;
                         j++)
                    {
                        bill.items[j] =
                            bill.items[j + 1];
                    }

                    bill.itemCount--;

                    printf("\nItem removed successfully.\n");

                    break;
                }
            }

            if (!found)
            {
                printf("\nFood ID is not in your bill.\n");
            }

            if (bill.itemCount == 0)
            {
                printf("\nNo items remaining in the order.\n");
                printf("Order cancelled.\n");
                return;
            }
        }

        else if (choice == 3)
        {
            char more;

            while (1)
            {
                displayMenu();

                printf("\nEnter Food ID: ");
                scanf("%d", &foodId);

                food = head;
                found = 0;

                while (food != NULL)
                {
                    if (food->foodId == foodId)
                    {
                        found = 1;
                        break;
                    }

                    food = food->next;
                }

                if (!found)
                {
                    printf("\nFood ID not found.\n");
                    continue;
                }

                int alreadySelected = 0;

                for (i = 0; i < bill.itemCount; i++)
                {
                    if (bill.items[i].foodId == foodId)
                    {
                        alreadySelected = 1;
                        break;
                    }
                }

                if (alreadySelected)
                {
                    printf("\nItem already exists in the bill.\n");
                    printf("Use Change Quantity option.\n");
                    continue;
                }

                printf("Food Name : %s\n", food->foodName);
                printf("Price     : %.2f\n", food->price);
                printf("Available : %d\n", food->quantity);

                printf("Enter Quantity: ");
                scanf("%d", &quantity);

                if (quantity <= 0 ||
                    quantity > food->quantity)
                {
                    printf("\nInvalid quantity.\n");
                    continue;
                }

                if (bill.itemCount >= MAX_BILL_ITEMS)
                {
                    printf("\nMaximum items reached.\n");
                    break;
                }

                bill.items[bill.itemCount].foodId =
                    food->foodId;

                strcpy(bill.items[bill.itemCount].foodName,
                       food->foodName);

                strcpy(bill.items[bill.itemCount].category,
                       food->category);

                bill.items[bill.itemCount].price =
                    food->price;

                bill.items[bill.itemCount].quantity =
                    quantity;

                bill.itemCount++;

                printf("\nItem added successfully.\n");

                printf("Do you want to add another item? (Y/N): ");
                scanf(" %c", &more);

                if (more != 'Y' && more != 'y')
                {
                    break;
                }
            }
        }

        else if (choice == 4)
        {
            time_t now;
            struct tm *localTime;

            now = time(NULL);
            localTime = gmtime(&now);
            localTime->tm_hour += 5;
            localTime->tm_min += 30;
            mktime(localTime);

            strftime(bill.date,
                    sizeof(bill.date),
                    "%d-%m-%Y",
                    localTime);

            strftime(bill.time,
                    sizeof(bill.time),
                    "%I:%M:%S %p",
                    localTime);

            bill.billNo = getNextBillNumber();

            bill.subtotal = subtotal;

            bill.discount = discount;

            bill.finalAmount = finalAmount;

            bill.status = 1;

            for (i = 0; i < bill.itemCount; i++)
            {
                food = head;

                while (food != NULL)
                {
                    if (food->foodId ==
                        bill.items[i].foodId)
                    {
                        food->quantity -=
                            bill.items[i].quantity;

                        break;
                    }

                    food = food->next;
                }
            }

            saveBill(&bill);

            saveProducts();

            printf("\n========================================================\n");
            printf("                    CAFETERIA BILL\n");
            printf("========================================================\n");

            printf("Bill No : %d\n", bill.billNo);
            printf("Date    : %s\n", bill.date);
            printf("Time    : %s\n", bill.time);

            printf("--------------------------------------------------------\n");

            printf("%-10s %-20s %-8s %-10s %-10s\n",
                   "Food ID",
                   "Food Name",
                   "Qty",
                   "Price",
                   "Total");

            printf("--------------------------------------------------------\n");

            for (i = 0; i < bill.itemCount; i++)
            {
                printf("%-10d %-20s %-8d %-10.2f %-10.2f\n",
                       bill.items[i].foodId,
                       bill.items[i].foodName,
                       bill.items[i].quantity,
                       bill.items[i].price,
                       bill.items[i].price *
                       bill.items[i].quantity);
            }

            printf("--------------------------------------------------------\n");

            printf("Subtotal     : %.2f\n",
                   bill.subtotal);

            printf("Discount     : %.2f\n",
                   bill.discount);

            printf("Final Amount : %.2f\n",
                   bill.finalAmount);

            printf("========================================================\n");

            printf("\nBill generated successfully.\n");

            return;
        }

        else if (choice == 5)
        {
            printf("\nOrder cancelled.\n");
            printf("No bill was generated.\n");

            return;
        }

        else
        {
            printf("\nInvalid choice.\n");
            printf("Please select a choice from 1 to 5.\n");
        }
    }
}

void updateFood()
{
    int foodId;
    int quantity;

    printf("Enter Food ID: ");
    scanf("%d", &foodId);

    Food *temp = head;

    while (temp != NULL)
    {
        if (temp->foodId == foodId)
        {
            printf("Food Name        : %s\n", temp->foodName);
            printf("Current Quantity : %d\n", temp->quantity);

            printf("Enter New Quantity: ");
            scanf("%d", &quantity);

            if (quantity < 0)
            {
                printf("Invalid quantity.\n");
                return;
            }

            temp->quantity = quantity;

            saveProducts();

            printf("\nQuantity updated successfully.\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nFood ID not found.\n");
}

void addFood()
{
    Food *newFood;
    Food *temp;

    int categoryChoice;

    newFood = malloc(sizeof(Food));

    if (newFood == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\nEnter Food ID: ");
    scanf("%d", &newFood->foodId);

    temp = head;

    while (temp != NULL)
    {
        if (temp->foodId == newFood->foodId)
        {
            printf("Food ID already exists.\n");
            free(newFood);
            return;
        }

        temp = temp->next;
    }

    printf("Enter Food Name: ");
    scanf("%[^\n]", newFood->foodName);

    printf("\nAvailable Categories:\n");
    printf("1. Beverages\n");
    printf("2. Snacks\n");
    printf("3. Fast Food\n");
    printf("4. Desserts\n");

    printf("Enter Category Choice: ");
    scanf("%d", &categoryChoice);

    if (categoryChoice == 1)
    {
        strcpy(newFood->category, "Beverages");
    }
    else if (categoryChoice == 2)
    {
        strcpy(newFood->category, "Snacks");
    }
    else if (categoryChoice == 3)
    {
        strcpy(newFood->category, "Fast Food");
    }
    else if (categoryChoice == 4)
    {
        strcpy(newFood->category, "Desserts");
    }
    else
    {
        printf("\nInvalid category.\n");
        printf("Please select a category from 1 to 4.\n");

        free(newFood);
        return;
    }

    printf("Enter Price: ");
    scanf("%f", &newFood->price);

    if (newFood->price < 0)
    {
        printf("Invalid price.\n");
        free(newFood);
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &newFood->quantity);

    if (newFood->quantity < 0)
    {
        printf("Invalid quantity.\n");
        free(newFood);
        return;
    }

    newFood->next = NULL;

    if (head == NULL)
    {
        head = newFood;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newFood;
    }

    saveProducts();

    printf("\nFood item added successfully.\n");
}