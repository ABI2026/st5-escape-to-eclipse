#pragma once
class Enemy
{
	public:
	Enemy();
	~Enemy();
	void Initialize();
	void Update(float deltaTime);
	void Render();
	void SetPosition(float x, float y);
	void SetSpeed(float speed);
	float GetX() const;
	float GetY() const;
	float GetSpeed() const;
private:
	float x;
	float y;
	float speed;
	//sf::Sprite sprite; // Assuming you have a sprite for the enemy
	//sf::Texture texture; // Texture for the enemy sprite
	float deltaTime; // Time since last update
	bool isAlive; // Flag to check if the enemy is alive
};

