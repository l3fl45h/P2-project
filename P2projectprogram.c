//importing of needed header files
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include "structures.h" 

/*
Manager username: admin
Manager password: adminpassword

Clerk usernames: clerk1, clerk2
Clerk passwords: clerk1, clerk2
*/



//creation of main array
artist artarr[MAX_ART];

//global variables
login loginfo;
int acurr = 0;
int bcurr[MAX_ART];

//declaration of file pointers
FILE *loginfp;
FILE *artistfp;
FILE *bookingfp;


int ValidatedLogin(char *uname, char *pword, int i) //function to validate login information from file
{
    int result;
	
    if((loginfp = fopen("ManagerFile.bin","rb+")) == NULL && (loginfp = fopen("ClerkFile.bin","rb+")) == NULL)
        printf("No file found. Employee accounts non-existent.");
    else
    {
        if(i==1)
            loginfp = fopen("ManagerFile.bin","rb+");
        else 
        if(i==2)
            loginfp = fopen("ClerkFile.bin","rb+");
        
        while((fread(&loginfo, sizeof(struct Login), 1, loginfp)))
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
}

int verification() //login function requiring username and password
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

        }while(pword[p-1]!='\r'); //do while loop prints asteriks in place of password
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
                printf("\n\aInvalid login credentials. Attempts left: %d\n\n", att);
        }
    }

    return id;
}

int managermenu() //function displays the options available to a manager
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

int clerkmenu() //function displays the options available to a clerk
{
    int pick;

    system("cls");
    printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                      MAIN MENU                           *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*               1.Add Artist Booking Information           *\n"); 
	printf("*                                                          *\n");
	printf("*               2.Update Artist Booking Information        *\n");
    printf("*                                                          *\n");
    printf("*               3.Search for an Artist                     *\n");
	printf("*                                                          *\n");
    printf("*               4.Generate Report                          *\n");
    printf("*                                                          *\n");
	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                      5.Exit                              *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
    
    printf("Enter selection: ");
    scanf("%d", &pick);

    return pick;
}

int findartist(char *sn) //function uses flag to find artist stage name
{
    int i;
    for(i=0;i<acurr;i++)
        if(strcmp(sn, artarr[i].stageName) == 0)
            return i;
    
    return -1;
}

int updateartist() //function returns 1 if artist stage name is found. returns -1 otherwise
{
    int pick, a;
    char sname[20];

    system("cls");

    printf("Enter artist stage name to be updated: ");
    scanf("%s", sname);

    a = findartist(sname);

    return a;
}

int managerupdatemenu() //function shows the update menu available to a manager
{
    int pick;

    system("cls");
    puts("************************************************************");
    puts("*                                                          *");
    puts("*               1.Update regular artist Information        *");
    puts("*                                                          *");
    puts("*               2.Add Booking Information                  *"); 
    puts("*                                                          *");
    puts("*               3.Update Booking Information               *");
    puts("*                                                          *");
    puts("*               4.Add Foundation Information               *");
    puts("*                                                          *");
    puts("*               5.Update Foundation Information            *");
    puts("*                                                          *");
    puts("************************************************************");
    puts("*                                                          *");
    puts("*                    6. Main menu                          *");
    puts("*                                                          *");
    puts("************************************************************");

    printf("Enter selection: ");
    scanf("%d", &pick);
    
    return pick;
}

int findbooking(int bnum, int a) //function searches for booking number by using a flag
{
    int i;
    for(i=0;i<MAX_BOOK;i++)
        if(bnum == artarr[a].booking[i].bookingNum)
            return i;
            
    return -1;
}

void addFoundation(int a) //function used to add foundation information for artist 
{
	if(artarr[a].foundation.fAccountNum != 0)
	{
		printf("\aArtist already has a foundation.\n\n");
		system("pause");	
	}
	else
	{
		printf("\nEnter foundation number: ");
	    scanf("%d", &artarr[a].foundation.fAccountNum);
	
	    printf("\nEnter foundation name: ");
	    scanf("%s", artarr[a].foundation.majorCurCharity);
	
	    printf("\nEnter foundation balance: $");
	    scanf("%f", &artarr[a].foundation.balance);
	}
    
    return;
}

void updateFoundation(int a) //function used to update foundation information for an artist
{
	system("cls");
	if(!artarr[a].foundation.fAccountNum)
	{
		printf("\aArtist does not have a foundation to update.\n\n");
		system("pause");	
	}
	else
	{
		printf("Enter foundation number: ");
		scanf("%s", artarr[a].foundation.fAccountNum);
		
		printf("\nEnter foundation name: ");
	    scanf("%s", artarr[a].foundation.majorCurCharity);
	
	    printf("\nEnter foundation balance: $");
	    scanf("%f", &artarr[a].foundation.balance);
	}

    return;
}

