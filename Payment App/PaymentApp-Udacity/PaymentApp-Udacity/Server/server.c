#include "server.h"
ST_accountsDB_t DataBase[255] =
{
	{600.00 ,RUNNING, "341604547423264138"},
	{800.00 , BLOCKED, "721833657909634317"},
	{1500.00 , RUNNING, "945417407604316254"},
	{350.00 , RUNNING, "912449191165197897"},
	{480.00 ,  BLOCKED, "200204990523307883"}
};
ST_transaction_t Transaction[255] = { 0 };

int Account_Index;
static int Current_Index = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(transData->cardHolderData.primaryAccountNumber, DataBase[i].primaryAccountNumber) == 0)
		{
			printf("found\n");
			Account_Index = i;
			if (DataBase[i].balance < transData->terminalData.transAmount)
			{
				return DECLINED_INSUFFECIENT_FUND;
			}
			else
			{
				DataBase[i].balance = DataBase[i].balance - transData->terminalData.transAmount;
				return APPROVED;
			}
		}

	}
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence, int* index)
{
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, DataBase[i].primaryAccountNumber) == 0)
		{
			int status;
			printf("Account found\n");
			accountRefrence = &DataBase[i];
			*index = i;
			status = isBlockedAccount(accountRefrence);
			if (status == SERVER_OK)
			{
				return SERVER_OK;
			}
			else
			{
				return DECLINED_STOLEN_CARD;
			}
		}
	}
	return ACCOUNT_NOT_FOUND;	
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{

		if (accountRefrence->state == BLOCKED)
		{
			printf("Stolen Card\n");
			return DECLINED_STOLEN_CARD;
		}
		else
		{
			return SERVER_OK;
		}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, int index)
{
	if (DataBase[index].balance < termData->transAmount)
	{
		
		return LOW_BALANCE;
	}
	else
	{
		DataBase[index].balance = DataBase[index].balance - termData->transAmount;
		printf("your current balance is %f\n", DataBase[index].balance);
		return APPROVED;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static uint32_t SequeceNumber = 72;
	if (transData->transState == APPROVED)
	{
		Transaction[Current_Index] = *transData;
		Current_Index++;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
}

