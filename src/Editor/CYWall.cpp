#include "CYWall.h"

CYWall::CYWall(const std::smatch& match_groups)
{
    std::ssub_match sub_match;

    // Start Position
    sub_match = match_groups[1];
    this->m_displacement_pos = sf::Vector2f(std::stof(sub_match.str()), 0);
    sub_match = match_groups[2];
    this->m_displacement_pos.y = std::stof(sub_match.str());

    // Displacement Position
    sub_match = match_groups[3];
    this->m_start_pos = sf::Vector2f(std::stof(sub_match.str()), 0);
    sub_match = match_groups[4];
    this->m_start_pos.y = std::stof(sub_match.str());

    // 5 = Colour, 6 = TextureID
    if (match_groups[5] != "")
        sub_match = match_groups[5];
    else
        sub_match = match_groups[6];
    std::cout << "Texture: " << sub_match.str() << std::endl;

    // 7 = Colour, 8 = TextureID
    if (match_groups[7] != "")
        sub_match = match_groups[7];
    else
        sub_match = match_groups[8];
    //std::cout << "Texture 2: " << sub_match.str() << std::endl;

    // If 10 doesn't exist then 9 = Level, else 9 = Z_Index
	int z_index, level;
    if (match_groups[10] != "") {
        sub_match = match_groups[9];    // Z_Index
		z_index = std::stoi(sub_match.str());

        sub_match = match_groups[10];   // Level
		level = std::stoi(sub_match.str());

    } else {
        sub_match = match_groups[9];    // Level
		level = std::stoi(sub_match.str());

		z_index = 1;
    }

	m_level = level;

	// Find mix and max heights from Z-Index (0 -> 1)
	switch (z_index)
	{
		case 2:  m_end_height = 3 / 4.f;  m_start_height = 0.f;		  break;
		case 3:  m_end_height = 2 / 4.f;  m_start_height = 0.f;		  break;
		case 4:  m_end_height = 1 / 4.f;  m_start_height = 0.f;		  break;

		case 5:  m_end_height =  2 / 4.f;  m_start_height =  1 / 4.f; break;
		case 6:  m_end_height =  3 / 4.f;  m_start_height =  2 / 4.f; break;
		case 7:  m_end_height =  4 / 4.f;  m_start_height =  3 / 4.f; break;

		case 8:  m_end_height =  4 / 4.f;  m_start_height =  2 / 4.f; break;
		case 9:  m_end_height =  4 / 4.f;  m_start_height =  1 / 4.f; break;
		case 10: m_end_height =  3 / 4.f;  m_start_height =  1 / 4.f; break;

		default: m_end_height =  4 / 4.f;  m_start_height = 0.f;	  break;
	}

    this->type = "WALL";
}

void CYWall::createModel() {
    Mesh mesh;
	glm::vec3 vertex[4];

	// Get geometric properties of the wall
	float min_height = (m_level + m_start_height) / 5.f;
	float max_height = (m_level + m_end_height)   / 5.f;
	glm::vec2 wall_origin = { m_start_pos.x, m_start_pos.y };
	glm::vec2 wall_finish = { m_start_pos.x + m_displacement_pos.x, m_start_pos.y + m_displacement_pos.y };

	// TODO : Make this a constant for all objects
	float WORLD_SIZE = 50.f;
    
	// Set the vertices of the wall using such properties
	vertex[1] = glm::vec3((wall_origin.x) / WORLD_SIZE, max_height, (wall_origin.y) / WORLD_SIZE);
	vertex[2] = glm::vec3((wall_finish.x) / WORLD_SIZE, max_height, (wall_finish.y) / WORLD_SIZE);
	vertex[3] = glm::vec3((wall_finish.x) / WORLD_SIZE, min_height, (wall_finish.y) / WORLD_SIZE);
	vertex[0] = glm::vec3((wall_origin.x) / WORLD_SIZE, min_height, (wall_origin.y) / WORLD_SIZE);

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
	for (int it = 0; it < 4; it++)
		mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });

	// default
    mesh.texCoords =
    {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };


    mesh.colour =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.7f
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
    jLevel[itemName]["end_POS"]["x"] = m_start_pos.x;
    jLevel[itemName]["end_POS"]["y"] = this->m_start_pos.y;

    jLevel[itemName]["DISP_POS"]["x"] = this->m_displacement_pos.x;
    jLevel[itemName]["DISP_POS"]["y"] = this->m_displacement_pos.y;

    jLevel[itemName]["LEVEL"] = this->m_level;

    return;
}
