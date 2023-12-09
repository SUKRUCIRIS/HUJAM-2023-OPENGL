#include "./core/core.h"
#include "./game/prepare_drink.h"

int main(void)
{
	GLFWwindow *window = create_window(0, 0, 1, 1, 4);
	if (window == 0)
	{
		return -1;
	}

	init_programs();

	prepare_drink_scene(window);

	destroy_programs();
	delete_window(window);

	return 0;
}