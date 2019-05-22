#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Commodity
{
    public:
        Commodity();
        Commodity(string name, double price, double num);
        void printInfo();  // �������Ʒ����Ϣ�����ơ����Ƽ۸񡢹�������
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
{                                                 // ���ﳵ��
    public:
        void addItem(Commodity &item);                      // ���һ����������Ʒ�����ﳵ
        double checkout();                  // �Թ��ﳵ�е���Ʒ���н���
        void printInvoice();               // ����Ʒ��Ϣ�������ʾ��

    private:
        Commodity iterms[20];
        int num = 0;        // ���ٸ�item
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
    Commodity tShirt("Tshirt", 79, 2);// ������װ�������ơ��۸�����
    Commodity suit("suit", 1099, 1);  // ��װ
    Commodity hat("hat", 129, 3);  // ñ��
    Commodity tv("tv set", 4899, 1); // �����ҵ�������ơ��۸�����
    Commodity ac("air condition", 5280, 1);// �յ�

    Cart myCart;
    //����Ʒ��ӵ����ﳵ
    myCart.addItem(tShirt);
    myCart.addItem(suit);
    myCart.addItem(hat);
    myCart.addItem(tv);
    myCart.addItem(ac);

    cout << "����Ҫ֧��" << myCart.checkout() << "Ԫ��" << endl;   // ���ﳵ��Ʒ���㣬��ʾ�˿���Ҫ֧�����ܽ��
    myCart.printInvoice(); // �������嵥�������ʾ����

    system("PAUSE");
    return 0;
}
