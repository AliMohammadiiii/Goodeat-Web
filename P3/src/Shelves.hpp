#ifndef shelves_hpp_
#define shelves_hpp_
#include "general.hpp"
#include "Recipes.hpp"
class Shelves
{
public:
	Shelves(string _name, int _id, string _username);
	~Shelves();
	void add_recipe(Recipes* recipe);
	string get_name();
	string abstract_info();
	bool is_it_my_id(int _id);
	bool is_it_my_username(string _username);
	string recipes_list();
	void alphabet_sort_recipes();
	void delete_recipe(int recipe_id);
	int find_stage_recipe(int recipe_id);
	int get_id();
	vector < Recipes* > get_recipe();
private:
	string name;
	string username;
	int id;
	vector < Recipes* > recipes;
};

#endif // !shelves_hpp_
