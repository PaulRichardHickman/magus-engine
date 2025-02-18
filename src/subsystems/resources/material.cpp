#include "material.h"

namespace MagusEngine
{
	Material::Material()
	{
		strcpy(_name, "UNKNOWN");

		_color1 = 0;
		_color2 = 0;
		_texture = 0;

		_enableFill = true; 
		_enableStroke = false;
	}

	Material::Material(const char* name)
	{
		strcpy(_name, name);

		_color1 = 0;
		_color2 = 0;
		_texture = 0;

		_enableFill = true;
		_enableStroke = false;
	}


	Material::Material(Material* other)
	{
		strcpy(_name, other->GetName());

		_color1 = other->GetColor1();
		_color2 = other->GetColor2();
		_texture = other->GetTexture();
		_enableFill = other->GetEnabledFill();
		_enableStroke = other->GetEnabledStroke();
	}

	/* Getters */
	char*		Material::GetName() { return _name; }
	Color*		Material::GetColor1() { return _color1; }
	Color*		Material::GetColor2() { return _color2; }
	Texture*	Material::GetTexture() { return _texture; }
	bool		Material::GetEnabledFill() { return _enableFill; }
	bool		Material::GetEnabledStroke() { return _enableStroke; }

		
	/* Setters */
	void Material::SetColor1(Color* color) { _color1 = color; }
	void Material::SetColor2(Color* color) { _color2 = color; }
	void Material::SetTexture(Texture* texture) { _texture = texture; }
	void Material::SetEnabledFill(bool fill) { _enableFill = fill; }
	void Material::SetEnabledStroke(bool stroke) { _enableStroke = stroke; }

}