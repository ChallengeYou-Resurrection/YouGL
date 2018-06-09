#include "CYWall.h"

CYWall::CYWall(const std::smatch& matchGroups)
{
    std::ssub_match subMatch;

    // Start Position
    subMatch = matchGroups[1];
    this->m_displacementPosition = sf::Vector2f(std::stof(subMatch.str()), 0);
    subMatch = matchGroups[2];
    this->m_displacementPosition.y = std::stof(subMatch.str());

    // Displacement Position
    subMatch = matchGroups[3];
    this->m_startPosition = sf::Vector2f(std::stof(subMatch.str()), 0);
    subMatch = matchGroups[4];
    this->m_startPosition.y = std::stof(subMatch.str());
  
    // 5 = Colour, 6 = TextureID (Front side)
	if (matchGroups[5] != "") {
		// Default colour texture
		m_frontMaterial.texture_id = 0;

		subMatch = matchGroups[5];
		m_frontMaterial.colour = stringToColor(subMatch.str());
	} else {
		sub_match = matchGroups[6];
		m_frontMaterial.textureId = 0;

		m_frontMaterial.colour = { 1.0f, 1.0f, 1.0f };
	}


    // 7 = Colour, 8 = TextureID
    if (matchGroups[7] != "")
        subMatch = matchGroups[7];
    else
        subMatch = matchGroups[8];
    //std::cout << "Texture 2: " << subMatch.str() << std::endl;

    // If 10 doesn't exist then 9 = Level, else 9 = Z_Index
	int z_index, level;
    if (matchGroups[10] != "") {
        subMatch = matchGroups[9];    // Z_Index
		z_index = std::stoi(subMatch.str());

        subMatch = matchGroups[10];   // Level
		level = std::stoi(subMatch.str());

    } else {
        subMatch = matchGroups[9];    // Level
		level = std::stoi(subMatch.str());

		z_index = 1;
    }

	m_level = level;

	// Find mix and max heights from Z-Index (0 -> 1)
	switch (z_index) {
		case 2:  m_endHeight = 3 / 4.f;  m_startHeight = 0.f; break;
		case 3:  m_endHeight = 2 / 4.f;  m_startHeight = 0.f; break;
		case 4:  m_endHeight = 1 / 4.f;  m_startHeight = 0.f; break;

		case 5:  m_endHeight =  2 / 4.f;  m_startHeight =  1 / 4.f; break;
		case 6:  m_endHeight =  3 / 4.f;  m_startHeight =  2 / 4.f; break;
		case 7:  m_endHeight =  4 / 4.f;  m_startHeight =  3 / 4.f; break;

		case 8:  m_endHeight =  4 / 4.f;  m_startHeight =  2 / 4.f; break;
		case 9:  m_endHeight =  4 / 4.f;  m_startHeight =  1 / 4.f; break;
		case 10: m_endHeight =  3 / 4.f;  m_startHeight =  1 / 4.f; break;

		default: m_endHeight =  4 / 4.f;  m_startHeight = 0.f;	  break;
	}

    this->type = "WALL";
}


void CYWall::createModel() {
	// TODO : Make this a constant for all objects
	float WORLD_SIZE = 50.f;
	float WORLD_HEIGHT = 2.5f;


    Mesh mesh;
	glm::vec3 vertex[4];

	// Get geometric properties of the wall
	float minHeight = (m_level + m_startHeight) / WORLD_HEIGHT;
	float maxHeight = (m_level + m_endHeight)   / WORLD_HEIGHT;
	glm::vec2 wallOrigin = { m_startPosition.x, m_start_pos.y };
	glm::vec2 wallFinish = { m_startPosition.x + m_displacementPosition.x, m_startPosition.y + m_displacementPosition.y };
    
	// Set the vertices of the wall using such properties
	vertex[1] = glm::vec3((wallOrigin.x) / WORLD_SIZE, maxHeight, (wallOrigin.y) / WORLD_SIZE);
	vertex[2] = glm::vec3((wallFinish.x) / WORLD_SIZE, maxHeight, (wallFinish.y) / WORLD_SIZE);
	vertex[3] = glm::vec3((wallFinish.x) / WORLD_SIZE, minHeight, (wallFinish.y) / WORLD_SIZE);
	vertex[0] = glm::vec3((wallOrigin.x) / WORLD_SIZE, minHeight, (wallOrigin.y) / WORLD_SIZE);

	// Use the cross product to determine the normal
	glm::vec3 normal = glm::cross(vertex[2] - vertex[1], vertex[3] - vertex[1]);

	// Reduce the need for duplicated vertices by using indices
    mesh.indices = {0, 3, 1, 1, 2, 3};

	// Add the calculated 3d properties into the mesh for constructing
	// Vertices
	mesh.vertices.insert(mesh.vertices.end(), { vertex[1].x, vertex[1].y, vertex[1].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertex[2].x, vertex[2].y, vertex[2].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertex[3].x, vertex[3].y, vertex[3].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertex[0].x, vertex[0].y, vertex[0].z });

	// Normals
	for (int i = 0; i < 4; i++)
		mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });

	// Colors
	for (int i = 0; i < 4; i++)
		mesh.colour.insert(mesh.colour.end(), { m_front_mat.mat_color[0], 
			m_front_mat.mat_color[1],
			m_front_mat.mat_color[2] });

	// default
    mesh.texCoords =
    {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };



    m_geometry.create(mesh);
}

void CYWall::render(Renderer& renderer)
{
    renderer.draw(m_geometry);
}

void CYWall::toJsonFormat(json& jLevel, int id)
{
    std::string itemName = "WALL_" + std::to_string(id);

    // Add in the properties to JSON
    jLevel[itemName]["end_POS"]["x"] = m_startPosition.x;
    jLevel[itemName]["end_POS"]["y"] = this->m_startPosition.y;

    jLevel[itemName]["DISP_POS"]["x"] = this->m_displacementPosition.x;
    jLevel[itemName]["DISP_POS"]["y"] = this->m_displacementPosition.y;

    jLevel[itemName]["LEVEL"] = this->m_level;

    return;
}
