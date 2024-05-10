#pragma once
/* 
CONCRETE CLASS 
���� �ʿ� ���������� map cell �� ĭ�� spawn�Ǵ� ���ٱ� block
*/
class StreamBlock
{
public:
	StreamBlock();
	virtual ~StreamBlock();

	void Init();

	virtual void Update();
	virtual void Render();

public:
	
	/// <summary>
	/// ���ٱ� block ������Ű��
	/// </summary>
	/// <param name="spawnCoord"> : ���� ��ġ </param>
	/// <param name="isEnd"> : �� �� ���ٱ����� </param>
	/// <returns> : ������ �ڱ��ڽ� return </returns>
	StreamBlock* Spawn(const Util::Coord& spawnCoord, const bool& isEnd = false);

public: /* Getters */

	bool			IsActive() const { return isActive; }

	ColliderRect*	GetBody() const { return body; }

	Util::Coord		GetSpawnCoord() const { return spawnCoord; }


protected:

	/*
	���ٱ��� ��� �ڽ��� ���ٱ� animation�� ���� �� �ڽ��� active�� ��
	���ٱ� animation End event�� (param false) �ɾ�� �Լ�
	*/
	void SetActive(const bool& isActive);

protected:

	/* 
	���ٱ� block animation�� ��� ������ ���� body collider�� �� ���� -> ���ٱ� ���� ����
	Animation������ AnimNotify call back���� Ư�� idx�� ������ �� ȣ��� �Լ� 
	*/
	void DisableBodyCollider();

protected: /* Collider call back functions */

	void OnColliderPointEnter(ColliderHolder* owner);
	void OnColliderRectEnter(ColliderRect* targetCollider, ColliderHolder* owner);

/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/

protected:

	bool isActive{};

	Util::Coord spawnCoord{};

	ColliderRect* body{};
	
protected:

	// ���ٱ� �� block�� animation�� ��¦ �ٸ�
	bool		isEnd{};		// isEnd�̸� endAnim�� ���
	Animation*	curAction{};	// ���� ���õ� animation
	Animation*	mainAnim{};		// �ڽ��� ��ġ�� ���ٱ��� ���κ��� �ƴ� �� ����� animation
	Animation*	endAnim{};		// �ڽ��� ���ٱ��� ���κ��� �� ����� animation
	
protected:

	VertexShader*	vertexShader{};
	PixelShader*	pixelShader{};

	MatrixBuffer*	worldBuffer{};
	ColorBuffer*	colorBuffer{};

protected:

	/* sprite ��� index ���� */
	const vector<UINT>	ANIM_INDICES{ 3, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10 };

	/* 
	���ٱ� block animation�� ��� ������ ���� BODY_COLLISION_DISABLE_IDX ���� ����Ͽ��ٸ� body collider�� �� ���� ->
	���ٱ� ���� ����
	*/
	const UINT			BODY_COLLISION_DISABLE_IDX{ 14 };
	
	const float			ANIM_SPEED = 0.04f;
};
