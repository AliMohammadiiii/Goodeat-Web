#include "Order.hpp"
Order::Order(vector<order_line> offers_need, int _price, int _recipe_id)
{
	price = _price;
	orders_lines = offers_need;
	recipe_id = _recipe_id;
}
string Order::info()
{
	string information;
	for (int orderline_cursur = 0; orderline_cursur < orders_lines.size(); orderline_cursur++)
	{
		information += orders_lines[orderline_cursur].supplier + ' ';
		for (int ingeradiant_cursur = 0; ingeradiant_cursur < orders_lines[orderline_cursur].ingradients.size()-1; ingeradiant_cursur++)
		{
			information += orders_lines[orderline_cursur].ingradients[ingeradiant_cursur] + ' ';
		}
		information += orders_lines[orderline_cursur].ingradients[orders_lines[orderline_cursur].ingradients.size()-1] + '\n';
	}
	information += to_string(price);
	return information;
}
int Order::get_recipe_id()
{
	return recipe_id;
}