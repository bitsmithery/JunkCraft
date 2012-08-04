#include <set>
#include <cassert>

#define _WIN32_WINNT   0x0501
#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "ui.hpp"

namespace app
{
	namespace ui
	{
		static LPCTSTR const window_class_name = TEXT("APP_UI_DISPLAY");

		static HWND hwnd;
		static HDC hdc;
		static HGLRC hglrc;

		namespace display
		{
			std::vector<util::sizeu> get_valid_sizes()
			{
				std::vector<util::sizeu> valid_sizes;
				DEVMODE devmode;
				devmode.dmSize = sizeof(DEVMODE);
				devmode.dmDriverExtra = 0;
				for (DWORD i = 0; EnumDisplaySettings(NULL, i, &devmode); ++i)
					if (devmode.dmBitsPerPel == 32) // only consider 32 bit color modes
					{
						util::sizeu size = {devmode.dmPelsWidth, devmode.dmPelsHeight};
						if (std::find(valid_sizes.begin(), valid_sizes.end(), size) == valid_sizes.end())
							valid_sizes.push_back(size);
					}
				std::sort(valid_sizes.begin(), valid_sizes.end(),
					[](util::sizeu const& a, util::sizeu const& b){
						return a.get_area() > b.get_area();
					}
				);
				return valid_sizes;
			};

			namespace event
			{
				std::function<void(util::sizeu const& new_size)> size_change;
			}

			static util::sizeu size;

			util::sizeu get_size()
			{
				return size;
			}

			void set_size(util::sizeu const& new_size)
			{
				DEVMODE dm;
				dm.dmSize = sizeof(DEVMODE);
				dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
				dm.dmBitsPerPel = 32;
				dm.dmPelsWidth = new_size.x;
				dm.dmPelsHeight = new_size.y;

				if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
					throw invalid_size();

				SetWindowPos
				(
					hwnd,
					HWND_TOP,
					0, 0,
					new_size.x, new_size.y,
					SWP_NOCOPYBITS | SWP_NOREDRAW
				);
			}

			void swap_buffers()
			{
				SwapBuffers(hdc);
			}
		}

		static void dispatch_display_event_size_change(util::sizeu const& new_size)
		{
			display::size = new_size;
			if (display::event::size_change != nullptr)
				display::event::size_change(new_size);
		}

		namespace keyboard
		{
			namespace event
			{
				std::map<std::string, std::function<void()>> key_press;
				std::map<std::string, std::function<void()>> key_release;
			}

			static std::set<std::string> keys_pressed;

			bool is_key_pressed(std::string const& key)
			{
				return keys_pressed.find(key) != keys_pressed.end();
			}

			namespace event
			{
				std::function<void(std::string const& text)> text_input;
			}
		}

		static void dispatch_keyboard_event_key_press(std::string const& key)
		{
			keyboard::keys_pressed.insert(key);
			auto handler = keyboard::event::key_press.find(key);
			if (handler != keyboard::event::key_press.end())
			{
				if (handler->second != nullptr)
					handler->second();
				else
					keyboard::event::key_press.erase(key);
			}
		}

		static void dispatch_keyboard_event_key_release(std::string const& key)
		{
			keyboard::keys_pressed.erase(key);
			auto handler = keyboard::event::key_release.find(key);
			if (handler != keyboard::event::key_release.end())
			{
				if (handler->second != nullptr)
					handler->second();
				else
					keyboard::event::key_release.erase(key);
			}
		}

		static void dispatch_keyboard_event_text_input(std::string const& text)
		{
			if (keyboard::event::text_input != nullptr)
				keyboard::event::text_input(text);
		}


		namespace mouse
		{
			namespace event
			{
				std::map<std::string, std::function<void()>> button_press;
				std::map<std::string, std::function<void()>> button_release;
			}

			static std::set<std::string> buttons_pressed;

			bool is_button_pressed(std::string const& button)
			{
				return buttons_pressed.find(button) != buttons_pressed.end();
			}

