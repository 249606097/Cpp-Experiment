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
    int total=0;                // ��ʱ��
    int on_floor=0;             // �������ڲ���
    int up_down=0;              // ���� �� ���� ����
    int left=p->number;         // ʣ������
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
    cout << "\b\b\b) " << endl;     // �ڸ����һ���Ӻ�
    return ;
}

int main()
{
    // ��������
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

    // ����
    int total=0;                // ��ʱ��
    int on_floor=0;             // �������ڲ���
    int up_down=0;              // ���� �� ���� ����
    int left=p->number;         // ʣ������
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