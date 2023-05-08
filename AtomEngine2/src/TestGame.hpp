#pragma once

#include <Atom.hpp>

using namespace atom;

class TestGame : public Game
{
public:
	void Start() override;
	const char* GetName() override;
};
