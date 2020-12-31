# arduino_remote
It is a small project to simulate action for keyboard with Arduino kit.

Demo:
    
    Youtube: https://www.youtube.com/watch?v=AO0TL2SNGiU

Arduino badges:

    Arduino Leonardo

    Arduino 321 Maker shield

    16x2 LCD

    esp8266

Background:

    I found that it is hard to control the video on my laptop wirelessly without a bluetooth mouse or a keyboard. I happened to have an Arduino kit which I bought for my course 1 year ago. Given of COVID-19 and the budget, I did not want spend extra money to build this project. The kit did not come with a Bluetooth module so that I decided to use the esp866 the conduct the wireless communication over tcp in the private network.

Setup:

    Laptop, Windows 10 operated, runs a socket server over TCP on a specified port
    
    Arduino Leonardo, configured as socket client over TCP on a specified port

Features:

    Rotate the dial on the board to adjust audio volume

    Press swith 1 to start or pause the video

    Press swith 2 to enter or exit fullscreen

    Display wifi connection with led and lcd

        a. ON on wifi section & red led on as the board is connected to the wifi

        b. OFF on wifi section & blue led on as the board is disconnected to the wifi

    Display socket connection with RGB led and lcd

        a. ON on socket section & RGB led on red channel on as the board is connected to the socket

        b. OFF on socket section & RGB led on blue channel on as the board is disconnected to the socket
    
    Connect to wifi & socket automatically

    Reconnect to wifi & socket automatically

Used Library:
    
    robotjs
        Link: http://robotjs.io