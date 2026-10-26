#include <iostream>
#include <windows.h>
#include <cmath>
#include <random>

using namespace std;

//number generation configuration
random_device rd;
mt19937 gen(rd());

//func for a random Delay
int GetRandomDelay(int minDelay, int maxDelay){
    uniform_int_distribution<> distr(minDelay, maxDelay);
    return distr(gen);
}


//func for a safe click by SENDINPUT
void MouseClick(){
    INPUT input = {};
    input.type = INPUT_MOUSE;

    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(GetRandomDelay(30, 70));
    
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));

}   

//func for checking, how much color was change
bool IsColorChanged (COLORREF c1, COLORREF c2, int tolerance = 25){
    int r1 = GetRValue(c1), g1 = GetGValue(c1), b1 = GetBValue(c1);
    int r2 = GetRValue(c2), g2 = GetGValue(c2), b2 = GetBValue(c2);

    return (abs (r1 - r2) > tolerance ||
            abs (g1 - g2) > tolerance ||
            abs (b1 - b2) > tolerance);
    
}

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

            if (IsColorChanged(originalColor, currColor, 30)){
                Sleep(GetRandomDelay(120, 210));

                MouseClick();
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
