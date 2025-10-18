---
title: Component Selection
---

# Component Selection (Individual – Flex Sensor Subsystem)

> **Scope:** This page covers the blocks I own in the system: **Flex Sensor**, **Signal-Conditioning/Voltage Divider**, **5 V Regulator**, **External Power Source**, **Connectors**, and **Microcontroller (short comparison)**.  
> **Interfaces:** Outputs digital lines **RA1, RB2, RC4** to the Motor Subsystem via Connector 2. Optional external rotary analog input to **RA2/AN2** (not owned here).

## Quick Checklist

- [ ] ≥ 3 options per block, each with **photo, descriptive link, cost, pros & cons**
- [ ] **Choice & Rationale** after each table
- [ ] **MCU table** included
- [ ] **Pin table** included and matches block diagram
- [ ] 5 V regulator thermal note: \( P*\text{diss} = (V*\text{in}-5)\times I\_\text{total} \)

---

## Pin Table (this subsystem)

| Function                | PIC Pin       | Notes                                 |
| ----------------------- | ------------- | ------------------------------------- |
| Flex sensor ADC         | **RA0 / AN0** | Divider output 0–5 V                  |
| Rotary sensor ADC (ext) | **RA2 / AN2** | External subsystem; shown for context |
| Motor control 1 (DO)    | **RA1**       | To motor subsystem via Conn. 2        |
| Motor control 2 (DO)    | **RB2**       | 〃                                    |
| Motor control 3 (DO)    | **RC4**       | 〃                                    |

---

<!-- 🔁 DUPLICATE THIS WHOLE SECTION PER BLOCK YOU OWN -->

## Block: <NAME THE BLOCK> <!-- e.g., Flex Sensor -->

**Role:** <One line on what this block does and why it matters>

### Options (choose ≥ 3)

| Solution                  | Photo                   |  Cost | Link                                          | Pros                          | Cons                |
| ------------------------- | ----------------------- | ----: | --------------------------------------------- | ----------------------------- | ------------------- |
| **Option 1: <Part name>** | ![](path/to/photo1.png) | $X.XX | [Short descriptive link](https://example.com) | • <pro 1> • <pro 2> • <pro 3> | • <con 1> • <con 2> |
| **Option 2: <Part name>** | ![](path/to/photo2.png) | $X.XX | [Short descriptive link](https://example.com) | • …                           | • …                 |
| **Option 3: <Part name>** | ![](path/to/photo3.png) | $X.XX | [Short descriptive link](https://example.com) | • …                           | • …                 |

**Choice:** <Option # and part name>

**Rationale:** <3–5 sentences tying to specs: voltage range, accuracy, availability/lead time, solderability, size, current draw, risk, schedule, cost.>

**Design Notes (if applicable):**

- Key spec(s): <e.g., resistance range, bend angle, ADC span, resolution, dropout, efficiency>
- Interface: <e.g., 0–5 V analog into RA0, logic-level DOs to driver, etc.>
- Risks & mitigations: <e.g., noise → RC filter; thermal → heatsink>

---

## Block: Flex Sensor _(example headings to guide you)_

<!-- Replace content by duplicating the template above -->
<!-- Keep your chosen model consistent across pages -->

## Block: Signal-Conditioning / Voltage Divider

<!-- Include Rin value targets and expected sensor resistance range -->
<!-- Option 1: Simple divider; Option 2: Divider + RC; Option 3: Op-amp buffer -->

## Block: 5 V Regulator

<!-- Option 1: 7805 linear; Option 2: LDO; Option 3: Buck -->

**Thermal Check:** \( P*\text{diss} = (V*\text{in}-5)\times I\_\text{total} = (9-5)\times \_ = \_ \) W → <OK/Needs heatsink>.

## Block: External Power Source (feeds the 5 V rail)

<!-- e.g., 9 V wall adapter vs AA pack + buck vs Li-ion + buck (no USB power packs) -->

## Block: Connectors (sensor + control header)

<!-- Pitch, locking, current rating, availability, assembly effort -->

---

## Microcontroller (short comparison required by checklist)

| Solution                                   | Photo                    |  Cost | Link                                | Pros                                               | Cons                                           |
| ------------------------------------------ | ------------------------ | ----: | ----------------------------------- | -------------------------------------------------- | ---------------------------------------------- |
| **PIC18F57Q43 Curiosity Nano (Dev Board)** | ![](path/to/picnano.png) | $X.XX | [Product page](https://example.com) | • Fast bring-up • On-board debugger • Known pinout | • Larger footprint • Dev-board BOM cost        |
| **Bare PIC18F57Q43 (custom PCB)**          | ![](path/to/barepic.png) | $X.XX | [Product page](https://example.com) | • Lowest per-unit cost • Small footprint           | • Longer bring-up • Needs programming/debug HW |
| **Alternate MCU Dev Board (<part>)**       | ![](path/to/altmcu.png)  | $X.XX | [Product page](https://example.com) | • Feature X • Ecosystem Y                          | • Porting effort • Different toolchain         |

**Choice:** <…>  
**Rationale:** <Why this MCU path best fits schedule, tools, drivers, and pin needs (RA0/RA2 ADCs; RA1/RB2/RC4 DOs).>

---

## Appendix (recommended)

- **Block Diagram Image:** ![](path/to/your_block_diagram.png)
- **Key Specifications:** <brief bullets you referenced>
- **Assumptions:** <e.g., worst-case currents used, bend-angle range, environment>
