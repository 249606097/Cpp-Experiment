#include <iostream>
#include<iomanip>

using namespace std;

void inputTemps(int temp[], int n);
void displayTemps(int temp[], int n);
void displayPeaks(int temp[], int n);
void displayFlat(int temp[], int n);
void displayNumber(int count);
void displaySpace(int count);
// void displayAppear(int temp[], int n);

int total=0;

int main()
{
    int temps[30];
    
    inputTemps(temps, 30);
    displayTemps(temps, 30);
    displayPeaks(temps, 30);
    displayFlat(temps, 30);
    // displayAppear(temps, 30);
    system("PAUSE");
    return 0;
}


void inputTemps(int temp[], int n)
{
    cout << "Please input the tempratures:" << endl;

    for (;;)
    {
        cin >> temp[total];
        total++;
        if (cin.get() == '\n')
            break;
    }

    cout << endl;
    return ;
}

void displayTemps(int temp[], int n)
{
    cout << "显示柱状图如下：" << endl;
    // bool under_zero = false;
    int min_temp=0;
    int i;
    // // 判断是否有零下温度
    // // 找出最低温度
    // for (i=0; i<15; i++)
    // {
    //     if (temp[i]<0)
    //     {
    //         under_zero = true;
    //         if (temp[i]<min_temp)
    //             min_temp = temp[i];
    //     }
    // }
    // 温度柱状图显示形式
    // if (under_zero) 
    // {
        // for (i=0; i<15; i++)
        // {
        //     if (temp[i]>=0)
        //     {
        //         cout << temp[i] << '\t';
        //         displaySpace(abs(min_temp));
        //         cout << '|';
        //         displayNumber(temp[i]);
        //         cout << endl;
        //     }
        //     else
        //     {
        //         cout << temp[i] << '\t';
        //         displaySpace(abs(min_temp)-abs(temp[i]));
        //         displayNumber(abs(temp[i]));
        //         cout << '|';
        //         cout << endl;
        //     }
        // }
    // }
    // else
    // {
        for (i=0; i<total; i++)
        {
            cout << setw(2) << i+1 << '\t';
            displayNumber(temp[i]);
            cout << endl;
        }
    // }
    cout << endl;

    return ;
}

void displayNumber(int count)
{
    while (count)
    {
        cout << '*';
        count--;
    }

    return ;
}

void displaySpace(int count)
{
    while (count)
    {
        cout << ' ';
        count--;
    }
    return ;
}

void displayPeaks(int temp[], int n)
{
    cout << "显示峰值如下：" << endl;
    bool is_Peak=false;
    for (int i=1; i<total-1; i++)
    {
        if (temp[i]>temp[i-1]&&temp[i]>temp[i+1])
        {
            cout << "Max at day " << i+1 << " is " << temp[i] << endl;
            is_Peak = true;
        }
    }
    if (!is_Peak)
        cout << "没有峰值";

    cout << endl;

    return ;
}

void displayFlat(int temp[], int n)
{
    cout << "显示崮的长度如下：" << endl;
    int length=0;
    int max_position=0+1;
    int max_length=1;
    for (int i=0; i<total-1; i++)
    {
        if (temp[i]==temp[i+1])
            length += 1;

        if (temp[i]!=temp[i+1])
        {
            if(max_length<length)
            {
                max_length = length;
                max_position = i - length + 1 + 1;
            }
            length = 1;
        }
    }

    cout << "The length of longest flat is " << max_position << endl;

    return ;
}

// void displayAppear(int temp[], int n)
// {
//     struct Each
//     {
//         int number;
//         int count=0;
//         struct Each* next;
//     };
//     Each all[15];
//     int many=0;
//     int i = 0;
//     all[0].number = temp[i];
//     all[0].count = 1;
    
//     for (i=1; i<15; i++)
//     {
//         bool existence = false;
//         for (int m=0; m<many; m++)
//         {
//             if (temp[i]==all[m].number)
//             {
//                 all[m].count += 1;
//                 existence = true;
//                 break;
//             }
//         }
//         if (!existence)
//         {
//             many += 1;
//             all[many].number = temp[i];
//             all[many].count = 1;
//         }
//     }
//     int max_position=0;
//     for (i=1; i<many+1; i++)
//     {
//         if (all[i].count > all[max_position].count)
//             max_position = i;
//     }

//     cout << "显示出现次数最多的温度及出现次数：" << endl;
//     cout << "出现最多的温度是 " << all[max_position].number << "，出现了" 
//          << all[max_position].count << "次" <<endl;
    
//     return ;
// }