#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define MAX_ART 20

void adduser();
int verification();
int ValidatedLogin(char *uname, char *pword, int i);
void run(int c, int i);
int managermenu();
void addartist();
int find(int anum);
void display();
void displayartist(int p);
void updateartist();
void addFoundation(int acurr);
void loadRec();
void storeRec(int a);

/*
int clerkmenu();
void addartist();
void artistdatabase(int anum, int c);
void displayartist();
void updateartistinfo();
void addBooking();
void updateBooking();
void updateFoundation();
void generatereport();
*/


//typedef enum {january=1, february, march, april, may, june, july, august, september, october, november, december} ;
//typedef enum {Manager=1, Clerk};

typedef union Rate
{
    float lrate;
    float frate;
} rate;

typedef struct Login
{
    char uname[20];
    char pword[20];
} login; 

typedef struct Bookings
{
    int bookingNum;
    char type;
    int day;
    int month;
    int year;
    char hotel[30];
    char location[50];
    char guide[40];
    char flightInfo[30];
    rate rateinfo;
} bookings;

typedef struct Foundation
{
    int fAccountNum;
    float balance;
    char majorCurCharity[40];
} foundations;

typedef struct Artist
{
    char stageName[20];
    char fName[30];
    char lName[30];
    int accountNum;
    float accountBal;
    long int telephone;
    float earningPerYr;
    bookings booking[MAX_ART];
    foundations foundation[MAX_ART];
} artist;

login loginfo;
artist artarr[20];
bookings bookarr[20];
foundations foundarr[20];

int acurr;
int bcurr;
int fcurr;

FILE *lfp;
FILE *cfp;
FILE *afp;
FILE *aptr;
FILE *ffp;

int main()
{
    int choice, id;

    //adduser();
    //remove comments form adduser function to add manager/clerk
    id = verification();
    loadRec();
    do
    {
        if(id == 1)
            choice = managermenu();
        //else
        //if(id == 2)
            //choice = clerkmenu();
        
        run(choice, id);
    } while (choice!= 7);

    return 0;
}

int verification()
{
    int id, att=3, p;
    char uname[50], pword[50];

    system("cls");
    printf("1. Manager\n");
    printf("2. Clerk\n\n");
    printf("Choice: ");
    scanf("%d", &id);

    while(att != 0)
    {
        p=0;
        printf("\nEnter username : ");
        scanf("%s", uname);
        printf("Enter password : ");
        
        do
        { 
            pword[p]=getch(); 
            
            if(pword[p]!='\r')
            { 
                printf("*"); 
            } 
            p++; 

        }while(pword[p-1]!='\r'); 
        pword[p-1]='\0';

        if(ValidatedLogin(uname, pword, id) == 0)
        {
            return id;
        }
        else
        {
            att--;
            if(att == 0)
            {
                printf("\nYou have exceeded the number of attempts.\n");
                exit(0);
            }
            else
                printf("\nInvalid login credentials. Attempts left: %d\n\n", att);
        }
    }

    return id;
}

int ValidatedLogin(char *uname, char *pword, int i)
{
    int result;

    if(i==1)
        lfp = fopen("ManagerFile.bin","rb+");
    else 
    if(i==2)
        lfp = fopen("ClerkFile.bin","rb+");
    
    while((fread(&loginfo, sizeof(struct Login), 1, lfp)))
    {
        if((strcmpi(loginfo.uname,uname) == 0) && (strcmpi(loginfo.pword,pword) == 0))
        {
            result = 0;
            return result;
        }
        else
        {
            result = -1;
        }
    }

    return result;    
}

void run(int c, int i)
{
    switch(c)
    {
        case 1: addartist(); break;

        case 2: display(); break;

        case 3: updateartist(); break;

        //case 7: storeRec(); break;
    }

    return;
}

