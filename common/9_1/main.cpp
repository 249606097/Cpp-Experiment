#include <iostream>
#include <iomanip>
#include "Account.h"
#include <cstdlib>

using namespace std;

int main()
{
	Account *accounts[3];
	accounts[0] = new SavingsAccount(100, 3);   //余额100元，利息3%
	accounts[1] = new CheckingAccount(100, 5);  //余额100元，交易费5元
	accounts[2] = new CheckingAccount(50, 5);   //余额50元，交易费5元

	for (int i = 0; i < 3; i++)
	{
		cout << "第" << i + 1 << "次循环的结果：" << endl;
		accounts[i]->debit(200);   //借款200元
		accounts[i]->debit(40);
		accounts[i]->credit(50);   //存款50元
		accounts[i]->debit(49);
		accounts[i]->debit(43);
		accounts[i]->credit(1);

		//将Account指针强制转换为SavingAccount指针
		SavingsAccount *derivedPtr =
			dynamic_cast<SavingsAccount *>(accounts[i]);
		if (derivedPtr != NULL)   //如果类型兼容，转换成功
			derivedPtr->credit(derivedPtr->calculateInterest());
		cout << fixed << setprecision(2);   //使用定点数格式，2位小数部分
		cout << "账户的余额为：" << accounts[i]->getBalance() << endl;

	}

	system("PAUSE");
	return 0;
}
