#include "Person.hpp"
Person::Person(string input_username, string input_password, string input_type)
{
	username = input_username;
	password = input_password;
	type = input_type;
	is_it_login = true;
	credits = 0;
}
Person::~Person()
{

}
int Person::get_credits()
{
	return credits;
}
string Person::get_name()
{
	return username;
}
void Person::add_recipe(Recipes* recipe)
{
	recipes.push_back(recipe);
}
void Person::logged_out()
{
	is_it_login = false;
}
void Person::logged_in()
{
	is_it_login = true;
}
bool Person::can_i_log_in(string input_username, string input_password)
{
	return (username == input_username && password == input_password);
}
bool Person::is_it_my_username(string input_username)
{
	return (username == input_username);
}
bool Person::is_it_my_job(string input_type)
{
	return (type == input_type);
}
bool Person::am_i_log_in()
{
	return is_it_login;
}
User::User(string input_username, string input_password, string input_type) : Person(input_username, input_password, input_type) {}
bool User::can_i_pay(int money)
{
	return (money <= credits);
}
void User::pay(int money)
{
	credits -= money;
}
string User::print_order_list()
{
	string information;
	for (int order_cursur = 0; order_cursur < orders.size(); order_cursur++)
	{
		information += "====order_" + to_string(order_cursur + 1) + "====\n";
		information += to_string(orders[order_cursur]->get_recipe_id()) + '\n';
		information += orders[order_cursur]->info() + '\n';
	}
	return information;
}

