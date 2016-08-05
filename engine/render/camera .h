/*
*  qianqians
*  2015-11-3
*/
#ifndef _camera_h_
#define _camera_h_

#include <array>

class camera {
public:
	std::array<float, 3> postion;
	std::array<float, 3> up;
	std::array<float, 3> lookat;
};

#endif //_camera_h_
