#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


int validate_name(char *str)
{
    int i=0;
    while(str[i]!='\0')
    {
    if(!(isalpha(str[i])) && str[i]!=' ')
    {
        printf("Entered Name is not valid!!\n");
        return 1;
    }
    i++;
    }

    return 0;
}


int validate_phone(char *str)
{
    int i=0;
    while(str[i]!='\0')
    {
        if(!(isdigit(str[i]) && strlen(str)==10))
        {
            printf("Entered Phone number is not valid!!\n");
            return 1;
        }
        i++;
    }    

    return 0;
}


int validate_email(char *str)
{
   int i=0,count=0;
   while(str[i]!='\0')
   {
   if(isalnum(str[i]) && !islower(str[i]))
   {
    printf("Entered Email is not valid!!\n");
    return 1;
   }
   i++;
   }
   if(strstr(str,".org")==NULL && strstr(str,"@gmail.com")==NULL && 
   strstr(str,"@yahoo.com")==NULL && strstr(str,"outlook.com")==NULL && strstr(str,".in")==NULL)
   {
    printf("Entered Email is not valid!!\n");
    return 1;
   }
   if(str[i]=='@')
   {
    printf("Entered Email is not valid!!\n");
    return 1;
   }

    return 0;
}


int search_name(char *str,  AddressBook *addressBook)
{
   int contactCount=addressBook->contactCount;
   int i=0,r=0,count=0;
    for(i=0;i<contactCount;i++)
    {
        if((strcasecmp(str,addressBook->contacts[i].name))==0)
        {
            count++;
            r=i;
        }
    }
    if(count==1)
    {
        return r;
    }
   else if(count>1)
    {
        printf("\nMultiple contacts exist in the same name\n");
        printf("Search by option 2 or 3\n\n");
        return -2;
    }
    else
    {
    return -1;
    }
}


int search_phone(char *str,  AddressBook *addressBook)
{
   int contactCount=addressBook->contactCount;
    for(int i=0;i<contactCount;i++)
    {
    if((strcmp(str,addressBook->contacts[i].phone))==0)
    {
        return i;
    }
    }

    return -1;
}


int search_email(char *str,  AddressBook *addressBook)
{
   int contactCount=addressBook->contactCount;
    for(int i=0;i<contactCount;i++)
    {
    if((strcmp(str,addressBook->contacts[i].email))==0)
    {
        return i;
    }
    }

    return -1;
}


void edit_name(char *str,int n, AddressBook *addressBook)
{
    strcpy(addressBook->contacts[n].name,str);
}

void edit_phone(char *str,int n, AddressBook *addressBook)
{
    strcpy(addressBook->contacts[n].phone,str);
}

void edit_email(char *str,int n, AddressBook *addressBook)
{
    strcpy(addressBook->contacts[n].email,str);
}


void sort_by_name( Contact *str ,AddressBook *addressBook)
{
    int c=addressBook->contactCount;
    Contact temp;
    int i,j;
    for(i=0;i<c-1;i++)
    {
        for(j=0;j<c-i-1;j++)
        {
            if(strcasecmp(str[j].name,str[j+1].name)>0)
            {
                temp=str[j];
                str[j]=str[j+1];
                str[j+1]=temp;
            }
        }
    }
}


void sort_by_phone( Contact *str ,AddressBook *addressBook)
{
    int c=addressBook->contactCount;
    Contact temp;
    int i,j;
    for(i=0;i<c-1;i++)
    {
        for(j=0;j<c-i-1;j++)
        {
            if(strcasecmp(str[j].phone,str[j+1].phone)>0)
            {
                temp=str[j];
                str[j]=str[j+1];
                str[j+1]=temp;
            }
        }
    }
}


void sort_by_email( Contact *str ,AddressBook *addressBook)
{
    int c=addressBook->contactCount;
    Contact temp;
    int i,j;
    for(i=0;i<c-1;i++)
    {
        for(j=0;j<c-i-1;j++)
        {
            if(strcasecmp(str[j].email,str[j+1].email)>0)
            {
                temp=str[j];
                str[j]=str[j+1];
                str[j+1]=temp;
            }
        }
    }
}


