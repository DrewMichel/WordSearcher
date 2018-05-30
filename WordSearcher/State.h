// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_STATE_H
#define DREW_STATE_H

// Namespace declaration
namespace Drewski
{
	// Abstract class that is extended by all State classes
	class State
	{
		public:
			// Member functions
			virtual void init() = 0;
			virtual void handleInput() = 0;
			virtual void update(float deltaTimeIn) = 0;
			virtual void draw(float deltaTimeIn) = 0;
			virtual void pause() {};
			virtual void resume() {};
	};
}

#endif