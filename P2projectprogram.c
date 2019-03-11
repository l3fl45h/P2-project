#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

void adduser();
int verification();
void run(int c, int i);
int ValidatedLogin(char *uname, char *pword, int i);
int managermenu();
//int clerkmenu();
/*
void addartist();
void updateartistinfo();
void addBooking();
void updateBooking();
void addFoundation();
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
    char realName[30];
    int accountNum;
    float accountBal;
    long int telephone;
    float earningPerYr;
    bookings booking;
    foundations foundation;
} artist;

login loginfo;
artist artarr[20];
bookings bookarr[20];
foundations foundarr[20];

int curr = 0;

FILE *lfp;
FILE *fp;

int main()
{
    int choice, id;

    //adduser();
    id = verification();
    printf("Lets goo\n");
    system("pause");

    /*if(id == 1)
        choice = managermenu();
    else
    if(id == 2)
        //choice = clerkmenu();
    
    run(choice, id);

    /*do
    {
        choice = clerkmenu();
        run(choice);

    } while (choice != 6);*/
    

    return 0;
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

void run(int c, int i)
{
    switch(c)
    {
        case 1: //addartist(); break;

        case 2: break;
    }
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
        lfp = fopen("ManagerFile.dat","ab+");

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
        lfp = fopen("ClerkFile.dat","ab+");

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

int verification()
{
    int id, att=3, p;
    char uname[50], pword[50];

    printf("1. Manager\n");
    printf("2. Clerk\n\n");
    printf("Choice: ");
    scanf("%d", &id);

    while(att != 0)
    {
        p=0;
        printf("Enter username : ");
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
        lfp = fopen("ManagerFile.dat","rb+");
    else 
    if(i==2)
        lfp = fopen("ClerkFile.dat","rb+");
    
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

/*void clerkupdateartistinfo()
{
    int choice;
    switch(choice)
    {
        case 1: updateBooking(); break;

        case 2: updateFoundation(); break;

        case 3: 
    }
}*/


/*void addartist()
{
    char opt;

    fp = fopen("artistinfo.dat","rb+");

    artarr[curr].accountNum = (curr+1) * 1111;

    fseek( fp, ( idnum - 1 ) * sizeof( struct client_info ), SEEK_SET ); //searches for the record in file
	fread( &cli, sizeof( struct client_info ), 1, fp ); //reads the record in file 

    printf("Enter artist real name: ");
    scanf("%s", artarr[curr].realName);

    printf("\nEnter artist stage name: ");
    scanf("%s", artarr[curr].stageName);

    printf("\nEnter artist telephone number: ");
    scanf("%d", &artarr[curr].telephone);

    printf("\nEnter artist yearly earnings: $");
    scanf("%f", &artarr[curr].earningPerYr);

    printf("\nEnter artist account balance: $");
    scanf("%d", &artarr[curr].accountBal);



    /*menu2();
    
    fflush(stdin);
    scanf("%c", &opt);

    if(opt == 'a')
    {
        arr[curr].Type = 's';
        printf("\nEnter balance: $");
        scanf("%f", &arr[curr].amount.balance);
    }
    else
    if(opt == 'b')
    {
        arr[curr].Type = 'c';
        printf("\nEnter balance: $");
        scanf("%f", &arr[curr].amount.overdraft);
    }
    else
        printf("Invalid choice");
    
    curr++;

    return;    
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
    scanf("%s", bookarr[curr].);

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

















