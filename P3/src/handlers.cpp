#include "handlers.hpp"
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
using namespace std;
Response* AddUser::callback(Request* req) {
	string username = req->getBodyParam("name");
	string password = req->getBodyParam("password");
	string type = req->getBodyParam("job");
	try
	{
		int uid = Web_interface::signup(username, password, type);
		cout << "username: " << username << ",\tpassword: " << password << endl;
		Response* res = Response::redirect("/");
		res->setSessionId(to_string(uid));
		return res;
	}
	catch (runtime_error& error)
	{
		Response* res = Response::redirect("/signup_inc");
		return res;
	}


}

Response* LoginHandler::callback(Request* req) {
	string username = req->getBodyParam("name");
	string password = req->getBodyParam("password");
	try
	{
		int uid = Web_interface::login(username, password);
		cout << "username: " << username << ",\tpassword: " << password << endl;
		Response* res = Response::redirect("/");
		res->setSessionId(to_string(uid));
		return res;
	}
	catch (runtime_error& error)
	{
		Response* res = Response::redirect("/login_inc");
		return res;
	}

}




Response* MainPageHandler::callback(Request* req) {
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Response* res = new Response;
	Person* temp_person = Web_interface::find_person_by_uid(uid);
	if (temp_person == NULL)
	{
		Response* res = Response::redirect("/signup");
		return res;
	}
	if (temp_person->is_it_my_job("chef"))
	{
		return chef_page(temp_person);
	}
	if (temp_person->is_it_my_job("user"))
	{
		return user_page(temp_person);
	}

}
Response* MainPageHandler::chef_page(Person* active_person)
{
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string username = active_person->get_name();
	string html;
	string head;
	head = "<!DOCTYPE html>";
	head += "<html lang=\"en\">";
	head += "<head>";
	head += "<title>Ap Goodeat</title>";
	head += "<meta charset=\"UTF-8\">";
	head += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	head += "<style>*{color: #2c3544}#create_recipe{position: relative;left: 25%;}body{background-color: #EFF2F6;padding: 25px;}#logout_link{text-decoration: none;font-weight: bold;position: relative;font-size: 18px;left: 50%;}#Hi{display: inline;position: relative;left: 25%;}.recipe{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 700px;position: relative;left: 25%;}.title{font-weight: bold;color: #43a6dd;font-size: 24px;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}button.create_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}.create_shelf{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 500px;position: relative;left: 25%;}</style>";
	head += "</head>";
	string body;
	body = "<body>";
	body += "<div class=\"nav_bar\">";
	body += "<h1 id=\"Hi\">";
	body += "Hi Chef " + username;
	body += "</h1>";
	body += "<a href=\"/logout\" id=\"logout_link\">Log Out</a></div>";
	body += "<a href=\"/create_recipe\"id = \"create_recipe\"><button type=\"button\" class=\"delete_btn\"> create recipe </button></a>";
	Chef* chef_temp = (Chef*)active_person;
	vector <Recipes*> my_recipes = chef_temp->show_my_recipe();
	ostringstream recipes_list;
	if (my_recipes.size() > 0)
	{
		for (int recipe_counter = 0; recipe_counter < my_recipes.size(); recipe_counter++)
		{
			recipes_list << "<div class=\"recipe\">"
				<< "<span class=\"title_recipe\">#" << my_recipes[recipe_counter]->get_id() + 1 << " : " << my_recipes[recipe_counter]->get_name() << "</span>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "rating: " << "</p>" << "<span class=\"detail\" >" << my_recipes[recipe_counter]->get_rate_str() << "</span>" << "</div>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "vegetarian: " << "</p>" << "<span class=\"detail\" >" << my_recipes[recipe_counter]->get_vegeterian_state() << "</span>" << "</div>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "ingredients: " << "</p>" << "<span class=\"detail\" >" << my_recipes[recipe_counter]->get_ingredients() << "</span>" << "</div>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "minutes to ready: " << "</p>" << "<span class=\"detail\" >" << my_recipes[recipe_counter]->get_minutes_to_ready() << "</span>" << "</div>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "tags: " << "</p>" << "<span class=\"detail\" >" << my_recipes[recipe_counter]->get_tags() << "</span>" << "</div>" << endl
				<< "<a href=\"/delete_recipe?Rid=" << my_recipes[recipe_counter]->get_id() << "\"><button type=\"button\" class=\"delete_btn\"> Delete </button></a>" << endl
				<< "</div>" << endl;
		}
	}
	html = head + body + recipes_list.str() + "</body>" + "</html>";
	res->setBody(html);
	return res;
}
Response* MainPageHandler::user_page(Person* active_person)
{
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string username = active_person->get_name();
	string html;
	string head;
	head = "<!DOCTYPE html>";
	head += "<html lang=\"en\">";
	head += "<head>";
	head += "<title>Ap Goodeat</title>";
	head += "<meta charset=\"UTF-8\">";
	head += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	head += "<style>*{color: #2c3544}#shelves{position: relative;left: 25%;}body{background-color: #EFF2F6;padding: 25px;}#logout_link{text-decoration: none;font-weight: bold;position: relative;font-size: 18px;left: 50%;}#Hi{display: inline;position: relative;left: 25%;}.recipe{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 700px;position: relative;left: 25%;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}.filter{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 500px;position: relative;left: 25%;}input{padding: 15px; border-bottom: 1px solid #2c3544; border-top: none; border-left: none; border-right: none;}.title{margin: 25px;font-size: 16px;font-weight: bold;}</style>";
	head += "</head>";
	string body;
	body = "<body>";
	body += "<div class=\"nav_bar\">";
	body += "<h1 id=\"Hi\">";
	body += "Hi " + username;
	body += "</h1>";
	body += "<a href=\"/logout\" id=\"logout_link\">Log Out</a></div>";
	body += "<a href=\"/shelves\"id = \"shelves\"><button type=\"button\" class=\"delete_btn\"> shelves managment </button></a>";
	Chef* chef_temp = (Chef*)active_person;
	vector <Recipes*> recipes = Web_interface::get_recipes();
	ostringstream recipes_list;
	recipes_list << "<form class=\"filter\" action=\"/add_filter\" method=\"POST\"><p class=\"title_recipe\">choose your filter</p><p style=\"color: #43a6dd;\">" << Web_interface::state_filter
		<< "</p><select name=\"vegetarian\" class=\"input100 dropdown-menu-right\" style=\"border: 0cm; padding: 0.4cm; color: #8f8fa1;\"><option value=\"0\" class=\"dropdown-item input100\"style=\"color: #8f8fa1;\">Does not matter</option><option value=\"Yes\" class=\"dropdown-item input100\"style=\"color: #8f8fa1;\">is vegetarian</option><option value=\"No\" class=\"dropdown-item input100\"style=\"color: #8f8fa1;\">is not vegetarian</option></select><p class=\"title\">Time:</p><input name=\"min_time\"  type=\"number\" placeholder=\"minimum time\"><input name=\"max_time\" type=\"number\"  placeholder=\"maximum time\"><p class=\"title\">Rate:</p><input name=\"min_rate\" type=\"number\"  placeholder=\"minimum rate\"><input name=\"max_rate\" type=\"number\" placeholder=\"maximum rate\"><button type=\"submit\">Add filter</button>"
		<< "<a href=\"/delete_filter\"><button type=\"button\">Reset</button></a></form>" << endl;


	if (recipes.size() > 0)
	{
		for (int recipe_counter = 0; recipe_counter < recipes.size(); recipe_counter++)
		{
			if (recipes[recipe_counter]->can_i_show())
			{
				recipes_list << "<a style=\"text-decoration: none;\" href=\"/Recipe_page?Rid=" << recipes[recipe_counter]->get_id() << "\"><div class=\"recipe\">"
					<< "<span class=\"title_recipe\">#" << recipes[recipe_counter]->get_id() + 1 << " : " << recipes[recipe_counter]->get_name() << "</span>" << endl
					<< "<div class=\"detail\">" << "<p class=\"detail\">" << "vegetarian: " << "</p>" << "<span class=\"detail\" >" << recipes[recipe_counter]->get_vegeterian_state() << "</span>" << "</div>" << endl
					<< "<div class=\"detail\">" << "<p class=\"detail\">" << "minutes to ready: " << "</p>" << "<span class=\"detail\" >" << recipes[recipe_counter]->get_minutes_to_ready() << "</span>" << "</div>" << endl
					<< "</div></a>" << endl;
			}
		}
	}
	html = head + body + recipes_list.str() + "</body>" + "</html>";
	res->setBody(html);
	return res;
}

