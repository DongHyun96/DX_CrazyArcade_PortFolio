#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring path);
	~BinaryReader();

	int		ReadInt();
	UINT	ReadUINT();
	float	Readfloat();
	string	ReadString();
	wstring ReadWString();
	Vector2 ReadVector2();
	Vector3 ReadVector3();
	Vector4 ReadVector4();

	Util::Coord ReadCoord();

	void ReadData(OUT void** data, UINT dataSize);

	bool Succeeded();

private:
	HANDLE file{};
	DWORD size{};
};
