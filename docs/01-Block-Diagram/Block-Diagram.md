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
![Flex Sensor Subsystem Block diagram-Updated](<https://github.com/LakshanandSugumar/lakshtest01.github.io/blob/main/docs/01-Block-Diagram/individual_block_diagram.drawio%20(3).png>)

---

## How Each Element of the Block Diagram Helps Meet Product Requirements

The Flex Sensor Subsystem is responsible for detecting door bending, validating door motion using rotary encoder data, and signaling the motor subsystem when to continue, stop, or shut down immediately. Each block in the diagram directly contributes to product requirements such as **safety**, **fault detection**, **accurate position sensing**, and **reliable subsystem communication**.

### **Flex Sensor (Spectra Symbol FS-L-095-103-ST)**

- Measures bending of the door and converts it into an analog voltage.
- Supports accurate tracking of door movement.
- Enables early detection of abnormal bending conditions.

### **Voltage Divider + Op-Amp (MCP6004 Low-Pass Filter)**

- Converts resistance-based flex changes into usable voltage.
- Filters electrical noise to provide stable ADC readings.
- Ensures reliable, accurate measurement required for safe door control.

### **Microchip PIC18F57Q43 Curiosity Nano**

#### **RA0 → ADC1 (Flex Sensor Input)**

- Reads the 0–5 V conditioned flex sensor output.
- Converts it into digital form for angle calculation.
- Enables real-time decision-making for motor control.

#### **Rotary Encoder Inputs (ADC2 and UART)**

- Provide independent rotational angle measurements.
- Used for cross-validation with flex sensor data.
- Detect mechanical issues such as:
  - Motor running without door movement
  - Excessive or unexpected bending
  - Jammed or obstructed door

#### **RF1 / RA2 (Communication with Motor Subsystem)**

- Send commands such as "continue," "stop," or "emergency stop."
- Provide fault feedback for safety-critical behavior.

#### **Digital I/O Ports (RC3, RA1, RB2, RC4, RA3)**

- Enable debugging, sensor validation, and internal system communication.
- RA3 specifically drives the **error LED** for visible fault detection.

### **Red LED (Flex Sensor Error Indicator)**

- Illuminates when unsafe bending or mismatched sensor data is detected.
- Aids both user awareness and subsystem debugging.

### **Switch (Debugging)**

- Allows manual testing of control logic.
- Supports calibration and verification during development.

### **Connector 2 (Digital + Analog Interface)**

- Provides structured outputs to motor subsystem and other modules.
- Ensures clean, modular subsystem integration.
- Enables transfer of angle data, stop signals, and digital I/O.

### **5 V Voltage Regulator (Digi-Key 785-14A2-5-ND)**

- Converts external 9 V supply into a stable 5 V rail.
- Prevents noise-induced sensor drift or microcontroller instability.
- Ensures safe and reliable operation for all subsystem components.

---

## Summary of Requirement Satisfaction

| Requirement                    | Contribution                                                            |
| ------------------------------ | ----------------------------------------------------------------------- |
| Accurate door position sensing | Flex sensor + op-amp + ADC1 convert bending into stable angle readings. |
| Redundant sensing for safety   | Rotary encoder inputs cross-check flex sensor behavior.                 |
| Fault & obstruction detection  | Mismatch in rotation vs. bending triggers immediate stop.               |
| Safe motor operation           | MCU sends real-time stop/continue commands.                             |
| User-visible error reporting   | Red LED shows sensor or mechanical faults.                              |
| Stable system operation        | Voltage regulator and filtering ensure consistent performance.          |