void displayartist(int a) //function displays all the information for a single artist including foundation and booking information
{
    int i;
    
    printf("         Regular artist information         \n");
    printf("**********************************************\n");
    printf("ID number                        : %d\n", artarr[a].id);
    printf("Name                             : %s %s\n", artarr[a].realName, artarr[a].lName);
    printf("Stage name                       : %s\n", artarr[a].stageName);
    printf("Date of birth                    : %d/%d/%d\n", artarr[a].day, artarr[a].month, artarr[a].year);
    printf("Telephone number                 : (876)%ld\n", artarr[a].telephone);
    printf("Earning per year                 : $%.2f\n", artarr[a].earningPerYr);
    printf("Account number                   : %d\n", artarr[a].accountNum);
    printf("Account Balance                  : $%.2f\n\n", artarr[a].accountBal);
    
    
    printf("           Foundation Information           \n");
    printf("**********************************************\n");
    printf("Foundation Number                : %d\n", artarr[a].foundation.fAccountNum);
    printf("Foundation Name                  : %s\n", artarr[a].foundation.majorCurCharity);
    printf("Foundation Balance               : $%.2f\n\n", artarr[a].foundation.balance);
    
    printf("           Booking Information              \n");
    printf("**********************************************\n");
	
    for(i=0; i<bcurr[a]; i++) //for loop prints all bookings along with their information for an artist if they have any bookings
    {
        printf("Booking Number                   : %d\n", artarr[a].booking[i].bookingNum);
        printf("Booking type                     : %c\n", toupper(artarr[a].booking[i].type));
        printf("Booking date                     : %d/%d/%d\n", artarr[a].booking[i].date.day, artarr[a].booking[i].date.month, artarr[i].booking[i].date.year);
        
        if(toupper(artarr[a].booking[i].type) == 'L')
            printf("Booking rate                     : $%.2f\n", artarr[a].booking[i].rateinfo.lrate);
        else
            printf("Booking rate                     : $%.2f\n", artarr[a].booking[i].rateinfo.orate);

        printf("Booking location                 : %s\n", artarr[a].booking[i].location);
        
        if(toupper(artarr[a].booking[i].type) == 'O')
        {
        	printf("Booking team number              : %d\n", artarr[a].booking[i].teamnum);
            printf("Booking flight information       : %s\n", artarr[a].booking[i].flightInfo);
            printf("Booking plane fare               : $%.2f\n", artarr[a].booking[i].planefare);
            printf("Booking hotel                    : %s\n", artarr[a].booking[i].hotel);
            printf("Booking hotel accommodation price: $%.2f\n", artarr[a].booking[i].hotelprice);
            printf("Booking guide                    : %s\n", artarr[a].booking[i].guide);
        }
        printf("\n");
    }
    printf("\n\n");

    return;
}

void display() //function used to check if artist is in database in order to display their information
{
	int a;
    char sname[20];

    system("cls");
        
    printf("Enter artist stage name: ");
    fflush(stdin);
    gets(sname);

    a = findartist(sname);

    if(a==-1)
        printf("\aArist not registered.\n");
    else
    {   system("cls");
        displayartist(a);
    }
    system("pause");
    return;
}

void displayallartists() //function uses displayartist() function to display information of all artists in the database
{
    int x;

    for(x=0; x<acurr; x++)
        displayartist(x);
    
    system("pause");    
    return;
}