Response* CreateRecipe::callback(Request* req)
{
	string title = req->getBodyParam("Title");
	string ingredients = req->getBodyParam("ingredients");
	string vegetarian = req->getBodyParam("vegetarian");
	string minutes_to_ready = req->getBodyParam("minutes_to_ready");
	string tags = req->getBodyParam("tags");
	string Image = req->getBodyParam("Image");
	string UID_string = req->getSessionId();
	int uid = stoi(req->getSessionId());
	Person* temp_person = Web_interface::find_person_by_uid(uid);
	Web_interface::create_Recipe(title, ingredients, vegetarian, minutes_to_ready, tags, Image, temp_person);
	Response* res = Response::redirect("/");
	return res;

}


Response* DeleteRecipe::callback(Request* req)
{
	string UID_string = req->getSessionId();
	int uid = stoi(req->getSessionId());
	Person* temp_person = Web_interface::find_person_by_uid(uid);
	string rid_str = req->getQueryParam("Rid");
	int rid = stoi(rid_str);
	Web_interface::delete_recipe(rid, temp_person);
	Response* res = Response::redirect("/");
	return res;
}



Response* LogOut::callback(Request* req)
{
	Web_interface::logout();
	Response* res = Response::redirect("/login");
	res->setSessionId("-1");
	return res;
}

