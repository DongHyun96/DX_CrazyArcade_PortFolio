#include "Framework.h"
#include "CharacterAnimFactory.h"


CharacterAnimFactory::CharacterAnimFactory()
{
}

CharacterAnimFactory::~CharacterAnimFactory()
{
}

CharacterAnim* CharacterAnimFactory::CreateCharacterAnim(const CharacterType& cType, ColliderRect* parent)
{
	switch (cType)
	{
	case BAZZI: return new BazziAnim(parent);
	case DAO:	return new DaoAnim(parent);
	case CAPPI:	return new CappiAnim(parent);
	case MARID:	return new MaridAnim(parent);
	default:	return nullptr;
	}
}
