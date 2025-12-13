#初期状態は青色に光り、ボタンを押し続けいていると赤色に光るプログラム
import wiringpi as pi
import time

LED_PIN_1 = 23 #赤色LED
LED_PIN_2 = 24 #青色LED
SW_PIN = 17    #ボタン

pi.wiringPiSetupGpio()

#LEDピンを出力モードに設定
pi.pinMode( LED_PIN_1, pi.OUTPUT )
pi.pinMode( LED_PIN_2, pi.OUTPUT )

#ボタン用ピンを入力用に設定
pi.pinMode( SW_PIN, pi.INPUT )

#PWMを0〜100%に設定
pi.softPwmCreate( LED_PIN_1, 0, 100 )
pi.softPwmCreate( LED_PIN_2, 0, 100 )

while True:
    time.sleep(1)

    #初期状態は消灯
    pi.digitalWrite( LED_PIN_1, pi.LOW)
    pi.digitalWrite( LED_PIN_2, pi.LOW)

    if(pi.digitalRead( SW_PIN ) == pi.HIGH ):#ボタンが押されたら
        value = 0
        #徐々に明るさを上げながら赤色に光る
        while( value < 100):
            pi.softPwmWrite( LED_PIN_1, value )
            pi.softPwmWrite( LED_PIN_2, 0)
            time.sleep(0.01)#0.01秒間隔
            value = value + 1
    #押されてないときは
    else      
        value = 0
        #徐々に明るさを上げながら青色に光る
        while( value < 100):
            pi.softPwmWrite( LED_PIN_1, 0 )
            pi.softPwmWrite( LED_PIN_2, value )
            time.sleep(0.01)#0.01秒間隔
            value = value + 1
