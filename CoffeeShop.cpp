#pragma warning(disable : 4996)

#include <exception>
#include "CoffeeShop.h"
#include "Customer.h"
#include "Employee.h"
#include "Shift.h"
#include "Product.h"
#include "Date.h"
#include "utils.h"

const int DEFAULT_ARRAY_SIZE = 20;

// ctor
CoffeeShop::CoffeeShop(const char* name, const Address& address) : name(nullptr), address(address)
{
	setName(name);

	this->numCustomers = 0;
	this->customersMaxSize = DEFAULT_ARRAY_SIZE;
	this->customers = new Customer*[customersMaxSize];

	this->numEmployees = 0;
	this->employeesMaxSize = DEFAULT_ARRAY_SIZE;
	this->employees = new Employee * [employeesMaxSize];

	this->numShifts = 0;
	this->shiftsMaxSize = DEFAULT_ARRAY_SIZE;
	this->shifts = new Shift * [shiftsMaxSize];

	this->numProducts = 0;
	this->productsMaxSize = DEFAULT_ARRAY_SIZE;
	this->products = new Product * [productsMaxSize];
}

CoffeeShop::CoffeeShop(const char* name, Address&& address) : name(nullptr), address(std::move(address))
{
	setName(name);

	this->numCustomers = 0;
	this->customersMaxSize = DEFAULT_ARRAY_SIZE;
	this->customers = new Customer * [customersMaxSize];

	this->numEmployees = 0;
	this->employeesMaxSize = DEFAULT_ARRAY_SIZE;
	this->employees = new Employee * [employeesMaxSize];

	this->numShifts = 0;
	this->shiftsMaxSize = DEFAULT_ARRAY_SIZE;
	this->shifts = new Shift * [shiftsMaxSize];

	this->numProducts = 0;
	this->productsMaxSize = DEFAULT_ARRAY_SIZE;
	this->products = new Product * [productsMaxSize];
}

CoffeeShop::CoffeeShop(CoffeeShop&& other) : name(std::move(other.name)), address(std::move(other.address)),
									customers(nullptr), employees(nullptr), shifts(nullptr), products(nullptr)
{
	numCustomers = other.numCustomers;
	customersMaxSize = other.customersMaxSize;
	std::swap(customers, other.customers);

	this->numEmployees = other.numEmployees;
	this->employeesMaxSize = other.employeesMaxSize;
	std::swap(employees, other.employees);

	this->numShifts = other.numShifts;
	this->shiftsMaxSize = other.shiftsMaxSize;
	std::swap(shifts, other.shifts);

	this->numProducts = other.numProducts;
	this->productsMaxSize = other.productsMaxSize;
	std::swap(products, other.products);
}

// dtor
CoffeeShop::~CoffeeShop()
{
	delete[] name;

	for (int i = 0; i < numCustomers; i++)
	{
		delete customers[i];
	}
	delete[]customers;

	for (int i = 0; i < numEmployees; i++)
	{
		delete employees[i];
	}
	delete[]employees;

	for (int i = 0; i < numProducts; i++)
	{
		delete products[i];
	}
	delete[]products;

	for (int i = 0; i < numShifts; i++)
	{
		delete shifts[i];
	}
	delete[]shifts;
}

// setters
void CoffeeShop::setName(const char* name)
{
	if (strlen(name) < 2)								//	if name is too short
		throw exception("Name is too short.");
	if (!isAlphaOnly(name))								//	if name contains non-alphabet characters
		throw exception("Name should contain characters only.");
	delete[] this->name;
	this->name = strdup(name);
}

