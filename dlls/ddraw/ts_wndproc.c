#include "config.h"
#include "wine/port.h"

#include "ddraw_private.h"

#include <stdbool.h>

bool CaptureMouse = false;
bool MouseIsLocked = false;
bool DrawFPS = false;
bool GameHandlesClose = true;

void mouse_lock(HWND hWnd)
{
    RECT rc;
    POINT pt, pt2;

    GetClientRect(hWnd, &rc);

    // Convert the client area to screen coordinates.
    pt.x = rc.left;
    pt.y = rc.top;

    pt2.x = rc.right;
    pt2.y = rc.bottom;
    ClientToScreen(hWnd, &pt);
    ClientToScreen(hWnd, &pt2);

    SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

    ClipCursor(&rc);
    CaptureMouse = true;
    MouseIsLocked = true;
}

void mouse_unlock(void)
{
    ClipCursor(NULL);
    MouseIsLocked = false;
}

void center_mouse(HWND hWnd)
{
    RECT size;
    POINT pos = { 0, 0 };

    GetClientRect(hWnd, &size);
    ClientToScreen(hWnd, &pos);

    SetCursorPos(size.right / 2 + pos.x, size.bottom / 2 + pos.y);
}


LRESULT CALLBACK TS_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    struct ddraw *this = exclusive_ddraw;

    LRESULT ret = 0;

    static DWORD rememberFPS = -1;

    static int redrawCount = 0;

    switch(uMsg)
    {
        //Workaround for invisible menu on Load/Save/Delete in Tiberian Sun
        case WM_PARENTNOTIFY:
        {
            if (LOWORD(wParam) == WM_DESTROY)
            {
                this->force_update = FALSE;
                redrawCount = 2;
            }
            else  if (LOWORD(wParam) == WM_CREATE)
            {
                this->force_update = TRUE;
                mouse_unlock();
            }
            break;
        }
        case WM_PAINT:
        {
            if (redrawCount > 0)
            {
                redrawCount--;
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN);
            }
            break;
        }

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            if (!MouseIsLocked)
                mouse_lock(hWnd);
            break;

        case WM_ACTIVATE:
            /* keep the cursor restrained after alt-tabbing */
            if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
            {
                if (rememberFPS != -1)
                    this->targetFPS = rememberFPS;

                this->update_interval = 1000 / this->targetFPS;
                this->window_focus = TRUE;

                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN);
            }
            else if (wParam == WA_INACTIVE)
            {
                rememberFPS = this->targetFPS;
                this->targetFPS = 10;
                this->update_interval = 1000 / this->targetFPS;
                this->window_focus = FALSE;
                mouse_unlock();
            }

            if (this->flags & DDSCL_FULLSCREEN)
            {
                if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
                {
                    wined3d_set_adapter_display_mode(this->wined3d, WINED3DADAPTER_DEFAULT, &this->mode);
                    mouse_lock(hWnd);
                }
                else if (wParam == WA_INACTIVE)
                {
                    wined3d_set_adapter_display_mode(this->wined3d, WINED3DADAPTER_DEFAULT, NULL);
                    ShowWindow(hWnd, SW_MINIMIZE);
                }
            }
            else // windowed
            {

            }

            wParam = WA_ACTIVE;
            break;

        case WM_SIZE:
            switch (wParam)
            {
            case SIZE_MAXIMIZED:
            case SIZE_MAXSHOW:
            case SIZE_RESTORED:
                center_mouse(hWnd);
            default: break;
            }
        case WM_MOVE:
            {
                /*POINT p = { 0, 0 };
                ClientToScreen(hWnd, &p);
                GetClientRect(hWnd, &this->winRect);
                OffsetRect(&this->winRect, p.x, p.y);
                */
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN);
                break;
            }

        /* don't ever tell they lose focus for real so they keep drawing
           Used for windowed mode but also fixes YR menus on alt+tab */
        case WM_ACTIVATEAPP:
            wParam = TRUE;
            lParam = 0;
            break;

        /* make windowed games close on X */
        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE && GameHandlesClose != true)
            {
                exit(0);
            }
            break;

        /* Prevent freezing on Alt or F10 in windowed mode */
        case WM_SYSKEYDOWN:
            if (wParam != VK_F4)
                return 0;
            break;

        case WM_KEYDOWN:

            if(wParam == VK_CONTROL || wParam == VK_TAB)
            {
                if(GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_TAB) & 0x8000)
                {
                    mouse_unlock();
                    return 0;
                }
            }
            if ((GetAsyncKeyState(VK_RMENU) & 0x8000) && GetAsyncKeyState(VK_RCONTROL) & 0x8000)
            {
                if (CaptureMouse)
                {
                    mouse_unlock();
                    CaptureMouse = false;
                }
                else
                {
                    mouse_lock(hWnd);
                    CaptureMouse = true;
                }
                return 0;
            }
            if ((wParam == 0x52) && (GetAsyncKeyState(VK_RCONTROL) & 0x8000))
            {
                DrawFPS = !DrawFPS;
                this->force_update = !this->force_update;
            }

            if ((wParam == VK_PRIOR) && (GetAsyncKeyState(VK_RCONTROL) & 0x8000))
            {
                this->targetFPS = this->targetFPS + 20;
                this->update_interval = 1000 / this->targetFPS;
            }

            if ((wParam == VK_NEXT) && (GetAsyncKeyState(VK_RCONTROL) & 0x8000))
            {
                this->targetFPS = this->targetFPS > 20 ? this->targetFPS - 20 : this->targetFPS;
                this->update_interval = 1000 / this->targetFPS;
            }

            break;

        case WM_MOUSELEAVE:
        case WM_CLOSE:
            mouse_unlock();
            return 0;
            break;
    }
    if (this && this->wndProc)
    {
        if (IsWindowUnicode(hWnd))
            ret = CallWindowProcW(this->wndProc, hWnd, uMsg, wParam, lParam);
        else
            ret = CallWindowProcA(this->wndProc,hWnd, uMsg, wParam, lParam);
    }

    return ret;
}
