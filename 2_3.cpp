#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
struct Data
{
    int num;
    string order;
};

bool situation(Data temp);

int main()
{
    int n;
    cin >> n;
    Data arr[n];
    int i;

    for (i = 0; i < n; i++)
    {
        cin >> arr[i].num;
        cin >> arr[i].order;
    }

    for (i = 0; i < n; i++)
    {
        cout << "结果_" << i +1 << endl;
        bool the_final;
        the_final = situation(arr[i]);
        if (the_final)
        {
            cout << "目标格局" << endl;
        }
        else
        {
            string test[6];
            int E_place = arr[i].order.find('E');
            int E_left = E_place-3;
            int E_right = E_place+3;
            int total = 0;
            if(E_left<0)
                E_left=0;
            if (E_right>=arr[i].order.length())
                E_right=arr[i].order.length()-1;
            while (E_left<E_place)
            {
                char temp;
                test[total] = arr[i].order; 
                temp = arr[i].order[E_left];
                test[total][E_left] = 'E';
                test[total][E_place] = temp;
                total++;
                E_left++;
            }
            while (E_right>E_place)
            {
                char temp;
                test[total] = arr[i].order; 
                temp = arr[i].order[E_right];
                test[total][E_right] = 'E';
                test[total][E_place] = temp;
                total++;
                E_right--;
            }
            for (int a=0; a<total; a++)
            {
                for (int b=a+1; b<total; b++)
                {
                    string temp;
                    if (test[a]>test[b])
                    {
                        temp = test[a];
                        test[a] = test[b];
                        test[b] = temp;
                    }
                }
            }
            for (int m=0; m<total; m++)
            {
                cout << test[m] << endl;
            }
        }
    }




    system("PAUSE");
    return 0;
    
}

bool situation(Data temp)
{
    int left_white;
    int right_black;

    left_white = temp.order.find('W');
    right_black = temp.order.find('B');
    if (left_white < right_black)
        return true;
    else
        return false;
}