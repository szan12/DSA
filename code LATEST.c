/* Case Study:
https://www.actaelectronicamalaysia.com/archives/AEM/2018-issue2/2aem2018-10-13.pdf
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

//int stack[100];
int top1 = -1;

struct Item
{
    int itemID;
    char name[50];
    int quantity;
    float unitPrice;
    float price;

    struct Location
    {
        char stor[10];
        char shelf[10];
    }location;

    struct Vendor
    {
        int vID;
        char vName[50];
        char hp[20][MAX];//array variable
        int totalHp;
        char email[50];
    }vendor[MAX]; //structure array

}item[MAX]; //structure array

struct Employee
{
    char eID[30];
    char position[30];
    struct Name
    {
        char fName[30];
        char lName[30];
    }eN;
};

int vendorCount[MAX];

int insertItem(int);
void display(int);
int deleteItem(int);
void updateItem(int);
void sortID(int,struct Item);
void sortName(int,struct Item);
void sortPrice(int,struct Item);
void searchItem(int);
void displayitem(int);
void Exit(struct Employee);
int isemptya();
int isfulla();

int insertItem(int count)
{
    int howMany;

    if(isfulla())
    {
        printf("\nQuota is full - cannot insert item.");
    }
    else
    {
        printf("\n-----------------------------------------");
        printf("\n             Key in Items");
        printf("\n-----------------------------------------");

        printf("\nHow many items do you want to key in?: ");
        scanf("%d",&howMany);

        for(int i=0;i<howMany;i++)
        {
        top1++;
        count++;
        printf("\n%d. Item ID (integers only!)   : ",i+1);
        scanf("%d",&item[top1].itemID);
        printf("Item Name                     : ");
        scanf(" %[^\n]s",&item[top1].name);
        printf("Quantity of this item         : ");
        scanf("%d",&item[top1].quantity);
        printf("Item Unit Price               : RM");
        scanf("%f",&item[top1].unitPrice);
        printf("\nStoreroom number to store item: ");
        scanf(" %[^\n]s",&item[top1].location.stor);
        printf("Shelf number to store item    : ");
        scanf(" %[^\n]s",&item[top1].location.shelf);

        item[top1].price = item[top1].unitPrice * item[top1].quantity;      // Calculation

        printf("\nNumber of vendors ordered from  : ");
        scanf("%d",&vendorCount[top1]);
        for(int j=0;j<vendorCount[top1];j++)
        {
            printf("\n%d. Vendor ID (only Integer!!): ",j+1);
            scanf("%d",&item[top1].vendor[j].vID);
            printf("Vendor Name                  : ",j+1);
            scanf(" %[^\n]s",&item[top1].vendor[j].vName);

            printf("How many phone numbers does this vendor have?: ");
            scanf("%d",&item[top1].vendor[j].totalHp);
            for(int n=0;n<item[top1].vendor[j].totalHp;n++)
            {
                printf("%d. Phone Number          :",n+1);
                scanf(" %[^\n]s",&item[top1].vendor[j].hp[n]);
            }
            printf("Vendor E-mail           : ",j+1);
            scanf(" %[^\n]s",&item[top1].vendor[j].email);
        }
        printf("-------------------------------------");
    }
    display(count);
    return count;
    }

}

int deleteItem(int count)
{
    int choose,i;

    if(isemptya())
    {
        printf("\nNo items to delete in the system! - Please insert items first.\n");
    }
    else
    {
        printf("\n-----------------------------------------");
        printf("\n             Delete Item");
        printf("\n-----------------------------------------");
        printf("\nEnter Item ID to be deleted: ");
        scanf("%d",&choose);
        for(i=0;i<count;i++)
        {
            if(item[i].itemID==choose)
            {
                for(int q=i;q<count;q++)
                {
                    item[q].itemID=item[q+1].itemID;
                    strcpy(item[q].name,item[q+1].name);
                    item[q].quantity=item[q+1].quantity;
                    item[q].unitPrice=item[q+1].unitPrice;
                    item[q].price=item[q+1].price;
                    strcpy(item[q].location.stor,item[q+1].location.stor);
                    strcpy(item[q].location.shelf,item[q+1].location.shelf);
                    vendorCount[q]=vendorCount[q+1];
                    for(int j=0;j<vendorCount[q];j++)
                    {
                        item[q].vendor[j].vID=item[q+1].vendor[j].vID;
                        strcpy(item[q].vendor[j].vName,item[q+1].vendor[j].vName);
                        strcpy(item[q].vendor[j].email,item[q+1].vendor[j].email);

                        item[q].vendor[j].totalHp=item[q+1].vendor[j].totalHp;
                        for(int m=0;m<item[q].vendor[j].totalHp;m++)
                        {
                            strcpy(item[q].vendor[j].hp[m],item[q+1].vendor[j].hp[m]);
                        }
                    }
                }
                break;
            }
        }

        if(i==count)
            printf("\nItem to be deleted does not exist!!");
        else
        {
            top1--;
            count=count-1;
            printf("\nItem successfully deleted!");
        }
    display(count);
    return count;
    }
}

void updateItem(int count)
{
    int choice, id, i;

    if(isemptya())
    {
        printf("\nNo item available to update!! - Please insert items first.\n");
    }
    else
    {
        printf("\n-----------------------------------------");
        printf("\n             Update Items");
        printf("\n-----------------------------------------");

        printf("\n1. Item unit price");
        printf("\n2. Item quantity");
        printf("\n3. Item location");
        printf("\nChoose a selection to update: ");
        scanf("%d",&choice);

        printf("\nWhich item ID to update?: ");
        scanf("%d",&id);
        for(i=0;i<count;i++)
        {
            if(item[i].itemID==id)
            {
                if(choice==1)
                {
                    printf("Enter new item unit price: ");
                    scanf("%f",&item[i].unitPrice);
                    item[i].price = item[i].unitPrice * item[i].quantity;   // Calculation
                }
                else if(choice==2)
                {
                    printf("Enter new item quantity: ");
                    scanf("%d",&item[i].quantity);
                    item[i].price = item[i].unitPrice * item[i].quantity;   // Calculation
                }
                else if(choice==3)
                {
                    printf("Enter new stor location: ");
                    scanf(" %[^\n]s",&item[i].location.stor);
                    printf("Enter new shelf location: ");
                    scanf(" %[^\n]s",&item[i].location.shelf);
                }
                else
                    printf("\nInvalid selection!!");

                break;
            }
        }
        if(i==count)
            printf("\nItem to be updated does not exist!!");
        else
            printf("\nItem successfully updated!");
        display(count);
    }
}

void sortItem(int count)
{
    int choice,exit;
    struct Item temp;

    if(isemptya())
    {
        printf("\nNo item available to sort!! - Please insert items first.\n");
    }
    else
    {
        printf("\n-----------------------------------------");
        printf("\n              Sort Items");
        printf("\n-----------------------------------------");
        do{
            printf("\n1. Sort items by ID");
            printf("\n2. Sort items by Name");
            printf("\n3. Sort items by Unit Price");
            printf("\nEnter selection: ");
            scanf("%d",&choice);
            if(choice==1)
                sortID(count,temp);
            else if(choice==2)
                sortName(count,temp);
            else if(choice==3)
                sortPrice(count,temp);
            else
                printf("\nInvalid selection!!");

            printf("Sort again? (yes=1 | no=0): ");
            scanf("%d",&exit);
        }while(exit!=0);
    }

}

void sortID(int count,struct Item temp)
{
    int a,smallest,temp2;
    for(a=0;a<count; a++)
    {
        smallest = a;
        for(int b=a+1;b<count; b++)
        {
            if(item[b].itemID<item[smallest].itemID)
            {
                smallest=b;
            }
        }
        temp=item[a];
        item[a]=item[smallest];
        item[smallest]=temp;

        temp2=vendorCount[a];
        vendorCount[a]=vendorCount[smallest];
        vendorCount[smallest]=temp2;
    }
    display(count);
}

void sortName(int count,struct Item temp)
{
    int a,smallest,temp2;
    for(a=0;a<count; a++)
    {
        smallest = a;
        for(int b=a+1;b<count; b++)
        {
            if(strcmp(item[b].name,item[smallest].name)<0)
            {
                smallest=b;
            }
        }
        temp=item[a];
        item[a]=item[smallest];
        item[smallest]=temp;

        temp2=vendorCount[a];
        vendorCount[a]=vendorCount[smallest];
        vendorCount[smallest]=temp2;
    }
    display(count);
}

void sortPrice(int count,struct Item temp)
{
    int a,smallest,temp2;
    for(a=0;a<count; a++)
    {
        smallest = a;
        for(int b=a+1;b<count; b++)
        {
            if(item[b].unitPrice<item[smallest].unitPrice)
            {
                smallest=b;
            }
        }
        temp=item[a];
        item[a]=item[smallest];
        item[smallest]=temp;

        temp2=vendorCount[a];
        vendorCount[a]=vendorCount[smallest];
        vendorCount[smallest]=temp2;
    }
    display(count);
}

void searchItem(int count)
{
    int select,choose,i,id;
    char name[30];
    float price;

    if(count==0)
    {
        printf("\nNo item available to search!! - Please insert items first.\n");
    }
    else
    {
        printf("\n-----------------------------------------");
    printf("\n             Search Item");
    printf("\n-----------------------------------------");
    printf("\n1. Search item name ");
    printf("\n2. Search item ID ");
    printf("\n3. Search item Price ");
    printf("\nPlease select 1 selection : ");
    scanf("%d",&select);
    if (select==1)
        {
            printf("Enter item name:");
            scanf(" %[^\n]s",&name);
            for(i=0;i<count;i++)
            {
                if(strcmp (item[i].name,name)==0)
                {
                        printf("\nItem ID   :%d\n",item[i].itemID);
                        printf("Item Name   :%s\n",item[i].name);
                        printf("Item Quantity   :%d\n",item[i].quantity);
                        printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                        printf("Item Total Price   :RM %.2f\n",item[i].price);
                        printf("Store for item location   :%s\n",item[i].location.stor);
                        printf("Shelf for item location   :%s\n",item[i].location.shelf);
                        for(int a=0;a<vendorCount[i];a++)
                        {
                            printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                            printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                            printf("Vendor Email :%s\n",item[i].vendor[a].email);

                            for(int h=0;h<item[i].vendor[a].totalHp;h++)
                            {
                                printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                            }
                        }
                        break;
                    }
            }
             if(i==count)
                printf("\nItem searched does not exist!!");
            else
                printf("\nItem successfully searched!");

        }
        else  if (select==2)
        {
            printf("Enter item ID:");
            scanf("%d",&id);
            for(i=0;i<count;i++)
            {
                if(item[i].itemID==id)
                {
                        printf("\nItem ID   :%d\n",item[i].itemID);
                        printf("Item Name   :%s\n",item[i].name);
                        printf("Item Quantity   :%d\n",item[i].quantity);
                        printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                        printf("Item Total Price   :RM %.2f\n",item[i].price);
                        printf("Store for item location   :%s\n",item[i].location.stor);
                        printf("Shelf for item location   :%s\n",item[i].location.shelf);
                        for(int a=0;a<vendorCount[i];a++)
                        {
                            printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                            printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                            printf("Vendor Email :%s\n",item[i].vendor[a].email);

                        for(int h=0;h<item[i].vendor[a].totalHp;h++)
                        {
                            printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                        }
                        }
                        break;
                    }
            }
              if(i==count)
                printf("\nItem searched does not exist!!");
            else
                printf("\nItem successfully searched!");
            }
        else
        {
            int found=0;

             printf("Enter item unit price:");
            scanf("%f",&price);
            for(i=0;i<count;i++)
            {
               if(item[i].unitPrice==price)
                {
                    found=1;
                        printf("\nItem ID   :%d\n",item[i].itemID);
                        printf("Item Name   :%s\n",item[i].name);
                        printf("Item Quantity   :%d\n",item[i].quantity);
                        printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                        printf("Item Total Price   :RM %.2f\n",item[i].price);
                        printf("Store for item location   :%s\n",item[i].location.stor);
                        printf("Shelf for item location   :%s\n",item[i].location.shelf);
                        for(int a=0;a<vendorCount[i];a++)
                        {
                            printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                            printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                            printf("Vendor Email :%s\n",item[i].vendor[a].email);

                        for(int h=0;h<item[i].vendor[a].totalHp;h++)
                        {
                            printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                        }
                        }
                        printf("\n-------------------------------------\n");
                  }
            }
            if(found==0)
                printf("\nItem searched does not exist!!");
            else
                printf("\nItem successfully searched!");
            }
    }

}

int isfulla() {

   if(top1 == MAX)
      return 1;
   else
      return 0;
}

int isemptya() {

   if(top1 == -1)
      return 1;
   else
      return 0;
}

void displayitem(int count)
{
     int i=0,ch,id,found=0;
     char name[30],location[30],slocation[30];

	 if (!isemptya())
     {
            printf("\n-----------------------------------------");
            printf("\n             Display Items Information");
            printf("\n-----------------------------------------");
            printf("\n1. Display by item name ");
            printf("\n2. Display by item location ");
            printf("\n3. Display by item ID ");
            printf("\nPlease select 1 selection : ");
            scanf("%d",&ch);
            if (ch==1)
                {
                    printf("Enter item name:");
                    scanf(" %[^\n]s",&name);
                    for(i=0;i<count;i++)
                    {
                        if(strcmp (item[i].name,name)==0)
                        {

                            printf("\nItem ID   :%d\n",item[i].itemID);
                            printf("Item Name   :%s\n",item[i].name);
                            printf("Item Quantity   :%d\n",item[i].quantity);
                            printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                            printf("Item Total Price   :RM %.2f\n",item[i].price);
                            printf("Store for item location   :%s\n",item[i].location.stor);
                            printf("Shelf for item location   :%s\n",item[i].location.shelf);
                            for(int a=0;a<vendorCount[i];a++)
                            {
                                printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                                printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                                printf("Vendor Email :%s\n",item[i].vendor[a].email);

                                for(int h=0;h<item[i].vendor[a].totalHp;h++)
                                {
                                    printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                                }

                            }
                            break;
                        }
                }
             if(i==count)
                printf("\nItem does not exist!!");
            else
                printf("\nItem successfully display!");

        }
        else  if (ch==2)
        {
            printf("Enter item stor location:");
            scanf(" %[^\n]s",&slocation);
            for(i=0;i<count;i++)
            {
                if(strcmp (item[i].location.stor,slocation)==0)
                {
                    found=1;

                        printf("\nItem ID   :%d\n",item[i].itemID);
                        printf("Item Name   :%s\n",item[i].name);
                        printf("Item Quantity   :%d\n",item[i].quantity);
                        printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                        printf("Item Total Price   :RM %.2f\n",item[i].price);
                        printf("Store for item location   :%s\n",item[i].location.stor);
                        printf("Shelf for item location   :%s\n",item[i].location.shelf);
                        for(int a=0;a<vendorCount[i];a++)
                        {
                            printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                            printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                            printf("Vendor Email :%s\n",item[i].vendor[a].email);

                        for(int h=0;h<item[i].vendor[a].totalHp;h++)
                        {
                            printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                        }
                        //printf("\n-------------------------------------\n");
                        }
                        printf("\n-------------------------------------\n");

                    }
            }
              if(found==0)
                printf("\nItem does not exist!!");
            else
                printf("\nItem successfully displayed!");
            }
        else
        {
             printf("Enter item ID:");
            scanf("%d",&id);
            for(i=0;i<count;i++)
            {
               if(item[i].itemID==id)
                {
                        printf("\nItem ID   :%d\n",item[i].itemID);
                        printf("Item Name   :%s\n",item[i].name);
                        printf("Item Quantity   :%d\n",item[i].quantity);
                        printf("Item Unit Price   :RM %.2f\n",item[i].unitPrice);
                        printf("Item Total Price   :RM %.2f\n",item[i].price);
                        printf("Store for item location   :%s\n",item[i].location.stor);
                        printf("Shelf for item location   :%s\n",item[i].location.shelf);
                        for(int a=0;a<vendorCount[i];a++)
                        {
                            printf("\nVendor ID   :%d\n",item[i].vendor[a].vID);
                            printf("Vendor Name   :%s\n",item[i].vendor[a].vName);
                            printf("Vendor Email :%s\n",item[i].vendor[a].email);

                        for(int h=0;h<item[i].vendor[a].totalHp;h++)
                        {
                            printf("Vendor Phone Number  :%s\n",item[i].vendor[a].hp[h]);
                        }
                        //printf("\n-------------------------------------\n");
                        }
                        break;
                    }
            }
            if(i==count)
                printf("\nItem does not exist!!");
            else
                printf("\nItem successfully displayed!");
            }
     }
      else
        {
            printf("\nSystem is empty!! - Please insert items first.\n");
        }

   printf("\nStack full: %s\n" , isfulla()?"true":"false");
   printf("Stack empty: %s\n" , isemptya()?"true":"false");
}


void display(int count)
{
	 int i=0;
	 if (!isemptya())
	 {
             printf("\n\n-----------------------------------------");
            printf("\n             Display Items");
            printf("\n-----------------------------------------");
            for (int i=0;i<count;i++)
            {
                printf("\n----------------------------------------------------------------------------------------------------------------------------");
                printf("\n|Item ID |  Item Name | Item Quantity | Item Unit Price | Item Total Price(RM) | Item location (Stor) | Item location (Shelf)|");
                printf("\n----------------------------------------------------------------------------------------------------------------------------");
                printf("\n  %d          %s           %d             RM %.2f              RM %.2f                %s                     %s",item[i].itemID,item[i].name,item[i].quantity,item[i].unitPrice,item[i].price,item[i].location.stor,item[i].location.shelf);
                printf("\n----------------------------------------------------------------------------------------------------------------------------");
                //printf("\n");
                for(int j=0;j<vendorCount[i];j++)
                {
                    printf("\n%d. Vendor ID  : %d",j+1,item[i].vendor[j].vID);
                    printf("\n%d. Vendor Name: %s",j+1,item[i].vendor[j].vName);

                    for(int n=0;n<item[i].vendor[j].totalHp;n++)
                    {
                        printf("\n%d. Phone Number: %s",n+1,item[i].vendor[j].hp[n]);
                    }
                    printf("\n%d. Vendor E-mail: %s",j+1,item[i].vendor[j].email);
                }
                printf("\n-------------------------------------\n");
            }
         }
    else
        {
            printf("\nSystem is empty!!\n\n");
        }

   printf("Stack full: %s\n" , isfulla()?"true":"false");
   printf("Stack empty: %s\n" , isemptya()?"true":"false");
}

void Exit(struct Employee employee)
{
    printf("\nLogging out as %s, ID: %s, Name: %s %s ",employee.position,employee.eID,employee.eN.fName,employee.eN.lName);
    printf("\n\tBye~~\n");
}

void main()
{
    struct Employee employee;
    int count=0,selection;
    printf("\n=================================================\n\n");
    printf("      Welcome to Stationary Inventory System");
    printf("\n\n=================================================\n");
    printf("Enter your employee ID: ");
    scanf(" %[^\n]s",&employee.eID);
    printf("Enter your position   : ");
    scanf(" %[^\n]s",&employee.position);
    printf("Enter first name      : ");
    scanf(" %[^\n]s",&employee.eN.fName);
    printf("Enter last name       : ");
    scanf(" %[^\n]s",&employee.eN.lName);

    do
    {
        printf("\n                  Task To Do");
        printf("\n=================================================\n");
        printf("\n1. Insert Stationary Item");
        printf("\n2. Delete a Stationary Item");
        printf("\n3. Update Stationary Details");
        printf("\n4. Sort Items");
        printf("\n5. Search an Item");
        printf("\n6. Display Items information");
        printf("\n7. Exit the system");
        printf("\n\n\tEnter a selection: ");
        scanf("%d",&selection);

        switch(selection)
        {
            case 1: count=insertItem(count);
            break;
            case 2: count=deleteItem(count);
            break;
            case 3: updateItem(count);
            break;
            case 4: sortItem(count);
            break;
            case 5: searchItem(count);
            break;
            case 6: displayitem(count);
            break;
            case 7: Exit(employee);
            break;
            default: printf("\nInvalid selection!!");
            break;
        }

    }while(selection!=7);

}
