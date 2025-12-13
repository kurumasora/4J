import wiringpi as pi
import time

MTR_PIN_1 = 23
MTR_PIN_2 = 24
SW_PIN = 17

pi.wiringPiSetupGpio()
pi.pinMode( MTR_PIN_1, pi.OUTPUT )
pi.pinMode( MTR_PIN_2, pi.OUTPUT )
pi.pinMode( SW_PIN, pi.INPUT )
pi.softPwmCreate( MTR_PIN_1, 0, 100 )
pi.softPwmCreate( MTR_PIN_2, 0, 100 )//定義

while True:
//１病後にduty比20で、回転
   value = 20
   time.sleep(1)
   pi.softPwmWrite( MTR_PIN_1, value)
   pi.softPwmWrite( MTR_PIN_2, 0)
//スイッチを押すと１００まで２０づつ増加
   while(value <= 99):
       if(pi.digitalRead( SW_PIN ) == pi.HIGH ):
           value += 20
           time.sleep(0.5)
       print('Duty ratio =',value)
       pi.softPwmWrite( MTR_PIN_1, value)
       pi.softPwmWrite( MTR_PIN_2, 0)
       
//スイッチを押すと２０まで２０ずつ減少
   while(value > 0):
       if(pi.digitalRead( SW_PIN ) == pi.HIGH ):
           value -= 20
           time.sleep(0.5)
       print('Duty ratio =',value)
       pi.softPwmWrite( MTR_PIN_1, value)
       pi.softPwmWrite( MTR_PIN_2, 0)