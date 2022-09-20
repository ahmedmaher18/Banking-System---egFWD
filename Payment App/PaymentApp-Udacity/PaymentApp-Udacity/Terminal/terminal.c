#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    int days = 0;
    int month = 0;
    int year = 0;
    printf("Please enter transaction date in DD/MM/YYYY format\n");
    scanf_s("%s", termData->transactionDate, 11);
    // validation still needed
    char* ptr_TranDate = termData->transactionDate;
    for (int i = 0; i < 2; i++)			// check that digits is entered in the expected locations
    {
        int digit;
        digit = isdigit(*(ptr_TranDate + i));
        if (digit == 0)
        {
            printf("error, digit not entered\n");
            return WRONG_DATE;
        }
    }
    for (int i = 3; i < 5; i++)			// check that digits is entered in the expected locations
    {
        int digit;
        digit = isdigit(*(ptr_TranDate + i));
        if (digit == 0)
        {
            printf("error, digit not entered\n");
            return WRONG_DATE;
        }
    }
    for (int i = 6; i < 10; i++)			// check that digits is entered in the expected locations
    {
        int digit;
        digit = isdigit(*(ptr_TranDate + i));
        if (digit == 0)
        {
            printf("error, digit not entered\n");
            return WRONG_DATE;
        }
    }
    if ((*(ptr_TranDate + 2) != '/') || (*(ptr_TranDate + 5) != '/'))
    {
        printf("error, dash not entered\n");
        return WRONG_DATE;
    }
    days = atoi(ptr_TranDate);
    month = atoi(ptr_TranDate + 3);
    year = atoi(ptr_TranDate + 6);
    if ((days > 31) || (days < 0) || (month < 0) || (month > 12) || (year < 0))
    {
        printf("error, invalid date entered\n");
        return WRONG_DATE;
    }
    printf("%s\n", termData->transactionDate);
    return Terminal_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    
    char* TranDate_String = termData.transactionDate;
    char* ExpDate_String = cardData.cardExpirationDate;
    int Tran_Month = 0;
    int Tran_Year = 0;
    int Exp_Month = 0;
    int Exp_Year = 0;
    Tran_Month = atoi(TranDate_String + 3);
    Tran_Year = atoi(TranDate_String + 8);
    Exp_Month = atoi(ExpDate_String);
    Exp_Year = atoi(ExpDate_String + 3);
    if ( (Exp_Year > Tran_Year) || ( (Exp_Year == Tran_Year) && (Exp_Month > Tran_Month) ) )
    {
        
        return Terminal_OK;
    }
    else
    {
       
        return EXPIRED_CARD;
    }
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Please eneter Transaction Amount\n");
    scanf_s("%f", &termData->transAmount);
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }  
    else if (termData->transAmount > 0)
    {
        
         return Terminal_OK;
    }
    else
    {
        
        return INVALID_AMOUNT;
    }
    
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
        return Terminal_OK;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    printf("Please enter max amount\n");
    scanf_s("%f", &termData->maxTransAmount);
    if (termData->maxTransAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        return Terminal_OK;
    }
}
