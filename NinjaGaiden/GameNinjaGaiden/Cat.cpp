﻿#include "Cat.h"
Cat::Cat()
{
	setSize(DEFAULT_CAT_WIDTH, DEFAULT_CAT_HEIGHT);
}

Cat::Cat(float x, float y)
{
	setSize(DEFAULT_CAT_WIDTH, DEFAULT_CAT_HEIGHT);
	spawnX = x;
	setX(x);
	setY(y + getHeight());
}

Cat::~Cat()
{
}

void Cat::Init()
{
	directionX = -1;	// mai mốt xét direction tùy theo vị trí của player
	setVelX(DEFAULT_CAT_VELOCITY * directionX);

	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Cat_right.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Cat_left.png", D3DCOLOR_XRGB(255, 255, 255));
	}
}

void Cat::SetStatus(ENEMY_STATUS status)
{
	//if (this->status != status || directionChanged)
	{
		this->status = status;

		switch (status)
		{
		case ENEMY_STANDING:
			startAnimation = false;

			break;
		case ENEMY_MOVING:
			startAnimation = true;
			sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
			if (getVelX() > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cat_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cat_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
		default:
			break;
		}
	}
}

void Cat::Update(DWORD dt, GameObject &player)
{
	timer.tickPerAnim = dt;

	SetStatus(ENEMY_MOVING);
	autoMove(10);
	Draw();
}

void Cat::autoMove(float range)
{
	// ?i qua l?i ? ?i?m ban ??u ph?m vi range  |<---range---spawnX---range--->|
	if (getX() <= spawnX - range || getX() >= spawnX + range - getWidth())
	{
		setVelX(-getVelX());
		directionChanged = true;
	}
	selfMovingX();
}