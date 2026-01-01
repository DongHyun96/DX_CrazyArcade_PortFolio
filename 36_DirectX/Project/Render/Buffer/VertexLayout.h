#pragma once

struct Vertex
{
	Vector3 pos = {};
};

struct VertexColor
{
	VertexColor(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		pos.z = 0.f;
	}

	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color) {}

	XMFLOAT3 pos{}; // float이 3개
	XMFLOAT4 color{};
};


struct VertexTexture
{
	VertexTexture()
	{
	}

	VertexTexture(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		pos.z = 0.f;
	}

	VertexTexture(Vector3 pos, Vector2 uv)
		:pos(pos), uv(uv) {}

	Vector3 pos{}; // float이 3개
	Vector2 uv{};
};

