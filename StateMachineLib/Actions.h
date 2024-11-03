#pragma once
class Actions
{
public:
	Actions() {}
	virtual ~Actions() {}

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
};

