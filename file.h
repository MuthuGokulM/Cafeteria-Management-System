#ifndef FILE_H
#define FILE_H

#include "products.h"

#define PRODUCT_FILE "products.dat"
#define BILL_FILE "bills.dat"
#define MAX_BILL_ITEMS 20


typedef struct
{
    int foodId;
    char foodName[MAX_NAME];
    char category[MAX_CATEGORY];
    float price;
    int quantity;

} OrderItem;


typedef struct
{
    int billNo;

    char date[12];
    char time[12];

    int itemCount;

    OrderItem items[MAX_BILL_ITEMS];

    float subtotal;
    float discount;
    float finalAmount;

    int status;

} Bill;

void saveProducts();
void loadProducts();

void saveBill(Bill *bill);
void loadBills();

void cancelBill();
void generateSalesReport();
int getNextBillNumber();

#endif