			namespace event
			{
				std::function<void(util::pointu const& new_position)> position_change;
			}

			static util::pointu position;

			util::pointu get_position()
			{
				return position;
			}

			void set_position(util::pointu const& new_position)
			{
				assert(false && "not implemented");
			}

			namespace event
			{
				std::function<void(float delta)> scroll;
			}
		}

		static void dispatch_mouse_event_button_press(std::string const& button)
		{
			mouse::buttons_pressed.insert(button);
			auto handler = mouse::event::button_press.find(button);
			if (handler != mouse::event::button_press.end())
			{
				if (handler->second != nullptr)
					handler->second();
				else
					mouse::event::button_press.erase(button);
			}
		}

		static void dispatch_mouse_event_button_release(std::string const& button)
		{
			mouse::buttons_pressed.erase(button);
			auto handler = mouse::event::button_release.find(button);
			if (handler != mouse::event::button_release.end())
			{
				if (handler->second != nullptr)
					handler->second();
				else
					mouse::event::button_release.erase(button);
			}
		}

		static void dispatch_mouse_event_position_change(util::pointu const& new_position)
		{
			mouse::position = new_position;
			if (mouse::event::position_change != nullptr)
				mouse::event::position_change(new_position);
		}

		static void dispatch_mouse_event_scroll(float delta)
		{
			if (mouse::event::scroll != nullptr)
				mouse::event::scroll(delta);
		}

