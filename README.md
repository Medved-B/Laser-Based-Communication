# Laser-Based-Communication

This is Tex Bir's laser based communication project for CSE 222

LinkedIn: www.linkedin.com/in/sam-bir

Required materials:
2x Arduino R3 UNO Board
2x Breadboard
1x LCD display
1x 650nm 5V laser emitter
1x Phototransistor
1x LED
2x 220 ohm resistors
1x 10K ohm resistors
1x 10K potentiometer
3x Jumper cables
11x Connecting cables




Transmitter:

Status LED:
A1 -> 220 ohm resistor -> LED -> GRND

Laser emitter:
D9 -> Laser leg 1
5V -> Laser leg 2
GRND -> Laser Leg 3

===============================================================================
Receiver:

LCD:
5V -> VDD
VSS -> GRND
Powered Potentiometer middle pin -> V0 (Contrast)
RS -> D7
RW -> GRND
E -> D8
(LCD)D4 -> D9
(LCD)D5 -> D10
(LCD)D6 -> D11
(LCD)D7 -> D12
5V -> 220 ohm resistor -> A
K -> GRND


Signal Receiver:
A0 -> Phototransitor Leg 1
5V -> 10k ohm resistor -> Phototransistor Leg 1
Phototransistor Leg 2 -> GRND
