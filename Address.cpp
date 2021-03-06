#pragma warning(disable : 4996)

#include <exception>
#include "Address.h"
#include "utils.h"

Address::Address(const char* city, const char* streetName, int streetNumber) 
{
	setCity(city);
	setStreetName(streetName);
	setStreetNumber(streetNumber);
}

// copy ctor
Address::Address(const Address& other)
{
	*this = other;
}

// move ctor
Address::Address(Address&& other) : city(nullptr), streetName(nullptr)
{
	*this = std::move(other);
}

void Address::setCity(const char* city)
{
	if (strlen(city) < 2)						//	if the city name is too short
		throw exception("City is too short.");
	if (!isAlphaOnly(city))						//	if the city name contains non-alphaber characters
		throw exception("City must be characters only.");

	delete[] this->city;
	this->city = strdup(city);
}

void Address::setStreetName(const char* street)
{
	if (strlen(street) < 2)						//	if the street name is too short
		throw exception("Street name is too short.");
	if (!isAlphaOnly(street))					//	if the street name contains non-alphaber characters
		throw exception("Street name must be characters only.");

	delete[] this->streetName;
	this->streetName = strdup(street);
}

void Address::setStreetNumber(int num)
{
	if (num <= 0)								// street number must be greater than zero
		throw exception("Street Number");
	this->streetNumber = num;
}

// assignment operator
const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		delete[] city;
		delete[] streetName;
		city = strdup(other.city);
		streetName = strdup(other.streetName);
		streetNumber = other.streetNumber;
	}
	return *this;
}

// move assignment operator
const Address& Address::operator=(Address&& other)
{
	if (this != &other)
	{
		std::swap(this->city, other.city);
		std::swap(this->streetName, other.streetName);
		streetNumber = other.streetNumber;
	}
	return *this;
}

// dtor
Address::~Address()
{
	delete[] city;
	delete[] streetName;
}

// functions
ostream& operator<<(ostream& os, const Address& address)
{
	os << address.streetName << " " << address.streetNumber << ", " << address.city;
	return os;
}