#pragma once

class CharacterAnimFactory
{
public:
	CharacterAnimFactory();
	~CharacterAnimFactory();
	
	static CharacterAnim* CreateCharacterAnim(const CharacterType& cType);

private:

};