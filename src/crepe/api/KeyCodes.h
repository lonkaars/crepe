#pragma once

//! \file InputEnums.h
//! \brief Defines enums for mouse buttons and keyboard keycodes used in the application.

//! \enum MouseButton
//! \brief Enumeration for mouse button inputs, including standard and extended buttons.
enum class MouseButton {
    //! No mouse button input.
    NONE = 0,
    //! Left mouse button.
    LEFT_MOUSE = 1,
    //! Right mouse button.
    RIGHT_MOUSE = 2,
    //! Middle mouse button (scroll wheel press).
    MIDDLE_MOUSE = 3,
    //! First extended mouse button.
    X1_MOUSE = 4,
    //! Second extended mouse button.
    X2_MOUSE = 5,
    //! Scroll wheel upward movement.
    SCROLL_UP = 6,
    //! Scroll wheel downward movement.
    SCROLL_DOWN = 7
};

//! \enum Keycode
//! \brief Enumeration for keyboard key inputs, including printable characters, function keys, and keypad keys.
enum class Keycode : int {
    //! No key input.
    NONE = 0,
    //! Spacebar.
    SPACE = 32,
    //! Apostrophe (').
    APOSTROPHE = 39,
    //! Comma (,).
    COMMA = 44,
    //! Minus (-).
    MINUS = 45,
    //! Period (.).
    PERIOD = 46,
    //! Slash (/).
    SLASH = 47,
    //! Digit 0.
    D0 = 48,
    //! Digit 1.
    D1 = 49,
    //! Digit 2.
    D2 = 50,
    //! Digit 3.
    D3 = 51,
    //! Digit 4.
    D4 = 52,
    //! Digit 5.
    D5 = 53,
    //! Digit 6.
    D6 = 54,
    //! Digit 7.
    D7 = 55,
    //! Digit 8.
    D8 = 56,
    //! Digit 9.
    D9 = 57,
    //! Semicolon (;).
    SEMICOLON = 59,
    //! Equal sign (=).
    EQUAL = 61,
    //! Key 'A'.
    A = 65,
    //! Key 'B'.
    B = 66,
    //! Key 'C'.
    C = 67,
    //! Key 'D'.
    D = 68,
    //! Key 'E'.
    E = 69,
    //! Key 'F'.
    F = 70,
    //! Key 'G'.
    G = 71,
    //! Key 'H'.
    H = 72,
    //! Key 'I'.
    I = 73,
    //! Key 'J'.
    J = 74,
    //! Key 'K'.
    K = 75,
    //! Key 'L'.
    L = 76,
    //! Key 'M'.
    M = 77,
    //! Key 'N'.
    N = 78,
    //! Key 'O'.
    O = 79,
    //! Key 'P'.
    P = 80,
    //! Key 'Q'.
    Q = 81,
    //! Key 'R'.
    R = 82,
    //! Key 'S'.
    S = 83,
    //! Key 'T'.
    T = 84,
    //! Key 'U'.
    U = 85,
    //! Key 'V'.
    V = 86,
    //! Key 'W'.
    W = 87,
    //! Key 'X'.
    X = 88,
    //! Key 'Y'.
    Y = 89,
    //! Key 'Z'.
    Z = 90,
    //! Left bracket ([).
    LEFT_BRACKET = 91,
    //! Backslash (\).
    BACKSLASH = 92,
    //! Right bracket (]).
    RIGHT_BRACKET = 93,
    //! Grave accent (`).
    GRAVE_ACCENT = 96,
    //! Non-US key #1.
    WORLD1 = 161,
    //! Non-US key #2.
    WORLD2 = 162,
    //! Escape key.
    ESCAPE = 256,
    //! Enter key.
    ENTER = 257,
    //! Tab key.
    TAB = 258,
    //! Backspace key.
    BACKSPACE = 259,
    //! Insert key.
    INSERT = 260,
    //! Delete key.
    DELETE = 261,
    //! Right arrow key.
    RIGHT = 262,
    //! Left arrow key.
    LEFT = 263,
    //! Down arrow key.
    DOWN = 264,
    //! Up arrow key.
    UP = 265,
    //! Page Up key.
    PAGE_UP = 266,
    //! Page Down key.
    PAGE_DOWN = 267,
    //! Home key.
    HOME = 268,
    //! End key.
    END = 269,
    //! Caps Lock key.
    CAPS_LOCK = 280,
    //! Scroll Lock key.
    SCROLL_LOCK = 281,
    //! Num Lock key.
    NUM_LOCK = 282,
    //! Print Screen key.
    PRINT_SCREEN = 283,
    //! Pause key.
    PAUSE = 284,
    //! Function keys (F1-F25).
    F1 = 290, F2 = 291, F3 = 292, F4 = 293, F5 = 294,
    F6 = 295, F7 = 296, F8 = 297, F9 = 298, F10 = 299,
    F11 = 300, F12 = 301, F13 = 302, F14 = 303, F15 = 304,
    F16 = 305, F17 = 306, F18 = 307, F19 = 308, F20 = 309,
    F21 = 310, F22 = 311, F23 = 312, F24 = 313, F25 = 314,
    //! Keypad digits and operators.
    KP0 = 320, KP1 = 321, KP2 = 322, KP3 = 323, KP4 = 324,
    KP5 = 325, KP6 = 326, KP7 = 327, KP8 = 328, KP9 = 329,
    KP_DECIMAL = 330, KP_DIVIDE = 331, KP_MULTIPLY = 332,
    KP_SUBTRACT = 333, KP_ADD = 334, KP_ENTER = 335, KP_EQUAL = 336,
    //! Modifier keys.
    LEFT_SHIFT = 340, LEFT_CONTROL = 341, LEFT_ALT = 342, LEFT_SUPER = 343,
    RIGHT_SHIFT = 344, RIGHT_CONTROL = 345, RIGHT_ALT = 346, RIGHT_SUPER = 347,
    //! Menu key.
    MENU = 348
};
