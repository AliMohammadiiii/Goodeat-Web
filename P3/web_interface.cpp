#include "web_interface.hpp"
void Web_interface::apply_time_filter(int min_time, int max_time)
{
	if (max_time < min_time || min_time < 0)
	{
		throw runtime_error(BAD_REQUEST);
	}
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_time(min_time, max_time);
	}
}
void Web_interface::apply_veg_filter(string state)
{
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		if (state == "Yes")
		{
			filters[filter_cursur]->add_filter_vegetarian(true);
		}
		else if (state == "No")
		{
			filters[filter_cursur]->add_filter_vegetarian(false);
		}
	}
}
void Web_interface::apply_rate_filter(float min, float max)
{
	if (max < min || max > 5 || min < 0)
	{
		throw runtime_error(BAD_REQUEST);
	}
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_rate(min, max);
	}
}
void Web_interface::create_shelves(string name, string creator_name)
{

	Shelves* shelf = new Shelves(name, last_id_of_shelf, creator_name);
	shelves.push_back(shelf);
	last_id_of_shelf++;
}
Shelves* Web_interface::find_shelf_by_id(int sid)
{
	for (int shelf_cursur = 0; shelf_cursur < shelves.size(); shelf_cursur++)
	{
		if (shelves[shelf_cursur]->is_it_my_id(sid))
		{
			return shelves[shelf_cursur];
		}
	}
	return NULL;
}
vector <Shelves*> Web_interface::find_shelves_by_username(string username)
{
	vector <Shelves*> list_shelves;
	for (unsigned int shelves_counter = 0; shelves_counter < shelves.size(); shelves_counter++)
	{
		if (shelves[shelves_counter]->is_it_my_username(username))
		{
			list_shelves.push_back(shelves[shelves_counter]);
		}
	}
	return list_shelves;
}
vector <Recipes*> Web_interface::get_recipes()
{
	return list_recipes;
}
Recipes* Web_interface::find_recipe_by_rid(int rid)
{
	for (int recipe_cursur = 0; recipe_cursur < list_recipes.size(); recipe_cursur++)
	{
		if (list_recipes[recipe_cursur]->is_it_my_id(rid))
		{
			return list_recipes[recipe_cursur];
		}
	}
	return NULL;
}
void Web_interface::clear_filter()
{
	for (int filter_counter = 0; filter_counter < filters.size(); filter_counter++)
	{
		filters[filter_counter]->reseat_filter();
	}
}
Person* Web_interface::find_person_by_uid(int uid)
{
	for (int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_uid(uid))
		{
			return list_person[person_counter];
		}
	}
	return NULL;
}
vector <Person*> Web_interface::list_person;
vector <Shelves*> Web_interface::shelves;
vector <Recipes*> Web_interface::list_recipes;
vector <Filter*> Web_interface::filters;
string Web_interface::state_filter = "";
Person* Web_interface::logged_in_person = NULL;
int Web_interface::last_id_of_recipe = 0;
int Web_interface::last_id_of_shelf = 0;
int Web_interface::get_size_list()
{
	return list_person.size();
}
int Web_interface::signup(string username, string password, string type)
{
	int uid = 0;
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_username(username))
		{
			throw runtime_error("this username isn't available");
		}
	}
	if (type != "chef" && type != "user")
	{
		throw runtime_error(BAD_REQUEST);
	}
	if (type == "chef")
	{
		Chef* new_chef = new Chef(username, password, type);
		list_person.push_back(new_chef);
		uid = new_chef->get_uid();
	}
	else
	{
		User* new_user = new User(username, password, type);
		list_person.push_back(new_user);
		uid = new_user->get_uid();
	}
	cout << SUCCESSFULL_MASSAGE;
	return uid;
}
int Web_interface::login(string username, string password)
{
	bool is_loggin_succesful = false;
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->can_i_log_in(username, password))
		{
			int uid_person = list_person[person_counter]->logged_in();
			logged_in_person = list_person[person_counter];
			cout << SUCCESSFULL_MASSAGE;
			is_loggin_succesful = true;
			return uid_person;
		}
	}
	if (!is_loggin_succesful)
	{
		throw runtime_error(BAD_REQUEST);
	}
	return -1;
}
void Web_interface::create_Recipe(string title, string ingredients, string vegetarian, string minutes_to_ready, string tags, string image_address, Person* creator)
{
	int recipe_id = last_id_of_recipe;
	Recipes* recipe = new Recipes(recipe_id, title, ingredients, vegetarian, stoi(minutes_to_ready), tags, image_address);
	list_recipes.push_back(recipe);
	creator->add_recipe(recipe);
	Filter* filter = new Filter(recipe);
	filters.push_back(filter);
	last_id_of_recipe++;
}
void Web_interface::delete_recipe(int rid, Person* creator)
{
	Chef* temp_chef = (Chef*)creator;
	for (int recipe_cursur = 0; recipe_cursur < list_recipes.size(); recipe_cursur++)
	{
		if (list_recipes[recipe_cursur]->is_it_my_id(rid))
		{
			cout << "hi" << endl;
			cout << rid << endl;
			list_recipes.erase(list_recipes.begin() + recipe_cursur);
			filters.erase(filters.begin() + recipe_cursur);
			temp_chef->delete_recipe(rid);
			return;
		}
	}
}
void Web_interface::logout()
{
	logged_in_person = NULL;
	state_filter = "";
	clear_filter();
}