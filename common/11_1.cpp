#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

template <class T>
T max(T array[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > array[max])
        {
            max = i;
        }
    }

    return array[max];
}

class Point {
    public:
        // 默认构造函数，默认值为左上角坐标(0, 0)
        Point(int x = 0, int y = 0);
        void setX(int x);
        int getX();

        void setY(int y);
        int getY();

        void print();
        void moveRight(int offset);
        void moveDown(int offset);

        double distanceTo();
        bool operator>(Point p);
    private:
        int x;
        int y;
};

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Point::setX(int x)
{
    this->x = x;
}

int Point::getX()
{
    return x;
}

void Point::setY(int y)
{
    this->y = y;
}

int Point::getY()
{
    return y;
}

void Point::print()
{
    cout << "(" << this->getX() << ", " << this->getY() << ")";
}


void Point::moveRight(int offset)
{
    this->x += offset;
}

void Point::moveDown(int offset)
{
    this->y -= offset;
}

double Point::distanceTo()
{
    return sqrt(this->x * this->x + this->y * this->y);
}

bool Point::operator>(Point p)
{
    if (this->distanceTo() > p.distanceTo())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Point array[5];
    array[0] = Point (1, 1);
    array[1] = Point (3, 3);
    array[2] = Point (2, 2);
    array[3] = Point (3, 4);
    array[4] = Point (0, 0);

    Point a = max(array, 5);
    
    a.print();
    cout << endl;

    system("PAUSE");
    return 0;
}