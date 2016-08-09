/*
 * qianqians
 * 2016-7-30
 * control.h
 */
#ifndef _control_h_
#define _control_h_

#include <array>
#include <string>

namespace core {

class control {
public:
	void switch_to_scene(std::string scene, std::string callbackid);

	void add_body(std::string asset_name, std::string callbackid);

	void remove_body(std::string bodyid, std::string callbackid);

	//scene control
	void set_scene_sky(std::string sky_name);

	void set_scene_weather(std::string weather_name);

	void set_scene_wind(std::array<float, 3> wind_direction, float force);

	//

};

}

#endif //_engine_control_h_
