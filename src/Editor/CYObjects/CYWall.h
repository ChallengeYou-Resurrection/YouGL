#pragma once

#include "CYGeneric.h"
#include "MeshBuilder.h"
#include "../OldFormat/OldFormatExtractor.h"

class CYWall : virtual public CYGeneric
{
public:
	// Create wall from OldFormat/Regex loader
	CYWall(std::smatch& matchGroups);

	virtual void createMesh(const WorldTextures& wTex);

	virtual Mesh& getMesh();
	virtual MinBoundingBox& getAABB();

	// For serializing
	template <typename Archive>
	void serialize(Archive& archive)
	{
		archive(floor, startPosition, endPosition,
			frontMaterial, backMaterial, height);
	}

protected:
	CYObject type = CYObject::CYWall;

private:
	Property::Position startPosition;
	Property::Position endPosition;

	Property::Material frontMaterial;
	Property::Material backMaterial;

	u8 floor;
	u8 height;
};

