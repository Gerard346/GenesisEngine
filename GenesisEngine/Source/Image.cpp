#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "GnJSON.h"
#include "Image.h"
#include "ResourceTexture.h"

Image::Image()
{
	type = ComponentType::IMAGE;
	is_UI = true;
}

Image::Image(GameObject* gameObject)
{
	type = ComponentType::IMAGE;
	is_UI = true;
}

Image::~Image()
{
}

void Image::Update()
{
}

void Image::OnEditor()
{
}

void Image::Save(GnJSONArray& save_array)
{
}

void Image::Load(GnJSONObj& load_object)
{
}

void Image::ChangeImage(uint new_image)
{
	image->SetUID(new_image);
}

uint Image::GetImageID() const
{
	if (image != nullptr) {
		return image->GetID();
	}
	else {
		return -1;
	}
}
