#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    // get resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // center monitor
    int centerx = screenWidth / 2;
    int centery = screenHeight / 2;
    
    // Получение контекста устройства (DC) экрана
    HDC screenDC = GetDC(NULL);
    if (!screenDC) { 
        cout << "Failed to get screen DC" << endl;
        return 1;
    }

    // record color pixel
    COLORREF originalColor = GetPixel(screenDC, centerx, centery);

    cout << "The color has been recorded... Press ESC to exit" << endl;

    while (true)
    {   
        // ::
        COLORREF currColor = GetPixel(screenDC, centerx, centery);

        // chek the color change
        if (currColor != originalColor)
        {
            // 
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

            cout << "Pixel color has changed, clicking button" << endl;
            
            Sleep(500);

            // update color
            originalColor = GetPixel(screenDC, centerx, centery);
        }
        
        Sleep(20);

        // 
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }

    //
    ReleaseDC(NULL, screenDC);
    return 0;
}
