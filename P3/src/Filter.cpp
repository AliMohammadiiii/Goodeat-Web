#include "Filter.hpp"
Filter::Filter(Recipes* _recipe)
{
	can_i_show_tag = true;
	can_i_show_vegetarian = true;
	can_i_show_minutes = true;
	can_i_show_rating = true;
	recipe = _recipe;
}
void Filter::reseat_filter()
{
	can_i_show_tag = true;
	can_i_show_vegetarian = true;
	can_i_show_minutes = true;
	can_i_show_rating = true;
	update_rate();
}
void Filter::update_rate()
{
	if (can_i_show_tag && can_i_show_vegetarian && can_i_show_minutes && can_i_show_rating)
	{
		recipe->change_visibility(true);
	}
	else
	{
		recipe->change_visibility(false);
	}
}
void Filter::add_filter_tag(string tag)
{
	if (recipe->am_i_have_a_this_tag(tag))
	{
		can_i_show_tag = true;
	}
	else
	{
		can_i_show_tag = false;
	}
	update_rate();
}
void Filter::add_filter_vegetarian(bool state)
{
	if (recipe->am_i_vegetarian() == state)
	{
		can_i_show_vegetarian = true;
	}
	else
	{
		can_i_show_vegetarian = false;
	}
	update_rate();
}
void Filter::add_filter_time(float min, float max)
{
	if (recipe->am_i_in_time(min, max))
	{
		can_i_show_minutes = true;
	}
	else
	{
		can_i_show_minutes = false;
	}
	update_rate();
}
void Filter::add_filter_rate(float min, float max)
{
	if (recipe->am_i_in_this_rate(min, max))
	{
		can_i_show_rating = true;
	}
	else
	{
		can_i_show_rating = false;
	}
	update_rate();
}
