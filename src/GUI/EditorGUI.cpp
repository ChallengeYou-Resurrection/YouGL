#include "EditorGUI.h"

EditorGUI::EditorGUI(sf::RenderWindow& win)
{
	ctx = nk_sfml_init(&win);

	struct nk_font_atlas *atlas;
	nk_sfml_font_stash_begin(&atlas);
	nk_sfml_font_stash_end();
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

void EditorGUI::update()
{
	struct nk_colorf bg;
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
	if (nk_begin(ctx, "Wall", nk_rect(50, 50, 230, 250),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		enum { EASY, HARD };
		static int op = EASY;
		static int property = 20;
		

		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
		if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, "Wall colour:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 25, 1);
		if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
			nk_layout_row_dynamic(ctx, 120, 1);
			bg = nk_color_picker(ctx, bg, NK_RGBA);
			nk_layout_row_dynamic(ctx, 25, 1);
			bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
			bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
			bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
			bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
			nk_combo_end(ctx);
		}

		nk_layout_row_static(ctx, 40, 130, 1);
		if (nk_button_label(ctx, "Set as Default"))
			fprintf(stdout, "button pressed\n");
	}
	nk_end(ctx);
}

void EditorGUI::render() const
{
	nk_sfml_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}