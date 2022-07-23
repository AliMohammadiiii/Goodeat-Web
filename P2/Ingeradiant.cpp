#include "Ingeradiant.hpp"
Ingerediant::Ingerediant(string _name, int _number_of_offer)
{
	name = _name;
	number_of_offer = _number_of_offer;
}
void Ingerediant::plus_number(int number)
{
	number_of_offer += number;
}
void Ingerediant::reduce_number(int number)
{
	number_of_offer += number;
}
bool Ingerediant::is_it_my_name(string _name)
{
	return name == _name;
}
bool Ingerediant::is_it_in_discount()
{
	if (number_of_offer >= DESCOUNT_NUMBER)
	{
		return true;
	}
	else
	{
		return false;
	}
}
