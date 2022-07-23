#ifndef person_hpp_
#define person_hpp_
#include "general.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
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
protected:
	string username;
	string password;
	vector <Recipes*> recipes;
	string type;
	bool is_it_login;
};
class User : public Person
{
public:
	User(string input_username, string input_password, string input_type);
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
