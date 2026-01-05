#include <pigpiod_if2.h>
#include <iostream>
const int LED = 6;
using namespace std;
int PigpioSetup()
{
    char *addrStr = NULL;
    char *portStr = NULL;
    // Bắt tay với daemon và lấy pi handle
    int pi = pigpio_start(addrStr, portStr);

    // Thiết lập chế độ chân và khởi tạo ở mức thấp
    set_mode(pi, LED, PI_OUTPUT);
    gpio_write(pi, LED, 0);
    return pi;
}
int main()
{
    int pi = PigpioSetup();

    // Kiểm tra kết nối
    if(pi >= 0)
        cout << "daemon interface started ok at " << pi << endl;
    else {
        cout << "Failed to connect to PIGPIO Daemon - Try running sudo pigpiod and try again." << endl;
        return -1;
    }

    // Bật LED
    gpio_write(pi, LED, 1);
    time_sleep(3.2); // chờ 3.2 giây
    // Tắt LED
    gpio_write(pi, LED, 0);

    // Ngắt kết nối daemon
    pigpio_stop(pi);
    return 0;
}
