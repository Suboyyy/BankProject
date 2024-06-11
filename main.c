#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_lines, user_id, advisor_id, advisor_index, number_advisors, nb_messages;

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

typedef struct Message
{
    int advisorID;
    char customerRIB[24];
    char message[200];
} Message;

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
    for (i = 0; i < number_advisors; i++)
    {
        if (strcmp(advisors[i].username, username) == 0)
        {
            if (strcmp(advisors[i].password, password) == 0)
            {
                advisor_id = advisors[i].advisorID;
                advisor_index = i;
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

void SaveFiles(Customer *customers, Advisor *advisors, Message *messages)
{
    FILE *file = NULL;
    file = fopen("Data/Customer.txt", "w");
    int i;
    for (i = 0; i < nb_lines; i++)
    {
        fprintf(file, "%s, %d, %s, %s, %s, %lf, %lf, %lf\n", customers[i].RIB, customers[i].advisorID, customers[i].username, customers[i].password, customers[i].birthdate, customers[i].netsalary, customers[i].loanpayment, customers[i].balance);
    }
    fclose(file);
    FILE *fileA = NULL;
    fileA = fopen("Data/Advisor.txt", "w");
    int j;
    int past_id = advisors[0].advisorID;
    int rib_pos = 0;
    int ad_pos = 0;
    for (j = 0; j < nb_lines; j++)
    {
        if (advisors[ad_pos].RIB[rib_pos][0] == 0)
        {
            rib_pos = 0;
            ad_pos++;
            fprintf(fileA, "%d, %s, %s, %s\n", advisors[ad_pos].advisorID, advisors[ad_pos].username, advisors[ad_pos].password, advisors[ad_pos].RIB[rib_pos]);
            rib_pos++;
        }
        else
        {
            fprintf(fileA, "%d, %s, %s, %s\n", advisors[ad_pos].advisorID, advisors[ad_pos].username, advisors[ad_pos].password, advisors[ad_pos].RIB[rib_pos]);
            rib_pos++;
        }
    }
    fclose(fileA);
    FILE *fileM = NULL;
    fileM = fopen("Data/Message.txt", "w");
    int k;
    for (k = 0; k < nb_messages; k++)
    {
        fprintf(fileM, "%d, %s, %s\n", messages[k].advisorID, messages[k].customerRIB, messages[k].message);
    }
    fclose(fileM);
    return;
}

Customer *create_customer(Customer *customers, Advisor *advisors)
{
    nb_lines++;
    Customer *temp_customers = realloc(customers, nb_lines * sizeof(Customer));
    customers = temp_customers;

    printf("Enter customer's RIB:\n");
    char rib[23];
    scanf("%s", rib);
    strcpy(customers[nb_lines - 1].RIB, rib);
    customers[nb_lines - 1].advisorID = advisor_id;
    printf("Enter customer's username:\n");
    scanf("%s", customers[nb_lines - 1].username);
    printf("Enter customer's password:\n");
    scanf("%s", customers[nb_lines - 1].password);
    printf("Enter customer's birthdate:\n");
    scanf("%s", customers[nb_lines - 1].birthdate);
    printf("Enter customer's netsalary:\n");
    scanf("%lf", &customers[nb_lines - 1].netsalary);
    printf("Enter customer's loanpayment:\n");
    scanf("%lf", &customers[nb_lines - 1].loanpayment);
    printf("Enter customer's balance:\n");
    scanf("%lf", &customers[nb_lines - 1].balance);

    for (int i = 0; i < 50; i++)
    {
        if (advisors[advisor_index].RIB[i][0] == 0)
        {
            strcpy(advisors[advisor_index].RIB[i], rib);
            break;
        }
    }
    return customers;
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
            printf("\nEnter the new username : \n");
            scanf("%s", &new_username);
            strcpy(customers[user_id].username, new_username);
            break;
        case 2:
            char new_birthdate[10];
            printf("\nEnter the new birthdate (dd/mm/yyyy) : \n");
            scanf("%s", &new_birthdate);
            strcpy(customers[user_id].birthdate, new_birthdate);
            break;
        case 3:
            char new_password[20];
            printf("\nEnter the new password : \n");
            scanf("%s", &new_password);
            strcpy(customers[user_id].password, new_password);
            break;
        case 4:
            double new_netsalary;
            printf("\nEnter the new salary : \n");
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

void checkInfo(Customer *customers, int choice)
{
    choice == 1 ? printf("Your username is : %s\n", customers[user_id].username) : printf("Your client username is : %s\n", customers[user_id].username);
    choice == 1 ? printf("Your RIB is : %s\n", customers[user_id].RIB) : printf("");
    choice == 1 ? printf("Your advisor ID is : %d\n", customers[user_id].advisorID) : printf("");
    choice == 1 ? printf("Your birthdate is : %s\n", customers[user_id].birthdate) : printf("Client birthdate is : %s\n", customers[user_id].birthdate);
    choice == 1 ? printf("Your password is : %s\n", customers[user_id].password) : printf("Your client password is : %s\n", customers[user_id].password);
    choice == 1 ? printf("Your salary is : %.2lf\n", customers[user_id].netsalary) : printf("Your client salary is : %.2lf\n", customers[user_id].netsalary);
    choice == 1 ? printf("Your loan payment is : %.2lf\n", customers[user_id].loanpayment) : printf("Your client loan payment is : %.2lf\n", customers[user_id].loanpayment);
    choice == 1 ? printf("Your balance is : %.2lf\n", customers[user_id].balance) : printf("Your client balance is : %.2lf\n", customers[user_id].balance);
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
            number_advisors++;
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

Message *loadM()
{
    FILE *file = NULL;
    Message *messages;
    int lines = 0;
    char buff[200];
    file = fopen("Data/Message.txt", "r");
    if (file == NULL)
    {
        printf("Error while opening file\n");
        exit(1);
    }
    while (fgets(buff, 200, file) != NULL)
    {
        lines++;
    }
    nb_messages = lines;
    rewind(file);
    messages = (Message *)malloc(nb_messages * sizeof(Message));
    if (messages == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }
    for (int i = 0; i < nb_messages; i++)
    {
        char rib[23];
        fscanf(file, "%d, %23[^,], %199[^\n]", &messages[i].advisorID, rib, messages[i].message);
        strncpy(messages[i].customerRIB, rib, sizeof(messages[i].customerRIB) - 1);
        messages[i].customerRIB[sizeof(messages[i].customerRIB) - 1] = '\0';
    }
    fclose(file);
    return messages;
}

void load_RIB(Customer *customers, Advisor *advisors)
{
    char rib[24];
    do
    {
        user_id = -1;
        printf("Which customer do you want to consult ?\n");
        scanf("%s", &rib);
        int i;
        for (i == 0; i < 50; i++)
        {
            if (strcmp(rib, advisors[advisor_index].RIB[i]) == 0)
            {
                user_id = findID(customers, rib);
                printf("%d", user_id);
                break;
            }
            printf("%s\n", rib);
            printf("%s\n", advisors[advisor_id].RIB[i]);
        }
        if (user_id == -1)
        {
            printf("Wrong RIB\n");
        }
    } while (user_id == -1);
    return;
}

void Consult_Messages(Message *messages)
{
    int have_messages = 0;
    for (int i = 0; i < nb_messages; i++)
    {
        if (messages[i].advisorID == advisor_id)
        {
            printf("Message from %s: %s", messages[i].customerRIB, messages[i].message);
            have_messages = 1;
        }
    }
    if (have_messages == 0)
    {
        printf("No messages\n");
    }
    return;
}

void Send_Message(Message *messages, Customer *customers)
{
    nb_messages++;
    Message *temp_messages = realloc(messages, nb_messages * sizeof(Message));
    messages = temp_messages;
    printf("Input you message (max 200 characters):\n");
    scanf(" %199[^\n]", messages[nb_messages - 1].message);
    messages[nb_messages - 1].advisorID = customers[user_id].advisorID;
    strcpy(messages[nb_messages - 1].customerRIB, customers[user_id].RIB);
    return;
}

int main()
{
    Customer *customers = loadC();
    Advisor *advisors = loadA();
    Message *messages = loadM();
    printf("Welcome to the bank\n");
    char username[20];
    char password[20];
    char reconnect = 'y';
    int type_of_account = 0;
    double amount;
    int choice;
    while (reconnect == 'y' || reconnect == 'Y')
    {
        printf("\nDo you want to log in as a customer or an advisor ?\n");
        printf("1. Customer\n");
        printf("2. Advisor\n");
        scanf("%d", &type_of_account);
        if (type_of_account == 1)
        {
            printf("Please enter your username and your password (enter 0 0 to quit):\n");
            scanf("%s %s", &username, &password);
            if (username[0] == '0')
            {
                return 0;
            }
            while (LogInC(customers, username, password) == 0)
            {
                printf("Login failed\n");
                printf("Please enter your username and your password (enter 0 0 to quit):\n");
                scanf("%s %s", &username, &password);
                if (username[0] == '0')
                {
                    return 0;
                }
            }
        }
        else if (type_of_account == 2)
        {
            printf("Please enter your username and your password (enter 0 0 to quit):\n");
            scanf("%s %s", &username, &password);
            if (username[0] == '0')
            {
                return 0;
            }
            while (LogInA(advisors, username, password) == 0)
            {
                printf("Login failed\n");
                printf("Please enter your username and your password (enter 0 0 to quit):\n");
                scanf("%s %s", &username, &password);
                if (username[0] == '0')
                {
                    return 0;
                }
            }
        }
        else
        {
            printf("Wrong choice\n");
        }
        printf("Login successful\n");
        int j = 0;
        do
        {
            printf("\nWhat would you like to do ?\n");
            type_of_account == 1 ? printf("1. Deposit\n") : printf("1. Add money to client account\n");
            type_of_account == 1 ? printf("2. Withdraw\n") : printf("2. Remove money from client account\n");
            type_of_account == 1 ? printf("3. Transfer Money\n") : printf("3. Transfer money from client account\n");
            type_of_account == 1 ? printf("4. Loan Eligibility\n") : printf("4. Loan eligibility of you client\n");
            type_of_account == 1 ? printf("5. Send message\n") : printf("5. Consult message\n");
            type_of_account == 1 ? printf("6. Check informations\n") : printf("6. Check informations of your client\n");
            type_of_account == 1 ? printf("7. Update informations\n") : printf("7. Update informations of your client\n");
            type_of_account == 1 ? printf("8. Log out\n") : printf("8. Create customer\n");
            type_of_account == 1 ? printf("") : printf("9. Log out\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                printf("\nEnter the amount you want to deposit :\n");
                scanf("%lf", &amount);
                Deposit(customers, amount, user_id);
                type_of_account == 1 ? printf("Your balance is now: %.2lf\n", customers[user_id].balance) : printf("Your customer balance is now: %.2lf\n", customers[user_id].balance);
                break;
            case 2:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                printf("\nEnter the amount you want to withdraw :\n");
                scanf("%lf", &amount);
                Withdraw(customers, amount, user_id);
                type_of_account == 1 ? printf("Your balance is now: %.2lf\n", customers[user_id].balance) : printf("Your customer balance is now: %.2lf\n", customers[user_id].balance);
                break;
            case 3:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                printf("Enter the RIB of the person you want to transfer to :\n");
                char RIB[24];
                scanf("%s", &RIB);
                printf("Enter the amount you want to transfer :\n");
                scanf("%lf", &amount);
                transfer(customers, RIB, amount);
                break;
            case 4:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                type_of_account == 1 ? printf("You can get %.2lf as a loan\n", loanEligibility(customers)) : printf("Your client get %.2lf as a loan\n", loanEligibility(customers));
                break;
            case 5:
                if (type_of_account == 2)
                {
                    Consult_Messages(messages);
                }
                else
                {
                    Send_Message(messages, customers);
                    printf("Message sent\n");
                    printf("Message: %s\n", messages[nb_messages - 1].message);
                    printf("RIB: %s\n", messages[nb_messages - 1].customerRIB);
                    printf("Advisor ID: %d\n", messages[nb_messages - 1].advisorID);
                }
                break;
            case 6:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                checkInfo(customers, type_of_account);
                break;
            case 7:
                if (type_of_account == 2)
                {
                    load_RIB(customers, advisors);
                }
                updateInfo(customers);
                break;
            case 8:
                if (type_of_account == 1)
                {
                    choice = 9;
                    printf("do you want to reconnect or not ? (y/n)\n");
                    scanf("%s", &reconnect);
                }
                else
                {
                    customers = create_customer(customers, advisors);
                }
                break;
            case 9:
                printf("do you want to reconnect or not ? (y/n)\n");
                scanf("%s", &reconnect);
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
        } while (choice != 9);
        printf("Goodbye\n");
        SaveFiles(customers, advisors, messages);
    }
    return 0;
}