int managermenu()
{
    int pick;

    system("cls");
    printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                      MAIN MENU                           *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*               1.Add Artist Information                   *\n"); 
	printf("*                                                          *\n");
	printf("*               2.Display Artist Information               *\n");
	printf("*                                                          *\n");
	printf("*               3.Update Artist Information                *\n");
	printf("*                                                          *\n");
    printf("*               4.Display All Artist Information           *\n");
    printf("*                                                          *\n");
    printf("*               5.Generate Report                          *\n");
    printf("*                                                          *\n");
    printf("*               6.Delete Artist Information                *\n");
    printf("*                                                          *\n");
	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                      7.Exit                              *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
    
    printf("Enter selection: ");
    scanf("%d", &pick);

    return pick;
}

void addartist()
{
    char sname[20], yn;
    int i, a;

    system("cls");

    if(acurr < MAX_ART)
    {
        if((cfp = fopen("Count.txt","r")) == NULL)
        {
            cfp = fopen("Count.txt","a");
            acurr = 0;
            fprintf(cfp,"%d", acurr);
        }
        else
        {
            cfp = fopen("Count.txt","r");
        }
            
        fscanf(cfp,"%d", &acurr);
        
        artarr[acurr].accountNum = (acurr+1) + 10000;

        printf("Enter artist first name: ");
        scanf("%s", &artarr[acurr].fName);

        printf("\nEnter artist last name: ");
        scanf("%s", &artarr[acurr].lName);

        printf("\nEnter artist stage name: ");
        scanf("%s", sname);

    
        for(i=0; i<acurr; i++)
        {
            if(strcmpi(sname, artarr[i].stageName) == 0)
                while((strcmpi(sname, artarr[i].stageName) == 0))
                {
                    printf("\nStage name is already taken. Enter unique stage name : ");
                    scanf("%s", sname);
                }
        }

        strcpy(artarr[acurr].stageName, sname);

        printf("\nEnter artist telephone number: (876)");
        scanf("%d", &artarr[acurr].telephone);

        printf("\nEnter artist yearly earnings: $");
        scanf("%f", &artarr[acurr].earningPerYr);

        printf("\nEnter artist account balance: $");
        scanf("%f", &artarr[acurr].accountBal);

        printf("\nDoes artist have a charity foundation? (Y)es (N)o: ");
        fflush(stdin);
        scanf("%c", &yn);

        while((yn != 'y') && (yn != 'n'))
        {
            printf("\nInvalid entry. (Y)es (N)o: ");
            fflush(stdin);
            scanf("%c", &yn);
        }

        if((yn == 'y')||(yn == 'Y'))
        {
            addFoundation(acurr);
        }        

        a = acurr;
        acurr++;
        printf("\nNumber of artists in database: %d\n", acurr);
        
        fclose(cfp);
        cfp = fopen("Count.txt","w");
        fprintf(cfp,"%d", acurr);
        storeRec(a);
        fclose(cfp);
    }
    else
        printf("Artist database is full.");

    system("pause");
    return;    
}

void addFoundation(int acurr)
{
    ffp = fopen("Foundation.txt","a");
    fcurr = acurr;
    
    printf("\nEnter foundation number: ");
    scanf("%d", &artarr[acurr].foundation[fcurr].fAccountNum);

    printf("\nEnter foundation name: ");
    scanf("%s", artarr[acurr].foundation[fcurr].majorCurCharity);

    printf("\nEnter foundation balance: $");
    scanf("%f", &artarr[acurr].foundation[fcurr].balance);

    fprintf(ffp,"%d %s $%.2f\n", artarr[acurr].foundation[fcurr].fAccountNum, artarr[acurr].foundation[fcurr].majorCurCharity, artarr[acurr].foundation[fcurr].balance);
    fclose(ffp);

    return;   
}

void updateartist()
{
    printf("1. Add booking\n");
    printf("2. Update Booking\n");

}

int find(int anum)
{
    int i=0;
    int found=0;

    while(found==0 && i<= acurr)
    {
        if (artarr[i].accountNum == anum)
            found=1;
        else
            i++;
    }

    if(found==1)
   	  return i;
    else
	  return -1;
}

