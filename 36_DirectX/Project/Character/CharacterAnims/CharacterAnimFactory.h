#pragma once

class CharacterAnimFactory
{
public:
	CharacterAnimFactory();
	~CharacterAnimFactory();
	
	/// <summary>
	/// CharacterType에 따른 각 CharacterAnim 생성
	/// </summary>
	/// <param name="cType"> : Character Type</param>
	/// <param name="parent"> : parentBody </param>
	/// <returns></returns>
	static CharacterAnim* CreateCharacterAnim(const CharacterType& cType, ColliderRect* parentBody);

private:

};
