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

	// MainGame �Ҹ��ڿ��� ȣ��
	static void Delete();

private:
	
	ScratchImage image;				// ������ �̹��� ������ ����� �ҷ���

	ID3D11ShaderResourceView* srv{};	// srv�� ���� �̹��� ������ �����Ͽ� gpu�� �ѱ�

	static map<wstring, Texture*> textures;

};
