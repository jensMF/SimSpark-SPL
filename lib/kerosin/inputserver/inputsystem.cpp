#include "inputsystem.h"

using namespace kerosin;
using namespace zeitgeist;


InputSystem::InputSystem() : Node(), mInputServer(NULL)
{
}

InputSystem::~InputSystem()
{
}

bool InputSystem::Init(kerosin::InputServer *inputServer)
{
	mInputServer = inputServer;
	
	if (mInputServer == NULL) return false;

	return true;
}

void InputSystem::AddInput(InputServer::Input &input)
{
	AddInputInternal(input);
}

bool InputSystem::GetInput(InputServer::Input &input)
{
	if (mInputQueue.size()>0)
	{
		input = mInputQueue.front();
		mInputQueue.pop_front();
		return true;
	}

	return false;
}

void InputSystem::AddInputInternal(InputServer::Input &input)
{
	mInputQueue.push_back(input);
}
