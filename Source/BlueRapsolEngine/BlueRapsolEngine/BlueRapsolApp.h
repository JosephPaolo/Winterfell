#pragma once

#include <stdio.h>
#include "BlueRapsolEngine.h"
#include <string>

//Name of this program for Mutex
#define MUTEX_APP_NAME L"BlueRapsolEngineMutex"

using namespace BlueRapsolEnums;

class BlueRapsolApp : public BlueRapsolEngine {

public:
	BlueRapsolApp(HINSTANCE hInstance);
	virtual bool Initialize();

protected:
	virtual void GameStart();
	virtual void GameUpdate();

private:
	void CheckInput();
	void TickCounters();
	void PlayerVictory(int playerNum);
	void Rematch();
	void CheckVictory();
	bool isAnyKeyPressed();

	std::string player1Key;
	std::string player2Key;

	Vector2 initPlayer1Dir;
	Vector2 initPlayer2Dir;

	float bulletSpeed = 240.0f;
	float playerSpeed = 80.0f;
	float hazardSpeed = 140.0f;
	int recycledBullets[20]; //TODO use a stack instead and utilize bullets after being removed from the level instead of simply iterating through the bullets
	int maxBullets = 20;
	int nextBullet = 0;
	int bulletCooldownInTicks = 40;
	int player1BulletCooldownTickCounter = 0;
	int player2BulletCooldownTickCounter = 0;
	bool player1ReadyToFire = false;
	bool player2ReadyToFire = false;
	bool player1Victory = false;
	bool player2Victory = false;
	bool isGameStarted = false;

	CardinalDirection player1CarDir = CardinalDirection::North;
	CardinalDirection player2CarDir = CardinalDirection::North;
};
