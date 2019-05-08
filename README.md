# fitness_monitoring_gadget
The system features includes finding the heart rate and cadence of the user and displaying it in real time on a display. It also involves saving the data and providing the user with graphical reports of his progress. The project could thus be divided in to following parts
1. Displaying current time and date.
2. Measuring and displaying heart rate with an accuracy of bpm.
3. Displaying the speed and distance covered with an accuracy of.
4. Recording and preparing a graphical report from the data.
## Top Level Design
![Top Level Design](/Hardware_Design.png)
## Hardware Design
The hardware of the system was divided into two parts.
### Arm Mounted Piece
#### Components Used
The components used in this part include
1. Arduino NANO
2. Pulse Sensor (SEN-1574)
3. Bluetooth Module (HC-05)
4. 128x128 TFT LCD (ST-7735)
5. RTC
#### Circuit Diagram
![Arm Mounted Piece](/Arm_Piece.png)
#### Functionality
This part of the hardware had the functionality of measuring Heart Beat using SEN-1754 pulse sensor. RTC is used to keep the device’s time synced with the world clock. The bluetooth module performs communication with the other part of the system. The main display of the system is a 128x128 TFT LCD to show time and other measurements performed.
### Foot Mounted Piece
#### Components Used
The components used in this part are
1. Arduino NANO
2. Accelerometer (AXL-335)
3. Bluetooth Module (HC-05)
4. SD Card Module
#### Circuit Diagram
![Foot Mounted Piece](/Foot_Piece.png)
#### Functionality
The major function of the foot mounted piece is to measure speed using accelerometer.
Bluetooth module is required to send the measured speed to arm mounted piece for display. Further,
the SD Card attached is used to measure the save the measurements performed for later use.
## Results
1. A graph of 500 readings taken from heart beat sensor after removing the noisy signals from it.
![Heart Beat Graph](/HeartBeat_Sensor_results.png)
2. Speed (m/s) and Heart beat (bpm) graphs
---![Graph of recorded Speed(m/s) and HeartBeat(bpm)](/Speed_and_HeartBeat_graph.png)
