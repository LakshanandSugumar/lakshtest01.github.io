---
title: Appendix – Inputs from Design Review
---

### Action Items / Feedback Summary

1. **Remove unnecessary resistor** in the linear voltage regulator path

   - The resistor currently tied between +5 V and GND is not required and should be deleted.

2. **Add thermal reliefs**

   - Ensure all through-hole pads (especially high-current or ground pads) have thermal relief spokes to improve solderability.

3. **Add test points for every signal on the 8-pin ribbon connector**

   - One labeled test point per pin for debugging and probing.

4. **Improve ground routing strategy**

   - Do **not** route every GND pin back to the barrel jack pad.
   - Instead, use a **ground plane (bottom layer)** for return paths and improved noise performance.

5. **Use top layer for the 5 V power net** if possible

   - Reduces via count and keeps power trace shorter and wider.

6. **Name all nets clearly**

   - Avoid default names like `N0001`.
   - Use meaningful labels (e.g., `FLEX_OUT`, `ADC_VIN`, `5V_IN`, `MOTOR_EN`, etc.).

7. **Flex sensor mechanical accommodation**
   - If the flex sensor readings saturate or the hinge angle exceeds its bend rating:
     - Mount the flex sensor on a **thin flexible silicon strip** or similar compliant material
     - This allows the door to move fully without forcing the sensor to bend beyond its limit.

---
