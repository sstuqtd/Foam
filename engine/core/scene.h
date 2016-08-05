/*
 * qianqians
 * 2016-7-29
 * event.h
 */
#ifndef _event_h_
#define _event_h_

#include <memory>
#include <string>
#include <queue>
#include <mutex>

namespace core{

class engine_event{
public:
	static std::shared_ptr<engine_event> create_engine_event();
	static std::shared_ptr<engine_event> get_engine_event();

private:
    engine_event();
    ~engine_event();

public:
	void push_event(std::string json_str);

	bool pop_event(std::string & json_str);

private:
	std::mutex _mutext_event_que;
	std::queue<std::string> _event_que;

private:
	static std::shared_ptr<engine_event> _engine_event;

};

}

#endif 