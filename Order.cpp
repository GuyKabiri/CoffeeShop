#pragma warning(disable : 4996)

#include "Order.h"
#include "Product.h"
#include "Employee.h"
#include "Customer.h"
#include "utils.h"

const int DEFAULT_ARRAY_SIZE = 20;

Order::Order(const Employee& employee, const Customer& customer) : employee(employee), customer(customer)
{
	this->numItems = 0;
	this->itemsMaxSize = DEFAULT_ARRAY_SIZE;
	this->items = new Product * [itemsMaxSize];
}

Order::Order(const Order& other) : employee(other.employee), customer(other.customer)
{
	*this = other;
}

Order::~Order()
{
	for (int i = 0; i < numItems; i++)
	{
		delete items[i];
	}
	delete[] items;
}

const Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{		
		for (int i = 0; i < numItems; i++)
		{
			delete items[i];
		}
		delete[] items;

		numItems = 0;
		itemsMaxSize = other.itemsMaxSize;
		items = new Product * [itemsMaxSize];

		for (int i = 0; i < other.numItems; i++)	//	iterate over the other order array and copy it's items
		{
			*this += other[i];
		}
	}
	return *this;
}

//	add an item to the order
Order& Order::operator+=(const Product& product)
{
	addItem(product);
	return *this;
}

bool Order::addItem(const Product& product)
{
	if (numItems == itemsMaxSize)			//	if the array is full -> double it's size
	{
		itemsMaxSize *= 2;
		Product** tempArr = new Product * [itemsMaxSize];
		memcpy(tempArr, items, numItems * sizeof(Product*));
		std::swap(tempArr, items);
		delete[] tempArr;
	}
	items[numItems++] = product.clone();	//	copy the product into the array
	return true;
}

int Order::getTotalCalories() const
{
	int totalCalories = 0;
	for (int i = 0; i < numItems; i++)				//	iterate over all the products and sum up the calories
		totalCalories += items[i]->getCalories();

	return totalCalories;
}

double Order::getOrderProfit() const
{
	double sumProfit = 0;
	for (int i = 0; i < numItems; i++)				//	iterate over all the products and calculate the profit of each
		sumProfit += (items[i]->getPrice() - items[i]->getCost());

	return sumProfit;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << "Employee: " << order.getEmployee().getName()
		<< ", Customer: " << order.getCustomer().getName()
		<< ", Number of products: " << order.getNumItems()
		<< ", Profit: " << order.getOrderProfit();
	return os;
}