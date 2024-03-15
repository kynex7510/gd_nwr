#include <Windows.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;

static DWORD removeSizebox(DWORD v) { return v & ~WS_SIZEBOX; }

static BOOL HookCb(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle) {
	return AdjustWindowRectEx(lpRect, removeSizebox(dwStyle), bMenu, dwExStyle);
}

$execute {
	(void)Mod::get()->hook(AdjustWindowRectEx, HookCb, "AdjustWindowRectEx", tulip::hook::TulipConvention::Stdcall);
}

$on_mod(Loaded) {
	auto window = FindWindowW(L"GLFW30", L"Geometry Dash");
	const DWORD styleFlags = GetWindowLongPtrW(window, GWL_STYLE);
	SetWindowLongPtrW(window, GWL_STYLE, removeSizebox(styleFlags));
}