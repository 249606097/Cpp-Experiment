#include<iostream>
#include<stdlib.h>

using namespace std;

struct Data
    {
        int number;
        struct Data *next;
    };

void print(Data *p)
{
    int total=0;                // 总时间
    int on_floor=0;             // 现在所在层数
    int up_down=0;              // 向上 或 向下 几层
    int left=p->number;         // 剩余人数
    p = p->next;
    cout << " (";
    for(;;)
    {
        if(left==0)
        {
            break;
        }
        up_down = p->number - on_floor;
        if(up_down>0)
        {
            cout << "6 * " << up_down << " + 5 + ";
        }
        if(up_down<0)
        {
            cout << "4 * " << abs(up_down) << " + 5 + ";
        }
        left = left - 1;
        on_floor = p->number;
        p = p->next;
    }
    cout << "\b\b\b) " << endl;     // 掩盖最后一个加号
    return ;
}

int main()
{
    // 所有数据
    int n;
    Data *head, *p;
    head = (Data *)malloc(sizeof(Data));
    p = head;
    for(;;)
    {
        cin >> n;
        if(n==0)
            break;
        p->number = n;
        p->next = (Data *)malloc(sizeof(Data));
        p = p->next;
    }
    p->next=NULL;
    p = head;

    // 计算
    int total=0;                // 总时间
    int on_floor=0;             // 现在所在层数
    int up_down=0;              // 向上 或 向下 几层
    int left=p->number;         // 剩余人数
    Data *now=head;
    p = p->next;
    for(;;)
    {
        if(left==0)
        {
            cout << total;
            print(now);
            total = 0;
            on_floor = 0;
            left = p->number;
            if(p->next==NULL)
                break;
            now = p;
            p = p->next;
            
        }
        up_down = p->number - on_floor;
        if(up_down>0)
        {
            total += up_down*6+5;
        }
        if(up_down<0)
        {
            total += abs(up_down)*4+5;
        }
        left = left - 1;
        on_floor = p->number;
        p = p->next;
    }

    system("PAUSE");
    return 0;
}