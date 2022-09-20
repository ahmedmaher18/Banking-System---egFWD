#include "app.h"

	
void appStart(void)
{
	//*****************************************Struct initializations*****************************************
	int status = -1;
	int index = 0;
	int* ptr_index = &index;
	ST_transaction_t Transaction;
	ST_transaction_t* ptr_Tran;
	ptr_Tran = &Transaction;
	ST_cardData_t* ptr_CD;
	ptr_CD = &Transaction.cardHolderData;
	ST_terminalData_t* ptr_TD;
	ptr_TD = &Transaction.terminalData;
	ST_accountsDB_t Reference;
	ST_accountsDB_t* ptr_Reference = &Reference;
	//*****************************************Implementation*****************************************
	status = getCardHolderName(ptr_CD);
	if (status == WRONG_NAME)
	{
		printf("ERROR! wrong name\n");
		
	}
	status = getCardExpiryDate(ptr_CD);
	if (status == WRONG_EXP_DATE)
	{
		printf("ERROR! Invalid expiration date\n");
		return;
	}
	status = getCardPAN(ptr_CD);
	if (status == WRONG_PAN)
	{
		printf("ERROR! wrong PAN\n");
		return;
	}
	status = getTransactionDate(ptr_TD);
	if (status == WRONG_DATE)
	{
		printf("ERROR! wrong date\n");
		return;
	}
	status = isCardExpired(Transaction.cardHolderData, Transaction.terminalData);
	if (status == EXPIRED_CARD)
	{
		printf("ERROR! Expired card\n");
		return;
	}
	status = setMaxAmount(ptr_TD);
	if (status == INVALID_MAX_AMOUNT)
	{
		printf("ERROR! Invalid maximum amount\n");
		return;
	}
	status = getTransactionAmount(ptr_TD);
	if (status == INVALID_AMOUNT)
	{
		printf("ERROR! Invalid  amount\n");
		return;

	}
	if (status == EXCEED_MAX_AMOUNT)
	{
		printf("ERROR! Exceeded maximum amount\n");
		return;
	}
	status = isValidAccount(ptr_CD, ptr_Reference, ptr_index);
	if (status == ACCOUNT_NOT_FOUND)
	{
		printf("ERROR! account not found\n");
		return;
	}
	else if (status == DECLINED_STOLEN_CARD)
	{
		printf("ERROR! declined, card is stolen\n");
		return;
	}
	else
	{
		printf("Valid, Account found\n");
		
	}
	status = isAmountAvailable(ptr_TD, index);
	if (status == LOW_BALANCE)
	{
		printf("insufficient funds\n");
		return;
	}
	else if (status == APPROVED)
	{
		printf("Valid Operation\n");
	}
	
}
