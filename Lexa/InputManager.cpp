#include <GLFW/glfw3.h>

#include "InputManager.h"


namespace Lexa
{
	EventHandler<InputManager::OnWindowResizeParams>& InputManager::s_OnWindowResize = EventHandler<InputManager::OnWindowResizeParams>::Instance("WindowResizeCallback");
	EventHandler<InputManager::OnScrollParams>& InputManager::s_OnScroll = EventHandler<InputManager::OnScrollParams>::Instance("ScrollCallback");
	EventHandler<InputManager::OnCharacterInputParams>& InputManager::s_OnCharacterInput = EventHandler<InputManager::OnCharacterInputParams>::Instance("CharacterCallback");
	EventHandler<InputManager::OnKeyInputParams>& InputManager::s_OnKeyInput = EventHandler<InputManager::OnKeyInputParams>::Instance("KeyCallback");
	EventHandler<InputManager::OnMouseButtonParams>& InputManager::s_OnMouseButton = EventHandler<InputManager::OnMouseButtonParams>::Instance("MouseButtonCallback");
	EventHandler<InputManager::OnMouseMoveParams>& InputManager::s_OnMouseMove = EventHandler<InputManager::OnMouseMoveParams>::Instance("MouseMoveCallback");


	static const std::unordered_map<int, InputManager::Key> s_Keys
	{
		{GLFW_KEY_SPACE            ,InputManager::Key::SPACE        },
		{GLFW_KEY_APOSTROPHE       ,InputManager::Key::APOSTROPHE   }, 
		{GLFW_KEY_COMMA            ,InputManager::Key::COMMA        }, 
		{GLFW_KEY_MINUS            ,InputManager::Key::MINUS        }, 
		{GLFW_KEY_PERIOD           ,InputManager::Key::PERIOD       }, 
		{GLFW_KEY_SLASH            ,InputManager::Key::SLASH        }, 
		{GLFW_KEY_0                ,InputManager::Key::ZERO         },
		{GLFW_KEY_1                ,InputManager::Key::ONE          },
		{GLFW_KEY_2                ,InputManager::Key::TWO          },
		{GLFW_KEY_3                ,InputManager::Key::THREE        },
		{GLFW_KEY_4                ,InputManager::Key::FOUR         },
		{GLFW_KEY_5                ,InputManager::Key::FIVE         },
		{GLFW_KEY_6                ,InputManager::Key::SIX          },
		{GLFW_KEY_7                ,InputManager::Key::SEVEN        },
		{GLFW_KEY_8                ,InputManager::Key::EIGHT        },
		{GLFW_KEY_9                ,InputManager::Key::NINE         },
		{GLFW_KEY_SEMICOLON        ,InputManager::Key::SEMICOLON    }, 
		{GLFW_KEY_EQUAL            ,InputManager::Key::EQUAL        }, 
		{GLFW_KEY_A                ,InputManager::Key::A            },
		{GLFW_KEY_B                ,InputManager::Key::B            },
		{GLFW_KEY_C                ,InputManager::Key::C            },
		{GLFW_KEY_D                ,InputManager::Key::D            },
		{GLFW_KEY_E                ,InputManager::Key::E            },
		{GLFW_KEY_F                ,InputManager::Key::F            },
		{GLFW_KEY_G                ,InputManager::Key::G            },
		{GLFW_KEY_H                ,InputManager::Key::H            },
		{GLFW_KEY_I                ,InputManager::Key::I            },
		{GLFW_KEY_J                ,InputManager::Key::J            },
		{GLFW_KEY_K                ,InputManager::Key::K            },
		{GLFW_KEY_L                ,InputManager::Key::L            },
		{GLFW_KEY_M                ,InputManager::Key::M            },
		{GLFW_KEY_N                ,InputManager::Key::N            },
		{GLFW_KEY_O                ,InputManager::Key::O            },
		{GLFW_KEY_P                ,InputManager::Key::P            },
		{GLFW_KEY_Q                ,InputManager::Key::Q            },
		{GLFW_KEY_R                ,InputManager::Key::R            },
		{GLFW_KEY_S                ,InputManager::Key::S            },
		{GLFW_KEY_T                ,InputManager::Key::T            },
		{GLFW_KEY_U                ,InputManager::Key::U            },
		{GLFW_KEY_V                ,InputManager::Key::V            },
		{GLFW_KEY_W                ,InputManager::Key::W            },
		{GLFW_KEY_X                ,InputManager::Key::X            },
		{GLFW_KEY_Y                ,InputManager::Key::Y            },
		{GLFW_KEY_Z                ,InputManager::Key::Z            },
		{GLFW_KEY_LEFT_BRACKET     ,InputManager::Key::LEFT_BRACKET }, 
		{GLFW_KEY_BACKSLASH        ,InputManager::Key::BACKSLASH    }, 
		{GLFW_KEY_RIGHT_BRACKET    ,InputManager::Key::RIGHT_BRACKET}, 
		{GLFW_KEY_GRAVE_ACCENT     ,InputManager::Key::GRAVE_ACCENT }, 
		{GLFW_KEY_WORLD_1          ,InputManager::Key::WORLD_1      }, 
		{GLFW_KEY_WORLD_2          ,InputManager::Key::WORLD_2      }, 
		{GLFW_KEY_ESCAPE           ,InputManager::Key::ESCAPE       },
		{GLFW_KEY_ENTER            ,InputManager::Key::ENTER        },
		{GLFW_KEY_TAB              ,InputManager::Key::TAB          },
		{GLFW_KEY_BACKSPACE        ,InputManager::Key::BACKSPACE    },
		{GLFW_KEY_INSERT           ,InputManager::Key::INSERT       },
		{GLFW_KEY_DELETE           ,InputManager::Key::DELETE       },
		{GLFW_KEY_RIGHT            ,InputManager::Key::RIGHT        },
		{GLFW_KEY_LEFT             ,InputManager::Key::LEFT         },
		{GLFW_KEY_DOWN             ,InputManager::Key::DOWN         },
		{GLFW_KEY_UP               ,InputManager::Key::UP           },
		{GLFW_KEY_PAGE_UP          ,InputManager::Key::PAGE_UP      },
		{GLFW_KEY_PAGE_DOWN        ,InputManager::Key::PAGE_DOWN    },
		{GLFW_KEY_HOME             ,InputManager::Key::HOME         },
		{GLFW_KEY_END              ,InputManager::Key::END          },
		{GLFW_KEY_CAPS_LOCK        ,InputManager::Key::CAPS_LOCK    },
		{GLFW_KEY_SCROLL_LOCK      ,InputManager::Key::SCROLL_LOCK  },
		{GLFW_KEY_NUM_LOCK         ,InputManager::Key::NUM_LOCK     },
		{GLFW_KEY_PRINT_SCREEN     ,InputManager::Key::PRINT_SCREEN },
		{GLFW_KEY_PAUSE            ,InputManager::Key::PAUSE        },
		{GLFW_KEY_F1               ,InputManager::Key::F1           },
		{GLFW_KEY_F2               ,InputManager::Key::F2           },
		{GLFW_KEY_F3               ,InputManager::Key::F3           },
		{GLFW_KEY_F4               ,InputManager::Key::F4           },
		{GLFW_KEY_F5               ,InputManager::Key::F5           },
		{GLFW_KEY_F6               ,InputManager::Key::F6           },
		{GLFW_KEY_F7               ,InputManager::Key::F7           },
		{GLFW_KEY_F8               ,InputManager::Key::F8           },
		{GLFW_KEY_F9               ,InputManager::Key::F9           },
		{GLFW_KEY_F10              ,InputManager::Key::F10          },
		{GLFW_KEY_F11              ,InputManager::Key::F11          },
		{GLFW_KEY_F12              ,InputManager::Key::F12          },
		{GLFW_KEY_F13              ,InputManager::Key::F13          },
		{GLFW_KEY_F14              ,InputManager::Key::F14          },
		{GLFW_KEY_F15              ,InputManager::Key::F15          },
		{GLFW_KEY_F16              ,InputManager::Key::F16          },
		{GLFW_KEY_F17              ,InputManager::Key::F17          },
		{GLFW_KEY_F18              ,InputManager::Key::F18          },
		{GLFW_KEY_F19              ,InputManager::Key::F19          },
		{GLFW_KEY_F20              ,InputManager::Key::F20          },
		{GLFW_KEY_F21              ,InputManager::Key::F21          },
		{GLFW_KEY_F22              ,InputManager::Key::F22          },
		{GLFW_KEY_F23              ,InputManager::Key::F23          },
		{GLFW_KEY_F24              ,InputManager::Key::F24          },
		{GLFW_KEY_F25              ,InputManager::Key::F25          },
		{GLFW_KEY_KP_0             ,InputManager::Key::KP_0         },
		{GLFW_KEY_KP_1             ,InputManager::Key::KP_1         },
		{GLFW_KEY_KP_2             ,InputManager::Key::KP_2         },
		{GLFW_KEY_KP_3             ,InputManager::Key::KP_3         },
		{GLFW_KEY_KP_4             ,InputManager::Key::KP_4         },
		{GLFW_KEY_KP_5             ,InputManager::Key::KP_5         },
		{GLFW_KEY_KP_6             ,InputManager::Key::KP_6         },
		{GLFW_KEY_KP_7             ,InputManager::Key::KP_7         },
		{GLFW_KEY_KP_8             ,InputManager::Key::KP_8         },
		{GLFW_KEY_KP_9             ,InputManager::Key::KP_9         },
		{GLFW_KEY_KP_DECIMAL       ,InputManager::Key::KP_DECIMAL   },
		{GLFW_KEY_KP_DIVIDE        ,InputManager::Key::KP_DIVIDE    },
		{GLFW_KEY_KP_MULTIPLY      ,InputManager::Key::KP_MULTIPLY  },
		{GLFW_KEY_KP_SUBTRACT      ,InputManager::Key::KP_SUBTRACT  },
		{GLFW_KEY_KP_ADD           ,InputManager::Key::KP_ADD       },
		{GLFW_KEY_KP_ENTER         ,InputManager::Key::KP_ENTER     },
		{GLFW_KEY_KP_EQUAL         ,InputManager::Key::KP_EQUAL     },
		{GLFW_KEY_LEFT_SHIFT       ,InputManager::Key::LEFT_SHIFT   },
		{GLFW_KEY_LEFT_CONTROL     ,InputManager::Key::LEFT_CONTROL },
		{GLFW_KEY_LEFT_ALT         ,InputManager::Key::LEFT_ALT     },
		{GLFW_KEY_LEFT_SUPER       ,InputManager::Key::LEFT_SUPER   },
		{GLFW_KEY_RIGHT_SHIFT      ,InputManager::Key::RIGHT_SHIFT  },
		{GLFW_KEY_RIGHT_CONTROL    ,InputManager::Key::RIGHT_CONTROL},
		{GLFW_KEY_RIGHT_ALT        ,InputManager::Key::RIGHT_ALT    },
		{GLFW_KEY_RIGHT_SUPER      ,InputManager::Key::RIGHT_SUPER  },
		{GLFW_KEY_MENU             ,InputManager::Key::MENU         },
	};


