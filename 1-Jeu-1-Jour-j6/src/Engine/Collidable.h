#pragma once

class Collider;

class Collidable
{
public:
	virtual void OnCollisionEnter(Collider* _self, Collider* _other) {}
	virtual void OnCollisionStay(Collider* _self, Collider* _other) {}
	virtual void OnCollisionExit(Collider* _self, Collider* _other) {}
};