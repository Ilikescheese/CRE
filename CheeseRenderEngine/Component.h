#pragma once
#include "Logger.h"
namespace ge {
	class Component
	{
	public:
	};

	class Health : public Component {
	public:
		int hp = 100;
		void sayHp() {
			Logger::info("hp=", hp);
		}
	};
}

