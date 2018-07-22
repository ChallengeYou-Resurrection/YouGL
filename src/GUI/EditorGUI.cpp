#include "EditorGUI.h"

EditorGUI::EditorGUI()
{
	bg.r = 1.0f, bg.g = 1.f, bg.b = 1.f, bg.a = 1.0f;
}

void EditorGUI::inputStart()
{
	nk_input_begin(ctx);
}

void EditorGUI::inputHandle(sf::Event& evt)
{
	nk_sfml_handle_event(&evt);
}

void EditorGUI::inputFinish()
{
	nk_input_end(ctx);
}

void EditorGUI::update(float deltaTime)
{
	if (nk_begin(ctx, "Wall", nk_rect(1000, 420, 230, 250),
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
		if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
			nk_layout_row_dynamic(ctx, 140, 1);
			bg = nk_color_picker(ctx, bg, NK_RGB);
			nk_layout_row_dynamic(ctx, 25, 1);
			bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
			bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
			bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
			nk_combo_end(ctx);
		}

		nk_layout_space_begin(ctx, NK_STATIC, 90, INT_MAX);
		nk_layout_space_push(ctx, nk_rect(30,60,150,20));
		if (nk_button_label(ctx, "Set as Default"))
			fprintf(stdout, "button pressed\n");
		nk_layout_space_end(ctx);
	}
	nk_end(ctx);
}