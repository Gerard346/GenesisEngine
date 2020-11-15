#pragma once

#include "Globals.h"
#include "MathGeoLib/include/MathGeoLib.h"

struct json_array_t;
typedef json_array_t JSON_Array;

struct json_value_t;
typedef json_value_t JSON_Value;

struct json_object_t;
typedef json_object_t JSON_Object;

class GnJSONArray;

class GnJSONObj 
{
public:
	GnJSONObj();
	GnJSONObj(const char* buffer);
	GnJSONObj(JSON_Object* object);
	~GnJSONObj();

	JSON_Object* GetJSONObject();
	JSON_Value* GetValue();
	void Release();

	uint Save(char** buffer);

	JSON_Array* GetArray(const char* name);

	int GetInt(const char* name);
	float GetFloat(const char* name);
	bool GetBool(const char* name);
	const char* GetString(const char* name);
	math::float3 GetFloat3(const char* name);
	Quat GetQuaternion(const char* name);

	void AddInt(const char* name, int number);
	void AddFloat(const char* name, float number);
	void AddFloat3(const char* name, math::float3 number);
	void AddQuaternion(const char* name, math::Quat number);
	void AddBool(const char* name, bool boolean);
	void AddString(const char* name, const char* string);
	GnJSONArray AddArray(const char* name);
	GnJSONArray AddArray(GnJSONArray array);

private:
	JSON_Object* _object;
	JSON_Value* _root;
};

class GnJSONArray 
{
public:
	GnJSONArray();
	GnJSONArray(JSON_Array* array);
	GnJSONArray(JSON_Array* array, JSON_Object* root_object);
	GnJSONArray(const char* name);
	~GnJSONArray();

	int Size();
	GnJSONObj GetObjectInArray(const char* name);
	GnJSONObj GetObjectAt(int index);

	void AddObject(GnJSONObj& object);
	void AddInt(int number);
	void AddFloat(float number);
	void AddString(const char* string);

private: 
	JSON_Array* _array;
	JSON_Value* _value;
	bool _nested;
};
