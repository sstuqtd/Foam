/*
 *  qianqians
 *  2015-10-9
 */
#ifndef _wnd_h_
#define _wnd_h_

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include <Windows.h>

#include "context.h"

class wnd{
	enum swStyle{
		showWND = 0,
		hideWND = 1,
	};

private:
	wnd(std::string title, 
		int left, int top, int width, int height, 
		std::function<void(LPRAWINPUT) > _sigRawInput, 
		std::function<void()> _sigActivate,
		std::function<void()> _sigUnActivate);

	~wnd();

	static void release_wnd(wnd * _wnd);

public:
	static std::shared_ptr<wnd> createWndInstance(std::string title,
		int left, int top, int width, int height,
		std::function<void(LPRAWINPUT) > _sigRawInput,
		std::function<void()> _sigActivate,
		std::function<void()> _sigUnActivate);

	static std::shared_ptr<wnd> getWndInstance();

private:
	static std::shared_ptr<wnd> _this_wnd;

public:
	void showWnd(swStyle swstyle);

	std::shared_ptr<context> get_context();

	void run();

private:
	HDC hdc;

	HDC getDC();

	friend class context;

private:
	HWND whandle;

	std::shared_ptr<context> c;

	std::function<void(LPRAWINPUT) > sigRawInput;
	std::function<void()> sigActivate;
	std::function<void()> sigUnActivate;

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

};

#endif 