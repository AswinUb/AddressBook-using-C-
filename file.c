#include <stdio.h>
#include<unistd.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
  int numContacts=addressBook->contactCount;
  FILE *fp;
  fp=fopen("addressBook.csv","w");
  if(fp==NULL)
  {
    printf("Invalid Address\n");
    return;
  }
  for(int i=0;i<numContacts;i++)
  {
    fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fp);
  printf("Contacts saved to addressBook.csv\n");
}


void loadContactsFromFile(AddressBook *addressBook)
{
    int *numContacts = &(addressBook->contactCount);
    FILE *fp;
    fp=fopen("addressBook.csv","r");
    if(fp==NULL)
   {
    printf("Invalid Address\n");
    return;
   }
   int i=0;
   while( fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,
   addressBook->contacts[i].email)!=EOF)  
   {
     i++;
   }
   *numContacts=i;
   fclose(fp);
   usleep(50000);
   printf("\nContacts loaded from addressBook.csv\n");


}