Response* Recipe_page::callback(Request* req)
{
	int rid = stoi(req->getQueryParam("Rid"));
	Recipes* temp_recipe = Web_interface::find_recipe_by_rid(rid);
	string UID_string = req->getSessionId();
	int uid = stoi(req->getSessionId());
	Person* active_person = Web_interface::find_person_by_uid(uid);

	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string username = active_person->get_name();
	string html;
	string head;
	head = "<!DOCTYPE html>";
	head += "<html lang=\"en\">";
	head += "<head>";
	head += "<title>Ap Goodeat</title>";
	head += "<meta charset=\"UTF-8\">";
	head += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	head += "<style>*{color: #2c3544}#back{position: relative;left: 25%;}body{background-color: #EFF2F6;padding: 25px;}#logout_link{text-decoration: none;font-weight: bold;position: relative;font-size: 18px;left: 50%;}#Hi{display: inline;position: relative;left: 25%;}.recipe{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 700px;position: relative;left: 25%;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}</style>";
	head += "</head>";
	string body;
	body = "<body>";
	body += "<div class=\"nav_bar\">";
	body += "<h1 id=\"Hi\">";
	body += "Hi " + username;
	body += "</h1>";
	body += "<a href=\"/logout\" id=\"logout_link\">Log Out</a></div>";
	body += "<a href=\"/\"id = \"back\"><button type=\"button\" class=\"delete_btn\">  Back </button></a>";
	Chef* chef_temp = (Chef*)active_person;
	vector <Recipes*> my_recipes = chef_temp->show_my_recipe();
	ostringstream recipes_list;
	recipes_list << "<div class=\"recipe\">"
		<< "<img src=\"" << temp_recipe->get_image_address() << "\" alt=\"Image recipe\" style=\"width: 100px; height: 100px; border-radius: 50px; margin: 10px;\">"
		<< "<span class=\"title_recipe\">#" << temp_recipe->get_id() + 1 << " : " << temp_recipe->get_name() << "</span>" << endl
		<< "<div class=\"detail\">" << "<p class=\"detail\">" << "rating: " << "</p>" << "<span class=\"detail\" >" << temp_recipe->get_rate_str() << "</span>" << "</div>" << endl
		<< "<div class=\"detail\">" << "<p class=\"detail\">" << "vegetarian: " << "</p>" << "<span class=\"detail\" >" << temp_recipe->get_vegeterian_state() << "</span>" << "</div>" << endl
		<< "<div class=\"detail\">" << "<p class=\"detail\">" << "ingredients: " << "</p>" << "<span class=\"detail\" >" << temp_recipe->get_ingredients() << "</span>" << "</div>" << endl
		<< "<div class=\"detail\">" << "<p class=\"detail\">" << "minutes to ready: " << "</p>" << "<span class=\"detail\" >" << temp_recipe->get_minutes_to_ready() << "</span>" << "</div>" << endl
		<< "<div class=\"detail\">" << "<p class=\"detail\">" << "tags: " << "</p>" << "<span class=\"detail\" >" << temp_recipe->get_tags() << "</span>" << "</div>" << endl;
	recipes_list << "<form method=\"POST\" action=\"/update_rate?Rid=" << temp_recipe->get_id() << "\">" << "<input type = \"text\" name=\"Rate\" class=\"detail\" value=\"" << temp_recipe->was_he_rated(username) << "\"></input>" << endl
		<< "<button class=\"delete_btn\" type=\"submit\">Update Rate </button>" << endl;
	recipes_list << "</div>" << endl;

	html = head + body + recipes_list.str() + "</body>" + "</html>";
	res->setBody(html);
	return res;
}

