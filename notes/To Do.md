# Cryptographic Tactical Node — Hardware & PCB Design To-Do List

**Project**: Cryptographic Tactical Node  
**Status**: Schematics Complete & Verified (0 ERC Errors)  
**Target Hardware**: STM32F411CEU6, NXP SE050, Ebyte E22-900T20D (LoRA), u-blox NEO-M8N (GPS), MCP73871, TPS61023  
**Security Focus**: Autonomous Hardware Zeroization via Mechanical Switch on Pin 2 (`PC13` / `RTC_TAMP1`)  

---

## Phase 1: Pre-PCB Prerequisites (Footprint Assignment & Netlist Sync)
> [!IMPORTANT]
> In KiCad, every schematic symbol must have an assigned footprint before pressing **F8** (**Update PCB from Schematic**). Currently, 92 components require footprint assignment.

- [ ] **1.1 Register SE050 Footprint Library**:
  - [ ] Add `custom/footprints/HX2QFN20.pretty` to `hardware/kicad/fp-lib-table`.
  - [ ] Assign footprint `HX2QFN20:HX2QFN20` to `U9` (NXP SE050) in `Crypt.kicad_sch`.
- [ ] **1.2 Assign Passive Component Footprints (0603 Metric Recommended)**:
  - [ ] Assign `Resistor_SMD:R_0603_1608Metric` to all 35 resistors:
    - `Power.kicad_sch`: `R1, R2, R5, R6, R7, R8, R9, R15, R16, R17, R18, R19, R23, R24, R25, R26, R27, R34, R35`
    - `STM32.kicad_sch`: `R10, R11, R12, R13, R14, R20, R21, R22`
    - `LoRA.kicad_sch`: `R29, R30`
    - `crypto_node.kicad_sch`: `R28, R31, R32, R33`
    - `Tampering.kicad_sch`: `R36`
  - [ ] Assign `Capacitor_SMD:C_0603_1608Metric` to all 44 capacitors:
    - `Power.kicad_sch`: `C1, C2, C3, C4, C5, C6, C7, C9, C10, C11, C12, C13, C14, C15, C16, C32, C40, C41, C42, C43`
    - `STM32.kicad_sch`: `C8, C21, C22, C23, C24, C25, C26, C27, C28, C29, C30, C31, C33, C34, C35, C36, C37, C38, C39`
    - `GPS.kicad_sch`: `C44, C45`
    - `LoRA.kicad_sch`: `C46, C47`
    - `Crypt.kicad_sch`: `C48, C49`
    - `Tampering.kicad_sch`: `C50`
- [ ] **1.3 Assign Electromechanical & Power Footprints**:
  - [ ] `BT1` (Li-Po battery input): Assign `Connector_JST:JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical` (or 2.54 mm through-hole pads).
  - [ ] `SW1` (Power slide switch): Assign `Button_Switch_SMD:SW_SPDT_PCM12`.
  - [ ] `L1` (TPS61023 Boost inductor, 1 µH, >3A saturation): Assign `Inductor_SMD:L_Wuerth_WE-LQ` or standard 2520/3030 SMD power inductor footprint.
  - [ ] `D1` (1SMA4734A Zener diode): Assign `Diode_SMD:D_SMA`.
  - [ ] `JP1–JP5` (Solder Jumpers): Assign `Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm`.
- [ ] **1.4 Push Netlist to PCB**:
  - [ ] In KiCad Schematic Editor, select **Tools → Update PCB from Schematic** (`F8`).
  - [ ] Confirm **0 errors** during component and netlist synchronization into `crypto_node.kicad_pcb`.

---

## Phase 2: Board Setup & Physical Constraints
- [ ] **2.1 Define 4-Layer Stackup**:
  - [ ] **Layer 1 (Top / F.Cu)**: High-speed digital signals, RF traces, and component placement.
  - [ ] **Layer 2 (In1.Cu)**: Solid, unbroken `GND` reference plane (critical for 50Ω RF coplanar waveguides and return currents).
  - [ ] **Layer 3 (In2.Cu)**: Power distribution planes (`+3.3V`, `+5V_BOOST`, `+BATT_PROC`).
  - [ ] **Layer 4 (Bottom / B.Cu)**: Low-speed signals, non-critical routing, and secondary ground pours.
- [ ] **2.2 Enclosure Mechanical Constraints**:
  - [ ] Define board outline on `Edge.Cuts` layer according to physical tactical enclosure dimensions.
  - [ ] Place M2.5 or M3 grounded mounting holes in all 4 corners with adequate keepout radius for screw heads.
  - [ ] Position tactile switch **`S4`** along the enclosure edge where the lid plunger firmly compresses the button when the case is closed.
  - [ ] Align board-edge connectors: USB-C port, antenna ports (SMA/U.FL for LoRA and GPS), SWD header `J5`, and power switch `SW1`.

---

## Phase 3: Critical Floorplanning & Subsystem Placement
- [ ] **3.1 RF & Antenna Isolation**:
  - [ ] Place `U8` (Ebyte LoRA) and `U7` (NEO-M8N GPS) away from high-speed digital busses and the switching boost converter.
  - [ ] Keep RF antenna feedlines as short and direct as possible.
  - [ ] Implement solid ground keepouts on all layers beneath the GPS patch antenna if integrated.
