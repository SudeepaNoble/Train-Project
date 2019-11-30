//To make a file of trainTickets.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define FILENAME "TrainTicketsData.dat"
struct passengerDetails
{
	char passengerName[20];
	char passengerSurname[20];
	char age[10];
	char departureStation[20];
	char arrivalStation[20];
	char date[12];
	char service[10];
	char phoneNumber[20];
	int PNRNumber;
	int passengerStatus;
}structDetails;
void showMenu();
void bookTickets();
void readBookedTrainTicketDetails();
void showSingleTicketDetails();
void updateTicketDetails();
void deleteTicketDetails();
void writeFileNotFound();
void readName();
void readSurname();;
void readAge();
void readDepartureStation();
void readArrivalStation();
void readDate();
void readService();
void readPhoneNumber();
void generatePNRNumber();
void showUpdateDetails();
int getNewPNRNumber();
void readDetails();
void writeDetails();
void showRecordNotFoundMessage();
void readPassengerStatus();
void showCancelledTickets();
void printFileEmpty();
char option;
char temp;
int menuOption, updateOption, PNRNumber, ticketActivationStatus, counter, decision, recordStatus=0;
FILE *fpPassengerDetails;
int main()
{
	showMenu();
}
void showMenu()
{
	printf("Press the corresponding key for your option.\n");
	printf("1. Book the ticket                     : \n");
	printf("2. Show booked ticket details          : \n");
	printf("3. To see particular passengers details: \n");
	printf("4. Update ticket Details               : \n");
	printf("5. Cancel passenger ticket             : \n");
	printf("6. Show cancelled ticket details       : \n");
	printf("Enter your option: ");
	scanf("%d", &menuOption);
	scanf("%c", &temp);
	switch(menuOption)
	{
		case 1:
		{
			bookTickets();
			break;
		}
		case 2:
		{
			readBookedTrainTicketDetails();
			break;
		}
		case 3:
		{
			showSingleTicketDetails();
			break;
		}
		case 4:
		{
			updateTicketDetails();
			break;
		}
		case 5:
		{
			deleteTicketDetails();
			break;
		}
		case 6:
		{
			printf("Showing cancelled ticket details.\n");
			showCancelledTickets();
			break;
		}
		default:
		{
			printf("Invaild option enter the number again.");
			showMenu();
		}
	}
}
void readName()
{
	printf("Passenger Name   : ");
	scanf("%s", structDetails.passengerName);
}
void readSurname()
{
	printf("Passenger Surname: ");
	scanf("%s", structDetails.passengerSurname);
}
void readAge()
{
	printf("passenger Age    : ");
	scanf("%s", structDetails.age);
}
void readDepartureStation()
{
	printf("From Station     : ");
	scanf("%s", structDetails.departureStation);
}
void readArrivalStation()
{
	printf("To Station       : ");
	scanf("%s", structDetails.arrivalStation);
}
void readDate()
{
	printf("Journey Date     : ");
	scanf("%s", structDetails.date);
}
void readService()
{
	printf("Service          : ");
	scanf("%s", structDetails.service);
}
void readPhoneNumber()
{
	printf("PhoneNumber      : ");
	scanf("%s", structDetails.phoneNumber);
	if((strlen(structDetails.phoneNumber))==10)
	{
		printf("Details entered successfully.\n");
	}
	else
	{
		printf("Invalid phone number entered.\nEnter valid phone number.\n");
		readPhoneNumber();
	}
}
void readPassengerStatus()
{
	structDetails.passengerStatus = ticketActivationStatus;
}
void generatePNRNumber()
{
	structDetails.PNRNumber = getNewPNRNumber();
}
int getNewPNRNumber()
{
	fpPassengerDetails=fopen(FILENAME, "r");
	if(fpPassengerDetails == NULL)
	{
		return 1001;
	}
	else
	{
		while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails))
		{
			// dumy loop to read the last record
		}
		fseek(fpPassengerDetails, -sizeof(structDetails.PNRNumber), SEEK_CUR);	
