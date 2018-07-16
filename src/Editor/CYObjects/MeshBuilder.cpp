#include "MeshBuilder.h"




/////////////
///  WALL  //
/////////////
namespace MeshBuilder
{
	WallHeight getWallGeometricHeight(const u8 zIndex)
	{
		float bottomHeight = 0.0f;
		float topHeight = 1.0f;

		switch (zIndex) {
		case 2:  topHeight = 3 / 4.0f;  bottomHeight = 0.0f; break;
		case 3:  topHeight = 2 / 4.0f;  bottomHeight = 0.0f; break;
		case 4:  topHeight = 1 / 4.0f;  bottomHeight = 0.0f; break;

		case 5:  topHeight = 2 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		case 6:  topHeight = 3 / 4.0f;  bottomHeight = 2 / 4.0f; break;
		case 7:  topHeight = 4 / 4.0f;  bottomHeight = 3 / 4.0f; break;

		case 8:  topHeight = 4 / 4.0f;  bottomHeight = 2 / 4.0f; break;
		case 9:  topHeight = 4 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		case 10: topHeight = 3 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		default: topHeight = 4 / 4.0f;  bottomHeight = 0.0f; break;
		}
		return {
			bottomHeight, topHeight
		};
	}

	float getPlatGeometricHeight(const u8 zIndex)
	{
		// Plat is offseted by a small amount so it doesn't z-fight with the terrain
		return ((zIndex - 1.f) / 4) + 0.001f;
	}

	short getPlatGeometricSize(const u8 size)
	{
		switch (size)
		{
		case 1:	 return 10; 
		case 2:  return 20; 
		case 3:  return 40; 
		case 4:  return 80; 
		default: return size * 10;
		}
	}

	// Mesh Building
	void addQuadToMesh(Mesh& mesh, const std::array<glm::vec3, 4>& vertices, 
		const Property::Material& mat, const WorldTextures& wTex)
	{
		// Create normal
		glm::vec3 normal = glm::cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);

		//Add Vertices
		mesh.vertices.insert(mesh.vertices.end(), { vertices[0].x, vertices[0].y, vertices[0].z });
		mesh.vertices.insert(mesh.vertices.end(), { vertices[3].x, vertices[3].y, vertices[3].z });
		mesh.vertices.insert(mesh.vertices.end(), { vertices[2].x, vertices[2].y, vertices[2].z });
		mesh.vertices.insert(mesh.vertices.end(), { vertices[1].x, vertices[1].y, vertices[1].z });

		//Normals
		for (int i = 0; i < 4; i++) {
			mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });
		}

		//Colours
		for (int i = 0; i < 4; i++) {
			mesh.colour.insert(mesh.colour.end(), {
				(float)mat.colour.r / 255.0f,
				(float)mat.colour.g / 255.0f,
				(float)mat.colour.b / 255.0f
				});
		}

		// Add new indices
		unsigned int max_index = -1;
		if (mesh.indices.size() > 0)
			max_index = *std::max_element(mesh.indices.begin(), mesh.indices.end());
		
		mesh.indices.insert(mesh.indices.end(), {max_index + 1, max_index + 2, max_index + 4, 
			max_index + 2, max_index + 3, max_index + 4 });
	}
}
