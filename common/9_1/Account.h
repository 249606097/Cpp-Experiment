class Account
{
public:
	Account(double balance);

	virtual void credit(double balance);
	virtual bool debit(double balance);
	double getBalance();

private:
	double balance;
};

class SavingsAccount : public Account
{
public:
	SavingsAccount(double balance, double interestRate);

	double calculateInterest();

private:
	double interestRate;
};

class CheckingAccount : public Account
{
public:
	CheckingAccount(double balance, double fee);

	virtual bool debit(double balance);
	virtual void credit(double balance);
private:
	double fee;
};