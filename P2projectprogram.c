#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

void verification();
int clerkmenu();
/*int managermenu();
void addartist();
void update();
void display();
void delete();*/

typedef struct artist
{
    char stageNAme[20];
    char realName[30];
    int accountNum;
    float accountBal;
    long int telephone;
    float earningPerYr;
} artist;

typedef struct booking
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
    float localRate; 
    float foreignRate;
    artist art;
} book;

typedef struct foundation
{
    int fAccountNum;
    float balance;
    char majorCurCharity[40];
    artist art;
} found;

artist artarr[20];
book bookarr[20];
found foundarr[20];

int main()
{
    int choice;

    verification();

    do
    {
        choice = clerkmenu();

    } while (choice != 6);
    

    return 0;
}

void verification()
{
    int pin, att = 3;
    char username[20];

    do
	{
        printf("Attempts left : %d\n", att);
        printf("Enter username : ");
        scanf("%s", username);
		printf("Enter password : ");
		scanf("%d", &pin);
		if ((pin != 1520)&&(strcmpi(username, "everald") != 0))
		printf("PLEASE ENTER VALID PASSWORD\n");
        att--;
        system("cls");
	}while (((pin != 1520)&&(strcmpi(username, "everald") != 0) == 0)&&(att != 0));

    if(att == 0)
    {
        printf("You have exceeded the amount of attempts");
        exit(0);
    }

    return;
}

int clerkmenu()
{
    int pick;

    system("cls");
    printf("Clerk Menu\n");
    printf("1. View Artist Information\n");
    printf("2. Add artist booking\n");
    printf("3. Update artist booking\n");
    printf("4. Display artist booking\n");
    printf("5. Generate report\n");
    printf("6. Quit\n\n");
    
    printf("Enter your choice: ");
    scanf("%d", &pick);

    return pick;
}



















