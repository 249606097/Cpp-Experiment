#include <iostream>
#include <cstdarg>

#include "Automobile.h"
#include "Park.h"

using namespace std;

int main() 
{
	int N;
	cout << "������ͣ��λ������";
	cin >> N;// ����ͣ��λ�������˴�����2

	Park *park = new Park(N);// ����һ��ͣ��������

	Car car1("³B-12345", "�µ�A6");  // �����γ�����
	car1.enter(park);    // car1����ͣ����������ͣ��λ

	Truck truck("³B-23456", 15);  // ������������
	truck.enter(park);   // truck����ͣ���������䳵λ

	car1.leave(park);   // car1�뿪ͣ����������ͣ����

	Bus bus("³B-34567", 50);  // ��������������
	bus.enter(park);   // bus����ͣ���������䳵λ

					   /* ��ʾ��ǰͣ�ŵĳ����ĳ��ƺ��룬�Լ���ǰ��ȫ��ͣ��������*/
	park->showInfo();

	Car car2("³B-45678", "����320");  // �����γ�����
	car2.enter(park);
	// car2����ͣ����������ͣ��λ����Ϊû�п���ͣ��λ�������޷�����

	bus.leave(park);  // bus�뿪ͣ����������ͣ����
	truck.leave(park);  // truck�뿪ͣ����������ͣ����

						/* ��ʾ��ǰͣ�ŵĳ����ĳ��ƺ��룬�Լ���ǰ��ȫ��ͣ��������*/
	park->showInfo();
	delete park;

	system("PAUSE");
	return 0;
}