void generatereport() //function used to generate earning per year or revenue in foundation and current charity reports
{
    int i, pick;

	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                       REPORTS                            *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
	printf("*                                                          *\n");
	printf("*                  1.Earning per year                      *\n"); 
	printf("*                                                          *\n");
	printf("*         2.Revenue in foundation and current charity      *\n");
    printf("*                                                          *\n");
	printf("************************************************************\n\n");
	
	printf("Enter type of report that you want to generate: ");
	scanf("%d", &pick);
	
	while(pick != 1 && pick != 2)
	{
		printf("Invalid entry. Enter type of report that you want to generate: ");
		scanf("%d", &pick);
	}
	
	system("cls");
	if(pick == 1)
	{
		FILE *earningfp; //file pointer to store earning per year report
		earningfp = fopen("EarningPerYearReport.txt", "w");
		
        printf("\t\t\t\t\t\tEarnings Per Year Report\n");
		printf("\t\t\t\t******************************************************\n");
        fprintf(earningfp,"\t\t\t\t\t\tEarnings Per Year Report\n");
		fprintf(earningfp,"\t\t\t\t******************************************************\n");
		
		for(i=0; i<acurr; i++)
		{
            printf("\t\t\t\t Artist Stage Name\t\t: %s\n", artarr[i].stageName);
			printf("\t\t\t\t Artist Real Name\t\t: %s %s\n", artarr[i].realName, artarr[i].lName);
			printf("\t\t\t\t Artist Earning Per Year\t: $%.2f\n\n", artarr[i].earningPerYr);
			
            fprintf(earningfp,"\t\t\t\t Artist Stage Name\t\t: %s\n", artarr[i].stageName);
			fprintf(earningfp,"\t\t\t\t Artist Real Name\t\t: %s %s\n", artarr[i].realName, artarr[i].lName);
			fprintf(earningfp,"\t\t\t\t Artist Earning Per Year\t: $%.2f\n\n", artarr[i].earningPerYr);
		}
		
		printf("\t\t\t\t******************************************************\n");
        fprintf(earningfp,"\t\t\t\t******************************************************\n");
		fclose(earningfp);
		system("pause");
	}
	else
	{
		FILE *revenuefp; //file pointer to store revenue in foundation and major charity report
		revenuefp = fopen("RevenueReport.txt", "w");
		
		printf("\t\t\t\t  Revenue in Foundation and Major Charity Report  \n");
		printf("\t\t\t\t***************************************************\n");
		fprintf(revenuefp,"\t\t\t\t  Revenue in Foundation and Major Charity Report  \n");
		fprintf(revenuefp,"\t\t\t\t***************************************************\n");
		
		for(i=0; i<acurr; i++)
		{
			printf("\t\t\t\t  Artist Stage Name\t\t: %s\n", artarr[i].stageName);
			printf("\t\t\t\t  Artist Foundation Number\t: %d\n", artarr[i].foundation.fAccountNum);
			printf("\t\t\t\t  Artist Foundation Name\t: %s\n", artarr[i].foundation.majorCurCharity);
			printf("\t\t\t\t  Artist Foundation Balance\t: $%.2f\n\n", artarr[i].foundation.balance);			
			
			fprintf(revenuefp,"\t\t\t\t  Artist Stage Name\t\t: %s\n", artarr[i].stageName);
			fprintf(revenuefp,"\t\t\t\t  Artist Foundation Number\t: %d\n", artarr[i].foundation.fAccountNum);
			fprintf(revenuefp,"\t\t\t\t  Artist Foundation Name\t: %s\n", artarr[i].foundation.majorCurCharity);
			fprintf(revenuefp,"\t\t\t\t  Artist Foundation Balance\t: $%.2f\n", artarr[i].foundation.balance);
			
		}
		
		printf("\t\t\t\t***************************************************\n");
		fprintf(revenuefp,"\t\t\t\t***************************************************\n");
		system("pause");
		fclose(revenuefp);
	}
	
	return;
}

