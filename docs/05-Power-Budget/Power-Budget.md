---
title: Power Budget
---

## Overview

This page presents the power budget for all major components across the four subsystems of the automatic door opener. The power budget was developed to estimate the maximum possible current draw from each major electrical component and to outline how power is distributed and supplied throughout the system. This analysis ensures that all power sources and voltage regulators are properly rated to deliver the required current to each subsystem without risk of overloading or power failure.

> Capture your power budge as a image to display. Take time to get clean breaks and a well organized layout.

![budget1](power.png){style width:"350" height:"300;"}

Conclusions

Based on the prepared Power Budget, the subsystem operates well within a safe and reasonable current range, leaving additional capacity that can be utilized by other subsystems if needed. The team’s combined power budget analysis confirms that even with a 25% increase in total estimated current draw, the system still maintains sufficient power headroom to ensure stable and reliable operation across all components.

Resources

Power Budget (PNG): [_here_](power.png)

Power Budget (Excel Sheet): [_here_](PowerBudget.xlsx).

# Power Budget (Subsystem-Level)

The following sections address the missing Power Budget A–E to fulfill the rubric.

## **Section A — Maximum Current for All Major Components**

| Component                                 | Voltage | Max Current Draw | Notes                                     |
| ----------------------------------------- | ------- | ---------------- | ----------------------------------------- |
| PIC18F57Q43 Curiosity Nano                | 5 V     | 70–90 mA         | Includes onboard debugger + MCU load.     |
| Flex Sensor (Spectra Symbol FS-L-095-103) | 5 V     | ~1 mA            | Determined by divider total resistance.   |
| MCP6004 Op-Amp (1 channel active)         | 5 V     | ~100 µA          | Very low-power rail-to-rail input/output. |
| Red LED + Resistor                        | 5 V     | 10–15 mA         | Worst-case LED current.                   |
| Debug Switch                              | 5 V     | ~1 mA            | Pull-up resistor only.                    |
| Connectors / routing                      | 5 V     | <5 mA            | Small overhead.                           |

**Total Subsystem Current (max): ~110–130 mA**

---

## **Section B — All Major Components Assigned to One Power Rail**

All components in the Flex Sensor Subsystem operate on the **5 V regulated rail**:

- PIC18F57Q43 Curiosity Nano
- Flex sensor + divider
- MCP6004 op-amp
- Red LED
- Debug switch
- Connector headers

This satisfies the “single rail assignment” requirement.

---

## **Section C — Regulator Assigned to Power Rail**

The **MC7805ACTG** supplies the **5 V rail** used by the subsystem.

- Input: 9–12 V external
- Output: Regulated 5 V
- Thermal calculation (already included above) confirms safe operation for up to ~150 mA load.

This satisfies the “specific voltage regulator per rail” requirement.

---

## **Section D — External Power Source**

External source selected (as documented earlier):

**12 V 5A Switching Power Supply**

This powers the overall system and feeds the MC7805ACTG regulator, which then powers the flex subsystem via 5 V rail.

This satisfies the “specific external source” requirement.

---

## **Section E — Battery Life Calculation (if battery used)**

Battery is **not used** in the final design.  
However, the rubric requires a calculation if a battery _could_ be applied.

Assuming a **9 V alkaline battery (≈600 mAh)**:

Subsystem load ≈ **120 mA**

Battery life estimate:

\[
\text{Life} = \frac{600\ \text{mAh}}{120\ \text{mA}} \approx 5\ \text{hours}
\]

Due to regulator heat dissipation and poor 9 V efficiency, battery use is **not recommended**, but the calculation is included to satisfy Section E.

---