- [ ] **3.2 Power Supply Layout (MCP73871 + TPS61023 + TLV74333 LDOs)**:
  - [ ] Minimize the high-current switching loop of `U1` (TPS61023): input cap `C5` $\to$ inductor `L1` $\to$ SW pin $\to$ output cap `C6` $\to$ GND.
  - [ ] Place an array of thermal vias (0.3 mm drill) into the exposed thermal pads (EP) of `U6` (MCP73871) and `U5` (STM32 QFN-48) to dissipate heat into the inner ground plane.
- [ ] **3.3 Microcontroller & Security Core**:
  - [ ] Place STM32 decoupling capacitors (`C24–C29`, 100 nF) immediately next to each `VDD`/`VSS` pin pair with direct, low-inductance vias to GND.
  - [ ] Position crystals `Y1` (25 MHz HSE) and `Y2` (32.768 kHz LSE) directly adjacent to MCU pins `PH0/PH1` and `PC14/PC15`, surrounded by a protective ground guard ring.
  - [ ] Place `U9` (SE050) adjacent to STM32 I2C pins with decoupling capacitor `C49` placed directly at its supply pin.
- [ ] **3.4 Anti-Tamper Circuit Placement**:
  - [ ] Place solder bypass jumper **`JP1`** in an easily accessible location for bench servicing and firmware flashing.
  - [ ] Route the `TAMPER` trace directly from `S4` / `JP1` to STM32 Pin 2 (`PC13`), routing away from noisy RF traces and switching inductors.

---

## Phase 4: Routing & Design Rules Check (DRC)
- [ ] **4.1 Calculate Controlled Impedance**:
  - [ ] Calculate 50Ω coplanar waveguide or microstrip trace width for the LoRA and GPS antenna feedlines using your manufacturer's 4-layer stackup (e.g. JLCPCB JLC04161H / PCBWay).
- [ ] **4.2 Signal Routing**:
  - [ ] Route crystal oscillator lines symmetrically without any vias.
  - [ ] Route I2C bus lines (`SCL`/`SDA` for SE050) as parallel differential pairs with clear spacing from high-power PWM lines (like `LED_DATA` for WS2812B).
  - [ ] Use wide traces ($\ge 0.5\text{ mm} - 1.0\text{ mm}$) for high-current power rails (`+5V_BOOST`, `+BATT`, and battery charging path).
- [ ] **4.3 Ground Planes & Stitching**:
  - [ ] Flood Top and Bottom layers with `GND` copper pours.
  - [ ] Add ground stitching vias (via fence) spaced $\le 3\text{ mm}$ along board boundaries and around RF sections to suppress EMI leakage.
- [ ] **4.4 Run DRC**:
  - [ ] Set manufacturer design rules (min trace width: 5 mil, min clearance: 5 mil, min drill: 0.3 mm).
  - [ ] Run KiCad Design Rules Check (**Inspect → Design Rules Checker**) and resolve all violations to **0 Errors**.

---

## Phase 5: Production & Fabrication Outputs
- [ ] **5.1 Silkscreen & DFM Polish**:
  - [ ] Add Pin 1 orientation markers for all ICs (`U5`, `U6`, `U7`, `U8`, `U9`).
  - [ ] Label external connectors clearly (`USB`, `SWD`, `BATT +/-`, `ON/OFF`).
  - [ ] Add descriptive silkscreen text next to `JP1`: `TAMPER BYPASS: SOLDER=DEBUG / OPEN=ARMED`.
- [ ] **5.2 Export Manufacturing Files**:
  - [ ] **Gerber & Drill Files**: Top/Bottom Copper, Inner 1/2, Solder Mask, Silkscreen, Edge.Cuts, and Excellon Drill files in a single ZIP.
  - [ ] **Bill of Materials (BOM)**: Export final CSV containing Ref, Value, Footprint, and manufacturer part numbers.
  - [ ] **Centroid / CPL File**: Export component placement file (XY coordinates and rotation angles) for automated SMT pick-and-place assembly.

---

## Phase 6: Firmware & Bench Assembly Checklist
- [ ] **6.1 Bench Flashing / Servicing**:
  - [ ] Bridge solder jumper **`JP1`** with solder to clamp `PC13` permanently to `GND`.
  - [ ] Flash STM32 firmware and provision cryptographic keys into NXP SE050 via SWD without triggering false zeroization.
- [ ] **6.2 Firmware Configuration in STM32CubeMX**:
  - [ ] Configure `PC13` as `RTC_TAMPER_1` with **Rising Edge** trigger and **Tamper Filter** enabled.
  - [ ] Implement zeroization routine in `TAMP_STAMP_IRQHandler` to wipe RAM keys upon intrusion.
- [ ] **6.3 Final Assembly & Arming**:
  - [ ] Desolder `JP1` (return to open circuit).
  - [ ] Mount PCB into tactical enclosure and close the chassis lid, depressing switch `S4`.
  - [ ] The node is actively armed: opening the enclosure lid releases `S4`, pulling `PC13` High and executing autonomous zeroization within 4 RTCCLK cycles.
