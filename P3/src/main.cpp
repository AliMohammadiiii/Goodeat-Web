#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
	srand(time(NULL)); // for rand
	try {
		MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
		server.setNotFoundErrPage("static/404.html");
		server.get("/login", new ShowPage("template/login.html"));
		server.get("/login_inc", new ShowPage("template/login_inc.html"));
		server.post("/login", new LoginHandler());
		server.get("/logout", new LogOut());
		server.get("/", new MainPageHandler());
		server.get("/Recipe_page", new Recipe_page());
		server.post("/update_rate", new UpdateRate());
		server.get("/shelves", new ShelvesManagment());
		server.get("/shelf_page", new ShelfPage());
		server.get("/delete_filter", new ClearFilter());
		server.post("/create_shelf", new CreateShelf());
		server.post("/add_recipe", new AddRecipe());
		server.post("/add_filter", new AddFilter());
		server.get("/signup", new ShowPage("template/signup.html"));
		server.get("/signup_inc", new ShowPage("template/signup_incorect.html"));
		server.get("/create_recipe", new ShowPage("template/create_recipe.html"));
		server.post("/create_recipe", new CreateRecipe());
		server.get("/delete_recipe", new DeleteRecipe());
		server.post("/add_user", new AddUser());
		server.run();
	}
	catch (Server::Exception e) {
		cerr << e.getMessage() << endl;
	}
	catch (runtime_error& error)
	{
		cout << error.what() << endl;
	}
}
