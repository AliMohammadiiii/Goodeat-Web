#ifndef OFFERS_HPP_
#define OFFERS_HPP_
#include "general.hpp"
const float DISCOUNT_PERCENT = 10 / 100;
class Offer
{
public:
	Offer(string _ingredient_name, int _price, int _count, int _packaging);
	~Offer();
	bool is_it_name(string name);
	void set_new_data(int _price, int _count);
	int get_price();
	void sale();
	bool is_exist();
	string get_ingredient();
private:
	string ingredient_name;
	int price;
	int count;
	int packaging;
};

#endif // !OFFERS_HPP_
