#include "Object.h"
Object::Object() {
	this->Gravity = false;
	this->angle = 0.f;
	this->objform = Objform::Non;
	this->CollisionProcess = nullptr;
	this->mass = 0.f;
	this->objectTag = "";
}
Object::Object(Objform form, Vec2 _posi, Vec2 _Sca, float _ang)
{
	this->objform = form;
	switch (objform)
	{
	case Objform::Cube:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	case Objform::Ball:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	}
	this->angle = _ang;
}
Object::~Object()
{

}
void Object::CreateObject(Objform form, Vec2 _posi, Vec2 _Sca, float _ang) 
{
	this->objform = form;
	switch (objform)
	{
	case Objform::Cube:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	case Objform::Ball:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	}
	this->angle = _ang;
}
bool Object::hit(Object& o)
{
	switch (this->objform)
	{
	case Objform::Cube:
		this->collisionCube.hitBase = {
			this->position.x,
			this->position.y,
			this->Scale.x + this->position.x,
			this->Scale.y + this->position.y };
		this->collisionCube.Rotate(this->angle);
		switch (o.objform)
		{
		case Objform::Cube:
			o.collisionCube.hitBase = {
				o.position.x,
				o.position.y,
				o.Scale.x + o.position.x,
				o.Scale.y + o.position.y};
			o.collisionCube.Rotate(o.angle);
			return this->collisionCube.hitBox(o.collisionCube);
			break;
		case Objform::Ball:
			o.collisionBall.hitBase = {
				o.Scale.x,
				o.position.x,
				o.position.y };
			return this->collisionCube.hitCircle(o.collisionBall);
			break;
		}
		break;
	case Objform::Ball:
		this->collisionBall.hitBase = {
			this->Scale.x,
			this->position.x,
			this->position.y };
		switch (o.objform)
		{
		case Objform::Cube:
			o.collisionCube.hitBase = {
				o.position.x,
				o.position.y,
				o.Scale.x + o.position.x,
				o.Scale.y + o.position.y };
			o.collisionCube.Rotate(o.angle);
			return this->collisionBall.hitBox(o.collisionCube);
			break;
		case Objform::Ball:
			o.collisionBall.hitBase = {
				o.Scale.x,
				o.position.x,
				o.position.y };
			return this->collisionBall.hitCircle(o.collisionBall);
			break;
		}
		break;
	}
	return false;
}

void Object::LineDraw()
{
	switch (this->objform)
	{
	case Objform::Cube:
	{
		this->collisionCube.hitBase = {
			this->position.x,
			this->position.y,
			this->Scale.x + this->position.x,
			this->Scale.y + this->position.y
		};
		this->collisionCube.Rotate(this->angle);
		Vec2 _v[4] = {
		{ this->collisionCube.hitBase.x,this->collisionCube.hitBase.y },
		{ this->collisionCube.hitBase.w - 1,this->collisionCube.hitBase.y },
		{ this->collisionCube.hitBase.w - 1,this->collisionCube.hitBase.h - 1 },
		{ this->collisionCube.hitBase.x,this->collisionCube.hitBase.h - 1 }
		};
		OG::_Rotate(this->collisionCube.angle, _v);
		OG::LineHitDraw(_v);
		break;
	}
	case Objform::Ball:
		break;
	case Objform::Non:
		break;
	}
}

void Object::AddObject(Object* obj)
{
	this->hitObj.push_back(obj);
}

bool Object::DeleteObject(Object* obj)
{
	for (auto id = this->hitObj.begin(); id != this->hitObj.end(); ++id)
	{
		if ((*id) == obj)
		{
			this->hitObj.erase(id);
			return true;
		}
	}
	return false;
}

void Object::AllDeleteObject()
{
	this->hitObj.clear();
}

CollisionObject::CollisionObject()
{
	this->hitObject.clear();
}
CollisionObject::~CollisionObject()
{
	this->hitObject.clear();
}

void CollisionObject::AddObject(Object* obj)
{
	this->hitObject.push_back(obj);
}

bool CollisionObject::DeleteObject(Object* obj)
{
	for (auto id = this->hitObject.begin(); id != this->hitObject.end(); ++id)
	{
		if ((*id) == obj)
		{
			this->hitObject.erase(id);
			return true;
		}
	}
	return false;
}

void CollisionObject::AllDeleteObject()
{
	this->hitObject.clear();
}

bool CollisionObject::ObjectHit(std::string objtag)
{
	for (int i = 0; i < this->hitObject.size(); ++i)
	{
		
	}
	return false;
}

void CollisionObject::ResetObject()
{
	this->hitObject.clear();
}