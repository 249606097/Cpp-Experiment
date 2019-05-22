#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Commodity
{
    public:
        Commodity();
        Commodity(string name, double price, double num);
        void printInfo();  // 输出该商品的信息：名称、标牌价格、购买数量
        double get_price();
        double get_num();

    private:
        string name;
        double price;
        double num;
};

Commodity::Commodity()
{
    ;
}

Commodity::Commodity(string name, double price, double num)
{
    this->name = name;
    this->price = price;
    this->num = num;
}

void Commodity::printInfo()
{
    cout << this->name << "," << this->price << "," << this->num << endl;

    return;
}

double Commodity::get_price()
{
    return this->price;
}

double Commodity::get_num()
{
    return this->num;
}

class Cart 
{                                                 // 购物车类
    public:
        void addItem(Commodity &item);                      // 添加一定数量的商品到购物车
        double checkout();                  // 对购物车中的商品进行结算
        void printInvoice();               // 将商品信息输出到显示器

    private:
        Commodity iterms[20];
        int num = 0;        // 多少个item
};

void Cart::addItem(Commodity &item)
{
    this->iterms[this->num] = item;
    this->num++;

    return;
}

void Cart::printInvoice()
{
    for (int i =0; i <this->num; i++)
    {
        this->iterms[i].printInfo();
    }

    return;
}

double Cart::checkout()
{
    double total = 0;

    for (int i = 0; i < this->num; i++)
    {
        total += this->iterms[i].get_price() * this->iterms[i].get_num();
    }

    return total;
}

int main() 
{
    Commodity tShirt("Tshirt", 79, 2);// 创建服装对象，名称、价格、数量
    Commodity suit("suit", 1099, 1);  // 套装
    Commodity hat("hat", 129, 3);  // 帽子
    Commodity tv("tv set", 4899, 1); // 创建家电对象，名称、价格、数量
    Commodity ac("air condition", 5280, 1);// 空调

    Cart myCart;
    //将商品添加到购物车
    myCart.addItem(tShirt);
    myCart.addItem(suit);
    myCart.addItem(hat);
    myCart.addItem(tv);
    myCart.addItem(ac);

    cout << "您需要支付" << myCart.checkout() << "元。" << endl;   // 购物车商品结算，显示顾客需要支付的总金额
    myCart.printInvoice(); // 将购物清单输出到显示器上

    system("PAUSE");
    return 0;
}
