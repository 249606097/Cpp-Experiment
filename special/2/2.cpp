#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

bool in_circle(double x, double y);

int main()
{
    double e = 0.01;
    int n = 1000;
    double pi = 100.0;
    double residual = 100.0;
    int count = 0;
    
    while (residual > e)
    {
        int m=0;
        srand(unsigned(time(0)));
        for (int i=0; i<n; i++)
        {
            int x = rand();
            int y = rand();
            if (in_circle(double(x)/double(RAND_MAX), double(y)/double(RAND_MAX)))
                m += 1;
        }
        residual = fabs(pi - 4.0 * double(m) / double(n));
        if (count == 1)
        {
            pi = 4.0 * double(m) / double(n);
        }
        else
        {
            pi = (pi * count + 4.0 * double(m) / double(n)) / (count + 1);
        }
        count++;
    }
    
    cout << pi << endl;
    
    system("PAUSE");
    return 0;
}

bool in_circle(double x, double y)
{
    double distance;
    bool is_in_circle = false; 
    distance = (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5);
    if (distance<=0.25)
        is_in_circle = true;
    
    return is_in_circle;
}