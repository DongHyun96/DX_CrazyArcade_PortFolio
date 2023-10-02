#include "Framework.h"
#include "BinaryReader.h"


BinaryReader::BinaryReader(wstring path)
{
	path = L"_TextData/" + path;

	file = CreateFile
	(
		path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	assert(file);
}

BinaryReader::~BinaryReader()
{
	CloseHandle(file);
}

int BinaryReader::ReadInt()
{
	int data{};

	assert(ReadFile(file, &data, sizeof(int), &size, nullptr));

	return data;
}

UINT BinaryReader::ReadUINT()
{
	UINT data{};

	assert(ReadFile(file, &data, sizeof(UINT), &size, nullptr));

	return data;
}

float BinaryReader::Readfloat()
{
	float data{};

	assert(ReadFile(file, &data, sizeof(float), &size, nullptr));

	return data;
}

string BinaryReader::ReadString()
{
	UINT dataSize = ReadUINT();

	char* data = new char[dataSize + 1];

	assert(ReadFile(file, data, sizeof(char) * dataSize, &size, nullptr));

	data[dataSize] = '\0';

	return data;
}

wstring BinaryReader::ReadWString()
{
	UINT dataSize = ReadUINT();

	WCHAR* data = new WCHAR[dataSize + 1];

	assert(ReadFile(file, data, sizeof(WCHAR) * dataSize, &size, nullptr));

	data[dataSize] = '\0';

	return data;
}

Vector2 BinaryReader::ReadVector2()
{
	Vector2 data{};

	data.x = Readfloat();
	data.y = Readfloat();

	return data;
}

Vector3 BinaryReader::ReadVector3()
{
	Vector3 data{};

	data.x = Readfloat();
	data.y = Readfloat();
	data.z = Readfloat();

	return data;
}

Vector4 BinaryReader::ReadVector4()
{
	Vector4 data{};

	data.x = Readfloat();
	data.y = Readfloat();
	data.z = Readfloat();
	data.w = Readfloat();

	return data;
}

Util::Coord BinaryReader::ReadCoord()
{
	Util::Coord coord{};

	coord.x = ReadUINT();
	coord.y = ReadUINT();

	return coord;
}

void BinaryReader::ReadData(OUT void** data, UINT dataSize)
{
	assert(ReadFile(file, *data, dataSize, &size, nullptr));
}

bool BinaryReader::Succeeded()
{
	return file != INVALID_HANDLE_VALUE;
}