	static const std::unordered_map<int, InputManager::Action> s_Actions
	{
		{ GLFW_PRESS, InputManager::Action::PRESS },
		{ GLFW_RELEASE, InputManager::Action::RELEASE },
		{ GLFW_REPEAT, InputManager::Action::REPEAT }
	};


	static const std::unordered_map<int, InputManager::MouseButton> s_MouseButtons
	{
		{ GLFW_MOUSE_BUTTON_1, InputManager::MouseButton::LEFT },
		{ GLFW_MOUSE_BUTTON_2, InputManager::MouseButton::RIGHT },
		{ GLFW_MOUSE_BUTTON_3, InputManager::MouseButton::MIDDLE }
	};


	static std::vector<InputManager::Mod> Mods(int mods)
	{
		std::vector<InputManager::Mod> ret;
		if (mods & GLFW_MOD_ALT) ret.push_back(InputManager::Mod::ALT);
		if (mods & GLFW_MOD_CAPS_LOCK) ret.push_back(InputManager::Mod::CAPS_LOCK);
		if (mods & GLFW_MOD_CONTROL) ret.push_back(InputManager::Mod::CTRL);
		if (mods & GLFW_MOD_NUM_LOCK) ret.push_back(InputManager::Mod::NUM_LOCK);
		if (mods & GLFW_MOD_SHIFT) ret.push_back(InputManager::Mod::SHIFT);
		if (mods & GLFW_MOD_SUPER) ret.push_back(InputManager::Mod::SUPER);
		return ret;
	};


