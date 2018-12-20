/*
Kyle Nida
Z#: 23410025
Unit 11 Programming assignment
Due Date:8/01/17
Professor: Dr. Bullard
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_screen, call_class & Org); //prints all the elements in the 
																			//list to the screen.
private:
	int count = 0;
	int size = 5;
	call_record *call_DB;
};

//driver to test the functionality of your class.
int main()
{
	string key;
	char answer;
	int check;

	call_class MyClass;

	ofstream out_stream;

	cout << "Would you like to search for an entry?(y or n): ";
	cin >> answer;
	cout << endl;

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Enter 10 digit cell number to be searched: ";
		cin >> key;
		check = MyClass.search(key);
		cout << endl;
	}

	cout << "Would you like to add a new entry?(y or n): ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		MyClass.add();
	}

	cout << endl;
	cout << "Would you like to remove an entry?(y or n): ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Enter 10 digit cell number to be removed: ";
		cin >> key;
		//cout << key << endl;
		MyClass - key;
	}

	MyClass.process();
	out_stream << MyClass;

	return 0;
}


/************************************************************************************************************************************/
//Name: default constructor
//Precondition: The dynamic array call_DB(call_record) has been created and count(int) and size(int) are both intialized.
//Postcondition: The dynamic array call_DB(call_record) will receive the input from the file "callstats_data.txt" and initialize the class call_record. 
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	ifstream in;
	in.open("callstats_data.txt");
	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}
	call_DB = new call_record[size];
	while (!in.eof())
	{
		if (is_full())
			double_size();
		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;
		count++;
	}
	in.close();


}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: Count(int) has been declared.
//Postcondition: Returns a 1 if empty, -1 otherwise.
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: Count(int) and size(int) has been declared.
//Postcondition: Returns 1 if full, -1 otherwise.
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: Call_DB(call_record) and count(int) has been initialized and key(string) holds a value.
//Postcondition: Returns the value of i(int) if found or -1 if not.
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	int i;

	for(i=0;i<=size;i++)
	{
		if (call_DB[i].cell_number == key)
		{
			cout << i << endl;
			return i;
		}
		else
			return -1;
	}
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: Call_DB(call_record), count(int), size(int), and key(string) has been initialized.
//Postcondition: If user wishes, call_DB(call_record) gets a new entry and count(int) is increased.
//Decription: adds the informaton for a call record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add()
{
	char answer;
	do
	{
		cout << "Enter the first name: ";
		cin >> call_DB[count].firstname;
		cout << endl;

		cout << "Enter the last name: ";
		cin >> call_DB[count].lastname;
		cout << endl;

		cout << "Enter the 10 digit cell number: ";
		cin >> call_DB[count].cell_number;
		cout << endl;

		cout << "Enter the number of relays: ";
		cin >> call_DB[count].relays;
		cout << endl;

		cout << "Enter the call length(in minutes): ";
		cin >> call_DB[count].call_length;
		cout << endl;

		cout << "Will you add an additional record?(y or n): ";
		cin >> answer;

		count++;

		if (is_full())
		{
			double_size();
		}

	} while (answer == 'Y' || answer == 'y');
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: Call_DB(call_record), count(int), and key(string) has been initialized.
//Postcondition: An array from call_DB(call_record) will be deleted.
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int i;

	for (i = 0; i <= size; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			call_DB[i].firstname = { "_____" };
			call_DB[i].lastname = { "_____" };
			call_DB[i].cell_number = { "__________" };
			call_DB[i].relays = 0;
			call_DB[i].call_length = 0;
			call_DB[i].net_cost = 0.00;
			call_DB[i].tax_rate = 0.00;
			call_DB[i].call_tax = 0.00;
			call_DB[i].total_cost = 0.00;

		}
	}

	return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: Count(int) is equal to size(int)
//Postcondition: Call_DB(call_record) array has double the size.
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: The values are stored into the struct for cell_number(call_record), relays(call_record), and call_length(call_record).
//Postcondition: The variables net_cost(call_record), tax_rate(call_record), call_tax(call_record), and total_cost(call_record) will be calculated.
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	int i;
	for (i = 0; i < count; i++)
	{
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = .01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = .03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = .05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = .08;
		}
		else
		{
			call_DB[i].tax_rate = .12;
		}
		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;

	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: The values are stored into the class for cell_number(call_record), relays(call_record), and call_length(call_record)
//				and the Process function has been called.
//Postcondition: prints every field of every call_record in call_DB formatted to the screen.
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen.
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	int i;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);
	cout.setf(ios::right);

	for (i = 0; i<Org.count; i++)
	{
		cout << Org.call_DB[i].firstname << setw(6);
		cout << "\t" << Org.call_DB[i].lastname << setw(6);
		cout << "\t" << Org.call_DB[i].cell_number << setw(7);
		cout << Org.call_DB[i].relays << setw(7);
		cout << Org.call_DB[i].call_length << setw(7);
		cout << Org.call_DB[i].net_cost << setw(7);
		cout << Org.call_DB[i].tax_rate << setw(7);
		cout << Org.call_DB[i].call_tax << setw(8);
		cout << Org.call_DB[i].total_cost << endl;
	}



	return out;  //must have this statement
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: The program is done running and the dynamic array is no longer needed.
//Postcondition: Call_DB(call_record) will be deleted.
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	if (call_DB)
	{
		delete[] call_DB;
	}
}






