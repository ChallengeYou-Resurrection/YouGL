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
    if (match_groups[10] != "") {
        sub_match = match_groups[9];    // Z_Index
        sub_match = match_groups[10];   // Level
    } else {
        sub_match = match_groups[9];    // Level
    }

    this->type = "WALL";
}

void CYWall::createModel() {
    Mesh mesh;

    /*mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x                         ), 1, (m_start_pos.y                        )});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x + m_displacement_pos.x  ), 1, (m_start_pos.y + m_displacement_pos.y )});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x + m_displacement_pos.x  ), 0, (m_start_pos.y + m_displacement_pos.y )});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x                         ), 0, (m_start_pos.y                        )});
    */

    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x                         ) / 50.f,  0.5f, (m_start_pos.y                            ) / 50.f});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x + m_displacement_pos.x  ) / 50.f,  0.5f, (m_start_pos.y + m_displacement_pos.y     ) / 50.f});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x + m_displacement_pos.x  ) / 50.f, -0.5f, (m_start_pos.y + m_displacement_pos.y ) / 50.f});
    mesh.vertices.insert(mesh.vertices.end(), {(m_start_pos.x                         ) / 50.f, -0.5f, (m_start_pos.y                        ) / 50.f});

    mesh.indices = {0, 3, 1, 1, 2, 3};

    mesh.texCoords =
    {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    mesh.normals =
    {
        1.0f, 1.0f, 1.0f,
        0.5f, 0.6f, 0.7f,
        0.7f, 0.5f, 0.3f,
        1.0f, 0.5f, 0.5f
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
    // Add in the properties to JSON
    jLevel["WALL"]["START_POS"]["x"] = m_start_pos.x;
    jLevel["WALL"]["START_POS"]["y"] = this->m_start_pos.y;

    jLevel["WALL"]["DISP_POS"]["x"] = this->m_displacement_pos.x;
    jLevel["WALL"]["DISP_POS"]["y"] = this->m_displacement_pos.y;

    jLevel["WALL"]["LEVEL"] = this->m_level;

    return;
}
