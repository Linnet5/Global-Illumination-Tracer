#pragma once
class Material
{	
public:
	float reflectance;

	Material();
	Material(float inReflectance);
	void setReflectance(float inReflectance);
};

