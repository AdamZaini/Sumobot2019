# Sumobot2019

On 23rd March 2019, Imperial College Robotics Society (ICRS) held a sumobot competition at their university. The objective of the competition is to simply knock the opposing robot off the playing arena in 120s. Every robot has to comply with the power and size restrictions set by the host. The robot can either be autonomous or human-controlled. I have opted for an autonomous robot. This was because I did not have enough time to purchase a Bluetooth or WiFi module. I had an IR module in hand, however, I found it to be inconsistent and unreliable. The robot utilised 3 ultrasonic sensors, 2 infrared sensors and a MD25 motor controller. A library from http://www.ipb.pt/~jpcoelho/downloads.htm was used for the MD25 motor controller. The code adopted the following strategy.

1. Start timer
2. Move forward at half speed
3. If floor is not detected, reverse, and rotate 180 degrees
4. If opponent robot is detected on side sensors, rotate to that direction
5. If opponent robot is detected at the front sensor, move forward at full speed
6. Once the timer has reached 120s, terminate robot
