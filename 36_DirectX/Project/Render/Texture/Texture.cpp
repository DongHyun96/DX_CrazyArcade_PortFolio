#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures{};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:image(move(image)), srv(srv) // move (shallow copy)
{
}

Texture::~Texture()
{
	srv->Release();

}

void Texture::SetPS(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

Texture* Texture::GetTexture(wstring file)
{
	file = L"_Texture/" + file;

	if (textures.count(file) > 0)
		return textures[file];

	ScratchImage image;

	LoadFromWICFile(file.c_str(), WIC_FLAGS_IGNORE_SRGB, nullptr, image);

	ID3D11ShaderResourceView* srv;

	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);

	if (!srv)
	{
		RaiseException(
			1,                    // exception code
			0,                    // continuable exception
			0, NULL);             // no arguments
	}
	

	textures.emplace(file, new Texture(srv, image));

	return textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : textures)
		delete pair.second;

	textures.clear();
}
