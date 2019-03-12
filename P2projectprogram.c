#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define MAX_ART 20

void adduser();
int verification();
void run(int c, int i);
int ValidatedLogin(char *uname, char *pword, int i);
int managermenu();
void addartist();
void artistdatabase(int anum, int c);
void displayartist();
//int clerkmenu();
/*

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
    char fName[30];
    char lName[30];
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

int curr;

FILE *lfp;
FILE *cfp;
FILE *afp;
FILE *aptr;

int main()
{
    int choice, id;

    //adduser();
    //remove comments form adduser function to add manager/clerk
    id = verification();

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

        case 2: displayartist(); break;
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
    char opt, sname[20];
    int anum, c, i;

    system("cls");

    if((cfp = fopen("CurrentPosition.txt","r")) == NULL)
    {
        cfp = fopen("CurrentPosition.txt", "w");
        curr = 0;
        fprintf(cfp,"%d", curr);
        fclose(cfp);
    }
    
    cfp = fopen("CurrentPosition.txt","r");
    fscanf(cfp,"%d", &curr);
    c = curr;
    anum = (curr+1) + 10000;
    fclose(cfp);

    if(c != MAX_ART)
    {
        cfp = fopen("CurrentPosition.txt","w");

        afp = fopen("ArtistInfo.bin","ab+");
        fseek(afp, (anum-1)*sizeof(struct Artist), SEEK_SET); 
        fread(&artarr[c], sizeof( struct Artist ), 1, afp); 

        artarr[c].accountNum = anum;

        printf("Enter artist first name: ");
        scanf("%s", &artarr[c].fName);

        printf("\nEnter artist last name: ");
        scanf("%s", &artarr[c].lName);

        printf("\nEnter artist stage name: ");
        scanf("%s", sname);

        for(i=0; i<=MAX_ART; i++)
        {
            //fseek(afp, (anum-i)*sizeof(struct Artist), SEEK_SET);
            while((fread(&artarr[i], sizeof(struct Artist), 1, afp))&&(i!=curr))
            {
                while((strcmpi(sname, artarr[i].stageName)) == 0)
                {
                    printf("\nStage name is already taken. Enter unique stage name : ");
                    scanf("%s", sname);
                }
                //i++;
            }
        }

        /*while((fread(&artarr[c], sizeof(struct Artist), 1, afp)))
        {
            if((strcmpi(sname, artarr[c].stageName)) == 0)
                while((strcmpi(sname, artarr[c].stageName)) == 0)
                {
                    printf("\nStage name is already taken. Enter unique stage name : ");
                    scanf("%s", sname);
                }
        }*/

        strcpy(artarr[c].stageName, sname);

        printf("\nEnter artist telephone number: ");
        scanf("%d", &artarr[c].telephone);

        printf("\nEnter artist yearly earnings: $");
        scanf("%f", &artarr[c].earningPerYr);

        printf("\nEnter artist account balance: $");
        scanf("%f", &artarr[c].accountBal);

        fseek( afp, ( anum - 1 ) * sizeof( struct Artist ), SEEK_SET ); //searches for the record in file
        fread( &artarr[c], sizeof( struct Artist ), 1, afp ); //reads the record in file 
        
        curr+=1;
        fprintf(cfp,"%d", curr);
        
        fclose(afp);
        fclose(cfp);

        artistdatabase(anum, c);
    }
    return;    
}

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