void display()
{
	int i, anum;
	printf("Enter artist account number: ");
	scanf("%d", &anum);
	//fflush(stdin);

	i = find(anum);

	printf("\n");

	if(i==-1)
		printf("This person is not registered here.\n");
	else
		displayartist(i);
}

void displayartist(int p)
{
	system("cls");
    printf("\nAccount number                 : %d\n", artarr[p].accountNum);
    printf("Name                             : %s %s\n", artarr[p].fName, artarr[p].lName);
    printf("Stage name                       : %s\n", artarr[p].stageName);
    printf("Mobile number                    : (876)%d\n", artarr[p].telephone);
    printf("Earning per year                 : $%.2f\n", artarr[p].earningPerYr);
    printf("Account Balance                  : $%.2f\n\n", artarr[p].accountBal);
    printf("Bookings :\n\n");
	printf("\n");
}

void storeRec(int a)
{
    int i;
    afp = fopen("ArtistInfo.txt","a");
	
    if((afp==NULL))
		printf("The file is not opened.\n");
	else
        for(i=a; i<acurr; i++)
		    fprintf(afp,"%d %s %s %s %d $%.2f $%.2f\n", artarr[i].accountNum, artarr[i].fName, artarr[i].lName, artarr[i].stageName, artarr[i].telephone, artarr[i].earningPerYr, artarr[i].accountBal);
        
	fclose(afp);
}

void loadRec()
{
    afp = fopen("C:/Users/evera/OneDrive/Desktop/P2/P2_group_project/ArtistInfo.txt","r");
	
    if(afp==NULL)
    {
        return;
    }	
	else
        do
        {
            fscanf(afp,"%d %s %s %s %d $%.2f $%.2f\n", &artarr[acurr].accountNum, artarr[acurr].fName, artarr[acurr].lName, artarr[acurr].stageName, &artarr[acurr].telephone, &artarr[acurr].earningPerYr, &artarr[acurr].accountBal);
            acurr++;

        } while (!feof(afp));
        
		fclose(afp);
}

