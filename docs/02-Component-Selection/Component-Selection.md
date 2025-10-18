---
title: Component Selection (Individual — Flex Sensor Subsystem)
---

> **Scope (Laksh / Flex Sensor Subsystem):** Flex Sensor, Signal-Conditioning/Voltage Divider, 5 V Regulator, External Power Source, Connectors used by this subsystem, and a short Microcontroller comparison.  
> **Interfaces:** Outputs digital lines **RA1, RB2, RC4** to the Motor subsystem via Connector 2. Optional rotary analog signal arrives on **RA2/AN2** from a different subsystem (shown for context only).

## Pin Table (this subsystem)

| Function                       | PIC Pin       | Notes                                  |
| ------------------------------ | ------------- | -------------------------------------- |
| Flex sensor ADC                | **RA0 / AN0** | Divider output 0–5 V                   |
| Rotary sensor ADC _(external)_ | **RA2 / AN2** | From Rotary subsystem (interface only) |
| Motor control 1 (digital out)  | **RA1**       | To Motor subsystem via Connector 2     |
| Motor control 2 (digital out)  | **RB2**       | 〃                                     |
| Motor control 3 (digital out)  | **RC4**       | 〃                                     |

---

## Block: Flex Sensor

**Role:** Measures bend angle; resistance increases with bend. Routed through a divider to 0–5 V for the ADC.

