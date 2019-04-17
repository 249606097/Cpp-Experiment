#include<iostream>
#include<cstdlib>

using namespace std;

struct Point
{
    int x;
    int y;
};


void displayMenu()
{
    cout << "*******************************" << endl;
    cout << "      1.  Circle(圆)" << endl;
    cout << "      2.  Rectangle(长方形)" << endl;
    cout << "      0.  Exit(退出)" << endl;
    cout << "*******************************" << endl;

    return;
}

void getTwoPoints(struct Point *p1, struct Point *p2)
{
    cout << "Please input the coordinate (x,y) of the start point:";
    cin >> p1->x;
    cin >> p1->y;
    cout << "Please input the coordinate (x,y) of the end point:";
    cin >> p2->x;
    cin >> p2->y;

    return;
}

void printPonit(struct Point *p)
{
    cout << "(" << p->x << "," << p->y << ")";
    return;
}

bool out_range(struct Point *p1, struct Point *p2)
{
    if (p1->x < 1 || p1->y < 1 || p2->x < 1 || p2->y < 1 || p1->x > p2->x || p1->y > p2->y)
        return true;
    else
        return false;
}



void drawCircle(struct Point *p1, struct Point *p2)
{
    if (!out_range(p1, p2))
        if (abs(p1->x - p2->x) == abs(p1->y - p2->y))
        {
            struct Point center;
            int temp_x = (p1->x + p2->x);
            int temp_y = (p1->y + p2->y);

            if (temp_x % 2 != 0 || temp_y % 2 != 0)
            {
                cout << "x or y of the center is not int" << endl;
            }
            else
            {        
                center.x = temp_x/2;
                center.y = temp_y/2;

                cout << "Draw a circle at center ";        
                printPonit(&center);
                cout << "with radius " << abs(p1->x - center.x) << endl;
            }
        }
        else
        {
            cout << "Not a circle, Select again" << endl;
        }
    else
        cout << "The points are not valid" << endl;

    return;
}

void drawRectangle(struct Point *p1, struct Point *p2)
{
    if (!out_range(p1, p2))
    {    
        cout << "Draw a rectangle at topleft ";
        printPonit(p1);
        cout << "whose width is " << abs(p1->x - p2->x) << " and height is " << abs(p1->y - p2->y) << endl;
    }
    else
        cout << "The points are not valid" << endl;
        
    return;
}

int main()
{
    int choice = 1;
    struct Point startP, endP;
    while (choice)    
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                getTwoPoints(&startP, &endP);
                drawCircle(&startP, &endP); break;
            case 2:
                getTwoPoints(&startP, &endP);
                drawRectangle(&startP, &endP); break;
            case 0:
                cout << "Good Bye\n"; break;
            default:
                cout << "Not support! Please select again!\n"; break;
        }
    }

    system("PAUSE");
    return 0;
}