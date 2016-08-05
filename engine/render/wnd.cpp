/*
*  qianqians
*  2015-10-9
*/

#include "wnd.h"

std::shared_ptr<wnd> wnd::_this_wnd = nullptr;

wnd::wnd(std::string title,
	int left, int top, int width, int height,
	std::function<void(LPRAWINPUT) > _sigRawInput,
	std::function<void()> _sigActivate,
	std::function<void()> _sigUnActivate){
	WNDCLASS wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wcx.style = CS_HREDRAW | CS_VREDRAW;                     // redraw if size changes 
	wcx.lpfnWndProc = wnd::WndProc;							 // points to window procedure 
	wcx.cbClsExtra = 0;										 // no extra class memory 
	wcx.cbWndExtra = 0;										 // no extra window memory 
	wcx.hInstance = NULL;									 // handle to instance 
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 // predefined app. icon 
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);               // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // white background brush 
	wcx.lpszMenuName = NULL;	 							 // name of menu resource 
	wcx.lpszClassName = "wnd";								 // name of window class 

	// Register the window class. 
	RegisterClass(&wcx);

	whandle = CreateWindow(
		"wnd",				 // name of window class 
		title.c_str(),		 // title-bar string 
		WS_OVERLAPPEDWINDOW, // top-level window 
		CW_USEDEFAULT,       // default horizontal position 
		CW_USEDEFAULT,       // default vertical position 
		CW_USEDEFAULT,       // default width 
		CW_USEDEFAULT,       // default height 
		(HWND)NULL,          // no owner window 
		(HMENU)NULL,         // use class menu 
		NULL,	             // handle to application instance 
		(LPVOID)NULL);       // no window-creation data 

	if (!whandle){
		auto error = GetLastError();
		throw std::exception("create window failed");
	}

	hdc = GetDC(whandle);

	c = std::make_shared<context>(this);

	sigRawInput = _sigRawInput;
	sigActivate = _sigActivate;
	sigUnActivate = _sigUnActivate;

	ShowWindow(whandle, SW_SHOW);
	UpdateWindow(whandle);

	c->init();
}

wnd::~wnd(){
	ReleaseDC(whandle, hdc);
	CloseWindow(whandle);
}

std::shared_ptr<wnd> wnd::createWndInstance(std::string title,
	int left, int top, int width, int height,
	std::function<void(LPRAWINPUT) > _sigRawInput,
	std::function<void()> _sigActivate,
	std::function<void()> _sigUnActivate)
{
	_this_wnd = std::shared_ptr<wnd>(
		new wnd(title, left, top, width, height, _sigRawInput, _sigActivate, _sigUnActivate),
		std::bind(&wnd::release_wnd, std::placeholders::_1));

	return _this_wnd;
}

void wnd::release_wnd(wnd * _wnd) {
	delete _wnd;
}

std::shared_ptr<wnd> wnd::getWndInstance() {
	return _this_wnd;
}

LRESULT CALLBACK wnd::WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam){
	switch (umsg)
	{
	case WM_INPUT:
		if (wParam == RIM_INPUT) {
			wnd::getWndInstance()->sigRawInput((LPRAWINPUT)lParam);
		}
		break;

	case WM_KILLFOCUS:
		wnd::getWndInstance()->c->release();
		wnd::getWndInstance()->sigUnActivate();
		break;

	case WM_SETFOCUS:
		wnd::getWndInstance()->c->make_current();
		wnd::getWndInstance()->sigActivate();
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, umsg, wParam, lParam);
}

void wnd::showWnd(swStyle swstyle){
	if (swstyle == showWND){
		ShowWindow(whandle, SW_SHOW);
	} else if (swstyle == showWND){
		ShowWindow(whandle, SW_HIDE);
	}
}

HDC wnd::getDC(){
	return hdc;
}

std::shared_ptr<context> wnd::get_context() {
	return c;
}

void wnd::run() {
	MSG msg;
	while (GetMessage(&msg, whandle, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		try {
			c->draw();
		}
		catch (...) {

		}
	}
}