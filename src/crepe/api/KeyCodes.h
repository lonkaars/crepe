#pragma once
namespace crepe {
	//! Enumeration for mouse button inputs, including standard and extended buttons.
	enum class MouseButton {
		NONE = 0, //!< No mouse button input.
		LEFT_MOUSE = 1, //!< Left mouse button.
		RIGHT_MOUSE = 2, //!< Right mouse button.
		MIDDLE_MOUSE = 3, //!< Middle mouse button (scroll wheel press).
		X1_MOUSE = 4, //!< First extended mouse button.
		X2_MOUSE = 5, //!< Second extended mouse button.
		SCROLL_UP = 6, //!< Scroll wheel upward movement.
		SCROLL_DOWN = 7, //!< Scroll wheel downward movement.
	};

	//! Enumeration for keyboard key inputs, including printable characters, function keys, and keypad keys.
	enum class Keycode {
		NONE = 0, //!< No key input.
		SPACE = 32, //!< Spacebar.
		APOSTROPHE = 39, //!< Apostrophe (').
		COMMA = 44, //!< Comma (,).
		MINUS = 45, //!< Minus (-).
		PERIOD = 46, //!< Period (.).
		SLASH = 47, //!< Slash (/).
		D0 = 48, //!< Digit 0.
		D1 = 49, //!< Digit 1.
		D2 = 50, //!< Digit 2.
		D3 = 51, //!< Digit 3.
		D4 = 52, //!< Digit 4.
		D5 = 53, //!< Digit 5.
		D6 = 54, //!< Digit 6.
		D7 = 55, //!< Digit 7.
		D8 = 56, //!< Digit 8.
		D9 = 57, //!< Digit 9.
		SEMICOLON = 59, //!< Semicolon (;).
		EQUAL = 61, //!< Equal sign (=).
		A = 65, //!< Key 'A'.
		B = 66, //!< Key 'B'.
		C = 67, //!< Key 'C'.
		D = 68, //!< Key 'D'.
		E = 69, //!< Key 'E'.
		F = 70, //!< Key 'F'.
		G = 71, //!< Key 'G'.
		H = 72, //!< Key 'H'.
		I = 73, //!< Key 'I'.
		J = 74, //!< Key 'J'.
		K = 75, //!< Key 'K'.
		L = 76, //!< Key 'L'.
		M = 77, //!< Key 'M'.
		N = 78, //!< Key 'N'.
		O = 79, //!< Key 'O'.
		P = 80, //!< Key 'P'.
		Q = 81, //!< Key 'Q'.
		R = 82, //!< Key 'R'.
		S = 83, //!< Key 'S'.
		T = 84, //!< Key 'T'.
		U = 85, //!< Key 'U'.
		V = 86, //!< Key 'V'.
		W = 87, //!< Key 'W'.
		X = 88, //!< Key 'X'.
		Y = 89, //!< Key 'Y'.
		Z = 90, //!< Key 'Z'.
		LEFT_BRACKET = 91, //!< Left bracket ([).
		BACKSLASH = 92, //!< Backslash (\).
		RIGHT_BRACKET = 93, //!< Right bracket (]).
		GRAVE_ACCENT = 96, //!< Grave accent (`).
		WORLD1 = 161, //!< Non-US key #1.
		WORLD2 = 162, //!< Non-US key #2.
		ESCAPE = 256, //!< Escape key.
		ENTER = 257, //!< Enter key.
		TAB = 258, //!< Tab key.
		BACKSPACE = 259, //!< Backspace key.
		INSERT = 260, //!< Insert key.
		DELETE = 261, //!< Delete key.
		RIGHT = 262, //!< Right arrow key.
		LEFT = 263, //!< Left arrow key.
		DOWN = 264, //!< Down arrow key.
		UP = 265, //!< Up arrow key.
		PAGE_UP = 266, //!< Page Up key.
		PAGE_DOWN = 267, //!< Page Down key.
		HOME = 268, //!< Home key.
		END = 269, //!< End key.
		CAPS_LOCK = 280, //!< Caps Lock key.
		SCROLL_LOCK = 281, //!< Scroll Lock key.
		NUM_LOCK = 282, //!< Num Lock key.
		PRINT_SCREEN = 283, //!< Print Screen key.
		PAUSE = 284, //!< Pause key.
		/**
		 * \name Function keys (F1-F25).
		 * \{
		 */
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		/// \}
		/**
		 * \name Keypad digits and operators.
		 * \{
		 */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		/// \}
		/**
		 * \name Modifier keys.
		 * \{
		 */
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		/// \}
		MENU = 348, //!< Menu key.
	};
}
