#include "mbed.h" 
#include <cstdlib> 

DigitalOut myled(LED1); 
DigitalIn pushbtn(BUTTON1, PullUp); 

Timer timer; 

 
 

int main() { 

    srand(time(NULL)); // 랜덤 시드 초기화 

 
 

    while (true) { 

        

        float v = (float)rand() / RAND_MAX;  // 난수를 사용하여 LED를 켭니다. 

        myled = (v < 0.5f) ? 1 : 0; 

         

        // LED가 켜졌을 때만 타이머를 시작합니다. 

        if (myled == 1) { 

            timer.start(); 

            bool button_pressed = false; 

 
 

            // 1초 동안 버튼이 눌리는지 확인합니다. 

            while(timer.read_ms() < 1000) { 

                if (pushbtn == 0) { // 버튼이 눌리면 

                    button_pressed = true; 

                    break; 

                } 

                ThisThread::sleep_for(10ms); // 10ms 대기 

            } 

 
 

            timer.stop(); 

            timer.reset(); 

 
 

            if (button_pressed) { 

                // 버튼이 눌렸으면 LED를 끕니다. 

                myled = 0; 

            } else { 

                // 버튼이 눌리지 않았으면 LED를 10번 깜박입니다. 

                for (int i = 0; i < 10; i++) { 

                    myled = !myled; // LED 상태를 반전합니다. 

                    ThisThread::sleep_for(300ms); // 300ms 대기 

                } 

            } 

        } 

 
 

        // 다음 LED 상태를 난수로 결정하기 전에 잠시 대기합니다. 

        ThisThread::sleep_for(1s); 

    } 

} 

 
 

 