	void GLFWWindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		InputManager::s_OnWindowResize(InputManager::OnWindowResizeParams{ width, height });
	}


	void GLFWScrollCallback(GLFWwindow* window, double x, double y)
	{
		InputManager::s_OnScroll(InputManager::OnScrollParams{ y });
	}


	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputManager::s_OnKeyInput(InputManager::OnKeyInputParams{ s_Keys.at(key), s_Actions.at(action), Mods(mods) });
	}


	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		InputManager::s_OnMouseButton(InputManager::OnMouseButtonParams{ s_MouseButtons.at(button), s_Actions.at(action), Mods(mods) });
	}


	void GLFWCharacterCallback(GLFWwindow* window, unsigned codepoint)
	{
		auto utf8encode = [](unsigned _codepoint)
		{
			std::string res = "";
			
			if (_codepoint <= 0x7F)
			{
				res += (char)_codepoint;
			}

			else if (_codepoint <= 0x07FF) 
			{
				res += (char)(((_codepoint >> 6) & 0x1F) | 0xC0);
				res += (char)(((_codepoint >> 0) & 0x3F) | 0x80);
			}

			else if (_codepoint <= 0xFFFF)
			{
				res += (char)(((_codepoint >> 12) & 0x0F) | 0xE0);
				res += (char)(((_codepoint >> 6) & 0x3F) | 0x80);
				res += (char)(((_codepoint >> 0) & 0x3F) | 0x80);
			}

			else if (_codepoint <= 0x10FFFF)
			{
				// 4-byte unicode
				res += (char)(((_codepoint >> 18) & 0x07) | 0xF0);
				res += (char)(((_codepoint >> 12) & 0x3F) | 0x80);
				res += (char)(((_codepoint >> 6) & 0x3F) | 0x80);
				res += (char)(((_codepoint >> 0) & 0x3F) | 0x80);
			}

			return res;
		};

		InputManager::s_OnCharacterInput(InputManager::OnCharacterInputParams{ utf8encode(codepoint) });
	}


	void GLFWCursorMoveCallback(GLFWwindow* window, double x, double y)
	{
		static double xpos, ypos;
		static bool once = false;

		if (!once)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			once = true;
		}

		else
		{
			double xDelta = x - xpos;
			double yDelta = -(y - ypos);
			xpos = x;
			ypos = y;
			InputManager::s_OnMouseMove(InputManager::OnMouseMoveParams{ xDelta, yDelta });
		}
	}


	void InputManager::SetContext(Window& window)
	{
		glfwSetWindowSizeCallback(window.Get(), GLFWWindowResizeCallback);
		glfwSetScrollCallback(window.Get(), GLFWScrollCallback);
		glfwSetMouseButtonCallback(window.Get(), GLFWMouseButtonCallback);
		glfwSetCursorPosCallback(window.Get(), GLFWCursorMoveCallback);
		glfwSetKeyCallback(window.Get(), GLFWKeyCallback);
		glfwSetCharCallback(window.Get(), GLFWCharacterCallback);
	}


	std::pair<double, double> InputManager::GetCursorPos(Window& window)
	{
		double x, y;
		glfwGetCursorPos(window.Get(),  & x, &y);
		y = window.GetHeight() - y;
		return std::make_pair(x, y);
	}
}