order_line add_orderline(Supplier* _supplier, vector <Offer*> offers)
{
	string name = _supplier->get_name();
	vector <string> ingradient_names;
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		ingradient_names.push_back(offers[offer_cursur]->get_ingredient());
	}
	order_line new_orderline;
	new_orderline.supplier = name;
	new_orderline.ingradients = ingradient_names;
	return new_orderline;
}
vector<Supplier*> remove_supplier_duplicates(vector<offer_findes> offers_need)
{
	vector<Supplier*> suppliers;
	for (int offer_cursur = 0; offer_cursur < offers_need.size(); offer_cursur++)
	{
		bool can_i_add = true;
		for (int supplier_cursur = 0; supplier_cursur < suppliers.size(); supplier_cursur++)
		{
			if (offers_need[offer_cursur].supplier == suppliers[supplier_cursur])
			{
				can_i_add = false;
				break;
			}
		}
		if (can_i_add)
		{
			suppliers.push_back(offers_need[offer_cursur].supplier);
		}
	}
	return suppliers;
}
vector <order_line> create_order_lines(vector<offer_findes> offers_need)
{
	vector <order_line> orderlines;
	vector<Supplier*> suppliers = remove_supplier_duplicates(offers_need);
	for (int supplier_cursur = 0; supplier_cursur < suppliers.size(); supplier_cursur++)
	{
		vector< Offer*> offer_list;
		for (int offer_cursur = 0; offer_cursur < offers_need.size(); offer_cursur++)
		{
			Offer* offer_temp = offers_need[offer_cursur].offer;
			if (suppliers[supplier_cursur]->am_i_have_this_offer(offer_temp))
			{
				offer_list.push_back(offer_temp);
			}
		}
		orderlines.push_back(add_orderline(suppliers[supplier_cursur], offer_list));
	}
	return orderlines;
}
Chef::Chef(string input_username, string input_password, string input_type) : Person(input_username, input_password, input_type)
{
	rates = 0;
}
void User::increase_credits(int increase)
{
	credits += increase;
}
string Chef::info()
{
	int number_recipes = recipes.size();
	rate_update();
	string info;
	info += username + '\n';
	string str_rates = to_string(ceil(rates * 10) / 10);
	str_rates = str_rates.substr(0, 3);
	info += str_rates + "\nrecipes:\n";
	for (int recipe_counter = 0; recipe_counter < number_recipes; recipe_counter++)
	{
		info += recipes[recipe_counter]->abstract_info() + ' ' + recipes[recipe_counter]->get_rate_str();
	}
	return info;
}
void Chef::update_rate()
{
	float sum = 0;
	float number_recipes = recipes.size();
	for (int recipe_counter = 0; recipe_counter < number_recipes; recipe_counter++)
	{
		sum += recipes[recipe_counter]->get_rate();
	}
	rates = sum / number_recipes;
}
void Chef::delete_recipe(int recipe_id)
{
	for (unsigned int recipe_counter = 0; recipe_counter < recipes.size(); recipe_counter++)
	{
		if (recipes[recipe_counter]->is_it_my_id(recipe_id))
		{
			recipes.erase(recipes.begin() + recipe_counter);
			return;
		}
	}
	throw runtime_error(PERMISION_DENIED);
}
string Chef::collect_recipes_info()
{
	string info;
	for (unsigned int recipe_counter = 0; recipe_counter < recipes.size(); recipe_counter++)
	{
		info += recipes[recipe_counter]->info() + '\n';
	}
	return info;
}
void Chef::show_my_recipe()
{
	if (recipes.size() == 0)
	{
		throw runtime_error(EMPTY);
	}
	else
	{
		cout << collect_recipes_info();
	}
}
void Chef::rate_update()
{
	float sum = 0;
	int number_of_rate = 0;
	for (unsigned int rate_counter = 0; rate_counter < recipes.size(); rate_counter++)
	{
		if (recipes[rate_counter]->has_been_rated())
		{
			number_of_rate++;
		}
		sum += recipes[rate_counter]->get_rate();
	}
	rates = sum / number_of_rate;
}
string Chef::abstract_info()
{
	rate_update();
	string info;
	string str_rates = to_string(ceil(rates * 10) / 10);
	str_rates = str_rates.substr(0, 3);
	info = username + " " + str_rates + '\n';
	return info;
}
Supplier::Supplier(string _name, string _email, string _password)
	:Person(_name, _password, SUPPLIER)
{
	email = _email;
}
bool Supplier::is_it_my_email(string _email)
{
	return (email == _email);
}
bool Supplier::can_i_log_in(string input_username, string  input_password)
{
	return (email == input_username && password == input_password);
}
void Supplier::create_offer(string _ingredient_name, int _price, int _count, int _packaging)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur]->is_it_name(_ingredient_name))
		{
			throw runtime_error(BAD_REQUEST);
		}
	}
	Offer* offer = new Offer(_ingredient_name, _price, _count, _packaging);
	offers.push_back(offer);
}
void Supplier::edit_offer(string _ingredient_name, int _price, int _count)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur]->is_it_name(_ingredient_name))
		{
			offers[offer_cursur]->set_new_data(_price, _count);
			return;
		}
	}
	throw runtime_error(BAD_REQUEST);
}
int Supplier::delete_offer(string _ingredient_name)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur]->is_it_name(_ingredient_name))
		{
			int price = offers[offer_cursur]->get_price();
			offers.erase(offers.begin() + offer_cursur);
			return price;
		}
	}
	throw runtime_error(BAD_REQUEST);
	return -1;
}
bool Supplier::am_i_have_ingrediant(string _ingredient_name)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur]->is_it_name(_ingredient_name) && offers[offer_cursur]->is_exist())
		{
			return true;
		}
	}
	return false;
}
Offer* Supplier::get_offer(string _ingredient_name)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur]->is_it_name(_ingredient_name))
		{
			return offers[offer_cursur];
		}
	}
	return NULL;
}
void Supplier::increase_credit(int money)
{
	credits += money;
}
bool Supplier::am_i_have_this_offer(Offer* offer)
{
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offers[offer_cursur] == offer)
		{
			return true;
		}
	}
	return false;
}
string User::order_creator(vector<offer_findes> offer_needed, int price, int recipe_id)
{
	vector <order_line> new_orderlines = create_order_lines(offer_needed);
	Order* new_order = new Order(new_orderlines, price, recipe_id);
	orders.push_back(new_order);
	return new_order->info();
}
