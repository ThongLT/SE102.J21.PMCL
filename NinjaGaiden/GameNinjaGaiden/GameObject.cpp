﻿#include "GameObject.h"



GameObject::GameObject()
{
	sprite = new Sprite();	// có lỗi gì thì nhớ quan tâm bạn này

	directionX = directionY = 1;

	timer.startTime = GetTickCount();
	timer.tickPerAnim = 3000;
}


GameObject::~GameObject()
{
}

void GameObject::CreateObject(const char * imagePath, D3DCOLOR transColor, float width, float height)
{
	setSize(width, height);
	sprite->LoadTexture(imagePath, transColor);
}

void GameObject::UpdateCollisionStatus(int nx, int ny, float collisionTime)
{
	this->nx = nx;
	this->ny = ny;
	this->collisionTime = collisionTime;
}

void GameObject::CheckCollisionStatus(GameObject * player)
{
}

void GameObject::setObjectType(GAME_OBJECT_TYPE objectType)
{
	this->objType = objectType;
}

GAME_OBJECT_TYPE GameObject::getObjectType()
{
	return objType;
}

void GameObject::setCollisionType(COLLISION_TYPE collisionType)
{
	this->clsType = collisionType;
}

COLLISION_TYPE GameObject::getCollisionType()
{
	return clsType;
}

void GameObject::Init()
{
}

void GameObject::Update(DWORD dt, GameObject & player)
{
}

void GameObject::Draw()
{
	// vòng lặp animation
	if (timer.isAtTime())
	{
		if (startAnimation)
		{
			if (sprite->getCurrentAnimation() == sprite->getLastAnimation())
			{
				sprite->setCurrentAnimation(sprite->getFirstAnimation());
			}
			else
			{
				sprite->setCurrentAnimation(sprite->getCurrentAnimation() + 1);
			}
		}
		else
		{
			sprite->setCurrentAnimation(sprite->getFirstAnimation());
		}
	}

	// vẽ object
	sprite->Draw(getX(), getY(), this);
}
