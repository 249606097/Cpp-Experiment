#include <iostream>
#include <cstdlib>

using namespace std;

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

int main()
{
    int x, y;

    cout << "Please input a point: ";
    cin >> x >> y;
    Point p1(x,y);            // 生成点对象1

    cout << "Point p1: ";
    p1.print();
    cout << endl;

    Point p2(x * 2, y * 2); //生成点对象2
    cout << "Point p2: ";
    p2.print();
    cout << endl;

    p1.moveRight(10);
    cout << "After moving right, p1: "; 
    p1.print();
    cout << endl;

    p2.moveDown(-10);        // 位移量为负数，表示向上移动
    cout << "After moving down, p2: ";
    p2.print();
    cout << endl;
    
    system("PAUSE");
    return 0;
}