// runtime_error.cpp
// compile with: /EHsc /GR
#include <iostream>
#include <typeinfo>
#include <string>
#include "table.h"

using namespace std;

class PositiveNumber
{
	int positiveNumber;
public:
	PositiveNumber(int num) :positiveNumber(num)
	{
		if (num < 0)
			throw exception("negative number");
	}
};
int main()
{
	int count = 0;
	////string a = "1";
	//int a = -1;
	//auto& ti1 = typeid(a);
	//cout << ti1.name() << endl;
	//// runtime_error
	//try
	//{
	//	PositiveNumber n(a);
	//}
	//catch (exception &e)
	//{
	//	cerr << "Caught " << e.what() << endl;
	//	cerr << "Type " << typeid(e).name() << endl;
	//};

	//cout << endl;

	Table<int, int> test(10);
	test.Add(5, 5);
	SortTable<int, int> stest(10);

	try
	{
		Table<int, int> t(test);
	}
	catch (const std::exception &e)
	{
		cerr << "Caught " << e.what() << endl;
		cerr << "Type " << typeid(e).name() << endl;
		count++;
	}

	try
	{
		test.Add(10, 10);
	}
	catch (const std::exception &e)
	{
		cerr << "Caught " << e.what() << endl;
		cerr << "Type " << typeid(e).name() << endl;
		count++;
	}

	try
	{
		test.Find(4);
	}
	catch (const std::exception &e)
	{
		cerr << "Caught " << e.what() << endl;
		cerr << "Type " << typeid(e).name() << endl;
		count++;
	}

	try
	{
		test.Find(5);
	}
	catch (const std::exception &e)
	{
		cerr << "Caught " << e.what() << endl;
		cerr << "Type " << typeid(e).name() << endl;
		count++;
	}

	try
	{
		SortTable<int, int> t1(stest);
	}
	catch (const std::exception &e)
	{
		cerr << "Caught " << e.what() << endl;
		cerr << "Type " << typeid(e).name() << endl;
		count++;
	}

	if (count == 0)
		cerr << "No exception found\n";
	else
		cerr << "Found " << count << " exceptions\n\n";
	cout << "-------------------------------------\n\n";


	srand(time(0));
	Table<int, int> t1(5000);
	Table<int, int> t2(5);
	t2.Add(40, 1);
	t2.Add(2, 50);
	t2.Add(300, 6);
	t2.Add(1, 200);
	t2.Add(5, 7000);

	for (int i = t1.getSize(); i > 0; i--)
		t1.Add(i, 1 + rand() % 100);
	cout << "Select 2 different sorts.\n\n";
	SortTable<int, int> st1(t1);
	cout << endl;
	SortTable<int, int> st2(t1);
	cout << "\n\n";
	cout << "-------------------------------------\n\n";
	cout << "Example of output\n\n";
	SortTable<int, int> st3(t2);
	cout << "Usual table:\n";
	t2.print();
	cout << "Sorted table:\n";
	st3.print();

	system("pause");
}
/* Output:
Caught bad locale name
Type class std::runtime_error
*/