#pragma once
#include "Globals.h"
#include <string>

class GameObject;
class GnJSONObj;
class GnJSONArray;
class Resource;
enum ResourceType;

enum ComponentType {
	TRANSFORM,
	MESH,
	MATERIAL, 
	CAMERA, 
	LIGHT,
	CANVAS,
	IMAGE,
	TEXT,
	BUTTON,
	CHECKBOX,
	RECT_TRANSFORM
};

class Component {
public: 
	Component();
	Component(GameObject* gameObject);
	virtual ~Component();
	virtual void Update();
	virtual void Enable();
	virtual void Disable();

	virtual void Save(GnJSONArray& save_array) {};
	virtual void Load(GnJSONObj& load_object) {};

	bool IsEnabled();
	ComponentType GetType();
	virtual void OnEditor() = 0;

	void SetGameObject(GameObject* gameObject);
	GameObject* GetGameObject();
	virtual void SetResourceUID(uint UID);
	virtual Resource* GetResource(ResourceType type) { return nullptr; };

	bool GetIsUI();

public:
	std::string name;

protected:
	ComponentType type;
	bool is_UI = false;
	GameObject* _gameObject;
	bool enabled;

	uint _resourceUID;
};
