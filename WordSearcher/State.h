#ifndef DREW_STATE_H
#define DREW_STATE_H

namespace Drewski
{
	class State
	{
		public:
			virtual void init() = 0;
			virtual void handleInput() = 0;
			virtual void update(float deltaTimeIn) = 0;
			virtual void draw(float deltaTimeIn) = 0;
			virtual void pause() {};
			virtual void resume() {};
	};
}

#endif