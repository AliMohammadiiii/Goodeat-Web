#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
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
class AddUser : public RequestHandler {
public:
	Response* callback(Request*);
};
class LoginHandler : public RequestHandler {
public:
	Response* callback(Request*);
};
class MainPageHandler : public RequestHandler
{
private:
	Response* chef_page(Person* active_person);
	Response* user_page(Person* active_person);
public:
	Response* callback(Request* req);
};
class CreateRecipe : public RequestHandler
{
public:
	Response* callback(Request* req);
};
class DeleteRecipe : public RequestHandler
{
public:
	Response* callback(Request* req);
};
class LogOut :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class Recipe_page :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class UpdateRate :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class ShelvesManagment :public RequestHandler
{
public:
	Response* callback(Request* req);
};
class CreateShelf :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class ShelfPage :public RequestHandler
{
public:
	Response* callback(Request* req);
};
class AddRecipe :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class RemoveRecipe :public RequestHandler
{
public:
	Response* callback(Request* req);
};

class AddFilter :public RequestHandler
{
public:
	Response* callback(Request* req);
};
class ClearFilter :public RequestHandler
{
public:
	Response* callback(Request* req);
};

#endif
