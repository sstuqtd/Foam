/*
 * qianqians
 * 2016-7-29
 * engine_event.cpp
 */
#include "event.h"

namespace core {
	
std::shared_ptr<engine_event> engine_event::_engine_event = nullptr;

std::shared_ptr<engine_event> engine_event::create_engine_event() {
	_engine_event = std::make_shared<engine_event>();
	return _engine_event;
}

std::shared_ptr<engine_event> engine_event::get_engine_event() {
	return _engine_event;
}

engine_event::engine_event() {
}

engine_event::~engine_event() {
}

void engine_event::push_event(std::string json_str) {
	std::lock_guard<std::mutex> lock(_mutext_event_que);
	_event_que.push(json_str);
}

bool engine_event::pop_event(std::string & json_str) {
	std::lock_guard<std::mutex> lock(_mutext_event_que);
	if (_event_que.empty()) {
		return false;
	}

	json_str = _event_que.front();
	_event_que.pop();
	
	return true;
}

}