---
title: Appendix – Inputs from Design Review
---

### Action Items / Feedback Summary

- The resistor currently tied between +5 V and GND is not required and should be deleted.
- Ensure all through-hole pads (especially high-current or ground pads) have thermal relief spokes to improve solderability.
- One labeled test point per pin for debugging and probing.
- Do **not** route every GND pin back to the barrel jack pad.
- Instead, use a **ground plane (bottom layer)** for return paths and improved noise performance.
- Reduces via count and keeps power trace shorter and wider.
- Avoid default names like `N0001`.
- Use meaningful labels (e.g., `FLEX_OUT`, `ADC_VIN`, `5V_IN`, `MOTOR_EN`, etc.).
- If the flex sensor readings saturate or the hinge angle exceeds its bend rating.
- Mount the flex sensor on a **thin flexible silicon strip** or similar compliant material
- This allows the door to move fully without forcing the sensor to bend beyond its limit.

---
