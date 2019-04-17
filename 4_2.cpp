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
        cout << "������� " << i+1 << " ������";
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
    cout << "����������������";
    int n;
    cin >> n;
    
    struct Rule rules[n];
    inputRules(rules, n);

    for (;;)
    {
        cout << "�������������룺";
        int income;
        cin >> income;

        if (income == -1)
        {
            cout << "�ټ�" << endl;
            break;
        }
        else
        {
            cout << "���������ǣ�" << income <<", Ӧ������˰��";
            cout.setf(ios::fixed);
            cout << setprecision(2) << computeTax(rules, n, income) << "Ԫ��" << endl;
        }
    }
    
    system("PAUSE");
    return 0;
}