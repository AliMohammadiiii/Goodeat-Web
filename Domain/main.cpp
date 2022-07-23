#include "Interface.hpp"

int main()
{
	Command_Interface* new_interface = new Command_Interface();
	new_interface->work();
	delete new_interface;
	return 0;
}