/*
 * qianqians
 * 2016-7-30
 * assets.h
 */
#ifndef _assets_h_
#define _assets_h_

#include <string>
#include <mutex>
#include <queue>

#include "actor.h"
#include "particles .h"
#include "scene.h"
#include "skeleton.h"
#include "object.h"

class assets {

//load_assets
public:
	void switch_to_scene(std::string scene_name);

private:
	void load_assets(std::string file_path);
	
private:


};

#endif //_assets_h_
