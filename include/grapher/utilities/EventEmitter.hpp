#pragma once

#include <deque>
#include <map>

namespace grapher::utilities
{
	template<class Identifier>
	class EventEmitter
	{
	public:
		using Listener = void (*)(void* emitter, ...);

		EventEmitter(void* emitter = nullptr);

		void on(Identifier identifier, Listener listener);
		void off(Identifier identifier, Listener listener);
		void off(Identifier identifier);

		void emit(Identifier identifier, ...);

	private:
		void* emitter = nullptr;

		std::map<Identifier, std::deque<Listener>> listeners;
	};
}

#include "EventEmitter.inl"