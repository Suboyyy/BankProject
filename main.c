#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_lines, user_id, advisor_id;

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
} Customer;

typedef struct Advisor
{
    int advisorID;
    char username[20];
    char password[20];
    char RIB[50][24];
} Advisor;

int LogInC(Customer *customers, char *username, char *password)
{
    int i = 0;
    for (i = 0; i < nb_lines; i++)
    {
        if (strcmp(customers[i].username, username) == 0)
        {
            if (strcmp(customers[i].password, password) == 0)
            {
                user_id = i;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int LogInA(Advisor *advisors, char *username, char *password)
{
    int i = 0;
    for (i = 0; i < nb_lines; i++)
    {
        if (strcmp(advisors[i].username, username) == 0)
        {
            if (strcmp(advisors[i].password, password) == 0)
            {
                advisor_id = i;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int findID(Customer *customers, char *RIB)
{
    int i = 0;
    for (i = 0; i < nb_lines; i++)
    {
        if (strcmp(customers[i].RIB, RIB) == 0)
        {
            return i;
        }
    }
    return -1;
}

int LogOut(Customer *customers)
{
    return 1;
}

void SaveFiles(Customer *customers)
{
    FILE *file = NULL;
    file = fopen("Data/Customer.txt", "w");
    int i;
    for (i = 0; i < nb_lines; i++)
    {
        fprintf(file, "%s, %d, %s, %s, %s, %lf, %lf, %lf\n", customers[i].RIB, customers[i].advisorID, customers[i].username, customers[i].password, customers[i].birthdate, customers[i].netsalary, customers[i].loanpayment, customers[i].balance);
    }
    fclose(file);
    free(customers);
    return;
}

int Withdraw(Customer *customers, double amount, int id)
{
    if (customers[id].balance >= amount)
    {
        customers[id].balance -= amount;
        return 1;
    }
    printf("You don't have enough money\n");
    return 0;
}

void Deposit(Customer *customers, double amount, int id)
{
    customers[id].balance += amount;
    return;
}

double loanEligibility(Customer *customers)
{
    double max_loan = customers[user_id].netsalary * 0.33;
    max_loan -= customers[user_id].loanpayment;
    return (max_loan);
}

void transfer(Customer *customers, char *RIB, double amount)
{
    int other_id = findID(customers, RIB);
    if (Withdraw(customers, amount, user_id) == 1)
    {
        Deposit(customers, amount, other_id);
        return;
    }
    return;
}

void updateInfo(Customer *customers)
{
    char again = 'y';
    while (again == 'y' || again == 'Y')
    {
        printf("\nwhat do you want to update ?\n");
        printf("1. Username\n");
        printf("2. Birthdate\n");
        printf("3. Password\n");
        printf("4. Salary\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
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

void checkInfo(Customer *customers)
{
    printf("Your username is : %s\n", customers[user_id].username);
    printf("Your RIB is : %s\n", customers[user_id].RIB);
    printf("Your advisor ID is : %d\n", customers[user_id].advisorID);
    printf("Your birthdate is : %s\n", customers[user_id].birthdate);
    printf("Your password is : %s\n", customers[user_id].password);
    printf("Your salary is : %.2lf\n", customers[user_id].netsalary);
    printf("Your loan payment is : %.2lf\n", customers[user_id].loanpayment);
    printf("Your balance is : %.2lf\n", customers[user_id].balance);
}

Customer *loadC()
{
    FILE *file = NULL;
    Customer *customers;
    int lines = 0;
    char buff[200];
    file = fopen("Data/Customer.txt", "r");
    if (file == NULL)
    {
        printf("Error while opening file\n");
        exit(1);
    }
    while (fgets(buff, 200, file) != NULL)
    {
        lines++;
    }
    nb_lines = lines;
    rewind(file);
    customers = (Customer *)malloc(nb_lines * sizeof(Customer));
    if (customers == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }
    int i = 0;
    for (i = 0; i < lines; i++)
    {
        fscanf(file, "%23[^,], %d, %20[^,], %20[^,], %10[^,], %lf, %lf, %lf\n", customers[i].RIB, &customers[i].advisorID, customers[i].username, customers[i].password, customers[i].birthdate, &customers[i].netsalary, &customers[i].loanpayment, &customers[i].balance);
    }

    fclose(file);
    return customers;
}

Advisor *loadA()
{
    FILE *file = NULL;
    Advisor *advisors = NULL;
    int lines = 0;
    char buff[200];

    file = fopen("Data/Advisor.txt", "r");
    if (file == NULL)
    {
        printf("Error while opening file\n");
        exit(1);
    }

    while (fgets(buff, sizeof(buff), file) != NULL)
    {
        lines++;
    }
    rewind(file);

    advisors = (Advisor *)calloc(lines, sizeof(Advisor));
    if (advisors == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }

    int past_ID = -1;
    int current_advisor = -1;
    int nb_customer = 0;

    for (int i = 0; i < lines; i++)
    {
        int advisorID = 0;
        char username[20] = {0};
        char password[20] = {0};
        char RIB[24] = {0};

        fscanf(file, "%d, %20[^,], %20[^,], %24[^\n]\n", &advisorID, username, password, RIB);

        if (advisorID != past_ID)
        {
            nb_customer = 0;
            current_advisor++;
            advisors = (Advisor *)realloc(advisors, (current_advisor + 1) * sizeof(Advisor));
            if (advisors == NULL)
            {
                printf("Memory not allocated.\n");
                exit(1);
            }
            memset(&advisors[current_advisor], 0, sizeof(Advisor)); // Initialize the newly allocated memory with 0
            advisors[current_advisor].advisorID = advisorID;
            advisors[current_advisor].advisorID = advisorID;
            strcpy(advisors[current_advisor].username, username);
            strcpy(advisors[current_advisor].password, password);
            strcpy(advisors[current_advisor].RIB[nb_customer], RIB);
            past_ID = advisorID;
        }
        else
        {
            nb_customer++;
            if (nb_customer < 50)
            {
                strcpy(advisors[current_advisor].RIB[nb_customer], RIB);
            }
        }
    }

    fclose(file);
    return advisors;
}

/*
int main() {
    Customer *customers = loadC();
    Advisor *advisors = loadA();
    printf("Welcome to the bank\n");
    char username[20];
    char password[20];
    char reconnect = 'y';
    double amount;
    int choice;
    while (reconnect == 'y' || reconnect == 'Y') {
        printf("\nDo you want to log in as a customer or an advisor ?\n");
        printf("1. Customer\n");
        printf("2. Advisor\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Please enter your username and your password (enter 0 0 to quit):\n");
            scanf("%s %s", &username, &password);
            if (username[0] == '0') {
                return 0;
            }
            while (LogInC(customers, username, password) == 0) {
                printf("Login failed\n");
                printf("Please enter your username and your password (enter 0 0 to quit):\n");
                scanf("%s %s", &username, &password);
                if (username[0] == '0') {
                    return 0;
                }
            }
            printf("Login successful\n");
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
        }
        else if (choice == 2) {
            printf("Please enter your username and your password (enter 0 0 to quit):\n");
            scanf("%s %s", &username, &password);
            if (username[0] == '0') {
                return 0;
            }
            while (LogInA(advisors, username, password) == 0) {
                printf("Login failed\n");
                printf("Please enter your username and your password (enter 0 0 to quit):\n");
                scanf("%s %s", &username, &password);
                if (username[0] == '0') {
                    return 0;
                }
            }
            printf("Login successful\n");
            char rib[24];
            do {
                user_id = -1;
                printf("Which customer do you want to consult ?\n");
                scanf("%s", &rib);
                int i;
                for (i == 0; i<50; i++) {
                    if (strcmp(rib, advisors[advisor_id].RIB[i]) == 0) {
                        user_id = findID(customers, rib);
                        printf("%d", user_id);
                        break;
                    }
                    printf("%s\n", rib);
                    printf("%s\n", advisors[advisor_id].RIB[i]);
                }
                if (user_id == -1) {printf("Wrong RIB\n");}
            } while (user_id == -1);
             do {
                printf("\nWhat would you like to do ?\n");
                printf("1. Deposit\n");
                printf("2. Withdraw\n");
                printf("3. Transfer Money\n");
                printf("4. Loan Eligibility\n");
                printf("6. Banking Advisors\n");
                printf("7. Check customers informations\n");
                printf("8. Update customers informations\n");
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

        }
        SaveFiles(customers);
        printf("Do you want to reconnect? (y / n)\n");
        scanf("%s", &reconnect);
    }
    return 0;
}
*/

int main()
{
    Customer *customers = loadC();
    Advisor *advisors = loadA();
    printf("Welcome to the bank\n");
    char username[20];
    char password[20];
    char reconnect = 'y';
    double amount;
    for (int i = 0; i < 3; i++)
    {
        printf("Advisor ID: %d\n", advisors[i].advisorID);
        printf("Username: %s\n", advisors[i].username);
        printf("Password: %s\n", advisors[i].password);
        printf("RIB:\n");
        for (int j = 0; j < 50; j++)
        {
            // Ensure we only print initialized RIBs (assuming empty ones are all zeroes)
            if (strlen(advisors[i].RIB[j]) > 0)
            {
                printf("At rank %d:\n%s\n", j, advisors[i].RIB[j]);
            }
        }
        printf("\n");
    }

    return 0;
}
