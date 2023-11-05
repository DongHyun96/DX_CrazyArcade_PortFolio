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
}

BinaryReader::~BinaryReader()
{
	CloseHandle(file);
}

int BinaryReader::ReadInt()
{
	int data{};

	if (!ReadFile(file, &data, sizeof(int), &size, nullptr))
		RaiseException(1, 0, 0, nullptr);

	return data;
}

UINT BinaryReader::ReadUINT()
{
	UINT data{};

	if(!ReadFile(file, &data, sizeof(UINT), &size, nullptr))
		RaiseException(1, 0, 0, nullptr);

	return data;
}

float BinaryReader::Readfloat()
{
	float data{};

	if(!ReadFile(file, &data, sizeof(float), &size, nullptr))
		RaiseException(1, 0, 0, nullptr);


	return data;
}

void BinaryReader::ReadAndCopyStr(string& target)
{
	UINT dataSize = ReadUINT();

	char* data = new char[dataSize + 1];

	if(!ReadFile(file, data, sizeof(char) * dataSize, &size, nullptr))
		RaiseException(1, 0, 0, nullptr);


	data[dataSize] = '\0';

	target = data;
	
	delete[] data;

}

void BinaryReader::ReadAndCopyWstr(wstring& target)
{
	UINT dataSize = ReadUINT();

	WCHAR* data = new WCHAR[dataSize + 1];

	if(!ReadFile(file, data, sizeof(WCHAR) * dataSize, &size, nullptr))
		RaiseException(1, 0, 0, nullptr);


	data[dataSize] = '\0';

	target = data;

	delete[] data;
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
	if(!ReadFile(file, *data, dataSize, &size, nullptr))
		RaiseException(1, 0, 0, nullptr);

}

bool BinaryReader::Succeeded()
{
	return file != INVALID_HANDLE_VALUE;
}

