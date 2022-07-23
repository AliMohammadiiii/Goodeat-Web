#ifndef person_hpp_
#define person_hpp_
#include "general.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Offers.hpp"
#include "Order.hpp"
class Person
{
public:
	Person(string input_username, string input_password, string input_type);
	~Person();
	bool am_i_log_in();
	void logged_out();
	void logged_in();
	bool is_it_my_username(string input_username);
	bool can_i_log_in(string input_username, string  input_password);
	bool is_it_my_job(string input_type);
	void add_recipe(Recipes* recipe);
	string get_name();
	int get_credits();
protected:
	string username;
	string password;
	string type;
	bool is_it_login;
	vector <Recipes*> recipes;
	int credits;
};
class Supplier : public Person
{
public:
	Supplier(string _name, string _email, string _password);
	void create_offer(string _ingredient_name, int _price, int _count, int _packaging);
	void edit_offer(string _ingredient_name, int _price, int _count);
	int delete_offer(string _ingredient_name);
	bool is_it_my_email(string _email);
	virtual bool can_i_log_in(string input_username, string  input_password);
	bool am_i_have_ingrediant(string _ingredient_name);
	Offer* get_offer(string _ingredient_name);
	void increase_credit(int money);
	bool am_i_have_this_offer(Offer* offer);
private:
	string email;
	vector < Offer* > offers;
};
struct offer_find
{
	Supplier* supplier;
	Offer* offer;
}; typedef struct offer_find offer_findes;
class User : public Person
{
public:
	User(string input_username, string input_password, string input_type);
	void increase_credits(int increase);
	bool can_i_pay(int money);
	void pay(int money);
	string order_creator(vector<offer_findes> offer_needed, int price, int recipe_id);
	string print_order_list();
private:
	vector <Order*> orders;
};
class Chef : public Person
{
public:
	Chef(string input_username, string input_password, string input_type);
	void delete_recipe(int recipe_id);
	void show_my_recipe();
	string abstract_info();
	string info();
	void update_rate();
private:
	void rate_update();
	string collect_recipes_info();
	float rates;
};

#endif // !person_hpp_
	