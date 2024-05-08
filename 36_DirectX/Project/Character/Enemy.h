#pragma once
/* 
CONCRETE CLASS
��ü decision-making process�� ���� control�� enemy ĳ����
*/
class Enemy : public Character
{

public:
	Enemy(const CharacterType& cType);
	~Enemy();

public:
	
	/// <summary>
	/// ������ ��ο� ��������� ����
	/// </summary>
	/// <param name="rescue_path_visited_pair"> : ������ο� AStar �˰��� visited pair</param>
	/// <param name="rescueTarget"> : ������ ����</param>
	void SetPathToRescueMission(const pair<stack<Util::Coord>, set<Util::Coord>>& rescue_path_visited_pair, Character* rescueTarget);

private:

	void Move()						override;
	void HandleUseConsumableItem()	override;
	void DeployBalloon()			override; 
	
	void Init()						override;

private:
	/* targetState�� ���� FSM ��Ȳ��ġ */
	void UpdateState();

private:
	/* ���ο� ��ǥ�������� path ���� */
	void UpdatePath(const Util::Coord& dest);

private:
	/* �ٸ� ���ῡ�� ������û �õ� */
	void RequestRescue(); 

private: /* ��ǳ�� ���� ���� */
	
	/* ��ǳ�� ���� */
	void DeployBalloonManually();
	
	/// <summary>
	/// AStar�� �湮�� ��ǥ �� ��ǳ���� ���Ƶ� �������밡 Ȯ���Ǵ� ��ǥ�� ã��
	/// </summary>
	/// <param name="visited"> : AStar�� �湮�� ��ǥ</param>
	/// <returns>�������밡 Ȯ���Ǵ� ��ǥ��</returns>
	vector<Util::Coord> GetDeployableCoords(const set<Util::Coord>& visited);

	/// <summary>
	/// �ش� ��ǥ�� ��ǳ���� ���Ƶ� �������밡 Ȯ���� �Ǵ��� �˻�
	/// </summary>
	/// <param name="coord"> : �˻��� ��ǥ</param>
	/// <param name="visited"> : AStar�� �湮ó���� ��ǥ��</param>
	/// <returns></returns>
	bool IsDeployable(const Util::Coord& coord, const set<Util::Coord>& visited);

	/// <summary>
	/// ��ǳ���� ���� �� �ִ� ��ǥ�� �� �� �� �̻����� ��ǥ(ex - �μ����� ��� ��)�� ���ϴ� �Լ�
	/// </summary>
	/// <param name="deployables"> : ��ǳ���� ���� �� �ִ� ��ǥ��</param>
	/// <returns>��ǳ���� ���� �̻����� ��ǥ</returns>
	Util::Coord GetIdealDeployCoord(const vector<Util::Coord>& deployables); 
	
private:
	/// <summary>
	/// ������ �̵� ��ǥ ���ϱ�
	/// </summary>
	/// <param name="visited"> : AStar�� �湮ó���� ��ǥ��</param>
	/// <param name="safeCoordExist"> : ������ �̵���ǥ�� �ִ����� ���� OUT reference ���</param>
	/// <returns>������ �̵���ǥ</returns>
	Util::Coord GetSafeCoord(const set<Util::Coord>& visited, OUT bool& safeCoordExist);

private:
	void Debug() override;



/***************************************************************************************************
*                                          Member variables                                        *
****************************************************************************************************/
private:

	/* Enemy target state - ���� �̵��� ��ǥ target ���� */
	enum TargetState
	{
		PLAYER,
		BALLOON_D_POS,		// ��ǳ���� ���� �ڸ��� �̵�
		SAFE_ZONE,			// ���ٱ⿡ ���� ���� �ڸ��� �̵�
		RESCUE_PEER,		// ������û�� �ٸ� ���ῡ�Լ� ������, ��ǳ���� ���� ���� ��ġ�� �̵�
		NONE				// ��ǥ target�� ������ ���� ����
	} targetState = NONE;

private:
	/* ���Ӹʿ����� ���� ��ǥ */
	Util::Coord myCoord{};

private: /* �̵� ��� ���� */

	stack<Util::Coord>	path{};		// AStarPathFinder�� ���� ��ǥ���������� ���
	set<Util::Coord>	visited{};	// AStarPathFinder�� ���� AStar �˰��� �� �湮�ߴ� ��ǥ��

private: /* Safe zone�� ���� �� ��ٸ� time */

	const float SAFE_ZONE_WAIT_TIME = 3.f;	// Safe Zone ���� ��, ������ ���ٸ� �ش� �ڸ����� ����� �ð�
	float		safeZoneWaitTime{};

private: /* ��� �̵� �� ��ΰ� ������ �� ���� */
	// ��� �̵� �� Ư�� �ð� �̻� ���� �ڸ��� �ӹ����ٸ�, ��ΰ� ���ع޾Ҵٰ� �Ǵ��Ͽ� targetState�� NONE���� �ξ� ��� ��Ž��

	const float BLOCKED_TIME_LIMIT = 0.5f;
	float		blockedTime{};

private: /* �̵� ��ǥ������ player ��ġ�� ��, ��ǥ���� ���� ���� */
	// �÷��̾�� �̵� ��ǥ�� ���� ��, ������ �����ϴ� ���� �ƴ� �����ϰ� �Ÿ����� ������ ����

	const UINT	PLAYER_APPROACH_MIN = 0;	// �ּ� ���� �Ÿ���
	const UINT	PLAYER_APPROACH_MAX = 3;	// �ִ� ���� �Ÿ���
	UINT		player_approach_lv{};		// �����ϰ� setting�� player ��ǥ ���������� �Ÿ���

private: /* RESCUE ����(���� ������ ��) */

	Character* rescueTarget{}; // �����ؾ� �� ����

private: /* RESCUE ����(���� ��ǳ���� ������ �ٸ� ������ ������ �޾ƾ� �� ��) */

	bool		requestResqueOnce{};			// ù ������ȣ�� ���´��� üũ
	bool		requestResqueTwice{};			// �ι� ° ������ȣ�� ���´��� üũ

	const float RESCUE_CALL_TIME_ONCE  = 0.5f;	// �ش� �ð��� �帥 ��, ù ������û ����
	const float RESCUE_CALL_TIME_TWICE = 2.f;	// �ش� �ð��� �帥 ��, �� ��° ������û ����
	float		capturedTime		   = 0.f;	// ��ǳ���� ���� �� �ð�


};