// functions
bool  CoffeeShop::addNewEmployee(const Employee& employee)
{
	if (isEmployeeExists(employee))
		return false;
	if (numEmployees == employeesMaxSize)	//	if the array full -> increase it
	{
		employeesMaxSize *= 2;
		Employee** tempArr = new Employee * [employeesMaxSize];
		memcpy(tempArr,employees, numEmployees * sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
	}
	employees[numEmployees++] = new Employee(employee);		//	copy employee
	return true;
}

bool  CoffeeShop::addNewEmployee(Employee&& employee)
{
	if (isEmployeeExists(employee))
		return false;
	if (numEmployees == employeesMaxSize)	//	if the array full -> increase it
	{
		employeesMaxSize *= 2;
		Employee** tempArr = new Employee * [employeesMaxSize];
		memcpy(tempArr,employees, numEmployees * sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
	}
	employees[numEmployees++] = new Employee(std::move(employee));		//	move employee
	return true;
}

bool  CoffeeShop::addNewProduct(const Product& product)
{
	if (isProductExists(product))
		return false;
	if (numProducts == productsMaxSize)	//	if the array full -> increase it
	{
		productsMaxSize *= 2;
		Product** tempArr = new Product * [productsMaxSize];
		memcpy(tempArr, products, numProducts * sizeof(Product*));
		std::swap(tempArr, products);
		delete[] tempArr;
	}
	products[numProducts++] = product.clone();			//	copy product
	return true;
}

bool  CoffeeShop::addNewCustomer(const Customer& customer)
{
	if (isCustomerExists(customer))
		return false;
	if (numCustomers == customersMaxSize)	//	if the array full -> increase it
	{
		customersMaxSize *= 2;
		Customer** tempArr = new Customer * [customersMaxSize];
		memcpy(tempArr, customers, numCustomers * sizeof(Customer*));
		std::swap(tempArr, customers);
		delete[] tempArr;
	}
	customers[numCustomers++] = new Customer(customer);		//	copy customer
	return true;
}

bool  CoffeeShop::addNewCustomer(Customer&& customer)
{
	if (isCustomerExists(customer))
		return false;
	if (numCustomers == customersMaxSize)	//	if the array full -> increase it
	{
		customersMaxSize *= 2;
		Customer** tempArr = new Customer * [customersMaxSize];
		memcpy(tempArr, customers, numCustomers * sizeof(Customer*));
		std::swap(tempArr, customers);
		delete[] tempArr;
	}
	customers[numCustomers++] = new Customer(std::move(customer));		//	move customer
	return true;
}

bool  CoffeeShop::openShift(double clubDiscountPercent, const Date& date)
{
	if (isShiftExists(date))
		return false;		//	false -> shift already exists with this date

	if (numShifts == shiftsMaxSize)	//	if the array full -> increase it
	{
		shiftsMaxSize *= 2;
		Shift** tempArr = new Shift * [shiftsMaxSize];
		memcpy(tempArr, shifts, numShifts * sizeof(Shift*));
		std::swap(tempArr, shifts);
		delete[] tempArr;
	}
	shifts[numShifts++] = new Shift(clubDiscountPercent, date);		//	create new shift
	return true;
}

Shift* CoffeeShop::getShiftByDate(const Date& date) const
{
	for (int i = 0; i < numShifts; i++)
	{
		const Date* currDate = shifts[i]->getShiftDate();		//	get current shift's date
		if (date == *currDate)									//	if equals to the desire date
			return shifts[i];									//	return current shift
	}
	return nullptr;		//	shift with this date does not exists
}

bool CoffeeShop::isEmployeeExists(const Person& employee) const
{
	for (int i = 0; i < numEmployees; i++)
	{
		if (employee == *employees[i])		//	if current employee equals to the desired one
			return true;
	}
	return false;
}

bool CoffeeShop::isCustomerExists(const Person& employee) const
{
	for (int i = 0; i < numCustomers; i++)
	{
		if (employee == *customers[i])			//	if current customer equals to the desired one
			return true;
	}
	return false;
}

bool CoffeeShop::isProductExists(const Product& product) const
{
	for (int i = 0; i < numProducts; i++)
	{
		if (product == *products[i])			//	if current product equals to the desired one
			return true;
	}
	return false;
}

bool CoffeeShop::isShiftExists(const Date& date) const
{
	for (int i = 0; i < numShifts; i++)
	{
		if (date == *shifts[i]->getShiftDate())			//	if the shift's date equals to the date asked for
			return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop)
{
	cout << "Name: " << coffeeShop.getName() << ", Address: " << *coffeeShop.getAddress() << endl;
	cout << endl << "Employees:" << endl;
	if (coffeeShop.numEmployees == 0)
		cout << "No employess." << endl;
	for (int i = 0; i < coffeeShop.numEmployees; i++)
	{
		cout << "\t" << *coffeeShop.employees[i] << endl;
	}

	cout << endl << "Products:" << endl;
	if (coffeeShop.numProducts == 0)
		cout << "No products." << endl;
	for (int i = 0; i < coffeeShop.numProducts; i++)
	{
		cout << "\t" << *coffeeShop.products[i] << endl;
	}

	cout << endl << "Customers:" << endl;
	if (coffeeShop.numCustomers == 0)
		cout << "No customers." << endl;
	for (int i = 0; i < coffeeShop.numCustomers; i++)
	{
		cout << "\t" << *coffeeShop.customers[i] << endl;
	}

	cout << endl << "Shifts:" << endl;
	if (coffeeShop.numShifts == 0)
		cout << "No shifts." << endl;
	for (int i = 0; i < coffeeShop.numShifts; i++)
	{
		cout << "\t" << *coffeeShop.shifts[i] << endl;
	}

	return os;
}