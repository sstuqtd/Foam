/*
 * qianqians
 * 2016-7-29
 * scene.h
 */
#ifndef _scene_h_
#define _scene_h_

#include <array>
#include <vector>
#include <unordered_map>
#include <memory>

namespace core{

class body;
class physical_body;
class water;
class particles;
class actor;
class terrain;

class scene {
public:
	scene();
    ~scene();

public:
	void lookat(std::array<float, 3> postion, std::array<float, 3> up, std::array<float, 3> lookat);

private:
	struct {
		std::array<float, 3> postion;
		std::array<float, 3> up;
		std::array<float, 3> lookat;
	} camera;

public:
	void preprocess();

	void draw();

private:
	std::shared_ptr<terrain> _terrain;

	struct speeddial {
		struct range {
			std::unordered_map<std::string, std::shared_ptr<body> > bodys;
			std::unordered_map<std::string, std::shared_ptr<physical_body> > physical_bodys;
			std::unordered_map<std::string, std::shared_ptr<water> > waters;
			std::unordered_map<std::string, std::shared_ptr<particles> > particless;
			std::unordered_map<std::string, std::shared_ptr<actor> > actors;
		};

		std::vector<std::vector<range> > ranges;

	} _speeddial;

};

}

#endif 