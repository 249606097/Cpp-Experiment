#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

int main(){
    
    int n;
    int i,j;
    int remaind;
    for(i=1;i<10;i++)
        {
            for(j=1;j<10;j++)
            {
                remaind = i * j % 9;
                if(remaind == 0)
                    remaind = 9;

                cout << setw(2) << remaind << setw(2);

                if(j == 9)
                    cout << endl;
            }
        }

        cout << "which number you want (1~9)? ";
        cin >> n;
        for(i=1;i<10;i++)
        {
            for(j=1;j<10;j++)
            {
                remaind = i * j % 9;
                if(remaind == 0)
                    remaind = 9;

                if(remaind==n)
                    cout << setw(2) << '*' << setw(2);
                else
                    cout << setw(2) << ' ' << setw(2);

                // cout << setw(2) << remaind << setw(2);

                if(j == 9)
                    cout << endl;
            }
        }
    system("PAUSE");
    return 0;
}