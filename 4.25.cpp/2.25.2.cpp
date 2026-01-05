#include <iostream>
#include <pigpiod_if2.h>
using namespace std;

const int BUTTON = 27;

void button_event(int pi, unsigned int gpio, unsigned int edge, unsigned int foo)
{
    static int i = 0;
    cout << "Button pressed. Press count = " << i++ << endl;
}

int main()
{
    char *addrStr = NULL;
    char *portStr = NULL;
    int pi = pigpio_start(addrStr, portStr);

    if(pi >= 0)
        cout << "daemon interface started ok at " << pi << endl;
    else {
        cout << "Failed to connect to PIGPIO Daemon - Try running sudo pigpiod and try again." << endl;
        return -1;
    }

    // Đặt chân 27 làm input
    set_mode(pi, BUTTON, PI_INPUT);

    // Khởi tạo callback
    int callbackID = callback(pi, BUTTON, RISING_EDGE, button_event);

    // Chạy chương trình 60 giây
    time_sleep(60);
    cout << "60 seconds has elapsed. Program ending." << endl;

    // Hủy callback và ngắt kết nối
    callback_cancel(callbackID);
    pigpio_stop(pi);
    return 0;
}
