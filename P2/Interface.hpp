#ifndef interface_hpp_
#define interface_hpp_
#include "general.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Filter.hpp"
#include "Person.hpp"
#include "Offers.hpp"
#include "Ingeradiant.hpp"
class Command_Interface
{
public:
	Command_Interface();
	~Command_Interface();
	void work();
	Person* find_logged_in();
	bool login_check();
	void signup();
	void login();
	void logout();
	void recipes();
	string recipes_abstract_info();
	void recipe_info(int id);
	Recipes* find_recipes_by_id(int id);
	int create_recipe();
	vector <string> read_input(string input);
	void alphabet_sort_person();
	void alphabet_sort_recipes();
	void delete_recipe();
	void my_recipes();
	void rates();
	void chefs_info();
	void chef_abstract_info();
	void chef_info();
	Person* find_person_by_username(string username);
	void user_list();
	int create_shelves(string name, int id);
	string shelves_list(int limit, string username);
	void add_to_shelves(int shelf_id, Recipes* recipe);
	Shelves* find_shelve_by_id(int id);
	vector <Shelves*> find_shelves_by_username(string username);
	string show_recipes_of_shelve(int shelf_id);
	void delete_recipe_from_shelves(int shelf_id, int recipe_id);
	void shelves_function();
	void shelves_recipes();
	void check_input_number_correct(int number_input);
	void check_input_type_correct(string input_type);
	void check_access(string type_need);
	void clear_filter();
	void apply_tag_filter();
	void apply_time_filter();
	void apply_veg_filter();
	void apply_rate_filter();
	void filter();
	void signup_supplier();
	void function_offers();
	void post_offer();
	void put_offer();
	void delete_offer();
	void credits();
	void orders();
	offer_findes find_best_price(vector<offer_findes>& offers);
	void find_ingrediant(vector<string>& ingredient_need_list, int recipe_id, vector<offer_findes>& offers_need);
	void post_order();
	void sale_order(vector<offer_findes>& offers_need, int price);
	void get_order();
	void add_ingradient(string offer_name, int number);
	void reduce_ingradient(string offer_name, int number);
	bool is_there_a_discount(string ingredient);
private:
	vector <Filter*> filters;
	vector <Person*> list_person;
	Person* logged_in_person;
	vector <Recipes*> list_recipes;
	int last_id_of_recipe;
	vector <Shelves*> shelves;
	int last_id_of_shelf;
	vector <string> command_word;
	vector <Ingerediant*> ingrediants_list;
};

#endif // !interface_hpp_
#pragma once
