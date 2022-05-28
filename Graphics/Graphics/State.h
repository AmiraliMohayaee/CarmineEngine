#pragma once

#include <vector>


class State
{
public:

	State() {}
	virtual ~State() = 0 {}

	virtual void InputHandle() = 0;
	virtual State* Update() = 0;
	virtual void Draw() = 0;
	virtual void Shutdown() = 0;

private:

	std::vector<State*> m_states;

	bool m_isRunning;

};