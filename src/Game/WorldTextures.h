#pragma once

#include <glad.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>
#include <memory>

const int TEXTURE_WIDTH = 256;
const int TEXTURE_HEIGHT = 256;

enum class TextureID : uint8_t
{
	// Normal Textures
	Color = 0,
	Grass = 1,
	Stucco = 2,
	Brick = 3,
	Stone = 4,
	Wood = 5,
	Happy = 6,
	Egypt = 7,
	Bark = 8,
	Scifi = 9,
	Tile = 10,
	Rock = 11,
	Parquet = 12,
	Books = 13,

	// Translucent Textures
	Bars = 14,
	Glass = 15,
};

struct WorldTex
{
	std::string name;
	std::string fileName;

	sf::Vector2f texScale;

	WorldTex(const std::string& name, const std::string& fileName,
		const sf::Vector2f& texScale) {
		this->name = name;
		this->fileName = fileName;
		this->texScale = texScale;
	}
};

class WorldTextures
{
public:
	WorldTextures();

	void bindTextureArray();
	GLuint getTexID();

	static TextureID getWallTexture(int id);

	const sf::Vector2f& getTextureScale(TextureID tex) const;

private:
	GLuint textureArrayID;

	std::map<TextureID, WorldTex> m_TextureMap;
	void inline setupMap();

	std::optional<const sf::Image>
		loadTexture(const std::string& fileName);
};

