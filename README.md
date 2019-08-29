### About

This cross-platform application built with C++ and programmatic Qt offers a class structure for reading, parsing, plotting, analyzing and saving the data read from a selected system serial port. Options are available to export the sorted data in .json, .xls/.xlsx, or .csv format, as well as save an image of the plot.

Its purpose is for use as a building block or sub-system of a larger serial communications control-station for remote monitoring and control of devices equipped with Bluetooth and WiFi modules. It can also serve as an example class structure for communication through other protocols like TCP/IP.

Features:
* Automatically parses the incoming serial data and extracts meaningful samples (rejects anomalies)
* Export data to .csv, .xls,. json, .xlsx
* Saves a well-cropped image of the current plot
* Selects a system port by name in the `Port > Choose Port...` menu

<p align="center">
<img src="https://raw.githubusercontent.com/NickJoannette/SerialControl/class_restructuring/images/serialcontrol_docked_dialog.PNG">
  </p>

