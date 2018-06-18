#include "WorldTextures.h"

void inline WorldTextures::setupMap()
{
	m_TextureMap.insert(std::make_pair(TextureID::Color,	WorldTex("Color",   "res/txrs/color256.jpg",		{ 2.f, 2.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Grass,	WorldTex("Grass",   "res/txrs/grass256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Stucco,	WorldTex("Stucco",  "res/txrs/stucco256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Brick,	WorldTex("Brick",   "res/txrs/brick256.jpg",		{ 2.5f, 2.666f })));
	m_TextureMap.insert(std::make_pair(TextureID::Stone,	WorldTex("Stone",   "res/txrs/stone256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Wood,		WorldTex("Wood",    "res/txrs/wood256.jpg",			{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Happy,	WorldTex("Happy",   "res/txrs/happy256.jpg",		{ 4.f, 4.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Egypt,	WorldTex("Egypt",   "res/txrs/egypt256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Bark,		WorldTex("Bark",	"res/txrs/bark256.jpg",			{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Scifi,	WorldTex("Sci-Fi",  "res/txrs/scifi256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Tile,		WorldTex("Tiles",   "res/txrs/tile256.jpg",			{ 4.f, 5.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Rock,		WorldTex("Rock",    "res/txrs/rock256.jpg",			{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Parquet,	WorldTex("Parquet", "res/txrs/parquet256.jpg",		{ 1.f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Books,	WorldTex("Books",   "res/txrs/bookshelf256.png",	{ 1.f, 1.333f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Bars,		WorldTex("Bars",	"res/txrs/bars256.png",			{ 3.5f, 1.f }	)));
	m_TextureMap.insert(std::make_pair(TextureID::Glass,	WorldTex("Glass",   "res/txrs/glass256.png",		{ 1.f, 1.f }	)));
};

WorldTextures::WorldTextures()
{
	std::cout << "Hello Textures\n";
	// Create the map used to reference texture information
	setupMap();

	// Create texture array
	glGenTextures(1, &textureArrayID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	// Set texture array parameters
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Setup array
	// OPENGL 4.2
	// glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RBGA, TEXTURE_WIDTH, TEXTURE_HEIGHT, 2 );

	// Data containing all the textures
	int image_size = 4 * TEXTURE_HEIGHT * TEXTURE_WIDTH;
	int total_size = m_TextureMap.size() * image_size;

	sf::Uint8* data = (sf::Uint8*)malloc(total_size);

	int textureCount = m_TextureMap.size();
	for (int tex = 0; tex < textureCount; tex++)
	{
		if (auto texture = this->loadTexture(m_TextureMap.at(static_cast<TextureID>(tex)).fileName))
		{
			std::cout << "Loaded texture: " << m_TextureMap.at(static_cast<TextureID>(tex)).fileName << "\n";
			memcpy(data + (tex*image_size), texture->getPixelsPtr(), image_size);
		}
		else {
			std::cout << "Could not load texture\n";
		}
	}

	// Generate the texture array
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, TEXTURE_WIDTH, TEXTURE_HEIGHT, textureCount,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

// Returns pointer to raw image data from a given file
std::optional<const sf::Image> 
    WorldTextures::loadTexture(const std::string& fileName)
{
	// Load from disk
	sf::Image img_data;
	if (!img_data.loadFromFile(fileName))
	{
		std::cout << "ERROR Loading texture " << fileName << "/n";
		return {};
	}

	// Manipulate image to fit with world
	img_data.flipHorizontally();
	img_data.flipVertically();

	// Return image
	return img_data;
}

TextureID WorldTextures::getWallTexture(int id)
{
	switch (id) // WALLS
	{
		case 1: return  TextureID::Brick;
		case 2: return  TextureID::Bars;
		case 3: return  TextureID::Stone;
		case 4: return  TextureID::Grass;
		case 5: return  TextureID::Wood;
		case 6: return  TextureID::Happy;
		case 7: return  TextureID::Egypt;
		case 8: return  TextureID::Glass;
		case 9: return  TextureID::Stucco;
		case 10: return TextureID::Bark;
		case 11: return TextureID::Scifi;
		case 12: return TextureID::Tile;
		case 13: return TextureID::Rock;
		case 14: return TextureID::Books;
		case 16: return TextureID::Parquet;

		default: return TextureID::Color;
	}
}

void WorldTextures::bindTextureArray()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->textureArrayID);
}

GLuint WorldTextures::getTexID()
{
	return this->textureArrayID;
}

const sf::Vector2f& WorldTextures::getTextureScale(TextureID tex) const
{
	return m_TextureMap.at(tex).texScale;
}
