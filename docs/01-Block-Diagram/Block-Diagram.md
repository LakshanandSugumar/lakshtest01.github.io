---
title: Individual Block Diagram
tags:
  - tag1
  - tag2
---

## Overview

This subsystem is responsible for reading analog data from the flex sensor and communicating the interpreted results to the motor subsystem to control door movement. All components within this subsystem operate on a regulated 5 V supply, derived from a 9 V input through an onboard voltage regulator, as shown in the dashed region of the block diagram.

The Microchip **PIC18F57Q43 Curiosity Nano** serves as the primary controller. It performs three main tasks:

- Reads the flex sensor’s analog output using its internal ADC.
- Processes the sensor data to determine door position and bend state.
- Sends digital status/control signals to external subsystems.

This subsystem interfaces directly with both the **Motor Subsystem** and the **Rotary Sensor Subsystem**. The rotary sensor inputs are used for cross-validation: the system compares the physical bend of the door (flex sensor) with the rotation angle (rotary sensor). Any mismatch indicates a mechanical failure (e.g., motor spinning without moving the door), enabling fault detection and automatic shutdown.

This interaction improves safety, prevents motor overrun, and reduces power waste. For a full system-level view of all interconnected subsystems, refer to the [team report.](https://egr304-2025-f-103.github.io)

![Flex Sensor Subsystem Block diagram-Updated](individual_block_diagram.drawio (3).png)

## Subsystem Role

The Flex Sensor Subsystem acts as a **feedback + validation node** in the overall system architecture. Its primary function is to:

- Convert real-world bending motion into a readable electrical signal
- Translate that signal into actionable logic for the motor subsystem
- Detect abnormal or unsafe mechanical conditions through sensor comparison

The rotary sensor signals shown on the right side of the diagram are _external inputs_ and are not part of this subsystem’s hardware. They are included to document the communication pathway and show how this subsystem cooperates with others to maintain correct and safe system behavior.

[draw.io](https://drive.google.com/file/d/1aowyaz1jB5e_mhioJ-Hf5ubIlwDby4pD/view?usp=sharing)
