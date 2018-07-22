#include "DebugLogGUI.h"

DebugLogGUI::DebugLogGUI()
{}

void DebugLogGUI::update(float deltaTime)
{
	// Calculate the average FPS
	// Gather the most recent frame counts
	fps_avg.push_front(1 / deltaTime);
	if (fps_avg.size() > FPS_MOVING_AVERAGE)
		fps_avg.pop_back();

	// Find the mean of all recent frame counts
	float fps = 0;
	for (float f : fps_avg)
		fps += f;
	fps /= fps_avg.size();

	// Display the FPS
	std::string fps_string = "FPS: " + std::to_string(fps);

	nk_style_push_color(ctx, &ctx->style.window.background, nk_rgb(255, 25, 255));
	nk_style_push_style_item(ctx, &ctx->style.window.fixed_background, nk_style_item_color(nk_rgba(0, 0, 0, 0)));
	if (nk_begin(ctx, "Debug", nk_rect(0, 0, 300, 200),
		NK_WINDOW_NO_INPUT | NK_WINDOW_BACKGROUND))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, fps_string.c_str(), NK_TEXT_LEFT);
	}
	nk_style_pop_color(ctx);
	nk_style_pop_style_item(ctx);
	nk_end(ctx);
}