#include <raylib.h>
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderer.c"

void HandleClayErrors(Clay_ErrorData error)
{
	printf("%s", error.errorText.chars);
	exit(1);
}

Clay_RenderCommandArray CreateLayout(void)
{
	Clay_BeginLayout();
	CLAY({.id = CLAY_ID("Container"),
	      .backgroundColor = {0, 0, 0, 255},
	      .layout = {.padding = {1, 24, 0, 24}}})
	{
		CLAY_TEXT(
			CLAY_STRING("Hello World"),
			CLAY_TEXT_CONFIG({.fontId = 0,
					  .fontSize = 64,
					  .textColor = {255, 255, 255, 255}}));
	}
	return Clay_EndLayout();
}

void UpdateDrawFrame(Font *fonts)
{
	Clay_RenderCommandArray render_commands = CreateLayout();
	BeginDrawing();
	ClearBackground(DARKGRAY);
	Clay_Raylib_Render(render_commands, fonts);
	EndDrawing();
}

int main(void)
{
	uint64_t total_memory_size = Clay_MinMemorySize();
	Clay_Arena clay_memory = Clay_CreateArenaWithCapacityAndMemory(
		total_memory_size, malloc(total_memory_size));

	Clay_Initialize(clay_memory,
			(Clay_Dimensions){(float)GetScreenWidth(),
					  (float)GetScreenHeight()},
			(Clay_ErrorHandler){HandleClayErrors, 0});

	Clay_Raylib_Initialize(1024, 768, "Clay - Example",
			       FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE |
				       FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

	Font fonts[1];
	fonts[0] = LoadFontEx("assets/Roboto-Regular.ttf", 32, 0, 400);
	SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
	Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

	while (!WindowShouldClose())
	{
		UpdateDrawFrame(fonts);
	}
	return 0;
}
