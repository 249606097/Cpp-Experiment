#include <iostream>

using namespace std;

#include "Account.h"

Account::Account(double balance)
{
	this->balance = balance;
}

void Account::credit(double balance)
{
	this->balance += balance;
}

bool Account::debit(double balance)
{
	if (this->balance > balance)
	{
		this->balance -= balance;
		return true;
	}
	else
	{
		cout << "Debit amount exceeded account balance" << endl;
		return false;
	}
}

double Account::getBalance()
{
	return this->balance;
}

SavingsAccount::SavingsAccount(double balance, double interestRate) : Account(balance)
{
	this->interestRate = interestRate;
}

double SavingsAccount::calculateInterest()
{
	return this->getBalance() * this->interestRate * 0.01;
}

CheckingAccount::CheckingAccount(double balance, double fee) : Account(balance)
{
	this->fee = fee;
}

bool CheckingAccount::debit(double balance)
{
	if (this->Account::debit(balance))
	{
		if (this->getBalance() > this->fee)
		{
			this->Account::debit(this->fee);
			return true;
		}
		else
		{
			this->Account::credit(balance);
			cout << "Transaction fee exceeded account balance while debiting" << endl;
			return false;
		}
	}

	return false;
}

void CheckingAccount::credit(double balance)
{
	this->Account::credit(balance);

	if (this->getBalance() > this->fee)
	{
		this->Account::debit(fee);
	}
	else
	{
		this->Account::debit(balance);
		cout << "Transaction fee exceeded account balance while crediting" << endl;
		return;
	}
}