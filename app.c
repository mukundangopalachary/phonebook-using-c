#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showMenu(void);
void enterPassword(void);
void addRecord(void);
void searchRecord(void);
void listRecords(void);
void modifyRecord(void);
void deleteRecord(void);
void exitProgram(void);

int main() {
    enterPassword();
    return 0;
}

void addRecord() {
    printf("\nNEW SECTION\n");
    FILE *fptr;
    char name[100], address[100], gmail[100], gender[8];
    double phone;

    fptr = fopen("phonebook_data.txt", "ab+");
    if (fptr == NULL) {
        printf("Failed to create the required file.\n");
        return;
    }

    do {
        printf("Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove newline

        printf("Address: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("Gender: ");
        fgets(gender, sizeof(gender), stdin);
        gender[strcspn(gender, "\n")] = '\0';

        printf("Gmail: ");
        fgets(gmail, sizeof(gmail), stdin);
        gmail[strcspn(gmail, "\n")] = '\0';

        printf("Phone Number: ");
        scanf("%lf", &phone);
        getchar(); // Clear newline

        fprintf(fptr, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);

        char ch;
        printf("Do you want to add more data? Press y for that: ");
        ch = getchar(); // Read character
        getchar(); // Clear newline

        if (ch != 'y') {
            break; // Exit loop if not 'y'
        }

    } while (1);

    fclose(fptr);
    printf("Press any key to continue...");
    getchar(); // Wait for key press
    showMenu(); // Go back to the menu after adding data
}

void searchRecord() {
    FILE *fptr;
    int flag = 0;
    char name[100], address[100], gmail[100], gender[8];
    double phone;
    char name1[100];

    printf("Enter the name of the person you want to see the details: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0'; // Remove newline

    fptr = fopen("phonebook_data.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    while (fscanf(fptr, "%s %s %s %s %lf\n", name, address, gender, gmail, &phone) != EOF) {
        if (strcmp(name, name1) == 0) {
            printf("Record Found\n");
            printf("----------------------------------------\n");
            printf("Name: %s\n", name);
            printf("Address: %s\n", address);
            printf("Gender: %s\n", gender);
            printf("Gmail: %s\n", gmail);
            printf("Phone Number: %.0lf\n", phone);
            printf("----------------------------------------\n");
            flag = 1;
            break;
        }
    }

    fclose(fptr);

    if (flag == 0) {
        printf("No record found.\n");
    }
    
    printf("Press any key to continue...");
    getchar(); // Wait for key press
    showMenu(); // Return to menu
}

void listRecords() {
    FILE *fptr;
    char name[100], address[100], gmail[100], gender[8];
    double phone;

    fptr = fopen("phonebook_data.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    printf("LIST SECTION OPENED\n");

    while (fscanf(fptr, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        printf("------------------------------------------\n");
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
        printf("Gender: %s\n", gender);
        printf("Gmail: %s\n", gmail);
        printf("Phone: %.0lf\n", phone);
        printf("------------------------------------------\n");
    }

    fclose(fptr);
    printf("Press any key to continue...");
    getchar(); // Wait for key press
    showMenu(); // Return to menu
}

void modifyRecord() {
    FILE *fptr, *fptr1;
    char name[100], address[100], gmail[100], name1[100], gender[8];
    double phone;
    int found = 0;

    fptr = fopen("phonebook_data.txt", "r");
    fptr1 = fopen("temp.txt", "w");
    if (fptr == NULL || fptr1 == NULL) {
        printf("Failed to open the files.\n");
        return;
    }

    printf("Enter the name: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0'; // Remove newline

    while (fscanf(fptr, "%s %s %s %s %lf\n", name, address, gender, gmail, &phone) != EOF) {
        if (strcmp(name, name1) == 0) {
            found = 1;
            printf("Enter the new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = '\0';
            printf("Enter the new gender: ");
            fgets(gender, sizeof(gender), stdin);
            gender[strcspn(gender, "\n")] = '\0';
            printf("Enter the new gmail: ");
            fgets(gmail, sizeof(gmail), stdin);
            gmail[strcspn(gmail, "\n")] = '\0';
            printf("Enter the new phone number: ");
            scanf("%lf", &phone);
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
        } else {
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
        }
    }

    fclose(fptr);
    fclose(fptr1);

    if (!found) {
        printf("Record Not found.\n");
    }

    remove("phonebook_data.txt");
    rename("temp.txt", "phonebook_data.txt");
    printf("Press any key to continue...");
    getchar(); // Wait for key press
    showMenu(); // Return to menu
}

void deleteRecord() {
    FILE *fptr, *fptr1;
    char name[100], name1[100], address[100], gmail[100], gender[8];
    double phone;
    int found = 0;

    fptr = fopen("phonebook_data.txt", "r");
    fptr1 = fopen("temp.txt", "w");
    if (fptr == NULL || fptr1 == NULL) {
        printf("Failed to open the files.\n");
        return;
    }

    printf("Enter the name to delete: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0'; // Remove newline

    while (fscanf(fptr, "%s %s %s %s %lf\n", name, address, gender, gmail, &phone) != EOF) {
        if (strcmp(name, name1) == 0) {
            found = 1; // Record found
            printf("Record deleted successfully\n");
        } else {
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
        }
    }

    fclose(fptr);
    fclose(fptr1);

    if (!found) {
        printf("Record Not found.\n");
    }

    remove("phonebook_data.txt");
    rename("temp.txt", "phonebook_data.txt");
    printf("Press any key to continue...");
    getchar(); // Wait for key press
    showMenu(); // Return to menu
}

void exitProgram() {
    printf("Thank you for using the program!\n");
    exit(0);
}

void enterPassword() {
    char pass[10], password[10] = "1234"; // Example password
    printf("Enter password: ");
    scanf("%s", pass);
    if (strcmp(pass, password) == 0) {
        showMenu();
    } else {
        printf("Incorrect password! Exiting...\n");
        exit(0);
    }
}

void showMenu() {
    printf("Welcome to Phonebook Application!\n");
    printf("MENU\n");
    printf("1. Add New Record\n");
    printf("2. Search Record\n");
    printf("3. List All Records\n");
    printf("4. Modify Record\n");
    printf("5. Delete Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear newline

    switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            searchRecord();
            break;
        case 3:
            listRecords();
            break;
        case 4:
            modifyRecord();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            exitProgram();
            break;
        default:
            printf("Invalid choice! Press any key to continue...");
            getchar(); // Wait for key press
            showMenu(); // Return to menu
            break;
    }
}
