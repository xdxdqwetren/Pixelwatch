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


    bool botEnable = false;// flag position bot
    cout << "bot started. Press F3 for turn on / off... Press ESC to exit" << endl;

    
    while (true){   
        if (GetAsyncKeyState(VK_F3) & 0x8000){
            botEnable = !botEnable;
            if (botEnable){
                cout << "bot activated" << endl;
                originalColor = GetPixel(screenDC, centerx, centery);

            
            }else{
                cout << "bot unactivate" << endl;
            }
            Sleep(300);
        }
        
        
        if (botEnable){
            // ::
            COLORREF currColor = GetPixel(screenDC, centerx, centery);

            if (currColor != originalColor){
                // 
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

                cout << "Pixel color has changed, clicking button" << endl;
                
                Sleep(500);

                // update color
                originalColor = GetPixel(screenDC, centerx, centery);
            
            }
        }
    
        
        Sleep(20);

        // 
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }
    }

    //
    ReleaseDC(NULL, screenDC);
    cout << "bot closed. Bye!" << endl;
    
    return 0;
}