Response* UpdateRate::callback(Request* req)
{
	stringstream rid_str(req->getQueryParam("Rid"));
	int rid = -1;
	rid_str >> rid;
	Recipes* temp_recipe = Web_interface::find_recipe_by_rid(rid);
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	string username = active_person->get_name();
	stringstream rate_str(req->getBodyParam("Rate"));
	float rate = -1;
	rate_str >> rate;
	temp_recipe->set_rate(username, rate);
	string address_redirect = "/Recipe_page?Rid=" + req->getQueryParam("Rid");
	Response* res = Response::redirect(address_redirect);
	return res;
}

Response* ShelvesManagment::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string username = active_person->get_name();
	string html;
	string head;
	head = "<!DOCTYPE html>";
	head += "<html lang=\"en\">";
	head += "<head>";
	head += "<title>Ap Goodeat</title>";
	head += "<meta charset=\"UTF-8\">";
	head += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	head += "<style>*{color: #2c3544}#home{position: relative;left: 25%; display: inline;}#home{position: relative;left: 25%; display: inline;}.title{font-weight: bold;color: #43a6dd;font-size: 24px;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}button{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}.create_shelf{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 500px;position: relative;left: 25%;} #shelf_name{padding: 15px; border-bottom: 1px solid #2c3544; border-top: none; border-left: none; border-right: none;}body{background-color: #EFF2F6;padding: 25px;}#logout_link{text-decoration: none;font-weight: bold;position: relative;font-size: 18px;left: 50%;}#Hi{display: inline;position: relative;left: 25%;}.recipe{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 700px;position: relative;left: 25%;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}</style>";
	head += "</head>";
	string body;
	body = "<body>";
	body += "<div class=\"nav_bar\">";
	body += "<h1 id=\"Hi\">";
	body += "Hi " + username;
	body += "</h1>";
	body += "<a href=\"/logout\" id=\"logout_link\">Log Out</a></div>";
	body += "<a href=\"/\"id = \"home\"><button type=\"button\" class=\"btn\">home</button></a>";
	vector <Shelves*> list_shelves = Web_interface::find_shelves_by_username(username);
	ostringstream shelves_list;
	shelves_list << " <form class=\"create_shelf\" method=\"POST\" action=\"/create_shelf\"><p class=\"title\">Create shelf</p>"
		<< "<input id=\"shelf_name\" type=\"text\" name=\"shelf_name\" placeholder=\"Enter shelf name\"/><button type=\"submit\" class=\"create_btn\"> create </button></form>";
	if (list_shelves.size() > 0)
	{
		for (int shelf_counter = 0; shelf_counter < list_shelves.size(); shelf_counter++)
		{
			shelves_list << "<a href=\"shelf_page?Sid=" << list_shelves[shelf_counter]->get_id() << "\" style = \"text-decoration: none;\"><div class=\"recipe\">"
				<< "<span class=\"title_recipe\">#" << list_shelves[shelf_counter]->get_id() + 1 << " : " << list_shelves[shelf_counter]->get_name() << "</span>" << endl
				<< "</div>" << endl;
		}
	}
	html = head + body + shelves_list.str() + "</body>" + "</html>";
	res->setBody(html);
	return res;
}