		static char const* translate_key(WPARAM wparam, LPARAM lparam)
		{
			switch (wparam)
			{
					// check the scancode to distinguish between left and right shift
				case VK_SHIFT :
				{
					static UINT lShift = MapVirtualKey(VK_LSHIFT, 0);
					UINT scancode = static_cast<UINT>((lparam & (0xFF << 16)) >> 16);
					return scancode == lShift ? "LEFT_SHIFT" : "RIGHT_SHIFT";
				}
					// check the "extended" flag to distinguish between left and right alt
				case VK_MENU : return (HIWORD(lparam) & KF_EXTENDED) ? "RIGHT_ALT" : "LEFT_ALT";
					// check the "extended" flag to distinguish between left and right control
				case VK_CONTROL : return (HIWORD(lparam) & KF_EXTENDED) ? "CTRL_RIGHT" : "CTRL_LEFT";
					// Other keys are reported properly
				case VK_LWIN:       return "SYSTEM_LEFT";
				case VK_RWIN:       return "SYSTEM_RIGHT";
				case VK_APPS:       return "MENU";
				case VK_OEM_1:      return "SEMICOLON";
				case VK_OEM_2:      return "SLASH";
				case VK_OEM_PLUS:   return "EQUAL";
				case VK_OEM_MINUS:  return "DASH";
				case VK_OEM_4:      return "BRACKET_LEFT";
				case VK_OEM_6:      return "BRACKET_RIGHT";
				case VK_OEM_COMMA:  return "COMMA";
				case VK_OEM_PERIOD: return "PERIOD";
				case VK_OEM_7:      return "QUOTE";
				case VK_OEM_5:      return "BACKSLASH";
				case VK_OEM_3:      return "TILDE";
				case VK_ESCAPE:     return "ESCAPE";
				case VK_SPACE:      return "SPACE";
				case VK_RETURN:     return "ENTER";
				case VK_BACK:       return "BACK";
				case VK_TAB:        return "TAB";
				case VK_PRIOR:      return "PAGE_UP";
				case VK_NEXT:       return "PAGE_DOWN";
				case VK_END:        return "END";
				case VK_HOME:       return "HOME";
				case VK_INSERT:     return "INSERT";
				case VK_DELETE:     return "DELETE";
				case VK_ADD:        return "ADD";
				case VK_SUBTRACT:   return "SUBTRACT";
				case VK_MULTIPLY:   return "MULTIPLY";
				case VK_DIVIDE:     return "DIVIDE";
				case VK_PAUSE:      return "PAUSE";
				case VK_F1:         return "F1";
				case VK_F2:         return "F2";
				case VK_F3:         return "F3";
				case VK_F4:         return "F4";
				case VK_F5:         return "F5";
				case VK_F6:         return "F6";
				case VK_F7:         return "F7";
				case VK_F8:         return "F8";
				case VK_F9:         return "F9";
				case VK_F10:        return "F10";
				case VK_F11:        return "F11";
				case VK_F12:        return "F12";
				case VK_LEFT:       return "ARROW_LEFT";
				case VK_RIGHT:      return "ARROW_RIGHT";
				case VK_UP:         return "ARROW_UP";
				case VK_DOWN:       return "ARROW_DOWN";
				case VK_NUMPAD0:    return "NUMPAD_0";
				case VK_NUMPAD1:    return "NUMPAD_1";
				case VK_NUMPAD2:    return "NUMPAD_2";
				case VK_NUMPAD3:    return "NUMPAD_3";
				case VK_NUMPAD4:    return "NUMPAD_4";
				case VK_NUMPAD5:    return "NUMPAD_5";
				case VK_NUMPAD6:    return "NUMPAD_6";
				case VK_NUMPAD7:    return "NUMPAD_7";
				case VK_NUMPAD8:    return "NUMPAD_8";
				case VK_NUMPAD9:    return "NUMPAD_9";
				case 'A':           return "A";
				case 'Z':           return "Z";
				case 'E':           return "E";
				case 'R':           return "R";
				case 'T':           return "T";
				case 'Y':           return "Y";
				case 'U':           return "U";
				case 'I':           return "I";
				case 'O':           return "0";
				case 'P':           return "P";
				case 'Q':           return "Q";
				case 'S':           return "S";
				case 'D':           return "D";
				case 'F':           return "F";
				case 'G':           return "G";
				case 'H':           return "H";
				case 'J':           return "J";
				case 'K':           return "K";
				case 'L':           return "L";
				case 'M':           return "M";
				case 'W':           return "W";
				case 'X':           return "X";
				case 'C':           return "C";
				case 'V':           return "V";
				case 'B':           return "B";
				case 'N':           return "N";
				case '0':           return "0";
				case '1':           return "1";
				case '2':           return "2";
				case '3':           return "3";
				case '4':           return "4";
				case '5':           return "5";
				case '6':           return "6";
				case '7':           return "7";
				case '8':           return "8";
				case '9':           return "9";
			}
			return "";
		}

