#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	void Update() override;
	void Render() override;

private:
	vector<Collider*> colliders{};
};
