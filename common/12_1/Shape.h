#ifndef SHA
#define SHA

class Shape
{
	public:
		Shape();
		virtual double getCircumference();
		void printCircumference();
		bool operator>(Shape &one);
		virtual void print_self();

		void set_price(double price);
		double get_price();
		int get_classId();

	protected:
		double Circumference = 0;
		int classId;
		double price;
};


#endif