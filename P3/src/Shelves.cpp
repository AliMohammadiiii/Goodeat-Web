#include "Shelves.hpp"
Shelves::Shelves(string _name, int _id, string _username)
{
	id = _id;
	name = _name;
	username = _username;
}
Shelves::~Shelves()
{
	for (int recipe_cursur = 0; recipe_cursur < recipes.size(); recipe_cursur++)
	{
		delete recipes[recipe_cursur];
	}
}
bool Shelves::is_it_my_id(int _id)
{
	return id == _id;
}
int Shelves::get_id()
{
	return id;
}
string Shelves::get_name()
{
	return name;
}
vector < Recipes* > Shelves::get_recipe()
{
	return recipes;
}

string Shelves::abstract_info()
{
	string info;
	info += to_string(id);
	info += " ";
	info += name;
	info += '\n';
	return info;
}
string Shelves::recipes_list()
{
	string list;
	if (recipes.size() == 0)
	{
		throw runtime_error(EMPTY);
	}
	for (unsigned int recipe_counter = 0; recipe_counter < recipes.size(); recipe_counter++)
	{
		list += recipes[recipe_counter]->abstract_info();
		list += '\n';
	}
	return list;
}
void Shelves::add_recipe(Recipes* recipe)
{
	recipes.push_back(recipe);
	alphabet_sort_recipes();
}
void Shelves::alphabet_sort_recipes()
{
	for (unsigned int i = 0; i < recipes.size(); i++)
	{
		for (unsigned int j = 0; j < recipes.size() - 1; j++)
		{
			if (recipes[j]->get_name() > recipes[j + 1]->get_name())
			{
				Recipes* temp_recipe = recipes[j];
				recipes[j] = recipes[j + 1];
				recipes[j + 1] = temp_recipe;
			}
		}
	}
}
bool Shelves::is_it_my_username(string _username)
{
	return username == _username;
}
int Shelves::find_stage_recipe(int recipe_id)
{
	for (unsigned int recipe_cursur = 0; recipe_cursur < recipes.size(); recipe_cursur++)
	{
		if (recipes[recipe_cursur]->is_it_my_id(recipe_id))
		{
			return recipe_cursur;
		}
	}
	throw runtime_error(BAD_REQUEST);
}
void Shelves::delete_recipe(int recipe_id)
{
	int stage_recipe = find_stage_recipe(recipe_id);
	recipes.erase(recipes.begin() + stage_recipe);
}
