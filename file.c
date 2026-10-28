#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "products.h"
#include "file.h"

typedef struct
{
    int foodId;
    char foodName[MAX_NAME];
    char category[MAX_CATEGORY];
    float price;
    int quantity;
} FoodFile;

void saveProducts()
{
    FILE *fp;
    Food *temp;
    FoodFile data;

    fp = fopen(PRODUCT_FILE, "wb");

    if (fp == NULL)
    {
        printf("Unable to open product file.\n");
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        data.foodId = temp->foodId;
        strcpy(data.foodName, temp->foodName);
        strcpy(data.category, temp->category);
        data.price = temp->price;
        data.quantity = temp->quantity;

        fwrite(&data, sizeof(FoodFile), 1, fp);

        temp = temp->next;
    }

    fclose(fp);
}

void loadProducts()
{
    FILE *fp;
    FoodFile data;
    Food *newFood;
    Food *temp;

    fp = fopen(PRODUCT_FILE, "rb");

    if (fp == NULL)
    {
        return;
    }

    while (fread(&data, sizeof(FoodFile), 1, fp) == 1)
    {
        newFood = malloc(sizeof(Food));

        if (newFood == NULL)
        {
            printf("Memory allocation failed.\n");
            break;
        }

        newFood->foodId = data.foodId;
        strcpy(newFood->foodName, data.foodName);
        strcpy(newFood->category, data.category);
        newFood->price = data.price;
        newFood->quantity = data.quantity;
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
    }

    fclose(fp);
}

void saveBill(Bill *bill)
{
    FILE *fp;

    fp = fopen(BILL_FILE, "ab");

    if (fp == NULL)
    {
        printf("Unable to open bill file.\n");
        return;
    }

    fwrite(bill, sizeof(Bill), 1, fp);

    fclose(fp);
}

void cancelBill()
{
    FILE *fp;
    FILE *tempFile;
    Bill bill;
    int billNo;
    int found = 0;

    printf("\nEnter Bill Number to cancel: ");
    scanf("%d", &billNo);

    fp = fopen(BILL_FILE, "rb");

    if (fp == NULL)
    {
        printf("\nNo bills found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        fclose(fp);
        printf("\nUnable to process cancellation.\n");
        return;
    }

    while (fread(&bill, sizeof(Bill), 1, fp) == 1)
    {
        if (bill.billNo == billNo &&
            bill.status == 1)
        {
            int i;
            Food *food;

            found = 1;

            for (i = 0; i < bill.itemCount; i++)
            {
                food = head;

                while (food != NULL)
                {
                    if (food->foodId == bill.items[i].foodId)
                    {
                        food->quantity += bill.items[i].quantity;
                        break;
                    }

                    food = food->next;
                }
            }

            bill.status = 0;

            printf("\nBill %d cancelled successfully.\n",
                   bill.billNo);
        }

        fwrite(&bill, sizeof(Bill), 1, tempFile);
    }

    fclose(fp);
    fclose(tempFile);

    if (found)
    {
        remove(BILL_FILE);
        rename("temp.dat", BILL_FILE);
        saveProducts();
    }
    else
    {
        remove("temp.dat");
        printf("\nBill not found or already cancelled.\n");
    }
}

void generateSalesReport()
{
    FILE *fp;
    Bill bill;

    int totalBills = 0;
    int completedBills = 0;
    int cancelledBills = 0;
    int totalItems = 0;

    float grossSales = 0;
    float totalDiscount = 0;
    float netSales = 0;

    char currentDate[12];
    char fileName[50];

    FILE *reportFile;

    time_t now = time(NULL);
    struct tm *localTime;

    localTime = gmtime(&now);

    localTime->tm_hour += 5;
    localTime->tm_min += 30;

    mktime(localTime);

    strftime(currentDate,
             sizeof(currentDate),
             "%d-%m-%Y",
             localTime);

    sprintf(fileName,
            "daily_report_%s.txt",
            currentDate);

    reportFile = fopen(fileName, "w");

    if (reportFile == NULL)
    {
        printf("\nUnable to create daily report file.\n");
        return;
    }

    fp = fopen(BILL_FILE, "rb");

    if (fp == NULL)
    {
        printf("\nNo sales records found.\n");
        fclose(reportFile);
        return;
    }

    while (fread(&bill, sizeof(Bill), 1, fp) == 1)
    {
        if (strcmp(bill.date, currentDate) == 0)
        {
            totalBills++;

            if (bill.status == 1)
            {
                int i;

                completedBills++;

                grossSales += bill.subtotal;
                totalDiscount += bill.discount;
                netSales += bill.finalAmount;

                for (i = 0; i < bill.itemCount; i++)
                {
                    totalItems += bill.items[i].quantity;
                }
            }
            else
            {
                cancelledBills++;
            }
        }
    }

    fclose(fp);

    printf("\n================================================\n");
    printf("              DAILY SALES REPORT\n");
    printf("================================================\n");

    printf("Date              : %s\n", currentDate);
    printf("Total Bills       : %d\n", totalBills);
    printf("Completed Bills   : %d\n", completedBills);
    printf("Cancelled Bills   : %d\n", cancelledBills);
    printf("Total Items Sold  : %d\n", totalItems);

    printf("Gross Sales       : %.2f\n", grossSales);
    printf("Total Discount    : %.2f\n", totalDiscount);
    printf("Net Sales         : %.2f\n", netSales);

    printf("================================================\n");

    fprintf(reportFile, "================================================\n");
    fprintf(reportFile, "              DAILY SALES REPORT\n");
    fprintf(reportFile, "================================================\n");

    fprintf(reportFile, "Date              : %s\n", currentDate);
    fprintf(reportFile, "Total Bills       : %d\n", totalBills);
    fprintf(reportFile, "Completed Bills   : %d\n", completedBills);
    fprintf(reportFile, "Cancelled Bills   : %d\n", cancelledBills);
    fprintf(reportFile, "Total Items Sold  : %d\n", totalItems);

    fprintf(reportFile, "Gross Sales       : %.2f\n", grossSales);
    fprintf(reportFile, "Total Discount    : %.2f\n", totalDiscount);
    fprintf(reportFile, "Net Sales         : %.2f\n", netSales);

    fprintf(reportFile, "================================================\n");

    fclose(reportFile);

    printf("\nDaily report saved as: %s\n", fileName);
}

int getNextBillNumber()
{
    FILE *fp;
    Bill bill;

    int maxBillNo = 0;

    char currentDate[12];

    time_t now = time(NULL);
    struct tm *localTime;

    localTime = gmtime(&now);

    localTime->tm_hour += 5;
    localTime->tm_min += 30;

    mktime(localTime);

    strftime(currentDate,
             sizeof(currentDate),
             "%d-%m-%Y",
             localTime);

    fp = fopen(BILL_FILE, "rb");

    if (fp == NULL)
    {
        return 1;
    }

    while (fread(&bill, sizeof(Bill), 1, fp) == 1)
    {
        if (strcmp(bill.date, currentDate) == 0)
        {
            if (bill.billNo > maxBillNo)
            {
                maxBillNo = bill.billNo;
            }
        }
    }

    fclose(fp);

    return maxBillNo + 1;
}