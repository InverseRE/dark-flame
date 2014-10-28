/**
 * DarkFlame Copyright (C) 2014 Alexey Shumeiko, Alexey Khomyakovsky
 *
 * This file is part of DarkFlame.
 *
 * DarkFlame is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DarkFlame is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DarkFlame.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For more details see LICENSE file.
 */

#include "arch.hpp"
#include "logger.hpp"
#include "window_winapi.hpp"

#if defined (WINDOWS)

#include <gl\gl.h> 
#include <windows.h>

using namespace window;

static LRESULT CALLBACK WndProc(HWND    hwnd,
                                UINT    message,
                                WPARAM  wParam,
                                LPARAM  lParam)
{
    switch (message) {

    case WM_DESTROY:
    case WM_CLOSE:

        ChangeDisplaySettings(NULL, 0);
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hwnd, message, wParam, lParam));
}

WINDOW_WINAPI::WINDOW_WINAPI()
{
    is_configured = false;
}

WINDOW_WINAPI::~WINDOW_WINAPI()
{
    if (is_configured) {
        ChangeDisplaySettings(NULL, 0);
        wglMakeCurrent(hdc, NULL);
        wglDeleteContext(hrc);
        ReleaseDC(hwnd, hdc);
    }
}

WINDOW_WINAPI::WINDOW_WINAPI(const WINDOW_WINAPI& m)
{
    is_configured = false;
}

WINDOW_WINAPI& WINDOW_WINAPI::operator =(const WINDOW_WINAPI& m)
{
    if (this == &m) {
        return *this;
    }

    if (is_configured) {
        ChangeDisplaySettings(NULL, 0);
        wglMakeCurrent(hdc, NULL);
        wglDeleteContext(hrc);
        ReleaseDC(hwnd, hdc);
    }

    is_configured = false;

    return *this;
}

void WINDOW_WINAPI::configure(const char* name, int width, int height, void* hinst)
{

    WNDCLASS wc;
    GLuint PixelFormat;

    if (is_configured) {
        ChangeDisplaySettings(NULL, 0);
        wglMakeCurrent(hdc, NULL);
        wglDeleteContext(hrc);
        ReleaseDC(hwnd, hdc);
    }

    wc.style                = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc          = (WNDPROC)WndProc;
    wc.cbClsExtra           = 0;
    wc.cbWndExtra           = 0;
    wc.hInstance            = hinst;
    wc.hIcon                = NULL;
    wc.hCursor              = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground        = NULL;
    wc.lpszMenuName         = NULL;
    wc.lpszClassName        = "OpenGL WinClass";

    if (!RegisterClass(&wc)) {
        DFLOG.addf("WINDOW_WINAPI: fails to register window class\n");
    }

    hwnd = CreateWindow(
            "OpenGL WinClass",
            "Core_D",
            WS_POPUP |
            WS_CLIPCHILDREN |
            WS_CLIPSIBLINGS,
            0, 0,
            width, height,
            NULL,
            NULL,
            hinst,
            NULL);

    if (!hwnd) {
        DFLOG.addf("WINDOW_WINAPI: fails to create window\n");
    }

    /* TODO: change to english comments */
    static  PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                              // ����� ������
        PFD_DRAW_TO_WINDOW |            // ������ ��� ����
        PFD_SUPPORT_OPENGL |            // ������ ��� OpenGL
        PFD_DOUBLEBUFFER,               // ������ ��� �������� ������
        PFD_TYPE_RGBA,                  // ��������� RGBA ������
        24,                             // ����� ��� ������� �����
        0, 0, 0, 0, 0, 0,               // �������� ����
        1,                              // ����� ������������
        0,                              // ��������� ���
        1,                              // ����� �����������
        0, 0, 0, 0,                     // ���� �����������
        24,                             // Z-�����
        0,                              // ����� ����������
        0,                              // ��������������� ������
        PFD_MAIN_PLANE,
        0,
        0, 0, 0};

    hdc = GetDC(hwnd);

    PixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (!PixelFormat) {
        DFLOG.addf("WINDOW_WINAPI: fails to choose pixel format\n");
    }
    if (!SetPixelFormat(hdc, PixelFormat, &pfd)) {
        DFLOG.addf("WINDOW_WINAPI: can't set pixel format\n");
    }

    hrc = wglCreateContext(hdc);
    if (!hrc) {
        DFLOG.addf("WINDOW_WINAPI: fails to create context\n");
    }
    if (!wglMakeCurrent(hdc, hrc)) {
        DFLOG.addf("WINDOW_WINAPI: can't make current\n");
    }

    /*
     * For full screen mode.
    DEVMODE dmScreenSettings;

    memset(&dmScreenSettings, 0, sizeof(DEVMODE));
    dmScreenSettings.dmSize = sizeof(DEVMODE);
    dmScreenSettings.dmPelsWidth    = width;
    dmScreenSettings.dmPelsHeight   = height;
    dmScreenSettings.dmFields       = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetFocus(hwnd);
    ::ShowCursor(false);
    */

    is_configured = true;
}

void WINDOW_WINAPI::make_current()
{
    if (is_configured) {
        if (!wglMakeCurrent(hdc, hrc)) {
            DFLOG.addf("WINDOW_WINAPI: can't activate GLRC.\n");
        }
    } else {
        DFLOG.addf("WINDOW_WINAPI: try to make current uninited context\n");
    }
}

void WINDOW_WINAPI::swap_buffers()
{
    SwapBuffers(hdc);
}

#endif  // WINDOWS
