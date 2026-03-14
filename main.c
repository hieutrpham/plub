#include "raylib.h"
#include "plug.h"
#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>

render_t render = NULL;

int main(void)
{
	char *libplug = "./libplug.so";
	void *lib = dlopen(libplug, RTLD_NOW);
	if (!lib)
		return fprintf(stderr, "%s\n", dlerror());
	render = dlsym(lib, "render");
    InitWindow(800, 600, "Raylib Template");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_R))
		{
			dlclose(lib);
			lib = dlopen(libplug, RTLD_NOW);
			if (!lib)
				return fprintf(stderr, "%s\n", dlerror());
			render = dlsym(lib, "render");
			if (!render)
				fprintf(stderr, "%s\n", dlerror());
		}
		render();
    }
    CloseWindow();
    return 0;
}
