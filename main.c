#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_lines, user_id;

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

typedef struct Advisor
{
    int advisorID;
    char username[20];
    char password[20];
    char RIB[50][23];
}Advisor;

int LogInC(Customer* customers, char* username, char* password) {
    int i = 0;
    for (i = 0; i < nb_lines; i++) {
        if (strcmp(customers[i].username, username) == 0) {
            if (strcmp(customers[i].password, password) == 0) {
                user_id = i;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int LogInA(Advisor* advisors, char* username, char* password) {
    int i = 0;
    for (i = 0; i < nb_lines; i++) {
        if (strcmp(advisors[i].username, username) == 0) {
            if (strcmp(advisors[i].password, password) == 0) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int findID(Customer* customers, char* RIB) {
    int i = 0;
    for (i = 0; i < nb_lines; i++) {
        if (strcmp(customers[i].RIB, RIB) == 0) {
            return i;
        }
    }
    return -1;
}

int LogOut(Customer* customers) {
    return 1;
}

void SaveFiles(Customer* customers) {
    FILE* file = NULL;
    file = fopen("Data/Customer.txt", "w");
    int i;
    for (i = 0; i < nb_lines; i++) {
        fprintf(file, "%s, %d, %s, %s, %s, %lf, %lf, %lf\n", customers[i].RIB, customers[i].advisorID, customers[i].username, customers[i].password, customers[i].birthdate, customers[i].netsalary, customers[i].loanpayment, customers[i].balance);
    }
    fclose(file);
    return;
}

int Withdraw(Customer* customers, double amount,int id) {
    if (customers[id].balance >= amount) {
        customers[id].balance -= amount;
        return 1;
    }
    printf("You don't have enough money\n");
    return 0;
}

void Deposit(Customer* customers, double amount, int id) {
    customers[id].balance += amount;
    return;
}

double loanEligibility(Customer* customers) {
    double max_loan = customers[user_id].netsalary * 0.33;
    max_loan -= customers[user_id].loanpayment;
    return (max_loan);
}

void transfer(Customer* customers, char* RIB, double amount) {
    int other_id=findID(customers, RIB);
    if (Withdraw(customers, amount, user_id) == 1) {
        Deposit(customers, amount, other_id);
        return;
    }
    return;
}

void updateInfo(Customer* customers) {
    char again='y';
    while(again=='y'||again=='Y'){
    printf("\nwhat do you want to update ?\n");
    printf("1. Username\n");
    printf("2. Birthdate\n");
    printf("3. Password\n");
    printf("4. Salary\n");
    int choice;
    scanf("%d", &choice);
    switch (choice){
        case 1:
            char new_username[20];
            printf("\nEnter your new username : \n");
            scanf("%s", &new_username);
            strcpy(customers[user_id].username, new_username);
            break;
        case 2:
            char new_birthdate[10];
            printf("\nEnter your new birthdate (dd/mm/yyyy) : \n");
            scanf("%s", &new_birthdate);
            strcpy(customers[user_id].birthdate, new_birthdate);   
            break;
        case 3:
            char new_password[20];
            printf("\nEnter your new password : \n");
            scanf("%s", &new_password);
            strcpy(customers[user_id].password, new_password);
            break;
        case 4:
            double new_netsalary;
            printf("\nEnter your new salary : \n");
            scanf("%lf", &new_netsalary);
            customers[user_id].netsalary = new_netsalary;
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    printf("\nDo you want to update again ? (y/n) \n");
    scanf("%c", &again);
    }
    return;
}

void checkInfo(Customer* customers) {
    printf("Your username is : %s\n", customers[user_id].username);
    printf("Your RIB is : %s\n", customers[user_id].RIB);
    printf("Your advisor ID is : %d\n", customers[user_id].advisorID);
    printf("Your birthdate is : %s\n", customers[user_id].birthdate);
    printf("Your password is : %s\n", customers[user_id].password);
    printf("Your salary is : %.2lf\n", customers[user_id].netsalary);
    printf("Your loan payment is : %.2lf\n", customers[user_id].loanpayment);
    printf("Your balance is : %.2lf\n", customers[user_id].balance);
}

Customer* loadC() {
    FILE* file = NULL;
    Customer* customers;
    int lines = 0;
    char buff[200];
    file = fopen("Data/Customer.txt", "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        exit(1);
    }
    while (fgets(buff, 200, file) != NULL) {
        lines++;
    }
    nb_lines = lines;
    rewind(file);
    customers = (Customer*)malloc(nb_lines *sizeof(Customer));
    if (customers == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(1);
    } 
    int i = 0;
    for (i = 0; i < lines; i++) {
        fscanf(file, "%23[^,], %d, %20[^,], %20[^,], %10[^,], %lf, %lf, %lf\n", customers[i].RIB, &customers[i].advisorID, customers[i].username, customers[i].password, customers[i].birthdate, &customers[i].netsalary, &customers[i].loanpayment, &customers[i].balance);
    }
    
    fclose(file);
    return customers;
}

Advisor *loadA() {
    FILE* file = NULL;
    Advisor* advisors;
    int lines = 0;
    char buff[200];
    file = fopen("Data/Advisor.txt", "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        exit(1);
    }
    while (fgets(buff, 200, file) != NULL) {
        lines++;
    }
    rewind(file);
    int past_ID = -1;
    int current_advisor = -1;
    int nb_customer = 0;
    int i = 0;
    for (i = 0; i < lines; i++) {
        current_advisor++;
        nb_customer = 0;
        int advisorID;
        char username[20];
        char password[20];
        char RIB[23];
        fscanf(file, "%d, %20[^,], %20[^,], %23[^,]\n", &advisorID, username, password, RIB);
        if (advisorID != past_ID) {
                advisors = realloc(advisors, (current_advisor+1) * sizeof(Advisor));
            if (advisors == NULL) { 
                printf("Memory not allocated.\n"); 
                exit(1);
            } 
            advisors[current_advisor].advisorID = advisorID;
            strcpy(advisors[current_advisor].username, username);
            strcpy(advisors[current_advisor].password, password);
            strcpy(advisors[current_advisor].RIB[nb_customer], RIB);
            past_ID = advisorID;
        }
        else {
            nb_customer++;
            strcpy(advisors[current_advisor].RIB[nb_customer], RIB);
        }

    }
    fclose(file);
    return advisors;
}

float test(Customer* customers) {
    return customers[0].balance;
}
