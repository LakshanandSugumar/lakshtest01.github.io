---
title: Power Budget
---

# Power Budget

## Overview

This page presents the **final power budget** for the automatic door opener. The goal of the power budget is to estimate the **maximum possible current draw** from each major subsystem and verify that our chosen power supplies and voltage regulators are correctly sized.

The team uses a **single 12 V system supply** (shared by the motor and all electronic subsystems). Each subsystem then regulates down to its required voltage (for example, 5 V for the PIC18F57Q43 Curiosity Nano and sensors). The power budget spreadsheet uses the course template: every major component is listed with its operating voltage, maximum current (from datasheets), and a 25% margin column.

> Capture your power budget as an image to display. Take time to get clean breaks and a well organized layout.

![budget1](power.png){style width:"350" height:"300;"}

This image (`power.png`) is exported directly from the final team power budget spreadsheet and reflects the **current, final design** of all four subsystems.

---

## Conclusions

We used the power budget in the template to **sum the maximum currents** for:

- The **motor subsystem** (which dominates the 12 V current),
- The **flex sensor subsystem** (PIC18F57Q43 Nano, flex sensor, op-amp, LED, switch),
- The **rotary encoder subsystem**, and
- Any additional control or support electronics.

From this spreadsheet we found:

- The **total current at 12 V** stays **well below the 5 A rating** of our chosen 12 V switching power supply, even after adding a **25% safety margin** to each subsystem row in the template.
- The **flex sensor subsystem** only draws on the order of **~120 mA at 5 V**, which confirms that our simple **MC7805 5 V linear regulator** is adequate and will not overheat in normal operation.
- Because all subsystems share the same 12 V source, the power budget helped ensure that the **motor’s peak current plus all electronics** still fit within the safe operating range of the supply and motor driver.
- The analysis also showed that trying to run the full system from a small 9 V battery would give limited runtime and poor efficiency, supporting our decision to stay with a **wall-powered 12 V brick** for this project.

Overall, the power budget confirmed that:

- Our **12 V 5 A supply** provides enough headroom for all subsystems,
- Each regulator (especially the 5 V regulator for the flex subsystem) operates within its safe current and thermal limits, and
- The design can tolerate reasonable future additions (extra indicators, small sensors) without needing a complete power redesign.

---

## Resources

Power Budget (PNG): [_here_](power.png)

Power Budget (Excel Sheet): [_here_](PowerBudget.xlsx)

<br>

<a href="PowerBudget.xlsx" download
   style="display:inline-block; padding:0.5rem 1rem; background:#007bff; color:white; border-radius:4px; text-decoration:none;">
⬇️ Download Power Budget (Excel)
</a>
