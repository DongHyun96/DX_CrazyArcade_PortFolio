#include "Framework.h"
#include "CharacterAnimFactory.h"


CharacterAnimFactory::CharacterAnimFactory()
{
}

CharacterAnimFactory::~CharacterAnimFactory()
{
}

CharacterAnim* CharacterAnimFactory::CreateCharacterAnim(const CharacterType& cType, ColliderRect* parentBody)
{
	switch (cType)
	{
	case BAZZI: return new BazziAnim(parentBody);
	case DAO:	return new DaoAnim(parentBody);
	case CAPPI:	return new CappiAnim(parentBody);
	case MARID:	return new MaridAnim(parentBody);
	default:	return nullptr;
	}
}
