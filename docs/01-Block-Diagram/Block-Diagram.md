---
title: Individal Block Diagram
tags:
  - tag1
  - tag2
---

## Overview

This subsystem is responsible for reading data from a flex sensor and communicating with the motor subsystem to control movement based on the sensor’s readings. All components within this subsystem are powered through a 5 V voltage regulator, which is supplied by a 9 V input, as shown by the dashed box in the diagram.

The Microchip PIC18F57Q43 Curiosity Nano acts as the main controller, handling the analog input from the flex sensor and sending digital control signals to other subsystems.

This subsystem connects directly with two other subsystems — the Motor Subsystem and the Rotary Sensor Subsystem. Together, these components enable the system to compare the rotary sensor inputs with the flex sensor readings to determine whether the motor is functioning as intended or if it has become disengaged from the door mechanism.

This interaction ensures accurate motion tracking and prevents unnecessary motor activity, improving both safety and energy efficiency. For a complete overview of how all subsystems integrate to form the full automatic door opener system, visit the  [team report.](https://egr304-2025-f-103.github.io)

![ Flex Sensor Subsystem Block diagram ](individual_block_diagram.drawio (3).png)


## Subsystem Role

The Flex Sensor Subsystem plays the role of a sensor-driven control unit. It constantly monitors the flex sensor’s readings, processes the analog signal, and uses that information to decide what commands to send to the motor.

The rotary sensor signals shown on the right are external inputs from another subsystem, not part of this subsystem’s hardware. They are included in the diagram purely to illustrate how this subsystem interfaces with others in the overall system.


