#ifndef filter_hpp_
#define filter_hpp_
#include "general.hpp"
#include "Recipes.hpp"
class Filter
{
public:
	Filter(Recipes* _recipe);
	void add_filter_tag(string tag);
	void add_filter_vegetarian();
	void add_filter_time(float min, float max);
	void add_filter_rate(float min, float max);
	void update_rate();
	void reseat_filter();
private:
	bool can_i_show_tag;
	bool can_i_show_vegetarian;
	bool can_i_show_minutes;
	bool can_i_show_rating;
	Recipes* recipe;
};
#endif // !filter_hpp_
