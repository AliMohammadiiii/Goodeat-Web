#include "Offers.hpp"
Offer::Offer(string _ingredient_name, int _price, int _count, int _packaging)
{
	ingredient_name = _ingredient_name;
	price = _price;
	count = _count;
	packaging = _packaging;
}
bool Offer::is_it_name(string name)
{
	return (ingredient_name == name);
}
void Offer::set_new_data(int _price, int _count)
{
	price = _price;
	count = _count;
}
int Offer::get_price()
{
	return price + packaging;
}
void Offer::sale()
{
	count--;
}
bool Offer::is_exist()
{
	if (count > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
string Offer::get_ingredient()
{
	return ingredient_name;
}