Response* CreateShelf::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	string shelf_name = req->getBodyParam("shelf_name");
	Web_interface::create_shelves(shelf_name, active_person->get_name());
	Response* res = Response::redirect("/shelves");
	return res;
}


Response* ShelfPage::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	stringstream sid_str(req->getQueryParam("Sid"));
	int sid = -1;
	sid_str >> sid;
	Shelves* temp_shelf = Web_interface::find_shelf_by_id(sid);
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string username = active_person->get_name();
	string html;
	string head;
	head = "<!DOCTYPE html>";
	head += "<html lang=\"en\">";
	head += "<head>";
	head += "<title>Ap Goodeat</title>";
	head += "<meta charset=\"UTF-8\">";
	head += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	head += "<style>*{color: #2c3544}#home{position: relative;left: 25%; display: inline;}#home{position: relative;left: 25%; display: inline;}.title{font-weight: bold;color: #43a6dd;font-size: 24px;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}button{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}.create_shelf{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 500px;position: relative;left: 25%;} #Recipe_id{padding: 15px; border-bottom: 1px solid #2c3544; border-top: none; border-left: none; border-right: none;}body{background-color: #EFF2F6;padding: 25px;}#logout_link{text-decoration: none;font-weight: bold;position: relative;font-size: 18px;left: 50%;}#Hi{display: inline;position: relative;left: 25%;}.recipe{padding: 25px;background-color: white;border-radius: 16px;margin: 50px;align-items:center;width: 700px;position: relative;left: 25%;}span.title_recipe{font-weight: bold;color: #43a6dd;font-size: 24px;}p.detail{display: inline;margin: 25px;font-size: 16px;font-weight: bold;}div.detail{margin-top: 15px;}button.delete_btn{margin: 15px;background-color: #43a6dd;color: white;padding: 15px;border-radius: 12px;border: none;font-weight: bold;}</style>";
	head += "</head>";
	string body;
	body = "<body>";
	body += "<div class=\"nav_bar\">";
	body += "<h1 id=\"Hi\">";
	body += "Shelf " + temp_shelf->get_name();
	body += "</h1>";
	body += "<a href=\"/logout\" id=\"logout_link\">Log Out</a></div>";
	body += "<a href=\"/\"id = \"home\"><button type=\"button\" class=\"btn\">home</button></a>";
	vector <Recipes*> recipes = temp_shelf->get_recipe();
	ostringstream recipes_list;
	recipes_list << " <form class=\"create_shelf\" method=\"POST\" action=\"/add_recipe\"><p class=\"title\">add recipe</p>"
		<< "<input id=\"Recipe_id\" type=\"number\" name=\"Rid\" placeholder=\"Enter Recipe Id\"/> <input type=\"hidden\" value=\"" << sid << "\" name=\"sid\"/><button type=\"submit\" class=\"create_btn\"> Add </button></form>";
	if (recipes.size() > 0)
	{
		for (int recipe_counter = 0; recipe_counter < recipes.size(); recipe_counter++)
		{
			recipes_list << "<a style=\"text-decoration: none;\" href=\"/Recipe_page?Rid=" << recipes[recipe_counter]->get_id() << "\"><div class=\"recipe\">"
				<< "<span class=\"title_recipe\">#" << recipes[recipe_counter]->get_id() + 1 << " : " << recipes[recipe_counter]->get_name() << "</span>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "vegetarian: " << "</p>" << "<span class=\"detail\" >" << recipes[recipe_counter]->get_vegeterian_state() << "</span>" << "</div>" << endl
				<< "<div class=\"detail\">" << "<p class=\"detail\">" << "minutes to ready: " << "</p>" << "<span class=\"detail\" >" << recipes[recipe_counter]->get_minutes_to_ready() << "</span>" << "</div>" << endl
				<< "<a href=\"/remove_recipe?Rid=" << recipes[recipe_counter]->get_id() << "&sid=" << sid << "\"><button type=\"button\" class=\"delete_btn\"> Remove </button></a>" << endl
				<< "</div></a>" << endl;
		}
	}
	html = head + body + recipes_list.str() + "</body>" + "</html>";
	res->setBody(html);
	return res;
}

