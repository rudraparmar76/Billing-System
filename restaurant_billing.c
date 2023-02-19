// Header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// function to generate bill header

void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t AnnaPurna Restaurant");
    printf("\n\t   -----------------");

    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

// function to generate bill body
void generateBillBody(char item[50], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    // qty entered  into the price per item
    printf("%0.2f\t\t", qty * price);
    printf("\n");
}

// defining structures

// function to  generate bill footer
void generateBillFooter(float total)
{
    printf("\n");
    // discount given at 10% of dicount  * total
    float discount = 0.1 * total;
    float netTotal = total - discount;
    // cgst = 0.09 and sgst = 0.09 therefore its net total after giving discount + the gst and we have stored net total into the grandtotal
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
    printf("---------------------------------------\n");

    printf("Sub Total \t\t\t%0.2f", total);
    printf("\nDiscount @10 %s\t\t\t%0.2f", "%", discount);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total \t\t\t%0.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%0.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%0.2f", "%", cgst);
    printf("\n---------------------------------------");

    printf("\nGrand Total \t\t\t%0.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

int main()
{
    float total;
    int option, n;
    struct orders ord;
    struct orders order;
    // to save the bill we will create file
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;
    while (contFlag == 'y')
    {
        system("cls");
        float total = 0;
        int invoiceFound = 0;
        // printing dadhboard to user
        printf("\t============AnnaPurna Restaurant============");
        printf("\n\n Please select your preferred operations");

        printf("\n\n 1.Generate Invoice");
        printf("\n 2.Show All Invoices");
        printf("\n 3.Search Invoice");
        printf("\n 4.Exit");
        printf("\n\n Enter your choice:\t");
        scanf("%d", &option);
        fgetc(stdin); // to take input even after whitespaces occur

        // switch case based on what user choose
        switch (option)
        {
        case 1:
            system("cls");
            printf("\n Please enter the name of customer:\t");
            fgets(ord.customer, 50, stdin);
            // removes the whitespaces after the customers name
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            // copies date from c function and stores in structure of date
            printf("\n Please enter the number of the items:\t");
            scanf("%d", &n);
            ord.numOfItems = n;

            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                // 0 sae item lena start nhi karna isliye
                printf("Please Enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf(" Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf(" Please enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice[y/n]:\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.txt", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                {
                    printf("\nSuccesfully Saved!");
                }
                else
                    printf("\nError Saving!");
                fclose(fp);
            }
            break;
        case 2:
            system("cls");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n  ******Your Previous Invoices******\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;
        case 3:
            printf("\nEnter the name of the customer:\t");
            // fgetc(stdin);
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("cls");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\t******Invoice Of %s******\n", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s is not found", name);
            }
            fclose(fp);
            break;
        case 4:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;
        default:
            printf("Sorry Invalid Option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]");
        scanf("%s", &contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");

    printf("\n\n");

    return 0;
}
