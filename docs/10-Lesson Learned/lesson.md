---
title: Lessons Learned and Recommendations for Future Students
---

# Lessons Learned and Recommendations for Future Students

This project took the Flex Sensor Subsystem all the way from concept → schematic → PCB → firmware → integration with the motor and rotary encoder subsystems. Along the way there were a lot of small “oops” moments that turned into useful lessons. This page summarizes what worked, what didn’t, and what I would recommend to future students doing a similar hardware project.

---

## Lessons Learned

### 1. Pin Planning and MCC Setup Matter More Than Expected

One of the most surprisingly time-consuming tasks was getting the **PIC18F57Q43 pin configuration (MCC)** correct and keeping it synced with the schematic and documentation.

- I changed pin assignments a few times (especially around RA0/RA2/RF1), which meant I had to update the schematic, PCB labels, the pin table, and MCC each time.
- A small mismatch (like listing RF1 as an ADC when it’s actually UART RX) can break the system in subtle ways.

**Lesson:**  
Freeze your **pinout early** and treat MCC, schematic symbols, and the “pin table” in your report as a single unit. Change one → change all three immediately.

---

### 2. Analog Front-End Quality Directly Affects System Behavior

The flex sensor looks simple on paper (just a resistor that changes with bend), but in practice:

- It is **noisy** and **non-linear**.
- The ADC readings jump around if you don’t filter or buffer the signal properly.
- The op-amp / RC filter made a big improvement in stability.

**Lesson:**  
Take the **analog side seriously**. Even for “simple” sensors, add:

- Proper **voltage divider values** (not too high, not too low).
- At least a basic **RC low-pass filter**.
- A **buffer op-amp** if the ADC input impedance could cause error.

---

### 3. Grounding and Power Are Easy to Underestimate

It’s tempting to focus on signals and forget about ground and power, but:

- Sharing ground with motor currents can inject noise into the sensor readings.
- The linear regulator is simple, but it does dissipate real power when stepping from 9–12 V to 5 V.
- Bypass capacitors close to the PIC’s VDD/VSS pins are absolutely required, not optional.

**Lesson:**  
Spend time on **power and grounding early**:

- Place bypass caps correctly (not just “on the schematic” but close in the PCB).
- Think about where motor return currents flow relative to your sensor grounds.
- Give yourself **current and thermal margin** in the power budget.

---

### 4. PCB Design Is Iterative (and Reality Wins Over CAD)

The PCB looks clean in ECAD (schem6.png), but real life uncovered a few things:

- Connector orientations and silkscreen labels are easy to misunderstand until you physically plug things in.
- Clear labeling of 5V, GND, and signal lines on the silkscreen saves a lot of time.
- Having **test points** (even just small pads) on key nodes would have made debugging easier.

**Lesson:**  
Design the PCB **with debugging in mind**:

- Add **test pads** for important analog nodes and communication lines.
- Label connector pins and key signals on silkscreen.
- Think about cable routing and real mechanical constraints, not just the 2D view.

---

### 5. Documentation Is Easier If You Do It as You Go

A lot of this report—component selection, power budget, block diagram explanations, and PCB documentation—would have been painful if done at the last minute.

**Lesson:**  
Update your **Markdown pages, images, and tables incrementally**:

- When you pick a final part → immediately update the component selection table.
- When you finalize a pin mapping → update the pin table and MCC screenshot.
- When you generate a new schematic or PCB revision → export and replace the PNG/PDF right away.

This keeps the report and the hardware in sync and avoids a panic rewrite later.

---

## Recommendations for Future Students

### 1. Start Prototyping Analog + MCU Early

- Get **one sensor + MCU** working on a breadboard before fully committing to a PCB.
- Confirm ADC ranges, noise level, and timing in firmware.
- Use this early test to refine your **RC filter** and divider values.

### 2. Lock Down Pinout Before Final PCB

- Plan ADC, UART, PWM, and GPIO needs on paper or in a spreadsheet.
- Configure MCC and verify all required peripherals are mapped correctly.
- Only after you are happy with the pinout should you finalize the schematic and PCB.

### 3. Treat Power Budget as a Design Tool, Not Just a Checkbox

- Use the power budget to pick your **regulator type**, heat dissipation expectations, and source sizing.
- Include a **margin (e.g., +25%)** so surprises don’t break your design.
- If you ever add motors or higher loads, seriously consider a **buck regulator** instead of just scaling up a linear regulator.

### 4. Add Extra Debug Features (LEDs, Test Pads, Headers)

- One or two extra LEDs (status, error) and a couple of test pads can save hours in the lab.
- Break out one spare UART or debug header if you can.
- These don’t cost much in PCB area but greatly improve visibility into what the board is doing.

### 5. Use Version Control and Clear File Naming

- Keep schematic, PCB, and project zips labeled clearly: `v1`, `v2`, etc.
- Don’t keep relying on `final.pdf` / `final2.pdf` / `final_final.pdf`—use dates or version numbers.
- Commit changes with short notes like “updated RA2 to ADC2 input” so future you knows what changed.

### 6. Ask for Feedback Early (and Actually Apply It)

- Take advantage of **TA / instructor feedback** on block diagrams, power budgets, and MCC configuration.
- Fix issues as soon as they’re pointed out instead of letting them accumulate.
- Many later “mystery bugs” are just the result of earlier feedback not being integrated.

---

## Closing Thoughts

The flex sensor subsystem ended up doing more than just reading a bend—it became a **safety and validation node** for the entire automatic door system. Going through the full process (schematic → PCB → firmware → integration) is challenging but also realistic compared to how real hardware projects run.

If future students focus on:

- Solid **pin planning & power design**,
- Respect for the **analog details**,
- And disciplined **documentation + versioning**,

their Version 1.0 will feel much more like a Version 2.0 from the start.
