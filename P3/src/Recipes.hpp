#ifndef recipe_hpp_
#define recipe_hpp_
#include "general.hpp"
struct Rates
{
	string name;
	float rate;
};
class Recipes
{
public:
	Recipes(int _id, string _title, string list_ingredients, string _vegetarian, int _minutes_to_ready, string list_tag, string image_address);
	string abstract_info();
	string info();
	bool is_it_my_id(int input_id);
	string get_name();
	void set_rate(string name, float input_rate);
	void change_rate(string name, float input_rate);
	float was_he_rated(string name);
	void update_rate();
	float get_rate();
	bool has_been_rated();
	string get_rate_str();
	string ingredients_item(string ingredient);
	bool am_i_vegetarian();
	bool am_i_have_a_this_tag(string tag);
	bool am_i_in_time(float min, float max);
	bool am_i_in_this_rate(float min, float max);
	void change_visibility(bool visibility);
	bool can_i_show();
	//........
	int get_id();
	string get_vegeterian_state();
	int get_minutes_to_ready();
	string get_ingredients();
	string get_tags();
	string get_image_address();
private:
	vector <string> spreate_ingredients(string ingredient);
	vector <string> spreate_tags(string tags);
	int id;
	string title;
	string is_it_veg;
	bool is_vegeterian;
	int minutes_to_ready;
	vector <string> ingredients;
	vector <string> tags;
	string image_address;
	float rates;
	vector <struct Rates> detail_rated;
	bool is_rated;
	bool visible;
};

#endif // recipe_hpp_
