#pragma once
#include "Dialog.h"

class AboutBox final : public Dialog
{

public:

	virtual void Create() final;
	virtual void Destroy() final;
	virtual void Draw(const Shader& shader) final;
	virtual void Update() final;


private:



};