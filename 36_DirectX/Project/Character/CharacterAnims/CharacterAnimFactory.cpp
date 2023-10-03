#include "Framework.h"
#include "CharacterAnimFactory.h"


CharacterAnimFactory::CharacterAnimFactory()
{
}

CharacterAnimFactory::~CharacterAnimFactory()
{
}

CharacterAnim* CharacterAnimFactory::CreateCharacterAnim(const CharacterType& cType)
{
	switch (cType)
	{
	case BAZZI: return new BazziAnim();
	case DAO:	return new DaoAnim();
	case CAPPI:	return new CappiAnim();
	case MARID:	return new MaridAnim();
	default:	return nullptr;
	}
}
