---
title: Hardware V2.0
---

# Hardware V2.0 — Future Improvements to the Flex Sensor Subsystem

This page outlines proposed improvements for a **Version 2.0** of the flex sensor subsystem hardware. The discussion is based on the current schematic (shown on the Schematic page) which includes the PIC18F57Q43 Curiosity Nano, a linear 5 V regulator, flex sensor interface (divider + op-amp), indicator LED, switch, and connectors to the rest of the system.

The goals of Hardware V2.0 are to:

- Improve **reliability** and **noise performance**
- Reduce **power dissipation** and **board complexity**
- Improve **mechanical robustness** and **serviceability**
- Make the subsystem easier to **manufacture**, **debug**, and **integrate** with the rest of the project

---

## 1. Power Architecture Improvements

### 1.1 Move from Linear Regulator to Switching Regulator (If System Current Increases)

In the current schematic, a 7805-style linear regulator drops 9–12 V down to 5 V for the Curiosity Nano and sensor circuitry. This is acceptable for Version 1 because the current is relatively low, but it becomes inefficient as more loads (motors, additional sensors, etc.) are added.

**V2.0 Improvement:**

- Replace the linear 5 V regulator with a **buck (switching) regulator** module or IC.
- Keep the 5 V output available for both this subsystem and any future logic/sensor expansions.

**Why:**

- Reduces heat dissipation compared to a linear regulator (especially with 12 V input).
- Improves overall system efficiency and allows more headroom for additional loads without thermal concerns.
- Makes the design more scalable to a full production system.

### 1.2 Enhanced Protection on Power Input

The current schematic shows a regulator connected to a 9–12 V supply, but protection elements are minimal.

**V2.0 Improvement:**

- Add a **reverse-polarity protection** element (e.g., FET or diode).
- Add a **fuse or resettable polyfuse** on the input.
- Add a **TVS diode** for surge protection and ESD on the external power jack.

**Why:**

- Protects the board from incorrect power connections and transient events.
- Reduces risk of damage during lab use and future field deployment.

---

## 2. Signal Integrity and Sensing Accuracy

The current schematic already includes a voltage divider and bypass capacitors near VDD pins. However, as the project evolves, signal integrity and sensor accuracy become more important.

### 2.1 Dedicated Analog Grounding and Filtering

In Version 1, analog and digital grounds share the same plane. This is acceptable but could be improved.

**V2.0 Improvement:**

- Introduce an **analog ground region** around the flex sensor divider and op-amp.
- Use a **single-point connection** between analog and digital grounds near the ADC reference.
- Refine the **RC filter** values to match the actual bending speed and sampling rate from the schematic’s ADC configuration.

**Why:**

- Reduces noise injected from digital switching and motor-related transients into the flex sensor measurement.
- Provides more stable ADC readings and improves accuracy in detecting small bending changes.

### 2.2 Improved Flex Sensor Interface (Instrumentation)

Currently, the flex sensor is read through a simple divider and an op-amp configured as a buffer or low-pass filter stage.

**V2.0 Improvement:**

- Consider using an **instrumentation amplifier** or a dedicated precision amplifier stage for the sensor.
- Add **test pads** at the sensor output and op-amp output so that signals can be probed easily during debugging.

**Why:**

- Better measurement linearity and gain adjustment if future requirements need higher resolution of small angle changes.
- Test pads make it easier to validate the analog path without modifying the board.

---

## 3. Microcontroller Integration and I/O

In the current design, the PIC18F57Q43 Curiosity Nano dev board is used directly on the PCB or via header connections.

### 3.1 Transition Toward a Fully Integrated MCU

**V2.0 Improvement:**

- Move from a plug-in Curiosity Nano dev board to a **bare PIC18F57Q43** placed directly on the custom PCB.
- Bring the programming/debug interface (ICSP or similar) to a small dedicated header.

**Why:**

- Reduces size and cost per unit if the design were scaled beyond the class project.
- Gives more control over layout around the MCU (shorter analog traces, cleaner ground).

### 3.2 Enhanced I/O and Test Access

**V2.0 Improvement:**

- Add labeled **test points** for key signals: flex sensor output, op-amp output, motor control signals, and UART lines to the rotary encoder subsystem.
- Clearly label **connector pinouts** on the silkscreen (e.g., 5V, GND, SIG, TX, RX).

**Why:**

- Simplifies bench debugging and brings the hardware closer to the schematic intent (easier to correlate the schematic nets with physical points).
- Reduces wiring mistakes when integrating with other subsystems.

---

## 4. Mechanical and Connector Improvements

The current board already includes mounting holes and basic connectors as shown in the PCB and schematic.

### 4.1 Robust Connectors for Field Use

**V2.0 Improvement:**

- Standardize on **locking connectors** (e.g., JST-XH) for all external connections related to the flex sensor and subsystem I/O.
- Ensure connectors are oriented in a way that matches cable routing in the full system enclosure.

**Why:**

- Prevents accidental unplugging during movement of the door mechanism.
- Makes wiring more intuitive and reduces debugging time caused by loose or reversed cables.

### 4.2 Mechanical Strain Relief for the Flex Sensor

**V2.0 Improvement:**

- Add **mechanical mounting / strain relief holes** or features near the flex sensor connection.
- Potentially add a small **clamp or anchor footprint** for a cable tie to reduce bending stress near the soldered pads.

**Why:**

- Flex sensors are mechanically fragile near the tail; reducing stress near the connector improves life and reliability.
- Aligns hardware design with the flex sensor’s mechanical usage conditions implied by the schematic.

---

## 5. Documentation and Versioning

Finally, Hardware V2.0 would also enhance how the design is documented and maintained.

**V2.0 Improvement:**

- Include **version labels** (e.g., “Flex Subsystem PCB V2.0”) on the silkscreen and in the schematic title block.
- Keep the **schematic, PCB, and Gerber ZIPs** organized under a `hardware_v2` directory in the repository.

**Why:**

- Makes it easy to distinguish between V1.0 and V2.0 hardware during future debugging or replacement.
- Ensures the schematic and PCB images on the documentation pages always match the physical hardware version being tested.

---

## Summary

Hardware V1.0 meets the course and project requirements, but a future **Hardware V2.0** could:

- Improve **efficiency and thermal performance** through a switching regulator.
- Enhance **measurement accuracy and robustness** with better grounding, filtering, and amplifiers.
- Increase **maintainability and manufacturability** by integrating the MCU, adding test points, and standardizing connectors.
- Improve **mechanical durability** of the flex sensor and wiring.

These changes all build directly on the existing schematic and PCB, using the current design as a stable baseline for iteration rather than a complete redesign.
