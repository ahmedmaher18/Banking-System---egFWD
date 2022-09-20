#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter your full name\n");
	scanf_s("%[^\n]%*c", cardData->cardHolderName , 25);
	if( (strlen(cardData->cardHolderName) > 24) || (strlen(cardData->cardHolderName) < 20) )
	{
		
		return WRONG_NAME;
	}
	else
	{
		return OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int month = 0;
	int year = 0;
	printf("Please enter Expiry date in the form MM/YY\n");
	scanf_s("%s", cardData->cardExpirationDate, 6);
	char* ptr_ExpDate = cardData->cardExpirationDate;
	if (*(ptr_ExpDate+2) != '/')       // first check of date form
	{
		printf("error, wrong date because of dash\n");
		return WRONG_EXP_DATE;
		
	}
	for (int i = 0; i < 2; i++)			// check that digits is entered in the expected locations
	{
		int digit;
		digit = isdigit(*(ptr_ExpDate + i));
		if (digit == 0)
		{
			
			return WRONG_EXP_DATE;
		}
	}
	for (int i = 3; i < 5; i++)
	{
		int digit;
		digit = isdigit(*(ptr_ExpDate + i));
		if (digit == 0)
		{
			
			return WRONG_EXP_DATE;
		}
	}
	month = atoi(ptr_ExpDate);
	year = atoi(ptr_ExpDate + 3);
	if ((month > 12) || (month < 0) || (year > 30) || (year < 0))
	{
		
		printf("error, invalid month or year entered\n");
		return WRONG_EXP_DATE;
	}
	
	printf("entered expiration date is %s\n", cardData->cardExpirationDate);
	return OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter your card PAN\n");
	scanf_s("%s", cardData->primaryAccountNumber, 20);
	if ((strlen(cardData->primaryAccountNumber) > 19) || (strlen(cardData->primaryAccountNumber) < 16))
	{
		return WRONG_PAN;
	}
	else
	{
		
		return OK;
	}
}
