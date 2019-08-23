Beginnings of a re-usable class structure to make applications for serial communication through the PC's serial ports. Currently opens and closed a selected system serial port, and then readis, parses, and plots incoming data from signals or whatever may be transmitted by the peripherals (in this case a signal from a Hall sensor communicated through an arduino)

Has just two classes; `MainWindow` and `SerialCommunicator` so it is very easy to implement, will soon add the ability to send serial data

![E44 Received Data](https://raw.githubusercontent.com/NickJoannette/qt-arduino-serial-interfaces/master/images/atqtsei.PNG)
