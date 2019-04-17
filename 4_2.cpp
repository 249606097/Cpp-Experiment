#include<iostream>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct Rule
{
    int money;
    int tax_rate;
};

void inputRules(struct Rule rules[], int n)
{
    int i;

    for (i=0; i<n; i++)
    {
        cout << "请输入第 " << i+1 << " 条规则：";
        cin >> rules[i].money;
        cin >> rules[i].tax_rate;
    }

    return;
}

double computeTax(struct Rule rules[], int n, int income)
{
    double tax = 0.00;

    if (income > rules[0].money)
    {
        int i;
        for (i=n; i>0; i--)
        {
            if (income >= rules[i].money)
                break;
        }

        tax = (income - rules[i].money) * rules[i].tax_rate * 0.01;

        for (;i>0;i--)
        {
            tax += (rules[i].money - rules[i-1].money) * rules[i-1].tax_rate *0.01;
        }
    }

    return tax;
}

int main()
{
    cout << "请输入规则的条数：";
    int n;
    cin >> n;
    
    struct Rule rules[n];
    inputRules(rules, n);

    for (;;)
    {
        cout << "请输入您的收入：";
        int income;
        cin >> income;

        if (income == -1)
        {
            cout << "再见" << endl;
            break;
        }
        else
        {
            cout << "您的收入是：" << income <<", 应缴所得税：";
            cout.setf(ios::fixed);
            cout << setprecision(2) << computeTax(rules, n, income) << "元。" << endl;
        }
    }
    
    system("PAUSE");
    return 0;
}