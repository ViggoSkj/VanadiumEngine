#include "Core.h"

int main()
{
	Application app(Vanadium::WindowOptions(1600, 1000, 3));

	app.Run();

	return 0;
}