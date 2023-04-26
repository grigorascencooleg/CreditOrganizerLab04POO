#include "pch.h"
#include "CreditCardAccount.h"

#using <mscorlib.dll>

using namespace System;

void CreditCardAccount::SetCreditLimit(double amount) {
	creditLimit = amount;
}

bool CreditCardAccount::MakePurchase(double amount) {
	if (currentBalance + amount > creditLimit) return false;

	currentBalance += amount;
	if (currentBalance >= creditLimit / 2) {
		if (scheme == nullptr) scheme = gcnew LoyaltyScheme();
		else scheme->EarnPointsOnAmount(amount);
	}
	return true;
}

void CreditCardAccount::RedeemLoyaltyPoints() {
	if (scheme == nullptr) {
		Console::WriteLine("Sorry, you do not have a loyalty scheme yet");
		return;
	}

	Console::Write("Points available:");
	Console::Write(scheme->GetPoints());
	Console::Write("\nHow many points do you want to redeem:");
	int points = Convert::ToInt32(Console::ReadLine());
	scheme->RedeemPoints(points);
	Console::WriteLine("Points remaining:{0}", scheme->GetPoints());
}

void CreditCardAccount::MakeRepayment(double amount) {
	currentBalance -= amount;
}

void CreditCardAccount::PrintStatement() {
	Console::WriteLine("Current balance:{0}",currentBalance);
}

long CreditCardAccount::GetAccountNumber() {
	return acoountNumber;
}

CreditCardAccount::CreditCardAccount(long number, double limit) {
	acoountNumber = number;
	creditLimit = limit;
	currentBalance = 0.0;
	numberOfAccounts++;
	scheme = nullptr;
	Console::WriteLine("This is account number :{0}", numberOfAccounts);

}

int CreditCardAccount::GetNumberOfAccounts() {
	return numberOfAccounts;
}

static CreditCardAccount::CreditCardAccount() {
	interestRate = 4.5;
	Console::WriteLine("Static constructor called");
}