#ifndef WEB_INTERFACE_HPP_
#define WEB_INTERFACE_HPP_
#include "general.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Filter.hpp"
#include "Person.hpp"
using namespace std;
class Web_interface
{
private:
	static vector <Filter*> filters;
	static vector <Person*> list_person;
	static Person* logged_in_person;
	static vector <Recipes*> list_recipes;
	static int last_id_of_recipe;
	static vector <Shelves*> shelves;
	static int last_id_of_shelf;
public:
	static string state_filter;
	static int get_size_list();
	static int signup(string username, string password, string type);
	static int login(string username, string password);
	static Person* find_person_by_uid(int uid);
	static Recipes* find_recipe_by_rid(int rid);
	static void create_Recipe(string title, string ingredients, string vegetarian, string minutes_to_ready, string tags, string Image, Person* creator);
	static void delete_recipe(int rid, Person* creator);
	static void logout();
	static void clear_filter();
	static vector <Shelves*> find_shelves_by_username(string username);
	static vector <Recipes*> get_recipes();
	static void create_shelves(string name, string creator_name);
	static Shelves* find_shelf_by_id(int sid);
	static void apply_time_filter(int min_time, int max_time);
	static void apply_veg_filter(string state);
	static void apply_rate_filter(float min, float max);
};
#endif