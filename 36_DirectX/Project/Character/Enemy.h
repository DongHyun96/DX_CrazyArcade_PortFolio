#pragma once
class Enemy : public Character
{
private:
	
	enum TargetState
	{
		PLAYER,
		BALLOON_D_POS,
		SAFE_ZONE,
		RESCUE_PEER,
		NONE
	};

public:
	Enemy(const CharacterType& cType);
	~Enemy();

public:
	
	void SetPathToRescueMission(const pair<stack<Util::Coord>, set<Util::Coord>>& path_visited, Character* rescueTarget);

private:

	virtual void Move() override;
	virtual void HandleUseConsumableItem() override;
	virtual void DeployBalloon() override;
	
	virtual void Init();

private:
	
	void UpdatePath(const Util::Coord& dest);

	void UpdateState();

	void DeployBalloonManually();

	void RequestRescue(); // �ڽ��� captured �Ǿ��� ���� event

private:
	
	vector<Util::Coord> GetDeployableCoords(const set<Util::Coord>& visited);
	bool IsDeployable(const Util::Coord& coord, const set<Util::Coord>& visited); // �ش� ��ǥ�� �������밡 Ȯ���� �Ǵ��� �˻�
	Util::Coord GetIdealDeployCoord(const vector<Util::Coord>& deployables);
	
	Util::Coord GetSafeCoords(const set<Util::Coord>& visited, OUT bool& safeCoordExist);

private:
	void Debug() override;

private:

	TargetState targetState{NONE};

	stack<Util::Coord> path{};
	set<Util::Coord> visited{};

	Util::Coord myCoord{};

	const float SAFE_ZONE_WAIT_TIME = 3.f;
	float safeZoneWaitTime = 0.f;

private:
	
	const float BLOCKED_TIME = 0.5f;
	float blockedTime = 0.f;

private:

	const UINT PLAYER_APPROACH_MIN = 0;
	const UINT PLAYER_APPROACH_MAX = 3;
	UINT player_approach_lv = 0;

private: // RESCUE ���� (���� ������ ��)

	Character* rescueTarget{};

private: // RESCUE ���� (���� ���� ���� �� ���)

	bool callRescueOnce{ false };
	bool callRescueTwice{ false };

	const float RESCUE_CALL_TIME_ONCE = 0.5f;
	const float RESCUE_CALL_TIME_TWICE = 2.f;

	float callRescueTime = 0.f;


};
