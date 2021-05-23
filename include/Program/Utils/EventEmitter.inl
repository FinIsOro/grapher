#include "EventEmitter.hpp"

#include <cstdarg>

namespace program
{
	template<class Identifier>
	inline EventEmitter<Identifier>::EventEmitter(void* emitter)
	{
		if (emitter == nullptr)
			this->emitter = this;
		else
			this->emitter = emitter;
	}

	template<class Identifier>
	void EventEmitter<Identifier>::on(Identifier identifier, Listener listener)
	{
		listeners[identifier].push_front(listener);
	}

	template<class Identifier>
	void EventEmitter<Identifier>::off(Identifier identifier, Listener listener)
	{
		auto stack = listeners[identifier];

		stack.erase(std::find(stack.begin(), stack.end(), listener));

		listeners[identifier] = stack;
	}

	template<class Identifier>
	inline void EventEmitter<Identifier>::off(Identifier identifier)
	{
		listeners[identifier].clear();
	}

	template<class Identifier>
	void EventEmitter<Identifier>::emit(Identifier identifier, ...)
	{
		va_list arguments;

		for (auto listener : listeners[identifier])
		{
			va_start(arguments, identifier);

			listener(emitter, arguments);

			va_end(arguments);
		}
	}
}