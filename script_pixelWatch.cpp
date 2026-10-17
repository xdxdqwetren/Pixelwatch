#include <iostream>
#include <windows.h>

using namespace std;


int main(){
    //get resolutin monitor
    int screenWidth = GetSystemMetrix(SM_CXSCREEN);
    int screenHeight = GetSystemMetrix(SM_CYSCREEN);

    //center monitor
    int centerx = screenWidth / 2;
    int centery = screenHeight / 2;

    //record colot pixel
    COLOROREF originalColor = GetPixel(centerx, centery);

    cout << "the colot has bin recorded";

    while (true)
    {   
        COLORPREF currColor = GerPixel(centerx, centery);

        //check the color change
        if (currColor != originalColor)
        {
            
            mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event (MOUSEEVENTF_LEFTUP 0, 0, 0, 0);

            cout << "pixel has been change color, press button" << endl;
            
            sleep(500);

            //update color
            originalColor = GetPixel(centerx, centery);


        }
        
        sleep(20);

        if (GetAsyncKeyState(VK_ECSAPE))
        {
            break;
        }
        
    }


    return 0;
}