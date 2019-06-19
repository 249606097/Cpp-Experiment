#ifndef FIL
#define FIL

#include <string>

using namespace std;

class FileNotFoundException
{
public:
	FileNotFoundException(const string &message) : message(message) {}
	~FileNotFoundException() {}
	const string &getMessage() { return message; }
private:
	string message;
};


#endif 
