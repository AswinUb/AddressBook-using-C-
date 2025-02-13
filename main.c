 #include <stdio.h>
 #include <stdio_ext.h>

#include<ctype.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    int sortChoice;        
    initialize(&addressBook); // Initialize the address book

    do {
        printf("╔═════════════════════════════════════╗\n");
        printf("║          Address Book Menu          ║\n");
        printf("╠═════╦═══════════════════════════════╣\n");
        printf("║ No. ║                               ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  1. ║ Create contact                ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  2. ║ Search contact                ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  3. ║ Edit contact                  ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  4. ║ Delete contact                ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  5. ║ List all Contacts             ║\n");
        printf("║═════╬═══════════════════════════════║\n");
        printf("║  6. ║ Save & Exit                   ║\n");
        printf("╚═════╩═══════════════════════════════╝\n");
        printf("Enter your choice: ");
      
        scanf("%d", &choice);
        __fpurge(stdin);
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
            do
            {
            
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                scanf("%d", &sortChoice);
            }while(!(sortChoice>=1 && sortChoice<=3));    
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6 );
    
       return 0;
}

