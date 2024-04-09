#include <stdio.h>
#include <stdlib.h>

typedef struct Customer
{
    char RIB[23];
    int advisorID;
    char username[20];
    char password[20];
    char birthdate[10];
    double netsalary;
    double loanpayment;
    double balance;
}Customer;

Customer* load() {
    FILE* fichier = NULL;
    Customer* customers;
    int lines = 0;
    char buff[200];
    fichier = fopen("Data/Customer.txt", "r");
    if (fichier == NULL) {
        printf("Error while opening file\n");
        exit(1);
    }
    while (fgets(buff, 200, fichier) != NULL) {
        lines++;
    }
    rewind(fichier);
    customers = (Customer*)malloc(lines *sizeof(Customer));
    if (customers == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(1);
    } 
    char RIB[23];
    int advisorID;
    char username[20];
    char password[20];
    char birthdate[10];
    double netsalary;
    double loanpayment;
    double balance;
    int i = 0;
    for (i = 0; i < lines; i++) {
        fscanf(fichier, "%s, %d, %s, %s, %s, %lf, %lf, %lf", &RIB, &advisorID, &username, &password, &birthdate, &netsalary, &loanpayment, &balance);
        customers[i] = (Customer){*RIB, advisorID, *username, *password, *birthdate, netsalary, loanpayment, balance};
    }
    
    fclose(fichier);
    return customers;
}

int main() {
    Customer *customers = load();
    printf("RIB: %s\n", customers[0].RIB);
    printf("Username: %s\n", customers[0].username);
    printf("Birthdate: %s\n", customers[0].birthdate);
    printf("Netsalary: %lf\n", customers[0].netsalary);
    printf("Loanpayment: %lf\n", customers[0].loanpayment);
    printf("Balance: %lf\n", customers[0].balance);
    return 0;
}