| Solution                                                    | Photo                                                                                                                                                                                                                              |     Cost | Link                                                                                                        | Pros                                                                                                       | Cons                                            |
| ----------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------: | ----------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- | ----------------------------------------------- |
| **Option 1: Spectra Symbol FS-L-095-103-RH (95 mm, 10 kΩ)** | <a href="https://www.digikey.com/en/products/detail/spectra-symbol/FS-L-095-103-RH/17051203"><img alt="FS-L-095-103-RH" src="https://media.digikey.com/Photos/Spectra%20Symbol%20Photos/FS-L-095-103-RH.jpg" width="120"/></a>     | ~$16–$20 | [Digi-Key product page](https://www.digikey.com/en/products/detail/spectra-symbol/FS-L-095-103-RH/17051203) | • Stock 10 kΩ; common in labs • Clear datasheet and ordering guide • Solder-tab/“RH” termination available | • ±30% R tol. • Needs strain relief on tail     |
| **Option 2: Spectra Symbol FS-L-060-103 (60 mm)**           | <a href="https://www.mouser.com/ProductDetail/Spectra-Symbol/FS-L-060-103?qs=WyAARYrb3f7k3ykdRz2Qbw%3D%3D"><img alt="FS-L-060-103" src="https://cdn.mouser.com/images/spectrasymbol/images/FlexSensor.jpg" width="120"/></a>       | ~$15–$18 | [Mouser product page](https://www.mouser.com/ProductDetail/Spectra-Symbol/FS-L-060-103)                     | • Shorter active length (tighter spaces) • Same 10 kΩ nominal • Similar calibration behavior               | • Lower absolute voltage swing for same bend    |
| **Option 3: Flexpoint Bend Sensor (similar 10 kΩ class)**   | <a href="https://www.mouser.com/c/sensors/position-sensors/flex-bend-sensors/"><img alt="Flexpoint example" src="https://cdn.mouser.com/images/mouserimages/hero/sensors-position-sensors-flex-bend-sensors.jpg" width="120"/></a> | ~$10–$20 | [Mouser bend sensors](https://www.mouser.com/c/sensors/position-sensors/flex-bend-sensors/)                 | • Alternative vendor/lead times • Various lengths/forms                                                    | • Different mechanical stackup; may need retest |

**Choice:** **FS-L-095-103-RH** (95 mm, 10 kΩ)  
**Rationale:** Matches our mechanical reach and gives a large ADC span after a simple divider; readily available with datasheet/support; consistent with classroom stock and examples.

---

## Block: Signal-Conditioning / Voltage Divider

**Role:** Convert the flex sensor’s resistance change to a 0–5 V signal for **RA0/AN0**; optionally filter/buffer.

| Solution                                                           | Photo                                                                                                                                                                                                                                                                                 |         Cost | Link                                                                                                                                                                                              | Pros                                                                                | Cons                                                                           |
| ------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -----------: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| **Option 1: Simple divider (10 kΩ sensor vs. fixed Rin 10–22 kΩ)** | <img alt="Divider" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8c/Voltage_divider.svg/240px-Voltage_divider.svg.png" width="120"/>                                                                                                                                    |       <$0.10 | —                                                                                                                                                                                                 | • Easiest; minimal BOM • Works directly into ADC                                    | • Source impedance varies → ADC sampling error • No anti-alias/noise filtering |
| **Option 2: Divider + RC low-pass (e.g., 1 kΩ + 0.1 µF)**          | <img alt="RC filter" src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6f/RC_Divider.svg/240px-RC_Divider.svg.png" width="120"/>                                                                                                                                            |       <$0.20 | —                                                                                                                                                                                                 | • Noise reduction; stable reading • Limits aliasing                                 | • Adds latency; cutoff must be chosen                                          |
| **Option 3: Buffer with rail-to-rail op-amp (e.g., **MCP6002**)**  | <a href="https://www.microchip.com/en-us/product/mcp6002"><img alt="MCP6002" src="https://www.microchip.com/en-us/product/mcp6002/_jcr_content/root/responsivegrid/carousel_copy_copy_copy_cop/item_1663534118.coreimg.png/1704767436954/mcp6002-6001-6004-pic.png" width="120"/></a> | ~$0.40–$0.80 | [Microchip MCP6002](https://www.microchip.com/en-us/product/mcp6002) • [Datasheet PDF](https://ww1.microchip.com/downloads/en/DeviceDoc/MCP6001-1R-1U-2-4-1-MHz-Low-Power-Op-Amp-DS20001733L.pdf) | • High input Z; isolates ADC • Rail-to-rail on 5 V • Easy to add active filter/gain | • Slightly higher BOM & layout effort                                          |

**Choice:** **Option 2: Divider + RC**, upgraded to **Option 3** if noise/ADC impedance errors appear.  
**Rationale:** We’ll start simple with an RC that stabilizes readings; if needed, drop in an MCP6002 buffer (same footprint series) to guarantee low source impedance to the ADC and allow filtering.

---

## Block: 5 V Regulator (from 9 V source)

**Role:** Provide regulated 5 V to the PIC Nano + sensor circuitry.

| Solution                                                   | Photo                                                                                                                                                                                                                                                                          |   Cost | Link                                                                                                                   | Pros                                                | Cons                                        |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | -----: | ---------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- | ------------------------------------------- |
| **Option 1: onsemi **MC7805ACTG** (TO-220, 5 V/1.5 A)**    | <a href="https://www.digikey.com/en/products/detail/onsemi/MC7805ACTG/919998"><img alt="MC7805ACTG" src="https://media.digikey.com/Photos/ON%20Semiconductor%20Photos/MC7805ACTG.jpg" width="120"/></a>                                                                        |    ~$1 | [Digi-Key MC7805ACTG](https://www.digikey.com/en/products/detail/onsemi/MC7805ACTG/919998)                             | • Simple; robust; easy to heatsink • Low EMI        | • Heat dissipation from 9 V→5 V at higher I |
| **Option 2: Automotive LDO **LM2940-5.0** (TO-220, ~1 A)** | <a href="https://www.ti.com/product/LM2940"><img alt="LM2940" src="https://www.ti.com/diagrams/parts/LM2940.jpg" width="120"/></a>                                                                                                                                             | ~$2–$3 | [TI LM2940](https://www.ti.com/product/LM2940)                                                                         | • Lower dropout than 7805 • Good line/load response | • 1 A limit; still linear (heat)            |
| **Option 3: Buck module **LM2596** 5 V/3 A adjustable**    | <a href="https://www.addicore.com/products/lm2596-step-down-adjustable-dc-dc-switching-buck-converter"><img alt="LM2596 Module" src="https://cdn.shopify.com/s/files/1/0828/5565/products/LM2596-Adjustable-Step-Down-Module-iso_1024x1024.jpg?v=1571439043" width="120"/></a> | ~$3–$6 | [Addicore LM2596 module](https://www.addicore.com/products/lm2596-step-down-adjustable-dc-dc-switching-buck-converter) | • High efficiency; low heat • Up to ~3 A            | • Needs layout care for EMI; module height  |

**Choice:** **MC7805ACTG** (Option 1) **if** I_total is small; else **LM2596 buck**.  
**Rationale:** For the Nano + sensor, current is modest, so a 7805 is simplest and quiet. If later loads increase (e.g., additional sensors), we’ll switch to the LM2596 module to avoid thermal issues.

**Thermal note:** \(P*{\text{diss}} = (9\text{ V} - 5\text{ V}) \times I*{\text{total}}\).

- Example: at 120 mA worst-case → \(0.48\text{ W}\) (safe on TO-220 with airflow). Add a small clip-on heatsink if \(>0.8\text{ W}\).

---

## Block: External Power Source (feeds 5 V rail)

| Solution                                                   | Photo                                                                                                                                                                                                               |             Cost | Link                                                                                                          | Pros                                                      | Cons                                 |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------: | ------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------- | ------------------------------------ |
| **Option 1: 9 V wall adapter, 2.1 mm barrel (center +)**   | <a href="https://resources.ampheo.com/static/datasheets/cui-inc/dpd090050-p5p-tk.pdf"><img alt="CUI 9V adapter" src="https://m.media-amazon.com/images/I/51m+u2A7nWL._AC_SL1500_.jpg" width="120"/></a>             |          ~$8–$12 | [CUI DPD0900xx series datasheet](https://resources.ampheo.com/static/datasheets/cui-inc/dpd090050-p5p-tk.pdf) | • Clean supply, plug-and-play • No charging safety issues | • Tethered to mains                  |
| **Option 2: 6×AA holder (9 V alkaline / ~7.2 V NiMH)**     | <a href="https://www.dfrobot.com/product-201.html"><img alt="6xAA holder" src="https://dfimg.dfrobot.com/store/data/FIT0078/7a8f9b46c8473a0af8f2a51b3b0a6307.jpg" width="120"/></a>                                 |           ~$1–$3 | [DFRobot 6×AA holder](https://www.dfrobot.com/product-201.html)                                               | • Cheap, easy to source • Field-portable                  | • Disposable cells or charger needed |
| **Option 3: 2×18650 holder (7.4 V nominal) + buck to 5 V** | <a href="https://www.parts-express.com/18650-Dual-Battery-Holder-with-Leads-140-781"><img alt="18650 holder" src="https://www.parts-express.com/data/default/images/catalog/140/140-781_HR_0.jpg" width="120"/></a> | ~$2–$5 (+ cells) | [2×18650 holder](https://www.parts-express.com/18650-Dual-Battery-Holder-with-Leads-140-781)                  | • High energy density • Reusable cells                    | • Must manage Li-ion safety/charging |

**Choice:** **Option 1: 9 V wall adapter** for lab bring-up; **Option 3** later if portable.  
**Rationale:** Wall adapter is safest/cleanest for bench testing; battery paths introduce charging and cutoff concerns we don’t need in the MVP.

---

## Block: Connectors (sensor input + subsystem headers)

| Solution                                             | Photo                                                                                                                                                                            |        Cost | Link                                                                                          | Pros                                                        | Cons                                     |
| ---------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------: | --------------------------------------------------------------------------------------------- | ----------------------------------------------------------- | ---------------------------------------- |
| **Option 1: JST-XH (2.5 mm pitch) wire-to-board**    | <a href="https://www.digikey.com/en/resources/datasheets/jst/xh-connector"><img alt="JST-XH" src="https://media.digikey.com/Photos/JST%20Photos/XH_Series.jpg" width="120"/></a> |         Low | [JST XH datasheet](https://www.jst-mfg.com/product/pdf/eng/eXH.pdf)                           | • Locking friction • ~3 A rating (AWG22) • Widely available | • 2.5 mm pitch (not breadboard-friendly) |
| **Option 2: Molex KK / JST-XH compatible headers**   | <a href="https://www.mouser.com/datasheet/2/737/Adafruit_4423_Web-3357984.pdf"><img alt="JST-XH kit" src="https://cdn-shop.adafruit.com/970x728/4423-02.jpg" width="120"/></a>   | Kit $20–$30 | [JST-XH kit (Adafruit)](https://www.mouser.com/datasheet/2/737/Adafruit_4423_Web-3357984.pdf) | • Complete assortment for lab use                           | • Bulk purchase; storage                 |
| **Option 3: 0.1'' (2.54 mm) pin headers + housings** | <img alt="0.1 headers" src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/33/Pin_header_2x05.jpg/240px-Pin_header_2x05.jpg" width="120"/>                               |    Very low | —                                                                                             | • Breadboard-compatible • Cheapest                          | • No latch; easier to pull loose         |

**Choice:** **JST-XH** on the PCB for field connections; **0.1" pins** for lab/breadboard adapters.  
**Rationale:** XH gives current capacity and retention; pin headers are convenient during prototyping.

---

## Microcontroller (short comparison — required by checklist)

| Solution                                                | Photo                                                                                                                                                                                                                                                                                 |     Cost | Link                                                                            | Pros                                               | Cons                                           |
| ------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------: | ------------------------------------------------------------------------------- | -------------------------------------------------- | ---------------------------------------------- |
| **PIC18F57Q43 Curiosity Nano (Dev Board)**              | <a href="https://www.microchip.com/en-us/development-tool/DM164150"><img alt="Curiosity Nano" src="https://www.microchip.com/content/dam/mchp/mrt-dam/devtools/low-pincount-8-bit-nano_600x600.jpg" width="120"/></a>                                                                 | ~$25–$35 | [Microchip DM164150](https://www.microchip.com/en-us/development-tool/DM164150) | • On-board debugger • Fast bring-up • Known pinout | • Larger footprint • Dev board BOM cost        |
| **Bare PIC18F57Q43 on custom PCB**                      | <a href="https://www.microchip.com/en-us/product/PIC18F57Q43"><img alt="PIC18F57Q43" src="https://www.microchip.com/_next/image?url=https%3A%2F%2Fmedia.microchip.com%2Fis%2Fimage%2Fmicrochiptechnologyinc%2FMicrochip%20PIC18F57Q43%3Ffmt%3Dpng-alpha&w=384&q=75" width="120"/></a> |   ~$3–$6 | [Product page](https://www.microchip.com/en-us/product/PIC18F57Q43)             | • Lowest unit cost • Small footprint               | • Needs programming/debug HW • Longer bring-up |
| **Alt MCU Dev Board (e.g., ATmega4809 Curiosity Nano)** | <a href="https://www.microchip.com/en-us/development-tool/EV35L43A"><img alt="Alt Nano" src="https://www.microchip.com/content/dam/mchp/mrt-dam/devtools/nano-boards_600x600.jpg" width="120"/></a>                                                                                   | ~$25–$30 | [Example alt board](https://www.microchip.com/en-us/development-tool/EV35L43A)  | • Similar toolchain • Abundant examples            | • Porting effort • Different peripherals       |

**Choice:** **PIC18F57Q43 Curiosity Nano**  
**Rationale:** Zero-friction bring-up (on-board debugger, USB power) and pin access to RA0/RA2 ADC + RA1/RB2/RC4 outputs make it the lowest-risk path for this class project.

---

# Power Budget (stub for next page)

> Create a separate page called **Power Budget**; paste the template below and fill currents from datasheets.

### Section A — Loads (Absolute Max or “worst realistic” currents)

| Device                              | Voltage | Current (mA) | Datasheet ref |
| ----------------------------------- | ------: | -----------: | ------------- |
| PIC18F57Q43 Curiosity Nano (active) |     5 V |              |               |
| Flex sensor divider + buffer        |     5 V |              |               |
| Indicator LEDs (if any)             |     5 V |              |               |
| **Subtotal**                        |         |              |               |

### Section B — Rails + 25% margin

| Rail    | Devices on rail   | Sum (mA) | +25% Margin | Rail total (mA) |
| ------- | ----------------- | -------: | ----------: | --------------: |
| **5 V** | MCU, sensor chain |          |             |                 |

### Section C — Regulator choice per rail

- **5 V:** **MC7805ACTG** (or LM2596 buck if thermal > ~0.8 W)  
  _Enter the final choice into your spreadsheet cell “Regulator or Source Choice.”_

### Section D — External power source

- **9 V wall adapter** (center-positive, 2.1 mm). Confirm **Remaining Current ≥ 0**.

### Section E — Battery life (if battery used)

\[
\text{Life (h)} \approx \frac{\text{Capacity (mAh)}}{\text{Total current (mA)}} \times \text{derating}
\]
Use derating 0.7–0.8 for real-world.