/*
void artistdatabase(int anum, int c)
{
    
	afp = fopen("ArtistInfo.bin","rb");
	fseek(afp, (anum - 1)*sizeof(struct Artist), SEEK_SET);
	fread(&artarr[c], sizeof(struct Artist), 1, afp);
	
	aptr = fopen("ArtistInfo.txt","a");
	
	fprintf(aptr,"Account number                   : %d\n", artarr[c].accountNum);
	fprintf(aptr,"Name                             : %s %s\n", artarr[c].fName, artarr[curr].lName);
    fprintf(aptr,"Stage Name                       : %s\n", artarr[c].stageName);
	fprintf(aptr,"Mobile number                    : (876)%d\n", artarr[c].telephone);
	fprintf(aptr,"Earning per year                 : $%.2f\n", artarr[c].earningPerYr);
	fprintf(aptr,"Account Balance                  : $%.2f\n\n", artarr[c].accountBal);
	
	fclose(afp);
	fclose(aptr);
	
	return;
}

void displayartist()
{
    int anum, i;

    if ((afp = fopen("ArtistInfo.bin","rb")) == NULL )
	{
		//displays the following if the file is empty
		printf("\aFile could not open.\n");
		printf("Press any key to go to the main menu....");
		getch();
		return;
	}
    else
    {
        afp = fopen("ArtistInfo.bin","rb+");

        printf("Enter artist account number: ");
        scanf("%d", &anum);
                            
        fseek(afp, (anum - 1)*sizeof(struct Artist), SEEK_SET);

        cfp = fopen("CurrentPosition.txt","r");
        for(i=0; i<curr; i++)
            fread(&artarr[i], sizeof(struct Artist), 1, afp);
        
        if (artarr[i].accountNum != anum)
        {
            printf("\n\aAccount does not exist.\n");
            system("pause");
            return;
        }
        else
        {
            printf("\nAccount number                 : %d\n", artarr[curr].accountNum);
            printf("Name                             : %s %s\n", artarr[curr].fName, artarr[curr].lName );
            printf("Stage n                          : %s\n", artarr[curr].stageName);
            printf("Mobile number                    : (876)%d\n", artarr[curr].telephone);
            printf("Earning per year                 : $%.2f\n", artarr[curr].earningPerYr);
            printf("Account Balance                  : $%.2f\n\n", artarr[curr].accountBal);
            printf("Bookings :\n\n");
        }
        
        fclose(cfp);
        fclose(afp);
        system("pause");
    }
    
    return;
}

void storeRec()
{
    int i;
    afp = fopen("ArtistInfo.txt","a");
	
    if((afp==NULL))
	{
		printf("The file is not opened.\n");
	}
	else
	{
		for (i=0; i<acurr; i++ )
		{
		    fprintf(fp,"%s $%.2f %s \n",amt[size].name,amt[size].price,amt[size].quantity);
        }
		}
		fclose(fp);
}

void loadRec()
{
    fptr=fopen("C:/Users/Devon Stoddart/Documents/cProjects/studFile1/student1.dat","r");
	if((fptr==NULL))
	{
		printf("The file is not opened.\n");
	}
	else
	{
		do
		{
				fscanf(fptr,"%s %s %s \n",StudArr[studArrSize].Id,StudArr[studArrSize].name,StudArr[studArrSize].address);
				studArrSize++;

		}while(!feof(fptr));
		}
		fclose(fptr);
}

void adduser()
{
    int midnum, cidnum, choice;

    printf("\nChoose user to be added:\n");
    printf("1. Manager\n");
    printf("2. Clerk\n\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        lfp = fopen("ManagerFile.bin","ab+");

        printf("Enter username: ");
        scanf("%s", &loginfo.uname);

        printf("Enter password: ");
        scanf("%s", &loginfo.pword);

        fseek(lfp, sizeof(struct Login), SEEK_SET);
        fwrite(&loginfo, sizeof(struct Login), 1, lfp);
        fclose(lfp);
    }
    else
    if(choice == 2)
    {
        lfp = fopen("ClerkFile.bin","ab+");

        printf("Enter username: ");
        scanf("%s", &loginfo.uname);

        printf("Enter password: ");
        scanf("%s", &loginfo.pword);

        fseek(lfp, sizeof(struct Login), SEEK_SET);
        fwrite(&loginfo, sizeof(struct Login), 1, lfp);
        fclose(lfp);
    }
    else
        printf("Invalid entry.");
    
    return;
}
*/





/*void clerkupdateartistinfo()
{
    int choice;
    switch(choice)
    {
        case 1: updateBooking(); break;

        case 2: updateFoundation(); break;

        case 3: 
    }
}




void updateartist()
{

}

void addBooking()
{
    int anum;

    printf("Enter artist account number: ");
    scanf("%d", &anum);

    printf("Enter booking number: ");
    scanf("%d", &bookarr[curr].bookingNum);

    printf("Enter booking type: ");
    scanf("%s", bookarr[curr].type);

    printf("Enter booking day, month and year: ");
    scanf("%d %d %d", &bookarr[curr].day, &bookarr[curr].month. &bookarr[curr].year);

    printf("Enter booking hotel name: ");
    scanf("%s", bookarr[curr].hotel);

    printf("Enter booking location: ");
    scanf("%s", bookarr[curr].location);

    printf("Enter booking location: ");
    scanf("%s", bookarr[curr].location);

    printf("Enter booking location: ");
    scanf("%s", bookarr[curr].location);

    printf("Enter booking location: ");
    scanf("%s", bookarr[curr].location);

    return;
}

void updateBooking()
{

}

void addFoundation()
{
    int anum;
    printf("Enter artist account number: ");
    scanf("%d", &anum);

    printf("Enter foundation account number: ");
    scanf("%d", &foundarr[curr].fAccountNum);

    printf("Enter foundation name: ");
    scanf("%s", foundarr[curr].majorCurCharity);

    printf("Enter foundation balance: $");
    scanf("%f", &foundarr[curr].balance);

    return;
}

void updateFoundation()
{

}

*/