void display(int n,AddressBook *addressBook)
{ 
    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");
    printf("|Sl/No| %-30s | %-15s | %-30s |\n", "Name", "Phone", "Email");
    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");

    printf("| %3d | %-30s | %-15s | %-30s |\n", n+1,
                addressBook->contacts[n].name, addressBook->contacts[n].phone, addressBook->contacts[n].email);
    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");
  
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    printf("\n\033[4mContact List\033[0m\n");
    printf("Number of Contacts : %d\n",addressBook->contactCount);
    switch(sortCriteria)
    {
        case 1:
        sort_by_name(addressBook->contacts, addressBook);
        break;

        case 2:
        sort_by_phone(addressBook->contacts,addressBook);
        break;

        case 3:
        sort_by_email(addressBook->contacts,addressBook);
        break;

    }

    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");
    printf("|Sl/No| %-30s | %-15s | %-30s |\n", "Name", "Phone", "Email");
    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %3d | %-30s | %-15s | %-30s |\n", i+1,
        addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    printf("+-----+--------------------------------+-----------------+--------------------------------+\n");

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
      loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	int i=addressBook->contactCount;
    int j,count=0;
    char name[30];
    char phone[10];
    char email[100];

    do
    {
        printf("Enter the Name : ");
        scanf(" %[^\n]",name);
    }
        while(validate_name(name));
        strcpy(addressBook->contacts[i].name,name);
numagain:
    count=0;
    do
    {
        printf("Enter the Phone num : ");
        scanf(" %[^\n]",phone);
    }
        while(validate_phone(phone));
        for(j=0;j<i;j++)
        {
        if(strcmp(phone,addressBook->contacts[j].phone)==0)
        {
            count=1;
        }
        }
        if(count==1)
        {
           printf("The Phone Number already exists!!\n"); 
           printf("Enter another Number\n");
           goto numagain;  
        }
        strcpy(addressBook->contacts[i].phone,phone);

emailagain:
    count=0;
    do
    {
        printf("Enter the Email: ");
        scanf(" %[^\n]",email);
    }
        while(validate_email(email));
        for(j=0;j<i;j++)
        {
            if(strcmp(email,addressBook->contacts[j].email)==0)
            {
                count=1;
            }
        }
        if(count==1)
        {
           printf("The Email is already exists!!\n"); 
           printf("Enter another Email\n");
           goto emailagain;
        }
        else
        strcpy(addressBook->contacts[i].email,email);

        printf("Contact Created Successfully\n");

    addressBook->contactCount++;
    
}


int searchContact(AddressBook *addressBook) 
{
    char name[30];
    char phone[10];
    char email[100];

    printf("Select search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    int Choice;
    int res;
nameagain:
    do
    {
    printf("Enter your choice: ");
    scanf("%d", &Choice);
    __fpurge(stdin);
    switch(Choice)
    {
        case 1:
        do
        {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);
        }
        while(validate_name(name));
        res=search_name(name,addressBook);
        if(res== -1)
        {
            printf("Contact is not found\n");
            goto nameagain;
        }
        else if(res==-2)
        {
            int res1=searchContact(addressBook);
            return res1;
        }
        else
        {
        display(res,addressBook);
        return res;
        }
        break;

phoneagain:
        case 2:
        do
        {
        printf("Enter the phone : ");
        scanf(" %[^\n]",phone);
        }
        while(validate_phone(phone));
        res=search_phone(phone,addressBook);
        if(res== -1)
        {
            printf("Contact is not found\n");
            goto phoneagain;
        }
        else
        {
          display(res,addressBook);
        }
        return res;
        break;

emailagain:
        case 3:
        do
        {
        printf("Enter the email : ");
        scanf(" %[^\n]",email);
        }
        while(validate_email(email));
        res=search_email(email,addressBook);
        if(res== -1)
        {
            printf("Contact is not found\n");
            goto emailagain;
        }
        else
        {
          display(res,addressBook);
        }
        return res;
        break;

        default:
        printf("Invalid\n");

    }  
    }while(!(Choice>=1 && Choice<=3));
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int index=searchContact(addressBook);
    char name[100];
    char phone[10];
    char email[100];

    if(index==-1)
    {
        printf("Enter existing contact\n");
        searchContact(addressBook);
    }

    printf("Select edit criteria:\n");
    printf("1. Edit the name\n");
    printf("2. Edit the phone number\n");
    printf("3. Edit the email\n");
    int Choice;
    do
    {
    printf("Enter your choice: ");
    scanf("%d", &Choice);   
    __fpurge(stdin);  
    switch(Choice)
    {
        case 1:
        
        do
        {
        printf("Enter the new name : ");
        scanf(" %[^\n]",name);       
        } while (validate_name(name));
        edit_name(name,index,addressBook);
        break;

         case 2:
        
        do
        {
        printf("Enter the new phone number: ");
        scanf(" %[^\n]",phone);       
        } while (validate_phone(phone));
        edit_phone(phone,index,addressBook);
        break;

         case 3:
        
        do
        {
        printf("Enter the new email : ");
        scanf(" %[^\n]",email);       
        } while (validate_email(email));
        edit_email(email,index,addressBook);
        break;
        
        default:
        printf("Invalid\n");
    }
    }while(!(Choice>=1 && Choice<=3));

    printf("Contact is Edited\n");
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

   int index=searchContact(addressBook);
   int c=addressBook->contactCount;
   int i;
   while(index==-1)
   {
      index=searchContact(addressBook);
   }
   for(i=index;i<c;i++)
   {
     addressBook->contacts[i]=addressBook->contacts[i+1];
   }
   addressBook->contactCount--;
   printf("Contact is deleted!\n");
}