//		printf("**%d**\n", structDetails.PNRNumber+1);
		return structDetails.PNRNumber+1;
	}
	fclose(fpPassengerDetails);
}
void bookTickets()
{
	ticketActivationStatus = 1;
	do
	{
		generatePNRNumber();
		readDetails();
		fpPassengerDetails=fopen(FILENAME,"a");
		fwrite(&structDetails, sizeof(structDetails), 1, fpPassengerDetails);
		fclose(fpPassengerDetails);
		printf("PNR Number of the passenger: %d.\n", structDetails.PNRNumber);
		scanf("%c", &temp);
		printf("Do you want to book another ticket(y/n): ");
		scanf("%c", &option);
	}while(option=='Y'||option=='y');
}
void readBookedTrainTicketDetails()
{
	printf("We are going to print all passenger details.\n");
	fpPassengerDetails=fopen(FILENAME, "r");
	if(fpPassengerDetails == NULL)
	{
		printFileEmpty();
	}
	else
	{
		while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails)>0)
		{
			if(structDetails.passengerStatus == 1)
			{
				writeDetails();
			}			
		}
	}
	fclose(fpPassengerDetails);
	exit;
}
void showSingleTicketDetails()
{
	printf("We are going to see passenger details you want.\n");
	printf("How many passenger ticket details do you want to see: ");
	scanf("%d", &decision);
	for(counter=1; counter<=decision; counter++)
	{
		printf("Enter passenger PNR number to show the details of the passenger: ");
		scanf("%d", &PNRNumber);
		fpPassengerDetails=fopen(FILENAME, "r");
		while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails))
		{
			if(PNRNumber == structDetails.PNRNumber)
			{
				fseek(fpPassengerDetails, -sizeof(structDetails), SEEK_CUR);
				if(structDetails.passengerStatus == 1)
				{
					writeDetails();
					break;
				}
				else
				{
					showRecordNotFoundMessage();
					break;
				}
			}
		}
		fclose(fpPassengerDetails);
	}
}
void updateTicketDetails()
{
	printf("We are going to update a particular passenger details.\n");
	printf("Enter passenger PNR number which passenger details do you want to update: ");
	scanf("%d", &PNRNumber);
	fpPassengerDetails=fopen(FILENAME, "r+");
	while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails))
	{
		if(PNRNumber == structDetails.PNRNumber)
		{
			fseek(fpPassengerDetails, -sizeof(structDetails), SEEK_CUR);
			if(structDetails.passengerStatus == 1)
			{
				showUpdateDetails();
				fwrite(&structDetails, sizeof(structDetails), 1, fpPassengerDetails);
				printf("Details are successfully updated.\n");
				break;
			}
	    	else
			{
				showRecordNotFoundMessage();
				break;
			}
		}
	}
	fclose(fpPassengerDetails);
}
void showUpdateDetails()
{
	printf("Press corresponding number to change the data: \n");
	printf("1. Passenger name    :\n");
	printf("2. Passenger Surname : \n");
	printf("3. passenger age     : \n");
	printf("4. Station           : \n");
	printf("5. Date              : \n");
	printf("6. Service           : \n");
	printf("7. PhoneNumber       : \n");
	printf("8. All details       : \n");
	printf("9. exit              : \n");
	printf("Enter your option: ");
	scanf("%d", &updateOption);
	switch(updateOption)
	{
		case 1:
		{
			readName();
			break;	
		}
		case 2:
		{
			readSurname();
			break;
		}
		case 3:
		{
			readAge();
			break;
		}
		case 4:
		{
			readDepartureStation();
			readArrivalStation();
			break;
		}
		case 5:
		{
			readDate();
			break;
		}
		case 6:
		{
			readService();
			break;
		}
		case 7:
		{
			readPhoneNumber();
			break;
		}
		case 8:
		{
			readDetails();
			break;
		}
		case 9:
		{
			exit;
			break;
		}
		default :
		{
			printf("Enter a invalid option.\nEnter again.\n");
			showUpdateDetails();
		}
	}
}
void deleteTicketDetails()
{
	printf("We are cancel the booked passenger details.\n");
	printf("How many train tickets do you want to delete: ");
	scanf("%d", &decision);
	for(counter=1; counter<=decision; counter++)
	{
		printf("Enter the PNR number of the passenger ticket do you want to cancel: ");
		scanf("%d", &PNRNumber);
		fpPassengerDetails=fopen(FILENAME, "r+");
		while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails))
		{
			if (PNRNumber == structDetails.PNRNumber)
			{
				structDetails.passengerStatus = 0;
				fseek(fpPassengerDetails, -sizeof(structDetails), SEEK_CUR);
				fwrite(&structDetails, sizeof(structDetails), 1, fpPassengerDetails);
				printf("Passenger ticket successfully cancelled.\n");
				recordStatus = 1;
				break;
			}
		}
		fclose(fpPassengerDetails);
		showRecordNotFoundMessage();	
	}
}
void writeDetails()
{
	printf("Passenger Name   : %s\n", structDetails.passengerName);
	printf("passenger Surname: %s\n", structDetails.passengerSurname);
	printf("Passenge Age     : %s\n", structDetails.age);
	printf("From Station     : %s\n", structDetails.departureStation);
	printf("To Station       : %s\n", structDetails.arrivalStation);
	printf("Date             : %s\n", structDetails.date);
	printf("Service          : %s\n", structDetails.service);
	printf("Phone Number     : %s\n", structDetails.phoneNumber);
	printf("PNR Number       : %d\n", structDetails.PNRNumber);
}
void readDetails()
{
	readPassengerStatus();
	readName();
	readSurname();
	readAge();
	readDepartureStation();
	readArrivalStation();
	readDate();
	readService();
	readPhoneNumber();
}
void showRecordNotFoundMessage()
{
	if(recordStatus != 1)
	{
		printf("Record does not exist.\n");
		exit;
	}
}
void showCancelledTickets()
{
	fpPassengerDetails=fopen(FILENAME,"r");
	if(fpPassengerDetails == NULL)
	{
		showRecordNotFoundMessage();
	}
	else
	{
		while(fread(&structDetails, sizeof(structDetails), 1, fpPassengerDetails)>0)
		{
			if(structDetails.passengerStatus == 0)
			{
				writeDetails();
			}
		}
	}
	fclose(fpPassengerDetails);
}
void printFileEmpty()
{
	printf("File is empty.\n");
}