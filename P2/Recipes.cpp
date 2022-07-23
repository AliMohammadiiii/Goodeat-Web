#include "Recipes.hpp"
Recipes::Recipes(int _id, string _title, string list_ingredients, string _vegetarian, int _minutes_to_ready, string list_tag, string _image_address)
{
	id = _id;
	visible = true;
	is_rated = false;
	title = _title;
	is_it_veg = _vegetarian;
	minutes_to_ready = _minutes_to_ready;
	image_address = _image_address;
	ingredients = spreate_ingredients(list_ingredients);
	tags = spreate_tags(list_tag);
	if (is_it_veg == "Yes")
	{
		is_vegeterian = true;
	}
	else
	{
		is_vegeterian = false;
	}
	rates = 0;
}
vector<string> Recipes::get_ingredients()
{
	return ingredients;
}
bool Recipes::can_i_show()
{
	return visible;
}
vector <string> Recipes::spreate_ingredients(string ingredient)
{
	stringstream spreated_ingredients(ingredient);
	string temp_ingredient;
	vector <string> list_ingredients;

	while (getline(spreated_ingredients, temp_ingredient, SEPARATOR))
	{
		list_ingredients.push_back(temp_ingredient);
	}
	return list_ingredients;
}
vector <string> Recipes::spreate_tags(string tags)
{
	stringstream spreated_tags(tags);
	string temp_tags;
	vector <string> list_tags;

	while (getline(spreated_tags, temp_tags, SEPARATOR))
	{
		list_tags.push_back(temp_tags);
	}
	return list_tags;
}
bool Recipes::has_been_rated()
{
	return is_rated;
}
string Recipes::abstract_info()
{
	return to_string(id) + ' ' + title + ' ' + is_it_veg + ' ' + to_string(minutes_to_ready);
}
string Recipes::ingredients_item(string ingredient)
{
	return ingredient + ", ";
}
string Recipes::get_rate_str()
{
	string rate;
	string str_rates = to_string(ceil(rates * 10) / 10);
	str_rates = str_rates.substr(0, 3);
	rate = str_rates + '\n';
	return rate;
}
string Recipes::info()
{
	string info;
	info += to_string(id) + '\n';
	info += title + '\n';
	info += "vegetarian: " + is_it_veg + '\n' + "ingredients: [";
	int ingredients_size = (int)ingredients.size();
	for (int ingredients_curser = 0; ingredients_curser < ingredients_size; ingredients_curser++)
	{
		info += ingredients[ingredients_curser];
		info += ", ";
	}
	int size_info = info.length();
	info = info.substr(0, size_info - 2);
	info += "]\nminutes to ready: " + to_string(minutes_to_ready) + '\n' + "tags: [";
	int tags_size = (int)tags.size();
	for (unsigned int tags_curser = 0; tags_curser < tags_size; tags_curser++)
	{
		info += tags[tags_curser];
		info += ", ";
	}
	size_info = info.length();
	info = info.substr(0, size_info - 2);
	info += "]\n";
	info += "rating: ";
	info += get_rate_str();
	return info;
}
bool Recipes::is_it_my_id(int input_id)
{
	return (id == input_id);
}
string Recipes::get_name()
{
	return title;
}
void Recipes::update_rate()
{
	float sum = 0;
	for (unsigned int rate_courser = 0; rate_courser < detail_rated.size(); rate_courser++)
	{
		sum += detail_rated[rate_courser].rate;
	}
	rates = sum / detail_rated.size();
}
int Recipes::was_he_rated(string name)
{
	unsigned int rate_counter = 0;
	for (rate_counter = 0; rate_counter < detail_rated.size(); rate_counter++)
	{
		if (detail_rated[rate_counter].name == name)
		{
			return rate_counter;
		}
	}
	return -1;
}
void Recipes::set_rate(string name, float input_rate)
{
	is_rated = true;
	int rate_counter = was_he_rated(name);
	if (rate_counter != -1)
	{
		throw runtime_error(BAD_REQUEST);
	}
	struct Rates new_rate;
	new_rate.name = name;
	new_rate.rate = input_rate;
	detail_rated.push_back(new_rate);
}
void Recipes::change_rate(string name, float input_rate)
{
	int rate_counter = was_he_rated(name);
	if (rate_counter == -1)
	{
		throw runtime_error(BAD_REQUEST);
	}
	else
	{
		detail_rated[rate_counter].rate = input_rate;
	}
}
void Recipes::change_visibility(bool visibility)
{
	visible = visibility;
}
bool Recipes::am_i_vegetarian()
{
	if (is_vegeterian)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Recipes::am_i_have_a_this_tag(string tag)
{
	for (int tag_cursur = 0; tag_cursur < tags.size(); tag_cursur++)
	{
		if (tags[tag_cursur] == tag)
		{
			return true;
		}
	}
	return false;
}
bool Recipes::am_i_in_this_rate(float min, float max)
{
	if (rates > max || rates < min)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Recipes::am_i_in_time(float min, float max)
{
	if (minutes_to_ready > max || minutes_to_ready < min)
	{
		return false;
	}
	else
	{
		return true;
	}
}
float Recipes::get_rate()
{
	return rates;
}