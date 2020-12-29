# arduino_remote
It is a small project to simulate action for keyboard with Arduino kit.

Arduino badges:

    Arduino Leonardo

    Arduino 321 Maker shield

    16x2 LCD

    esp8266

Background:

    I found that it is hard to control my laptop wirelessly without a bluetooth mouse or a keyboard. I happened to have some Arduino kits which I bought for my course. The Arduino kit did not come with Bluetooth module so that I decided to use the esp866 the conduct wireless communication.

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
