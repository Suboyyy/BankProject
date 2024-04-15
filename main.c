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

Customer create_customer(char* RIB, int advisorID, char* username, char* password, char* birthdate, double netsalary, double loanpayment, double balance) {
    Customer customer = {0};
    strcpy(customer.RIB, RIB);
    customer.advisorID = advisorID;
    strcpy(customer.username, username);
    strcpy(customer.password, password);
    strcpy(customer.birthdate, birthdate);
    customer.netsalary = netsalary;
    customer.loanpayment = loanpayment;
    customer.balance = balance;
    return customer;
}

int LogIn(Customer* customers, char* username, char* password) {
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

int findID(Customer* customers, char* RIB) {
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (strcmp(customers[i].RIB, RIB) == 0) {
            return i;
        }
    }
    return 0;
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

Customer* load() {
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
    char RIB[24];
    int advisorID;
    char username[21];
    char password[21];
    char birthdate[11];
    double netsalary;
    double loanpayment;
    double balance;
    int i = 0;
    for (i = 0; i < nb_lines; i++) {
        fscanf(file, "%23[^,], %d, %20[^,], %20[^,], %10[^,], %lf, %lf, %lf\n", RIB, &advisorID, username, password, birthdate, &netsalary, &loanpayment, &balance);
        customers[i] = create_customer(RIB, advisorID, username, password, birthdate, netsalary, loanpayment, balance);
    }
    
    fclose(file);
    return customers;
}

int main() {
    Customer *customers = load();
    printf("Welcome to the bank\n");
    char username[20];
    char password[20];
    char reconnect = 'y';
    double amount;
    while (reconnect == 'y' || reconnect == 'Y') {
        printf("Please enter your username and your password (enter 0 0 to quit):\n");
        scanf("%s %s", &username, &password);
        if (username[0] == '0') {
            return 0;
        }
        while (LogIn(customers, username, password) == 0) {
            printf("Login failed\n");
            printf("Please enter your username and your password (enter 0 0 to quit):\n");
            scanf("%s %s", &username, &password);
            if (username[0] == '0') {
                return 0;
            }
        }
        printf("Login successful\n");
        int choice;
        do {
            printf("\nWhat would you like to do ?\n");
            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("3. Transfer Money\n");
            printf("4. Loan Eligibility\n");
            printf("5. Send message\n");
            printf("6. Banking Advisors\n");
            printf("7. Check your informations\n");
            printf("8. Update your informations\n");
            printf("9. Log out\n");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("\nEnter the amount you want to deposit :\n"); 
                    scanf("%lf", &amount);
                    Deposit(customers, amount, user_id);
                    printf("Your new balance is : %.2lf\n", customers[user_id].balance);
                    break;
                case 2:
                    printf("\nEnter the amount you want to withdraw :\n");
                    scanf("%lf", &amount);
                    Withdraw(customers, amount, user_id);
                    printf("Your new balance is : %.2lf\n", customers[user_id].balance);
                    break;
                case 3:
                    printf("Enter the RIB of the person you want to transfer to :\n");
                    char RIB[24];
                    scanf("%s", &RIB);
                    printf("Enter the amount you want to transfer :\n");
                    scanf("%lf", &amount);
                    transfer(customers, RIB, amount);
                    break;
                case 4:
                    printf("You can get %.2lf as a loan\n", loanEligibility(customers));
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    checkInfo(customers);
                    break;
                case 8:
                    updateInfo(customers);
                    break;
                case 9:
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        } while (choice != 9);
        printf("Goodbye\n");
        SaveFiles(customers);
        printf("Do you want to reconnect? (y / n)\n");
        scanf("%s", &reconnect);
    }  
    return 0;
}
