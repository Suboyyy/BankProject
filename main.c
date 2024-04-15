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
    for (i = 0; i < 5; i++) {
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

void Withdraw(Customer* customers, double amount) {
    if (customers[user_id].balance >= amount) {
        customers[user_id].balance -= amount;
        return;
    }
    printf("You don't have enough money\n");
    return;
}

void Deposit(Customer* customers, double amount) {
    customers[user_id].balance += amount;
    return;
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
    customers = (Customer*)malloc(lines *sizeof(Customer));
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
    for (i = 0; i < lines; i++) {
        fscanf(file, "%23[^,], %d, %20[^,], %20[^,], %10[^,], %lf, %lf, %lf\n", RIB, &advisorID, username, password, birthdate, &netsalary, &loanpayment, &balance);
        customers[i] = create_customer(RIB, advisorID, username, password, birthdate, netsalary, loanpayment, balance);
    }
    
    fclose(file);
    return customers;
}

int main() {
    printf("CA MARCHE , C'EST BIEN ?\n");
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
            printf("What would you like to do ?\n");
            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("3. Check balance\n");
            printf("4. Transfer Money\n");
            printf("5. Loan Eligibility\n");
            printf("6. Send message\n");
            printf("7. Banking Advisors\n");
            printf("8. Settings\n");
            printf("9. Log out\n");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("Enter the amount you want to deposit :\n"); 
                    scanf("%lf", &amount);
                    Deposit(customers, amount);
                    printf("Your new balance is : %.2lf\n", customers[user_id].balance);
                    break;
                case 2:
                    printf("Enter the amount you want to withdraw :\n");
                    scanf("%lf", &amount);
                    Withdraw(customers, amount);
                    printf("Your new balance is : %.2lf\n", customers[user_id].balance);
                    break;
                case 3:
                    printf("Your balance is : %.2lf\n", customers[user_id].balance);
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        } while (choice != 9);
        printf("Goodbye\n");
        printf("Do you want to reconnect? (y / n)\n");
        scanf("%s", &reconnect);
    }  
    SaveFiles(customers);
    return 0;
}
