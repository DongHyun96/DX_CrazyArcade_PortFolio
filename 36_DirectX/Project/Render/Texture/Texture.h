#pragma once
class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:

	void SetPS(UINT slot = 0);

	Vector2 GetSize() { return Vector2( image.GetMetadata().width, image.GetMetadata().height ); }

	static Texture* GetTexture(wstring file);

	// MainGame 소멸자에서 호출
	static void Delete();

private:
	
	ScratchImage image;				// 온전한 이미지 정보를 여기로 불러옴

	ID3D11ShaderResourceView* srv{};	// srv를 통해 이미지 정보를 가공하여 gpu에 넘김

	static map<wstring, Texture*> textures;

};
