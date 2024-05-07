#pragma once

class CharacterAnimFactory
{
public:
	CharacterAnimFactory();
	~CharacterAnimFactory();
	
	/// <summary>
	/// CharacterType�� ���� �� CharacterAnim ����
	/// </summary>
	/// <param name="cType"> : Character Type</param>
	/// <param name="parent"> : parentBody </param>
	/// <returns></returns>
	static CharacterAnim* CreateCharacterAnim(const CharacterType& cType, ColliderRect* parentBody);

private:

};
