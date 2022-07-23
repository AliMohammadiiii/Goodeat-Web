#ifndef ORDER_HPP_
#define ORDER_HPP_
#include "Offers.hpp"
#include "general.hpp"

class Order
{
public:
	Order(vector<order_line> offers_need, int _price, int _recipe_id);
	string info();
	int get_recipe_id();
private:
	vector<order_line> orders_lines;
	int price;
	int recipe_id;
};


#endif // !ORDER_HPP_
