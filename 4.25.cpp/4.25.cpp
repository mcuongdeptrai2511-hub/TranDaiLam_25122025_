#include <iostream>
#include <pigpiod_if2.h>

// Định nghĩa các chân GPIO
const int PWM_A = 21;
const int MOTOR_A_FWD = 26;
const int MOTOR_A_REV = 13;
using namespace std;

// Hàm thiết lập Pigpio Daemon và cấu hình GPIO
int pigpio_setup() {
    char *addrStr = NULL;
    char *portStr = NULL;

    // Kết nối với Pigpio Daemon
    const int pi = pigpio_start(addrStr, portStr);

    // Thiết lập chế độ chân
    set_mode(pi, PWM_A, PI_OUTPUT);
    set_mode(pi, MOTOR_A_FWD, PI_OUTPUT);
    set_mode(pi, MOTOR_A_REV, PI_OUTPUT);

    // Khởi tạo motor ở trạng thái OFF (HIGH = OFF)
    gpio_write(pi, MOTOR_A_FWD, 1);
    gpio_write(pi, MOTOR_A_REV, 1);

    return pi;
}

int main() {
    int pi = pigpio_setup();
    if (pi < 0) {
        cout << "Failed to connect to Pigpio Daemon. Is it running?" << endl;
        return -1;
    }

    // Chạy motor xuôi nửa tốc độ
    gpio_write(pi, MOTOR_A_FWD, 0);
    set_PWM_dutycycle(pi, PWM_A, 127); // 50% duty cycle
    time_sleep(3);

    // Tăng lên tốc độ tối đa
    set_PWM_dutycycle(pi, PWM_A, 255);
    time_sleep(3);

    // Dừng motor
    gpio_write(pi, MOTOR_A_FWD, 1);
    time_sleep(1);

    // Quay ngược
    gpio_write(pi, MOTOR_A_REV, 0);
    set_PWM_dutycycle(pi, PWM_A, 127);
    time_sleep(3);

    set_PWM_dutycycle(pi, PWM_A, 255);
    time_sleep(3);

    gpio_write(pi, MOTOR_A_REV, 1);

    // Ngắt kết nối
    pigpio_stop(pi);
    return 0;
}
