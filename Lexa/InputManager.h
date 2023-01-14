#pragma once

#include "EventHandler.hpp"
#include "Window.h"


namespace Lexa
{

	namespace InputManager
	{
		void SetContext(Window& window);

		std::pair<double, double> GetCursorPos(Window& window);

		enum class Action
		{
			PRESS,
			RELEASE,
			REPEAT
		};

		enum class Mod
		{
			SHIFT,
			CTRL,
			ALT,
			SUPER,
			CAPS_LOCK,
			NUM_LOCK
		};

		enum class MouseButton
		{
			LEFT,
			RIGHT,
			MIDDLE
		};

		enum class Key
		{
			SPACE, APOSTROPHE, COMMA, MINUS, PERIOD, SLASH,
			ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
			SEMICOLON, EQUAL,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET, GRAVE_ACCENT, WORLD_1, WORLD_2,
			ESCAPE, ENTER, TAB, BACKSPACE, INSERT, DELETE, RIGHT, LEFT, DOWN, UP, PAGE_UP, PAGE_DOWN, HOME, END,
			CAPS_LOCK, SCROLL_LOCK, NUM_LOCK, PRINT_SCREEN, PAUSE, 
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
			KP_0, KP_1, KP_2, KP_3, KP_4, KP_5, KP_6, KP_7, KP_8, KP_9, 
			KP_DECIMAL, KP_DIVIDE, KP_MULTIPLY, KP_SUBTRACT, KP_ADD, KP_ENTER, KP_EQUAL, 
			KP_LEFT_SHIFT, KP_LEFT_CONTROL, KP_LEFT_ALT, KP_LEFT_SUPER, KP_RIGHT_SHIFT, KP_RIGHT_CONTROL, KP_RIGHT_ALT, KP_RIGHT_SUPER, 
			LEFT_SHIFT, LEFT_CONTROL, LEFT_ALT, LEFT_SUPER, RIGHT_SHIFT, RIGHT_CONTROL, RIGHT_ALT, RIGHT_SUPER, MENU
		};

		struct OnWindowResizeParams
		{
			int width;
			int height;
		};

		struct OnMouseButtonParams
		{
			MouseButton button;
			Action action;
			std::vector<Mod> mods;
		};

		struct OnScrollParams
		{
			double amount;
		};

		struct OnCharacterInputParams
		{
			std::string c;
		};

		struct OnKeyInputParams
		{
			Key key;
			Action action;
			std::vector<Mod> mods;
		};

		struct OnMouseMoveParams
		{
			double xDelta;
			double yDelta;
		};

		extern EventHandler<OnWindowResizeParams>& s_OnWindowResize;
		extern EventHandler<OnMouseButtonParams>& s_OnMouseButton;
		extern EventHandler<OnScrollParams>& s_OnScroll;
		extern EventHandler<OnCharacterInputParams>& s_OnCharacterInput;
		extern EventHandler<OnKeyInputParams>& s_OnKeyInput;
		extern EventHandler<OnMouseMoveParams>& s_OnMouseMove;
	};
}