		static LRESULT WINAPI window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
		{
			switch (message)
			{
				case WM_CREATE:
				{
					CREATESTRUCT* cs = (CREATESTRUCT*)lparam;
					dispatch_display_event_size_change({cs->cx, cs->cy});
					break;
				}

				case WM_SIZE:
				{
					dispatch_display_event_size_change({LOWORD(lparam), HIWORD(lparam)});
					break;
				}

				case WM_SETFOCUS:
				{
					ShowWindow(hwnd, SW_RESTORE);
					RECT rect = {0, 0, (LONG)display::size.x, (LONG)display::size.y};
					ClipCursor(&rect);
					break;
				}

				case WM_KILLFOCUS:
				{
					ShowWindow(hwnd, SW_MINIMIZE);
					ClipCursor(NULL);
					break;
				}

				case WM_KEYDOWN:
				{
					dispatch_keyboard_event_key_press(translate_key(wparam, lparam));
					break;
				}

				case WM_KEYUP:
				{
					dispatch_keyboard_event_key_release(translate_key(wparam, lparam));
					break;
				}

				case WM_CHAR:
				{
						// input arrives as utf16 units, which can be parts of surrogate pairs, so we accumulate them until they form valid sequence
					static WCHAR text_input[2];
					static int text_input_size = 0;
					text_input[text_input_size++] = (WCHAR)wparam;
					char text_output[4];
					int text_output_size = WideCharToMultiByte(CP_UTF8, 0, text_input, text_input_size, text_output, 4, NULL, NULL);
					if (text_output_size != 0)
					{
						dispatch_keyboard_event_text_input(std::string(text_output, text_output_size));
						text_input_size = 0;
					}
					break;
				}

				case WM_LBUTTONDOWN:
				{
					dispatch_mouse_event_button_press("LEFT");
					break;
				}

				case WM_MBUTTONDOWN:
				{
					dispatch_mouse_event_button_press("MIDDLE");
					break;
				}

				case WM_RBUTTONDOWN:
				{
					dispatch_mouse_event_button_press("RIGHT");
					break;
				}

				case WM_LBUTTONUP:
				{
					dispatch_mouse_event_button_release("LEFT");
					break;
				}

				case WM_MBUTTONUP:
				{
					dispatch_mouse_event_button_release("MIDDLE");
					break;
				}

				case WM_RBUTTONUP:
				{
					dispatch_mouse_event_button_release("RIGHT");
					break;
				}

				case WM_MOUSEMOVE:
				{
					dispatch_mouse_event_position_change({LOWORD(lparam), (display::size.y - 1) - HIWORD(lparam)});
					break;
				}

				case WM_MOUSEWHEEL:
				{
						// cast to SHORT to correctly make it signed
					SHORT distance = HIWORD(wparam);
					float delta = float(distance)/float(WHEEL_DELTA);
					dispatch_mouse_event_scroll(delta);
					break;
				}
			}
			return DefWindowProc(hwnd, message, wparam, lparam);
		}

		bool dispatch_event()
		{
			MSG msg;
			if (!PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
				return false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}

		static unsigned initialization_count = 0u;

		initializer::initializer()
		{
			if (initialization_count++ == 0)
			{
				WNDCLASSEX wcex;
				wcex.cbSize = sizeof(WNDCLASSEX);
				wcex.style = CS_OWNDC | CS_NOCLOSE;
				wcex.lpfnWndProc = window_proc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = 0;
				wcex.hInstance = NULL;
				wcex.hIcon = NULL;
				wcex.hCursor = NULL;
				wcex.hbrBackground = NULL;
				wcex.lpszMenuName = NULL;
				wcex.lpszClassName = window_class_name;
				wcex.hIconSm = NULL;
				RegisterClassEx(&wcex);

				DEVMODE dm;
				dm.dmSize = sizeof(DEVMODE);
				dm.dmDriverExtra = 0;
				EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

				hwnd = CreateWindow
				(
					window_class_name,
					TEXT(""),
					WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,
					0, 0,
					dm.dmPelsWidth, dm.dmPelsHeight,
					NULL,
					NULL,
					NULL,
					NULL
				);

				hdc = GetDC(hwnd);

				PIXELFORMATDESCRIPTOR pfd;
				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
				pfd.iPixelType = PFD_TYPE_RGBA;
				pfd.cColorBits = 24;
				pfd.cAlphaBits = 8;
				pfd.cAccumBits = 32;
				pfd.cDepthBits = 24;
				pfd.cStencilBits = 8;
				pfd.cAuxBuffers = 4;
				pfd.iLayerType = PFD_MAIN_PLANE;
				int pixel_format_index = ChoosePixelFormat(hdc, &pfd);
				SetPixelFormat(hdc, pixel_format_index, &pfd);

				hglrc = wglCreateContext(hdc);

				wglMakeCurrent(hdc, hglrc);

				ShowCursor(FALSE);
			}
		}

		initializer::~initializer()
		{
			if (--initialization_count == 0)
			{
				ShowCursor(TRUE);

				wglMakeCurrent(NULL, NULL);

				wglDeleteContext(hglrc);

				ReleaseDC(hwnd, hdc);

				ChangeDisplaySettings(NULL, 0);

				DestroyWindow(hwnd);

				UnregisterClass(window_class_name, NULL);
			}
		}
	}
}


