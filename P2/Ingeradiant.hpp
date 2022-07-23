#ifndef _INGERADIANT_HPP
#define _INGERADIANT_HPP
#include "general.hpp"
const int DESCOUNT_NUMBER = 20;
class Ingerediant
{
public:
	Ingerediant(string _name, int _number_of_offer);
	void plus_number(int number);
	void reduce_number(int number);
	bool is_it_my_name(string _name);
	bool is_it_in_discount();
private:
	string name;
	int number_of_offer;
};
#endif // !_INGERADIANT_HPP
