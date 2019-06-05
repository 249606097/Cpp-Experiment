#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Date{
    public:
        /* Ĭ�Ϲ��캯������fullyear����ʽ���������գ�Ĭ��ֵΪ1990��1��1�գ�ͬʱ�������ڷָ���Ϊ��-�� */
        Date(int year = 1990, int month = 1, int day = 1);

        /* get��set���� */
        // �������ڣ�����зǷ����»��գ�������Ϊ1
        void setDate(int year, int month, int day);
        void setYear(int year);
        int getYear();
        void setMonth(int month);
        int getMonth();
        void setDay(int month);
        int getDay();
        void setSeparator(char separator);

        /* �����������ʹ��setfill(��0��)��setw(2)����Ҫ����<iomanip>ͷ�ļ� */
        void printFullYear();      // ��YYYY-MM-DD����ʽ��ӡ��2011-01-08
        void printStandardYear(); // ��YY-MM-DD����ʽ��ӡ������11-01-08
        /*  ���㺯��  */
        // ���㵱ǰ�������������֮���������꣬�����ǲ������ڱȵ�ǰ����������
        int fullYearsTo(int year, int month, int day);
        /* ���㵱ǰ�������������֮����������(��������)��������������ڵ�ǰ����֮ǰ�����ظ����� */
        int daysTo(int year, int month, int day);
    private:
        int year;
        int month;
        int day;
        char separator = '-';  // ���ڷָ���
};

Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

int correct_day(int year,int month, int day)
{
    int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year%4==0 && year%100!=0) || year%400==0)
        m[1] = 29;

    if (day > m[month] || day < 1)
    {
        return 1;
    }
    else
    {
        return day;
    } 
}

int correct_month(int month)
{
    if (month > 12 || month < 1)
    {
        return 1;
    }
    else
    {
        return month;
    }
    
}

void Date::setDate(int year, int month, int day)
{
    this->year = year;
    this->month = correct_month(month);
    this->day = correct_day(year, month, day);
}

void Date::setYear(int year)
{
    this->year = year;
}

int Date::getYear()
{
    return this->year;
}

void Date::setMonth(int month)
{
    this->month = correct_month(month);
}

int Date::getMonth()
{
    return this->month;
}

void Date::setDay(int day)
{
    this->day = correct_day(this->year, this->month, day);
}

int Date::getDay()
{
    return this->day;
}

void Date::setSeparator(char separator)
{
    if (separator == '-' || separator == '*' || separator == '/')
        this->separator = separator;
}

void Date::printFullYear()
{
    cout << this->year << this->separator << setfill('0') << setw(2) << this->month << this->separator;
    cout << setfill('0') << setw(2) << this->day << endl;
}

void Date::printStandardYear()
{
    cout << this->year %100 << this->separator << setfill('0') << setw(2) << this->month << this->separator;
    cout << setfill('0') << setw(2) << this->day << endl;
}

int Date::fullYearsTo(int year, int month, int day)
{
    int y = year - this->year;
    if (this->month > month || (this->month == month && this->day > day))
        y--;
    
    return y;
}

int Date::daysTo(int year, int month, int day)
{
    int total = 0;

    if (this->year < year || (this->year == year && this->month < month) || (this->year == year && this->month == month && this->day <= day))
    {   
        int y=year-1;
        while (y > this->year)
        {
            if ((y%4==0 && y%100!=0) || y%400==0)
                total += 366;
            else
                total += 365;
            
            y--;
        }

        int i;
        if (this->year < year)
        {
            int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

            // ������� �������µ�
            if ((year%4==0 && year%100!=0) || year%400==0)
                m[1] = 29;
            else
                m[1] = 28;
                
            for (i=month-1; i>0; i--)
            {
                total += m[i-1];
            }

            total += day;

            // ��ǰ��� �������µ�
            if ((this->year%4==0 && this->year%100!=0) || this->year%400==0)
                m[1] = 29;
            else
                m[1] = 28;

            for (i=this->month+1; i<=12; i++)
            {
                total += m[i-1];
            }

            total += m[this->month-1] - this->day;
        }
        else
        {
            int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

            if ((year%4==0 && year%100!=0) || year%400==0)
                m[1] = 29;
            else
                m[1] = 28;

            for (i=month-1; i>this->month; i--)
            {
                total += m[i-1];
            }

            if (month == this->month)
            {
                total += (day - this->day);
            }
            else
            {
                total += day;
                total += m[this->month-1] - day;
            }
        }
    }
    else
    {
        int y = this->year;
        int m = this->month;
        int d = this->day;

        this->year = year;
        this->month = month;
        this->day = day;

        total = -this->daysTo(y, m, d);
        
        this->year = y;
        this->month = m;
        this->day = d;
    }

    return total;
}

int main()
{
    Date birthDate(1969, 8, 11);

    birthDate.printFullYear();      // ��ӡ��1969-08-11
    birthDate.printStandardYear(); // ��ӡ��69-08-11
    birthDate.setSeparator('/');
    birthDate.printFullYear(); // ��ӡ��1969/08/11

    cout << birthDate.fullYearsTo(2010, 4, 15) << endl; // ��ӡ��40������ʮ��
    cout << birthDate.daysTo(2010, 4, 15) << endl; // ��ӡ14857������14857����
    // ��ӡ-7254�����͹������絮����7254��
    cout << birthDate.daysTo(1949, 10, 1) << endl;

    system("PAUSE");
    return 0;
}
