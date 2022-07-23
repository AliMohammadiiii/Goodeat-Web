#include "Interface.hpp"

Command_Interface::Command_Interface()
{
	last_id_of_shelf = 1;
	last_id_of_recipe = 1;
}
Command_Interface::~Command_Interface()
{
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		delete filters[filter_cursur];
	}
	for (int llist_recipes_cursur = 0; llist_recipes_cursur < list_recipes.size(); llist_recipes_cursur++)
	{
		delete list_recipes[llist_recipes_cursur];
	}
}
void Command_Interface::check_access(string type_need)
{
	if (!logged_in_person->is_it_my_job(type_need))
	{
		throw runtime_error(PERMISION_DENIED);
	}
}
void Command_Interface::check_input_number_correct(int number_input)
{
	if (command_word.size() != number_input)
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::check_input_type_correct(string input_type)
{
	if (command_word[TYPE] != input_type)
	{
		throw runtime_error(BAD_REQUEST);
	}
}
bool Command_Interface::login_check()
{
	if (logged_in_person != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Command_Interface::my_recipes()
{
	check_input_number_correct(2);
	check_input_type_correct(GET);
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_access("chef");
	Chef* temp_chef = (Chef*)logged_in_person;
	temp_chef->show_my_recipe();
}
void Command_Interface::delete_recipe()
{
	int recipe_id = stoi(command_word[4]);
	Chef* temp_chef = (Chef*)logged_in_person;
	if (recipe_id > last_id_of_recipe)
	{
		throw runtime_error(NOT_FOUND);
	}
	if (logged_in_person == NULL)
	{
		throw runtime_error(PERMISION_DENIED);
	}
	temp_chef->delete_recipe(recipe_id);
	for (unsigned int recipe_counter = 0; recipe_counter < last_id_of_recipe; recipe_counter++)
	{
		if (list_recipes[recipe_counter]->is_it_my_id(recipe_id))
		{
			list_recipes.erase(list_recipes.begin() + recipe_counter);
			filters.erase(filters.begin() + recipe_counter);
			break;
		}
	}
}
void Command_Interface::alphabet_sort_person()
{
	for (unsigned int i = 0; i < list_person.size(); i++)
	{
		for (unsigned int j = 0; j < list_person.size() - 1; j++)
		{
			if (list_person[j]->get_name() < list_person[j + 1]->get_name())
			{
				Person* temp_person = list_person[j];
				list_person[j] = list_person[j + 1];
				list_person[j + 1] = temp_person;
			}
		}
	}
}
void Command_Interface::alphabet_sort_recipes()
{
	for (unsigned int i = 0; i < list_recipes.size(); i++)
	{
		for (unsigned int j = 0; j < list_recipes.size() - 1; j++)
		{
			if (list_recipes[j]->get_name() > list_recipes[j + 1]->get_name())
			{
				Recipes* temp_recipe = list_recipes[j];
				list_recipes[j] = list_recipes[j + 1];
				list_recipes[j + 1] = temp_recipe;
			}
		}
	}
}
vector <string> Command_Interface::read_input(string input)
{
	stringstream input_list(input);
	vector <string> input_word;
	string temp_word;
	while (input_list >> temp_word)
	{
		input_word.push_back(temp_word);
	}
	return input_word;
}
Person* Command_Interface::find_logged_in()
{
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->am_i_log_in())
		{
			return list_person[person_counter];
		}
	}
	return NULL;
}
void Command_Interface::signup()
{
	if (login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_input_number_correct(9);
	check_input_type_correct(POST);
	string username, password, type;
	username = command_word[4];
	password = command_word[6];
	type = command_word[8];
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_username(username))
		{
			throw runtime_error(BAD_REQUEST);
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
	}
	else
	{
		User* new_user = new User(username, password, type);
		list_person.push_back(new_user);
	}
	cout << SUCCESSFULL_MASSAGE;
}
void Command_Interface::login()
{
	if (login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_input_number_correct(7);
	check_input_type_correct(POST);
	string username, password, temp_input, type_check;
	bool is_loggin_succesful = false;
	type_check = command_word[3];
	username = command_word[4];
	password = command_word[6];
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (type_check == "email")
		{
			if (list_person[person_counter]->is_it_my_job(SUPPLIER))
			{
				Supplier* temp_supplier = (Supplier*)list_person[person_counter];
				if (temp_supplier->can_i_log_in(username, password))
				{
					list_person[person_counter]->logged_in();
					cout << SUCCESSFULL_MASSAGE;
					is_loggin_succesful = true;
					continue;
				}
			}
		}
		else
		{
			if (list_person[person_counter]->can_i_log_in(username, password))
			{
				list_person[person_counter]->logged_in();
				cout << SUCCESSFULL_MASSAGE;
				is_loggin_succesful = true;
				continue;
			}
		}
	}
	if (!is_loggin_succesful)
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::clear_filter()
{
	for (int filter_counter = 0; filter_counter < filters.size(); filter_counter++)
	{
		filters[filter_counter]->reseat_filter();
	}
}
void Command_Interface::logout()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_input_number_correct(2);
	check_input_type_correct(POST);
	logged_in_person->logged_out();
	cout << SUCCESSFULL_MASSAGE;
	clear_filter();
}
string Command_Interface::recipes_abstract_info()
{
	string info;
	int number_recipes = 0;
	for (unsigned int recipes_counter = 0; recipes_counter < list_recipes.size(); recipes_counter++)
	{
		if (list_recipes[recipes_counter]->can_i_show())
		{
			info += list_recipes[recipes_counter]->abstract_info();
			info += '\n';
			number_recipes++;
		}
	}
	if (number_recipes == 0)
	{
		throw runtime_error(EMPTY);
	}
	return info;
}
Recipes* Command_Interface::find_recipes_by_id(int id)
{
	for (unsigned int recipe_counter = 0; recipe_counter < list_recipes.size(); recipe_counter++)
	{
		if (list_recipes[recipe_counter]->is_it_my_id(id))
		{
			return list_recipes[recipe_counter];
		}
	}
	throw runtime_error(NOT_FOUND);
	return NULL;
}
void Command_Interface::recipe_info(int id)
{
	Recipes* recipe = find_recipes_by_id(id);
	if (recipe == NULL)
	{
		throw runtime_error(NOT_FOUND);
	}
	cout << recipe->info();
}
int Command_Interface::create_recipe()
{
	string temp_input, title, ingredients, vegetarian, tags, image_address;
	int minutes_to_ready;
	title = command_word[4];
	ingredients = command_word[6];
	vegetarian = command_word[8];
	minutes_to_ready = stoi(command_word[10]);
	tags = command_word[12];
	image_address = command_word[14];
	int recipe_id = last_id_of_recipe;
	Recipes* recipe = new Recipes(recipe_id, title, ingredients, vegetarian, minutes_to_ready, tags, image_address);
	list_recipes.push_back(recipe);
	logged_in_person->add_recipe(recipe);
	Filter* filter = new Filter(recipe);
	filters.push_back(filter);
	last_id_of_recipe++;
	return recipe_id;
}
void Command_Interface::recipes()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	else
	{
		if (command_word[TYPE] == GET && logged_in_person->is_it_my_job("user"))
		{

			if (command_word.size() == 2)
			{
				if (list_recipes.size() == 0)
				{
					throw runtime_error(EMPTY);
				}
				cout << recipes_abstract_info();
			}
			else
			{
				check_input_number_correct(5);
				recipe_info(stoi(command_word[command_word.size() - 1]));
			}
		}
		else if (command_word[TYPE] == POST && logged_in_person->is_it_my_job("chef"))
		{
			check_input_number_correct(15);
			cout << create_recipe() << endl;
			alphabet_sort_recipes();
		}
		else if (command_word[TYPE] == DELETE && logged_in_person->is_it_my_job("chef"))
		{
			check_input_number_correct(5);
			delete_recipe();
			cout << SUCCESSFULL_MASSAGE;
		}
		else
		{
			throw runtime_error(PERMISION_DENIED);
		}
	}
}
void Command_Interface::rates()
{
	check_input_number_correct(7);
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_access("user");
	int id = stoi(command_word[4]);
	float rate = stof(command_word[6]);
	if (rate < 1 || rate > 5)
	{
		throw runtime_error(BAD_REQUEST);
	}
	Recipes* rated_recipes = find_recipes_by_id(id);
	if (rated_recipes == NULL)
	{
		throw runtime_error(NOT_FOUND);
	}
	if (command_word[0] == POST)
	{
		rated_recipes->set_rate(logged_in_person->get_name(), rate);
		rated_recipes->update_rate();
		cout << SUCCESSFULL_MASSAGE;
	}
	else if (command_word[0] == PUT)
	{
		rated_recipes->change_rate(logged_in_person->get_name(), rate);
		rated_recipes->update_rate();
		cout << SUCCESSFULL_MASSAGE;
	}
	else
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::user_list()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_input_number_correct(2);
	check_input_type_correct(GET);
	string info;
	int number_user = 0;
	string loggedin_username = logged_in_person->get_name();
	check_access("user");
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_job("user"))
		{
			if (list_person[person_counter]->get_name() != loggedin_username)
			{
				info += list_person[person_counter]->get_name();
				info += '\n';
				number_user++;
			}
		}
	}
	if (number_user == 0)
	{
		throw runtime_error(EMPTY);
	}
	else
	{
		cout << info;
	}
}
void  Command_Interface::chef_abstract_info()
{
	string info;
	int number_user = 0;
	string loggedin_username = logged_in_person->get_name();
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_job("chef"))
		{
			if (list_person[person_counter]->get_name() != loggedin_username)
			{
				Chef* new_chef = (Chef*)list_person[person_counter];
				info += new_chef->abstract_info();
				number_user++;
			}
		}
	}
	if (number_user == 0)
	{
		throw runtime_error(EMPTY);
	}
	else
	{
		cout << info;
	}
}
Person* Command_Interface::find_person_by_username(string username)
{
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_username(username))
		{
			return list_person[person_counter];
		}
	}
	throw runtime_error(NOT_FOUND);
	return NULL;
}
void Command_Interface::chef_info()
{
	string chef_username = command_word[4];
	try
	{
		Person* chef = find_person_by_username(chef_username);
		if (!chef->is_it_my_job("chef"))
		{
			throw runtime_error(NOT_FOUND);
		}
		Chef* main_chef = (Chef*)chef;
		cout << main_chef->info();
	}
	catch (runtime_error& ex)
	{
		cout << ex.what() << endl;
		return;
	}

}
void Command_Interface::chefs_info()
{
	check_input_type_correct(GET);
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	if (logged_in_person->is_it_my_job("user"))
	{
		if (command_word.size() == 2)
		{
			chef_abstract_info();
		}
		else
		{
			check_input_number_correct(5);
			chef_info();
		}
	}
	else
	{
		throw runtime_error(PERMISION_DENIED);
	}
}
int Command_Interface::create_shelves(string name, int id)
{
	string username = logged_in_person->get_name();
	Shelves* shelf = new Shelves(name, id, username);
	shelves.push_back(shelf);
	return id;
}
vector <Shelves*> Command_Interface::find_shelves_by_username(string username)
{
	vector <Shelves*> list_shelves;
	for (unsigned int shelves_counter = 0; shelves_counter < shelves.size(); shelves_counter++)
	{
		if (shelves[shelves_counter]->is_it_my_username(username))
		{
			list_shelves.push_back(shelves[shelves_counter]);
		}
	}
	if (list_shelves.size() == 0)
	{
		throw runtime_error(EMPTY);
	}
	return list_shelves;
}
Shelves* Command_Interface::find_shelve_by_id(int id)
{
	for (unsigned int shelf_counter = 0; shelf_counter < shelves.size(); shelf_counter++)
	{
		if (shelves[shelf_counter]->is_it_my_id(id))
		{
			return shelves[shelf_counter];
		}
	}
	throw runtime_error(EMPTY);
	return NULL;
}
string Command_Interface::shelves_list(int limit, string username)
{
	vector <Shelves*> list_shelves = find_shelves_by_username(username);
	if (limit == -1 || limit > list_shelves.size())
	{
		limit = list_shelves.size();
	}
	string list;
	if (list_shelves.size() == 0)
	{
		throw runtime_error(EMPTY);
	}
	for (int shelf_counter = 0; shelf_counter < limit; shelf_counter++)
	{
		list += list_shelves[shelf_counter]->abstract_info();
	}
	return list;
}
void Command_Interface::add_to_shelves(int shelf_id, Recipes* recipe)
{
	Shelves* shelf = find_shelve_by_id(shelf_id);
	string username = logged_in_person->get_name();
	if (!shelf->is_it_my_username(username))
	{
		throw runtime_error(PERMISION_DENIED);
	}
	shelf->add_recipe(recipe);
}
string Command_Interface::show_recipes_of_shelve(int shelf_id)
{
	string info;
	Shelves* shelf = find_shelve_by_id(shelf_id);
	info += shelf->recipes_list();
	return info;
}
void Command_Interface::delete_recipe_from_shelves(int shelf_id, int recipe_id)
{
	Shelves* shelf = find_shelve_by_id(shelf_id);
	string username = logged_in_person->get_name();
	if (!shelf->is_it_my_username(username))
	{
		throw runtime_error(PERMISION_DENIED);
	}
	shelf->delete_recipe(recipe_id);
}
void Command_Interface::shelves_function()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_access("user");
	if (command_word[TYPE] == "POST")
	{
		check_input_number_correct(5);
		string shelf_name = command_word[4];
		int shelf_id = last_id_of_shelf;
		last_id_of_shelf++;
		create_shelves(shelf_name, shelf_id);
		cout << shelf_id << endl;
	}
	else if (command_word[TYPE] == "GET")
	{
		check_input_number_correct(7);
		string username = command_word[4];
		int limit = stoi(command_word[6]);
		cout << shelves_list(limit, username);
	}
	else
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::shelves_recipes()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_access("user");
	if (command_word[TYPE] == "PUT")
	{
		check_input_number_correct(7);
		stringstream shelf_id_stream(command_word[4]);
		stringstream recipe_id_stream(command_word[6]);
		int shelf_id = -1;
		shelf_id_stream >> shelf_id;
		if (shelf_id <= 0)
		{
			throw runtime_error(BAD_REQUEST);
		}
		int recipe_id = -1;
		recipe_id_stream >> recipe_id;
		if (recipe_id <= 0)
		{
			throw runtime_error(BAD_REQUEST);
		}
		Recipes* recipe = find_recipes_by_id(recipe_id);
		add_to_shelves(shelf_id, recipe);
		cout << SUCCESSFULL_MASSAGE;
	}
	else if (command_word[TYPE] == "GET")
	{
		check_input_number_correct(5);
		int limit = stoi(command_word[4]);
		cout << show_recipes_of_shelve(limit);
	}
	else if (command_word[TYPE] == "DELETE")
	{
		check_input_number_correct(7);
		int shelf_id = stoi(command_word[4]);
		int recipe_id = stoi(command_word[6]);
		delete_recipe_from_shelves(shelf_id, recipe_id);
		cout << SUCCESSFULL_MASSAGE;
	}
	else
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::apply_tag_filter()
{
	string tag = command_word[4];
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_tag(tag);
	}
}
void Command_Interface::apply_time_filter()
{
	stringstream min_stream(command_word[4]);
	stringstream max_stream(command_word[6]);
	int min = 0;
	min_stream >> min;
	int max = 0;
	max_stream >> max;
	if (max < min)
	{
		throw runtime_error(BAD_REQUEST);
	}
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_time(min, max);
	}
}
void Command_Interface::apply_veg_filter()
{
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_vegetarian();
	}
}
void Command_Interface::apply_rate_filter()
{
	stringstream min_stream(command_word[4]);
	stringstream max_stream(command_word[6]);
	int min = 0;
	min_stream >> min;
	int max = 0;
	max_stream >> max;
	if (max < min || max > 5 || min < 0)
	{
		throw runtime_error(BAD_REQUEST);
	}
	for (int filter_cursur = 0; filter_cursur < filters.size(); filter_cursur++)
	{
		filters[filter_cursur]->add_filter_rate(min, max);
	}
}
void Command_Interface::filter()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	string type_input = command_word[TYPE];
	if (type_input == POST)
	{
		string type_filter = command_word[3];
		if (type_filter == "tag")
		{
			check_input_number_correct(5);
			check_input_type_correct(POST);
			apply_tag_filter();
			cout << SUCCESSFULL_MASSAGE;
		}
		else if (type_filter == "vegetarian")
		{
			check_input_number_correct(4);
			check_input_type_correct(POST);
			apply_veg_filter();
			cout << SUCCESSFULL_MASSAGE;
		}
		else if (type_filter == "min_minutes")
		{
			check_input_number_correct(7);
			check_input_type_correct(POST);
			apply_time_filter();
			cout << SUCCESSFULL_MASSAGE;
		}
		else if (type_filter == "min_rating")
		{
			check_input_number_correct(7);
			check_input_type_correct(POST);
			apply_rate_filter();
			cout << SUCCESSFULL_MASSAGE;
		}
		else
		{
			throw runtime_error(BAD_REQUEST);
		}
	}
	else if (type_input == DELETE)
	{
		check_input_number_correct(2);
		check_input_type_correct(DELETE);
		clear_filter();
		cout << SUCCESSFULL_MASSAGE;
	}
	else
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::signup_supplier()
{
	if (login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	check_input_number_correct(9);
	check_input_type_correct(POST);
	string name = command_word[4],
		email = command_word[6],
		password = command_word[8];
	for (unsigned int person_counter = 0; person_counter < list_person.size(); person_counter++)
	{
		if (list_person[person_counter]->is_it_my_username(name))
		{
			throw runtime_error(BAD_REQUEST);
		}
		if (list_person[person_counter]->is_it_my_job(SUPPLIER))
		{
			Supplier* temp_supplier = (Supplier*)list_person[person_counter];
			if (temp_supplier->is_it_my_email(email))
			{
				throw runtime_error(BAD_REQUEST);
			}
		}
	}
	Supplier* new_supplier = new Supplier(name, email, password);
	list_person.push_back(new_supplier);
	cout << SUCCESSFULL_MASSAGE;
}

void Command_Interface::add_ingradient(string offer_name, int number)
{
	for (int ingeradient_cursur = 0; ingeradient_cursur < ingrediants_list.size(); ingeradient_cursur++)
	{
		if (ingrediants_list[ingeradient_cursur]->is_it_my_name(offer_name))
		{
			ingrediants_list[ingeradient_cursur]->plus_number(number);
			return;
		}
	}
	Ingerediant* new_ingrediant = new Ingerediant(offer_name, number);
	ingrediants_list.push_back(new_ingrediant);
	return;
}
void Command_Interface::reduce_ingradient(string offer_name, int number)
{
	for (int ingeradient_cursur = 0; ingeradient_cursur < ingrediants_list.size(); ingeradient_cursur++)
	{
		if (ingrediants_list[ingeradient_cursur]->is_it_my_name(offer_name))
		{
			ingrediants_list[ingeradient_cursur]->reduce_number(number);
			return;
		}
	}
}
void Command_Interface::post_offer()
{
	check_input_number_correct(11);
	string ingredient = command_word[4];
	int price = stoi(command_word[6]),
		count = stoi(command_word[8]),
		packaging = stoi(command_word[10]);
	Supplier* supplier = (Supplier*)logged_in_person;
	supplier->create_offer(ingredient, price, count, packaging);
	cout << SUCCESSFULL_MASSAGE;
	add_ingradient(ingredient, price);
}
void Command_Interface::put_offer()
{
	check_input_number_correct(9);
	string ingredient = command_word[4];
	int price = stoi(command_word[6]),
		count = stoi(command_word[8]);
	Supplier* supplier = (Supplier*)logged_in_person;
	supplier->edit_offer(ingredient, price, count);
	cout << SUCCESSFULL_MASSAGE;
}
void Command_Interface::delete_offer()
{
	check_input_number_correct(5);
	string ingredient = command_word[4];
	Supplier* supplier = (Supplier*)logged_in_person;
	int price = supplier->delete_offer(ingredient);
	reduce_ingradient(ingredient, price);
	cout << SUCCESSFULL_MASSAGE;
}
void Command_Interface::function_offers()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	if (!logged_in_person->is_it_my_job(SUPPLIER))
	{
		throw runtime_error(PERMISION_DENIED);
	}
	if (command_word[TYPE] == POST)
	{
		post_offer();
	}
	if (command_word[TYPE] == PUT)
	{
		put_offer();
	}
	if (command_word[TYPE] == DELETE)
	{
		delete_offer();
	}
}
void Command_Interface::credits()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	if (command_word[TYPE] == GET)
	{
		check_input_number_correct(2);
		cout << logged_in_person->get_credits() << endl;
	}
	else if (command_word[TYPE] == PUT)
	{
		check_input_number_correct(5);
		int money = stoi(command_word[4]);
		if (!logged_in_person->is_it_my_job("user"))
		{
			throw runtime_error(PERMISION_DENIED);
		}
		User* user = (User*)logged_in_person;
		user->increase_credits(money);
		cout << SUCCESSFULL_MASSAGE;
	}
}
void Command_Interface::find_ingrediant(vector<string>& ingredient_need_list, int recipe_id, vector<offer_findes>& offers_need)
{
	for (int ingredient_need_cursur = 0; ingredient_need_cursur < ingredient_need_list.size(); ingredient_need_cursur++)
	{
		string ingrediant_need_name = ingredient_need_list[ingredient_need_cursur];
		vector<offer_findes> offers;
		for (int person_cursur = 0; person_cursur < list_person.size(); person_cursur++)
		{
			if (list_person[person_cursur]->is_it_my_job(SUPPLIER))
			{
				Supplier* supplier = (Supplier*)list_person[person_cursur];
				if (supplier->am_i_have_ingrediant(ingrediant_need_name))
				{
					offer_findes new_offer_find;
					new_offer_find.offer = supplier->get_offer(ingrediant_need_name);
					new_offer_find.supplier = supplier;
					offers.push_back(new_offer_find);
				}
			}
		}
		if (offers.size() == 0)
		{
			throw runtime_error(NOT_FOUND);
		}
		offer_findes offer_ingrediant = find_best_price(offers);
		offers_need.push_back(offer_ingrediant);
	}
}
offer_findes Command_Interface::find_best_price(vector<offer_findes>& offers)
{
	offer_findes offer_ingrediant;
	offer_ingrediant = offers[0];
	for (int offer_cursur = 0; offer_cursur < offers.size(); offer_cursur++)
	{
		if (offer_ingrediant.offer->get_price() > offers[offer_cursur].offer->get_price())
		{
			offer_ingrediant = offers[offer_cursur];
		}
	}
	return offer_ingrediant;
}
bool Command_Interface::is_there_a_discount(string ingredient)
{
	for (int ingeradient_cursur = 0; ingeradient_cursur < ingrediants_list.size(); ingeradient_cursur++)
	{
		if (ingrediants_list[ingeradient_cursur]->is_it_my_name(ingredient))
		{
			if (ingrediants_list[ingeradient_cursur]->is_it_in_discount())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
void Command_Interface::post_order()
{
	check_input_number_correct(5);
	if (!logged_in_person->is_it_my_job("user"))
	{
		throw runtime_error(PERMISION_DENIED);
	}
	User* user = (User*)logged_in_person;
	int recipe_id = stoi(command_word[4]);
	Recipes* recipe = find_recipes_by_id(recipe_id);
	vector<string> ingredient_need_list = recipe->get_ingredients();
	vector<offer_findes> offers_need;
	find_ingrediant(ingredient_need_list, recipe_id, offers_need);
	int price = 0;
	for (int offer_cursur = 0; offer_cursur < offers_need.size(); offer_cursur++)
	{
		if (is_there_a_discount(offers_need[offer_cursur].offer->get_ingredient()))
		{
			int new_price = offers_need[offer_cursur].offer->get_price();
			new_price -= offers_need[offer_cursur].offer->get_price() * DISCOUNT_PERCENT;
			price += new_price;
		}
		else
		{
			price += offers_need[offer_cursur].offer->get_price();
		}
	}
	sale_order(offers_need, price);
	cout << user->order_creator(offers_need, price, recipe_id) << endl;
}
void Command_Interface::sale_order(vector<offer_findes>& offers_need, int price)
{
	User* user = (User*)logged_in_person;
	if (user->can_i_pay(price))
	{
		user->pay(price);
		for (int offer_cursur = 0; offer_cursur < offers_need.size(); offer_cursur++)
		{
			offers_need[offer_cursur].offer->sale();
			int price = offers_need[offer_cursur].offer->get_price();
			offers_need[offer_cursur].supplier->increase_credit(price);
			reduce_ingradient(offers_need[offer_cursur].offer->get_ingredient(), 1);
		}
	}
	else
	{
		throw runtime_error(BAD_REQUEST);
	}
}
void Command_Interface::get_order()
{
	check_input_number_correct(2);
	if (!logged_in_person->is_it_my_job("user"))
	{
		throw runtime_error(PERMISION_DENIED);
	}
	User* user = (User*)logged_in_person;
	cout << user->print_order_list();
}
void Command_Interface::orders()
{
	if (!login_check())
	{
		throw runtime_error(PERMISION_DENIED);
	}
	if (command_word[TYPE] == POST)
	{
		post_order();
	}
	else if (command_word[TYPE] == GET)
	{
		get_order();
	}
}
void Command_Interface::work()
{
	string type_input, command;
	logged_in_person = NULL;
	string input;
	while (getline(cin, input))
	{
		try
		{
			logged_in_person = find_logged_in();
			command_word = read_input(input);
			if (command_word.size() == 0)
			{
				continue;
			}
			if (command_word[TYPE] != POST && command_word[TYPE] != GET && command_word[TYPE] != DELETE && command_word[TYPE] != PUT)
			{
				throw runtime_error(BAD_REQUEST);
				continue;
			}
			if (command_word[COMMAND] == "signup")
			{
				signup();
				alphabet_sort_person();
				continue;
			}
			else if (command_word[COMMAND] == "login")
			{
				login();
				continue;
			}
			else if (command_word[COMMAND] == "logout")
			{
				logout();
				continue;
			}
			else if (command_word[COMMAND] == "recipes")
			{
				recipes();
				continue;
			}
			else if (command_word[COMMAND] == "my_recipes")
			{
				my_recipes();
				continue;
			}
			else if (command_word[COMMAND] == "rates")
			{
				rates();
				continue;
			}
			else if (command_word[COMMAND] == "users")
			{
				user_list();
				continue;
			}
			else if (command_word[COMMAND] == "chefs")
			{
				chefs_info();
				continue;
			}
			else if (command_word[COMMAND] == "shelves")
			{
				shelves_function();
				continue;
			}
			else if (command_word[COMMAND] == "shelves_recipes")
			{
				shelves_recipes();
				continue;
			}
			else if (command_word[COMMAND] == "filters")
			{
				filter();
				continue;
			}
			else if (command_word[COMMAND] == "signup_supplier")
			{
				signup_supplier();
				continue;
			}
			else if (command_word[COMMAND] == "offers")
			{
				function_offers();
				continue;
			}
			else if (command_word[COMMAND] == "credits")
			{
				credits();
				continue;
			}
			else if (command_word[COMMAND] == "orders")
			{
				orders();
				continue;
			}
			else
			{
				throw runtime_error(NOT_FOUND);
				continue;
			}
		}
		catch (runtime_error& error)
		{
			cout << error.what() << endl;
			continue;
		}

	}
}