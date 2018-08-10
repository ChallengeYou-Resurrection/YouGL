#include "EditorGUI.h"

EditorGUI::EditorGUI(u8* cFloor, CameraType* cType)
	: m_currentFloor(cFloor)
	, m_cameraType(cType)
{
	bg.r = 1.0f, bg.g = 1.f, bg.b = 1.f, bg.a = 1.0f;
}

void EditorGUI::update(float deltaTime)
{
	// Object Property Editor 
	if (nk_begin(ctx, "Wall", nk_rect(1020, 30, 230, 250),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		enum { EASY, HARD };
		static int op = EASY;
		static int property = 20;
		static int current_texture = 1;
		const char *textures[] = { "Grass","Wood","Bark","Brick","Happy" };

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, "Texture", NK_TEXT_LEFT);
		nk_layout_row_static(ctx, 25, 200, 1);
		current_texture = nk_combo(ctx, textures, NK_LEN(textures), current_texture, 25, nk_vec2(200, 200));

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, "Colour", NK_TEXT_LEFT);

		nk_layout_row_dynamic(ctx, 25, 1);
		nk_style_push_style_item(ctx, &ctx->style.scrollv.active, nk_style_item_hide());
		if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
			nk_layout_row_dynamic(ctx, 120, 1);
			bg = nk_color_picker(ctx, bg, NK_RGB);
			nk_layout_row_dynamic(ctx, 25, 1);
			bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
			bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
			bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
			nk_combo_end(ctx);
		}
		nk_style_pop_style_item(ctx);

		nk_layout_space_begin(ctx, NK_STATIC, 90, INT_MAX);
		nk_layout_space_push(ctx, nk_rect(30,60,150,20));
		if (nk_button_label(ctx, "Set as Default"))
			fprintf(stdout, "button pressed\n");
		nk_layout_space_end(ctx);
	}
	nk_end(ctx);

	// Floor Change (bottom right: 1070, 650)
	if (nk_begin(ctx, "Floor", nk_rect(1020-180-30, 30, 180, 37),
		NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
	{
		std::string floorText = "Floor: " + std::to_string(*m_currentFloor);

		nk_layout_row_begin(ctx, NK_STATIC, 25, 12);

		nk_layout_row_push(ctx, 25);
		if (nk_button_symbol(ctx, NK_SYMBOL_TRIANGLE_UP))
			(*m_currentFloor)++;

		nk_layout_row_push(ctx, 100);
		nk_label(ctx, floorText.c_str(), NK_TEXT_CENTERED);

		nk_layout_row_push(ctx, 25);
		if (nk_button_symbol(ctx, NK_SYMBOL_TRIANGLE_DOWN))
			(*m_currentFloor)--;

		nk_layout_row_end(ctx);
	}
	nk_end(ctx);

	// Editor View
	if (nk_begin(ctx, "View", nk_rect(30, 720-37-30, 120*3 + 25, 37),
		NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
	{
		CameraType currentType = *m_cameraType;

		nk_layout_row_begin(ctx, NK_STATIC,25,3);

		auto createButton = [&](CameraType cType, const std::string& buttonLabel) {
			nk_layout_row_push(ctx, 120);

			if (currentType == cType)
				nk_style_push_color(ctx, &ctx->style.button.border_color, nk_rgb(255, 255, 255));
			
			if (nk_button_label(ctx, buttonLabel.c_str())) {
				*m_cameraType = cType;
			}

			if (currentType == cType) nk_style_pop_color(ctx);
		};

		createButton(CameraType::GRID, "Grid View");
		createButton(CameraType::FREEROAM, "Freeroam");
		createButton(CameraType::PLAYER, "Player Mode");

		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
}