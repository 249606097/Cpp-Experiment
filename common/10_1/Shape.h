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

	protected:
		double Circumference = 0;
};


#endif