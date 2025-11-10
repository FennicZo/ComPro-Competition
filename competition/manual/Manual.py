   import event, time, cyberpi, gamepad, mbot2

@event.start
def on_start():
    
    cyberpi.led.show('green')
    cyberpi.console.clear()
    cyberpi.console.println("Bluetooth Connected - Ready")
    
    BServe = 0
    Serve1 = 0
    Serve2 = 0
    Dc = 0

    while True:
        # Joystick
        Lx = gamepad.get_joystick('Lx')
        Ly = gamepad.get_joystick('Ly')
        Ry = gamepad.get_joystick('Ry')

        Lx = -Lx

        left_speed = Ly + Lx
        right_speed = Ly - Lx

        left_speed = -left_speed

        # Limit encoder speeds
        left_speed = max(min(left_speed, 100), -100)
        right_speed = max(min(right_speed, 100), -100)

        # Drive encoders
        mbot2.drive_power(left_speed, right_speed)
        
        # Servo controls
        if gamepad.is_key_pressed('Up'):
            BServe = min(BServe + 20, 180)
        elif gamepad.is_key_pressed('Down'):
            BServe = max(BServe - 20, 0)
            
        if gamepad.is_key_pressed('N1'):
            Serve1 = min(Serve1 + 20, 180)
        elif gamepad.is_key_pressed('N4'):
            Serve1 = max(Serve1 - 20, 0)
            
        if gamepad.is_key_pressed('N2'):
            Serve2 = min(Serve2 + 20, 180)
        elif gamepad.is_key_pressed('N3'):
            Serve2 = max(Serve2 - 20, 0)
            
        # Servo position 
        mbot2.servo_set(BServe, "S1")
        mbot2.servo_set(Serve1, "S3")
        mbot2.servo_set(Serve2, "S4")

        # DC Motor controls
        Dc = int(Ry)
        Dc = max(min(Dc, 100), -100)
        mbot2.motor_set(Dc, "M1")

        # Output print
        cyberpi.console.println("L: " + str(left_speed) + 
                                " | R: " + str(right_speed) +
                                " | BServo: " + str(BServe) +
                                " | Servo1: " + str(Serve1) +
                                " | Servo2: " + str(Serve2) +
                                " | DC: " + str(Dc))

        time.sleep(0.05)