Response* AddRecipe::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	stringstream Rid_str(req->getBodyParam("Rid"));
	int rid = -1;
	Rid_str >> rid;
	rid--;
	Recipes* temp_recipe = Web_interface::find_recipe_by_rid(rid);
	stringstream sid_str(req->getBodyParam("sid"));
	int sid = -1;
	sid_str >> sid;
	Shelves* temp_shelf = Web_interface::find_shelf_by_id(sid);
	temp_shelf->add_recipe(temp_recipe);
	string redirect_address = "/shelf_page?sid=" + sid_str.str();
	Response* res = Response::redirect(redirect_address);
	return res;
}

Response* RemoveRecipe::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	cout << uid << endl;
	stringstream Rid_str(req->getQueryParam("Rid"));
	int rid = -1;
	Rid_str >> rid;
	Recipes* temp_recipe = Web_interface::find_recipe_by_rid(rid);
	cout << rid << endl;
	stringstream sid_str(req->getQueryParam("sid"));
	int sid = -1;
	sid_str >> sid;
	Shelves* temp_shelf = Web_interface::find_shelf_by_id(sid);
	temp_shelf->delete_recipe(temp_recipe->get_id());
	string redirect_address = "/shelf_page?sid=" + to_string(sid);
	Response* res = Response::redirect(redirect_address);
	return res;
}


Response* AddFilter::callback(Request* req)
{
	stringstream uid_str(req->getSessionId());
	int uid = -1;
	uid_str >> uid;
	Person* active_person = Web_interface::find_person_by_uid(uid);
	string vegeterian = req->getBodyParam("vegetarian");
	stringstream min_time_str(req->getBodyParam("min_time"));
	int min_time = -1;
	min_time_str >> min_time;
	stringstream max_time_str(req->getBodyParam("max_time"));
	int max_time = -1;
	max_time_str >> max_time;
	stringstream min_rate_str(req->getBodyParam("min_rate"));
	float min_rate = -1;
	min_rate_str >> min_rate;
	stringstream max_rate_str(req->getBodyParam("max_rate"));
	int max_rate = -1;
	max_rate_str >> max_rate;
	try
	{
		if (vegeterian != "0")
		{
			Web_interface::apply_veg_filter(vegeterian);
		}
		if (min_time != -1 && max_time != -1)
		{
			Web_interface::apply_time_filter(min_time, max_time);
		}
		if (min_rate != -1 && max_rate != -1)
		{
			Web_interface::apply_rate_filter(min_rate, max_rate);
		}
		Web_interface::state_filter = "Success to add filter";
		Response* res = Response::redirect("/");
		return res;
	}
	catch (const std::exception& e)
	{
		Web_interface::state_filter = "Failed to add filter";
		Response* res = Response::redirect("/");
		return res;
	}
}

Response* ClearFilter::callback(Request* req)
{
	Web_interface::state_filter = "";
	Web_interface::clear_filter();
	Response* res = Response::redirect("/");
	return res;
}