void addBooking(int a) //function used to add booking information for an artist
{
    int i, x, bn;
    char yn;

    system("cls");
    printf("\nCurrent number of bookings for artist: %d\n", bcurr[a]);
    printf("\nEnter the number of bookings to be added: ");
    scanf("%d", &bn);

    while(bn+bcurr[a] > MAX_BOOK) //while loop checks if accumulated booking number exceeds the maximum booking amount
    {
        printf("\aNumber of artist bookings cannot exceed 15.\nEnter the number of bookings: ");
        scanf("%d", &bn);
    }

    for(i=0; i<bn; i++) //for loop adds booking based on the number entered by user
    {
    	printf("\nEnter booking number: ");
    	scanf("%d", &artarr[a].booking[bcurr[a]].bookingNum);
    	
        printf("\nEnter booking type (L)ocal or (O)verseas: ");
        fflush(stdin);
        scanf("%c", &artarr[a].booking[bcurr[a]].type);

        while((toupper(artarr[a].booking[bcurr[a]].type) != 'L') && (toupper(artarr[a].booking[bcurr[a]].type) != 'O'))
        {
            printf("\nInvalid entry. (Y)es/ (N)o: ");
            fflush(stdin);
            scanf("%c", &artarr[a].booking[bcurr[a]].type);
        }

        if(toupper(artarr[a].booking[bcurr[a]].type) == 'L')
        {
            localdate:printf("\nEnter booking date\nDD MM YYYY\n");
            scanf("%d %d %d", &artarr[a].booking[bcurr[a]].date.day, &artarr[a].booking[bcurr[a]].date.month, &artarr[a].booking[bcurr[a]].date.year);
                            
            while ((artarr[a].booking[bcurr[a]].date.day < 1) || (artarr[a].booking[bcurr[a]].date.day > 31))
            {
                printf("\n\aInvalid day entry.\n");
                printf("DD : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.day);	
            } 

            while ((artarr[a].booking[bcurr[a]].date.month > 12)||(artarr[a].booking[bcurr[a]].date.month < 1))
            {
                printf("\n\aInvalid month entry.\n");
                printf("MM : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.month);	
            } 
            
            while (artarr[a].booking[bcurr[a]].date.year < 2019)
            {
                printf("\n\aInvalid year entry.\n");
                printf("YEAR : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.year);	
            } 
            
            for(x=0; x<bcurr[a]; x++) //for loop checks if the date entered will clash with another booking date
            {
            	if(artarr[a].booking[bcurr[a]].date.day == artarr[a].booking[x].date.day &&
                   artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                   artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto localdate;
                }
			}
			
			strcpy(artarr[a].booking[bcurr[a]].location, "Jamaica");
            printf("\nIs this a voluntary booking? (Y)es/(N)o: ");
            fflush(stdin);
            scanf("%c", &yn);
            
            while((toupper(yn) != 'Y') && (toupper(yn) != 'N'))
            {
                printf("\nInvalid entry. (Y)es/ (N)o: ");
                fflush(stdin);
                scanf("%c", &yn);
            }

            if(toupper(yn) == 'Y')
            {
                artarr[a].booking[bcurr[a]].rateinfo.lrate = 0;
            }
            else
            {
                printf("\nEnter the local rate amount: $");
                scanf("%f", &artarr[a].booking[bcurr[a]].rateinfo.lrate);
            }
        }
        else
        {
            overseasdate:printf("\nEnter booking date\nDD MM YYYY\n");
            scanf("%d %d %d", &artarr[a].booking[bcurr[a]].date.day, &artarr[a].booking[bcurr[a]].date.month, &artarr[a].booking[bcurr[a]].date.year);
                            
            while ((artarr[a].booking[bcurr[a]].date.day < 1) || (artarr[a].booking[bcurr[a]].date.day > 31))
            {
                printf("\n\aInvalid entry.\n");
                printf("DD : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.day);	
            } 

            while ((artarr[a].booking[bcurr[a]].date.month > 12)||(artarr[a].booking[bcurr[a]].date.month < 1))
            {
                printf("\n\aInvalid entry.\n");
                printf("MM : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.month);	
            } 
            
            while (artarr[a].booking[bcurr[a]].date.year < 2019)
            {
                printf("\n\aInvalid entry.\n");
                printf("YEAR : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.year);	
            } 

            for(x=0; x<bcurr[a]; x++) //for loop checks if the date entered will clash with another booking date or is too close to another booking date
            {
            	if(artarr[a].booking[bcurr[a]].date.day == artarr[a].booking[x].date.day && 
                    artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                    artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto overseasdate;
                }
                else
                if(artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day - 2) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day + 2) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day - 1) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day + 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 31 && artarr[a].booking[x].date.day == 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 30 && artarr[a].booking[x].date.day == 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 1 && artarr[a].booking[x].date.day == 31) ||
                   (artarr[a].booking[bcurr[a]].date.day == 1 && artarr[a].booking[x].date.day == 30) &&
                   artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                   artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto overseasdate;
                }
                
			}
			
			printf("\nEnter the number of persons(team) going with artist: ");
			scanf("%d", &artarr[a].booking[bcurr[a]].teamnum);
			
            printf("\nEnter the overseas rate amount: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].rateinfo.orate);

            printf("\nEnter booking location: ");
            scanf("%s", artarr[a].booking[bcurr[a]].location);

            printf("\nEnter booking flight info: ");
            scanf("%s", artarr[a].booking[bcurr[a]].flightInfo);

            printf("\nEnter booking plane fare: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].planefare);

            printf("\nEnter booking hotel: ");
            scanf("%s", artarr[a].booking[bcurr[a]].hotel);

            printf("\nEnter booking hotel accommodation price: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].hotelprice);

            printf("\nEnter booking guide: ");
            scanf("%s", artarr[a].booking[bcurr[a]].guide);

        }
        bcurr[a]++;  
        printf("\n\n");  
        printf("Booking added successfully.\n");  
    }
}

void addartist() //function used to add regular artist information as well as foundation and booking
{
    char sname[20], yn;
    int i, a;

    system("cls");

	if(acurr == 0) //if statement automatically assigns id number to artist
		artarr[acurr].id = acurr + 10001;
	else
		artarr[acurr].id = artarr[acurr-1].id + 1;

    printf("Enter artist stage name: ");
    scanf("%s", sname);

    
    for(i=0; i<acurr; i++) //for loop checks if stage name entered is already being used by another artist
    {
        if(strcmp(sname, artarr[i].stageName) == 0)
        {
            while(strcmp(sname, artarr[i].stageName) == 0)
            {
                system("cls");
                printf("\aStage name is already taken. Enter unique stage name : ");
                scanf("%s", sname);
            }
        }
    }
    
    strcpy(artarr[acurr].stageName, sname);
    
    printf("\nEnter artist first name: ");
    scanf("%s", &artarr[acurr].realName);

    printf("\nEnter artist last name: ");
    scanf("%s", &artarr[acurr].lName);

    printf("\nEnter artist date of birth: \n");
    printf("DD MM YYYY\n");
    scanf("%d %d %d", &artarr[acurr].day, &artarr[acurr].month, &artarr[acurr].year);
    
    while ((artarr[a].booking[bcurr[a]].date.day < 1) || (artarr[a].booking[bcurr[a]].date.day > 31))
    {
        printf("\n\aInvalid day entry.\n");
        printf("DD : ");
        scanf("%d", &artarr[a].booking[bcurr[a]].date.day);	
    } 

    while ((artarr[a].booking[bcurr[a]].date.month > 12)||(artarr[a].booking[bcurr[a]].date.month < 1))
    {
        printf("\n\aInvalid month entry.\n");
        printf("MM : ");
        scanf("%d", &artarr[a].booking[bcurr[a]].date.month);	
    } 
    
    while ((artarr[a].booking[bcurr[a]].date.year < 1940 || artarr[a].booking[bcurr[a]].date.year > 2019)
    {
        printf("\n\aInvalid year entry.\n");
        printf("YYYY : ");
        scanf("%d", &artarr[a].booking[bcurr[a]].date.year);	
    } 
    
    printf("\nEnter artist telephone number: (876)");
    scanf("%ld", &artarr[acurr].telephone);
    
    while ((artarr[acurr].telephone < 1000000)||(artarr[acurr].telephone > 9999999))
    {
    	printf("\nInvlaid entry.\n");
    	printf("\nEnter artist telephone number: (876)");
		scanf("%ld", &artarr[acurr].telephone);
	}

    printf("\nEnter artist yearly earnings: $");
    scanf("%f", &artarr[acurr].earningPerYr);

    printf("\nEnter artist account number: ");
    scanf("%d", &artarr[acurr].accountNum);

    printf("\nEnter artist account balance: $");
    scanf("%f", &artarr[acurr].accountBal);

    printf("\nDoes artist have a charity foundation? (Y)es/(N)o: ");
    fflush(stdin);
    scanf("%c", &yn);

    while((toupper(yn) != 'Y') && (toupper(yn) != 'N'))
    {
        printf("\nInvalid entry. (Y)es/(N)o: ");
        fflush(stdin);
        scanf("%c", &yn);
    }

    if(toupper(yn) == 'Y')
    {
        printf("\nEnter foundation number: ");
        scanf("%d", &artarr[acurr].foundation.fAccountNum);

        printf("\nEnter foundation name: ");
        scanf("%s", artarr[acurr].foundation.majorCurCharity);

        printf("\nEnter foundation balance: $");
        scanf("%f", &artarr[acurr].foundation.balance);
    }
    else
    {
        artarr[acurr].foundation.fAccountNum = 0;
        strcpy(artarr[acurr].foundation.majorCurCharity, "-");
        artarr[acurr].foundation.balance = 0;
    }

    printf("\nDoes artist have any bookings? (Y)es/(N)o: ");
    fflush(stdin);
    scanf("%c", &yn);

    while((toupper(yn) != 'Y') && (toupper(yn) != 'N'))
    {
        printf("\nInvalid entry. (Y)es/ (N)o: ");
        fflush(stdin);
        scanf("%c", &yn);
    }

    a = acurr;
    if(toupper(yn) == 'Y')
        addBooking(a);

    acurr++;
    system("pause");
    return;    
}

void updateregartistinfo(int a) //function used to update regular artist information
{
    printf("\nEnter artist first name: ");
    scanf("%s", &artarr[a].realName);

    printf("\nEnter artist last name: ");
    scanf("%s", &artarr[a].lName);

    printf("\nEnter artist date of birth: \n");
    printf("DD MM YYYY\n");
    scanf("%d %d %d", &artarr[a].day, &artarr[a].month, &artarr[a].year);
    
    printf("\nEnter artist telephone number: (876)");
    scanf("%ld", &artarr[a].telephone);

    printf("\nEnter artist yearly earnings: $");
    scanf("%f", &artarr[a].earningPerYr);

    printf("\nEnter artist account number: ");
    scanf("%d", &artarr[a].accountNum);

    printf("\nEnter artist account balance: $");
    scanf("%f", &artarr[a].accountBal);

    printf("\n");
    printf("Artist successfully update.\n");
    system("pause");

    return;
}

void deleteartist() //function used to delete an artist from the database
{
    int a,i,counter;
    char yn, sname[20];

    system("cls");
    printf("Enter artist stage name to be deleted: ");
    scanf("%s", sname);

    a = findartist(sname);

    if(a==-1)
    {
        printf("\aArist not registered.\n");
        system("pause");
    }
    else
    {   
        system("cls");
        displayartist(a);

        printf("\nAre you sure that you want to delete this artist? (Y)es/(N)o : ");
        fflush(stdin);
        scanf("%c", &yn);

        while((toupper(yn) != 'Y') && (toupper(yn) != 'N'))
        {
            printf("\nInvalid entry. (Y)es/(N)o: ");
            fflush(stdin);
            scanf("%c", &yn);
        } 

        if(toupper(yn) == 'Y')
        {
            for(i=a; i<=acurr; i++)
            {
            	artarr[i].id = artarr[i+1].id;
                strcpy(artarr[i].stageName,artarr[i+1].stageName);
                strcpy(artarr[i].realName,artarr[i+1].realName);
                strcpy(artarr[i].lName,artarr[i+1].lName);
                artarr[i].day = artarr[i+1].day;
                artarr[i].month = artarr[i+1].month;
                artarr[i].year = artarr[i+1].year;
                artarr[i].telephone = artarr[i+1].telephone;
                artarr[i].earningPerYr = artarr[i+1].earningPerYr;
                artarr[i].accountNum = artarr[i+1].accountNum;
                artarr[i].accountBal = artarr[i+1].accountBal;
                
                artarr[i].foundation.fAccountNum = artarr[i+1].foundation.fAccountNum ;
                strcpy(artarr[i].foundation.majorCurCharity,artarr[i+1].foundation.majorCurCharity);
                artarr[i].foundation.balance = artarr[i+1].foundation.balance;
                
                if(bcurr[i]<=bcurr[i+1])
                {
                    for(counter=0;counter<bcurr[i+1];counter++)
                    {
                        artarr[i].booking[counter].bookingNum = artarr[i+1].booking[counter].bookingNum;
                        artarr[i].booking[counter].type = artarr[i+1].booking[counter].type;
                        artarr[i].booking[counter].date.day = artarr[i+1].booking[counter].date.day;
                        artarr[i].booking[counter].date.month = artarr[i+1].booking[counter].date.month;
                        artarr[i].booking[counter].date.year = artarr[i+1].booking[counter].date.year;
                        strcpy(artarr[i].booking[counter].location,artarr[i+1].booking[counter].location);
                        artarr[i].booking[counter].rateinfo.lrate = artarr[i+1].booking[counter].rateinfo.lrate;
                        artarr[i].booking[counter].rateinfo.orate = artarr[i+1].booking[counter].rateinfo.orate;
                        artarr[i].booking[counter].planefare = artarr[i+1].booking[counter].planefare;
                        strcpy(artarr[i].booking[counter].hotel,artarr[i+1].booking[counter].hotel);
                        artarr[i].booking[counter].hotelprice = artarr[i+1].booking[counter].hotelprice;
                        strcpy(artarr[i].booking[counter].flightInfo,artarr[i+1].booking[counter].flightInfo);
                        strcpy(artarr[i].booking[bcurr[i]].guide,artarr[i+1].booking[counter].guide);
                        bcurr[acurr]--;
                    }
                }
                else 
                if(bcurr[i]>bcurr[i+1])
                {
                    for(counter=0;counter<bcurr[i];counter++)
                    {
                        artarr[i].booking[counter].bookingNum = artarr[i+1].booking[counter].bookingNum;
                        artarr[i].booking[counter].type = artarr[i+1].booking[counter].type;
                        artarr[i].booking[counter].date.day = artarr[i+1].booking[counter].date.day;
                        artarr[i].booking[counter].date.month = artarr[i+1].booking[counter].date.month;
                        artarr[i].booking[counter].date.year = artarr[i+1].booking[counter].date.year;
                        strcpy(artarr[i].booking[counter].location,artarr[i+1].booking[counter].location);
                        artarr[i].booking[counter].rateinfo.lrate = artarr[i+1].booking[counter].rateinfo.lrate;
                        artarr[i].booking[counter].rateinfo.orate = artarr[i+1].booking[counter].rateinfo.orate;
                        artarr[i].booking[counter].planefare = artarr[i+1].booking[counter].planefare;
                        strcpy(artarr[i].booking[counter].hotel,artarr[i+1].booking[counter].hotel);
                        artarr[i].booking[counter].hotelprice = artarr[i+1].booking[counter].hotelprice;
                        strcpy(artarr[i].booking[counter].flightInfo,artarr[i+1].booking[counter].flightInfo);
                        strcpy(artarr[i].booking[bcurr[i]].guide,artarr[i+1].booking[counter].guide);
                        bcurr[acurr]--;
                    }
                }
            }
            printf("\nArtist found and deleted.\n");
            system("pause");
        }
        else
        {
            return;
        }
    }
    acurr--;    
    return;    
}

void updateBooking(int a) //function used to update booking information for an artist
{
    char yn;
    int bnum, x;

    system("cls");
    displayartist(a);

    printf("Enter the booking number for the booking you want to update: ");
    scanf("%d", &bnum);

    bnum = findbooking(bnum, a);

    if(bnum == -1)
    {
    	printf("Booking does not exist.\n");
        system("pause");
	} 
    else
    {
        printf("\nEnter booking type (L)ocal or (O)verseas: ");
        fflush(stdin);
        scanf("%c", &artarr[a].booking[bcurr[a]].type);

        while((toupper(artarr[a].booking[bcurr[a]].type) != 'L') && (toupper(artarr[a].booking[bcurr[a]].type) != 'O'))
        {
            printf("\nInvalid entry. (Y)es/ (N)o: ");
            fflush(stdin);
            scanf("%c", &artarr[a].booking[bcurr[a]].type);
        }

        if(toupper(artarr[a].booking[bcurr[a]].type) == 'L')
        {
            localdate:printf("\nEnter booking date\nDD MM YYYY\n");
            scanf("%d %d %d", &artarr[a].booking[bcurr[a]].date.day, &artarr[a].booking[bcurr[a]].date.month, &artarr[a].booking[bcurr[a]].date.year);
                            
            while ((artarr[a].booking[bcurr[a]].date.day < 1) || (artarr[a].booking[bcurr[a]].date.day > 31))
            {
                printf("\n\aInvalid day entry.\n");
                printf("DD : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.day);	
            } 

            while ((artarr[a].booking[bcurr[a]].date.month > 12)||(artarr[a].booking[bcurr[a]].date.month < 1))
            {
                printf("\n\aInvalid month entry.\n");
                printf("MM : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.month);	
            } 
            
            while (artarr[a].booking[bcurr[a]].date.year < 2019)
            {
                printf("\n\aInvalid year entry.\n");
                printf("YEAR : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.year);	
            } 
            
            for(x=0; x<bcurr[a]; x++)
            {
            	if(artarr[a].booking[bcurr[a]].date.day == artarr[a].booking[x].date.day &&
                   artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                   artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto localdate;
                }
			}
			
			strcpy(artarr[a].booking[bcurr[a]].location, "Jamaica");
            printf("\nIs this a voluntary booking? (Y)es/(N)o: ");
            fflush(stdin);
            scanf("%c", &yn);
            
            while((toupper(yn) != 'Y') && (toupper(yn) != 'N'))
            {
                printf("\nInvalid entry. (Y)es/ (N)o: ");
                fflush(stdin);
                scanf("%c", &yn);
            }

            if(toupper(yn) == 'Y')
            {
                artarr[a].booking[bcurr[a]].rateinfo.lrate = 0;
            }
            else
            {
                printf("\nEnter the local rate amount: $");
                scanf("%f", &artarr[a].booking[bcurr[a]].rateinfo.lrate);
            }
        }
        else
        {
            overseasdate:printf("\nEnter booking date\nDD MM YYYY\n");
            scanf("%d %d %d", &artarr[a].booking[bcurr[a]].date.day, &artarr[a].booking[bcurr[a]].date.month, &artarr[a].booking[bcurr[a]].date.year);
                            
            while ((artarr[a].booking[bcurr[a]].date.day < 1) || (artarr[a].booking[bcurr[a]].date.day > 31))
            {
                printf("\n\aInvalid entry.\n");
                printf("DD : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.day);	
            } 

            while ((artarr[a].booking[bcurr[a]].date.month > 12)||(artarr[a].booking[bcurr[a]].date.month < 1))
            {
                printf("\n\aInvalid entry.\n");
                printf("MM : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.month);	
            } 
            
            while (artarr[a].booking[bcurr[a]].date.year < 2019)
            {
                printf("\n\aInvalid entry.\n");
                printf("YEAR : ");
                scanf("%d", &artarr[a].booking[bcurr[a]].date.year);	
            } 

            for(x=0; x<bcurr[a]; x++)
            {
            	if(artarr[a].booking[bcurr[a]].date.day == artarr[a].booking[x].date.day && 
                    artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                    artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto overseasdate;
                }
                else
                if(artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day - 2) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day + 2) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day - 1) ||
                   artarr[a].booking[bcurr[a]].date.day == (artarr[a].booking[x].date.day + 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 31 && artarr[a].booking[x].date.day == 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 30 && artarr[a].booking[x].date.day == 1) ||
                   (artarr[a].booking[bcurr[a]].date.day == 1 && artarr[a].booking[x].date.day == 31) ||
                   (artarr[a].booking[bcurr[a]].date.day == 1 && artarr[a].booking[x].date.day == 30) &&
                   artarr[a].booking[bcurr[a]].date.month == artarr[a].booking[x].date.month &&
                   artarr[a].booking[bcurr[a]].date.year == artarr[a].booking[x].date.year)
                {
                    printf("\a\nBooking date not available.\n");
                    goto overseasdate;
                }
                
			}

            printf("\nEnter the overseas rate amount: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].rateinfo.orate);

            printf("\nEnter booking location: ");
            scanf("%s", artarr[a].booking[bcurr[a]].location);

            printf("\nEnter booking flight info: ");
            scanf("%s", artarr[a].booking[bcurr[a]].flightInfo);

            printf("\nEnter booking plane fare: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].planefare);

            printf("\nEnter booking hotel: ");
            scanf("%s", artarr[a].booking[bcurr[a]].hotel);

            printf("\nEnter booking hotel accommodation price: $");
            scanf("%f", &artarr[a].booking[bcurr[a]].hotelprice);

            printf("\nEnter booking guide: ");
            scanf("%s", artarr[a].booking[bcurr[a]].guide);
        }
    }
     
    printf("Booking successfully updated.\n");
    system("pause");
}

void clerkrun(int c) //function used to run the avaliable options to a clerk
{
    int a;
    switch(c)
    {
        case 1: if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                {
                    a = updateartist();
                    if(a != -1)
                    {
                        addBooking(a);
                    }
                    else
                    {
                        printf("\aArtist not in database.\n");
                        system("pause");
                    }
                }
        break;

        case 2: if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                {
                    a = updateartist();
                    if(a != -1)
                    {
                        updateBooking(a);
                    }
                    else
                    {
                        printf("\aArtist not in database.\n");
                        system("pause");
                    } 
                }
        break;

        case 3: if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                    display();
        break;

        case 4: if(acurr == 0)
                {
                    printf("\aNo information in database.\n");
                    system("pause");
                }
                else
                    generatereport();
		break;
    }

    return;

}

void run2(int a, int p) //function used to run the update options for a manager
{
    switch(p)
    {
        case 1: updateregartistinfo(a); break;

        case 2: addBooking(a); break;

        case 3: updateBooking(a); break;

        case 4: addFoundation(a); break;

        case 5: updateFoundation(a); break;

        case 6: return;

        default: printf("Invalid selection."); break;
    }
    managerupdatemenu();

    return;
}

void storeRec() //function used to store the structured data of an artist into a file as well as the booking count for each artist
{
    int i;
    artistfp = fopen("ArtistInfo.bin","wb");
    bookingfp = fopen("BookingCount.txt", "w");
	
    if(artistfp==NULL)
		printf("The file is not opened.\n");
	else
        fwrite(&artarr, sizeof(artist), acurr, artistfp);
    
    fclose(artistfp);

    for (i=0; i<acurr; i++)
        fprintf(bookingfp,"%d\n", bcurr[i]);
    fclose(bookingfp);
}

void loadRec() //function used to load all artist information from files
{
    int i;
    artistfp = fopen("ArtistInfo.bin","rb");
	bookingfp = fopen("BookingCount.txt", "r");

    if(artistfp==NULL)
    {
        return;
    }	
	else
	{
		while (!feof(artistfp))
        {
            fread(&artarr[acurr], sizeof( artist ), 1, artistfp );
            acurr++;
        }
        acurr--;
	}
	fclose(artistfp);

    for(i=0; i<acurr; i++)
        fscanf(bookingfp,"%d", &bcurr[i]);
    fclose(bookingfp);
}

void managerun(int c) //function used to run the options available to a manager
{
    int a, pick;

    //enum used to represent numbers that would be used for the manager menu
    typedef enum Managerun{AddArtist=1, DisplayArtist, UpdateArtist, DisplayAllArtist, GenerateReport, DeleteArtist, Exit} managerun;
    managerun menu = c;

    system("cls");
    switch(menu)
    {
        case AddArtist: 
				if(acurr < MAX_ART)
                    addartist();
                else
                {
                	printf("\aArtist database is full.\n");
                	system("pause");
				}
                    
        break;

        case DisplayArtist: 
				if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                    display(); 
        break;

        case UpdateArtist: 
				if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                {
                    a = updateartist();
                    if(a != -1)
                    {
                        pick = managerupdatemenu();
                        system("cls");
                        run2(a, pick);
                    }
                    else
                    {
                        printf("\aArtist not in database.\n");
                        system("pause");
                    } 
                }
        break;

        case DisplayAllArtist: 
				if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else
                {
                    system("cls");
                    displayallartists();
                } 
        break;
        
        case GenerateReport: 
				if(acurr == 0)
                {
                    printf("\aNo information in database.\n");
                    system("pause");
                }
                else
                	generatereport();
        break;

        case DeleteArtist: 
				if(acurr == 0)
                {
                    printf("\aNo artists in database.\n");
                    system("pause");
                }
                else            
                    deleteartist();
        break;

        case Exit: storeRec(); break;
    }

    return;
}

int main() //main c function
{
    int choice, id;

    id = verification();
    loadRec();
    do
    {
        if(id == 1) //if statement runs manager menu if the login credentials are that of a manager
        {    
            choice = managermenu();
            managerun(choice);
        }
        else
        if(id == 2) //if statement runs clerk menu if the login credentials are that of a clerk
        {
            choice = clerkmenu();
            clerkrun(choice);
        }
        
    } while((id == 1 && choice != 7)||(id == 2 && choice != 5));

    return 0;
}

