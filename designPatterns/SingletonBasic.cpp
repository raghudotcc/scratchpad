#include <iostream>

using namespace std;

class Singleton{
	int a = 2;
	static Singleton *instance;
	Singleton()
	{  
		cout << "Created Singleton object" << endl;
	}
public:
	static Singleton* getInstance()
	{
		if(instance == NULL)
			instance =  new Singleton;
		return instance;
	}

	int getInt(){
		return a;
	}
	void setInt(int a) {
		this->a = a;
	}

};

Singleton *Singleton::instance = NULL;
int main()
{
	Singleton *singleton1 = Singleton::getInstance();
	int a = singleton1->getInt();
	a += 1;
	singleton1->setInt(a);
	cout << singleton1->getInt() << endl;

	Singleton *singleton2 = Singleton::getInstance();
	a = singleton2->getInt();
	a += 5;
	singleton2->setInt(a);
	cout << singleton2->getInt() << endl;

	return 0;
}