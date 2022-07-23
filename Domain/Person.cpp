#include "Person.hpp"
Person::Person(string input_username, string input_password, string input_type)
{
	username = input_username;
	password = input_password;
	type = input_type;
	is_it_login = true;
}
Person::~Person()
{

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
Chef::Chef(string input_username, string input_password, string input_type) : Person(input_username, input_password, input_type)
{
	rates = 0;
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
