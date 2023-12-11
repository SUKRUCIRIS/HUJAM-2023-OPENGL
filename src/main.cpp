#include "./core/core.h"
#include "./game/intro.h"
#include "./game/mainmenu.h"

int main(void)
{
	GLFWwindow *window = create_window(0, 0, 1, 1, 4);
	if (window == 0)
	{
		return -1;
	}

	init_programs();

	intro(window);
	mainmenu(window);

	destroy_programs();
	delete_window(window);

	return 0;
}