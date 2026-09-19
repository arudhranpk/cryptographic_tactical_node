#### encryption IC
[NXP SE050](https://www.lioncircuits.com/parts/SE050C1HQ1%2FZ01SCZ)
[NXP SE051](https://www.lioncircuits.com/parts/SE051C2HQ1%2FZ01XDZ)

#### STM32
[STM32f411CE - 512kb](https://robu.in/product/stm32f411ceu6-minimum-system-board-microcomputer-stm32-arm-core-board/)

#### LORA
[20dBm](https://robu.in/product/ebyte-e32-900t20d-ebyte-868mhz-lora-solution-semtech-ic-long-distance-uart-20dbm-lora-module/)
[22dBm](https://robu.in/product/ebyte-e220-900t22d-lora-wireless-uart-module-rssi-ism-868mhz-915mhz-22dbm-module-lora-spread-spectrum-uart-interface-sma-k-antenna/)
[30dBm](https://robu.in/product/ebyte-e220-900t30d-ebyte-llcc68-wireless-transmitter-module-915mhz-lora-rf-module/)

915MHz
[sharvi](https://sharvielectronics.com/product/915mhz-lora-gateway-antenna-3dbi-gain-with-sma-male-connector/)
[amazon](https://www.amazon.in/TX915-JKD-20-Omnidirectional-Communication-Compatible-Meshtastic/dp/B0F7HT92V6/ref=sr_1_8?sr=8-8)

868MHz
[sharvi](https://sharvielectronics.com/product/868mhz-lora-gateway-antenna-3dbi-gain-with-sma-male-connector/)
[amazon](https://www.amazon.in/TX868-JKD-20-Wireless-Communication-Antenna-Compatible/dp/B0F7HZ3WBG/ref=sr_1_2?sr=8-2)

#### GPS
[neo m8n sharvi](https://sharvielectronics.com/product/neo-m8m-gps-module-with-ceramic-active-antenna/)
[neo m8n amazon](https://amzn.in/d/0ffmnUyG)


#### Battery (2S 18650 Configuration - "The New Norm")
*   **Battery Cells**: 2x 18650 Li-Ion cells in series (3.7V nominal each, 7.4V nominal pack, 8.4V max charge, 2600–3500 mAh).
    *   *Recommended Safety Practice*: Protected Button-Top 18650 cells (e.g. KeepPower 18650 Protected 2600/3500mAh) with integrated micro-PCM.
*   **Battery Holders (BT1, BT2)**: [Keystone 1042](https://www.keyelco.com/product.cfm/product_id/811) (SMD 18650 single-cell battery clip/holder, 2 required in series).

#### Fuse & Protection
*   **Resettable PPTC Fuse (F1)**: Bel Fuse `0ZCF0185FF2C` (1.85A Hold, 3.7A Trip, 2920 SMD).
*   **Reverse Polarity P-MOSFET (Q1)**: [FDN304PZ](https://robu.in/product/fdn304pz-onsemi-power-mosfet-p-channel-20-v-2-4-a-0-036-ohm-supersot-surface-mount/) (P-Channel -20V 2.4A, 36 mΩ).
*   **Gate Clamp Zener Diode (D2)**: [1SMA4734A](https://robu.in/product/1sma4734a-mdd-1w-5-32v5-92v-5-6v-sma-zener-diodes-rohs/) (5.6V 1W SMA).
*   **USB 5V Bypass Schottky Diode (D3)**: `SS24B` (2A 40V SMA Schottky Diode, Slkor).

### POWER
#### Buck Converter ("The New Norm")
*   **Buck IC (U1)**: [TPS563201](https://www.ti.com/product/TPS563201) (Texas Instruments 4.5V–17V input, 3A output, 580 kHz synchronous step-down, SOT-23-6).
*   **Inductor (L1)**: SWPA5040S2R2NT (2.2 µH, 4.2A saturation current, SMD).

#### Power Switch (SW1)
*   **Switch**: [SS-12D10L7-XKB](https://robu.in/product/ss-12d10l7-xkb-direct-insert-3a-single-pole-double-throw-spdt-125v-125v-3a-10000-times-black-plugin-slide-switches-rohs/) (Direct Insert 3A Single Pole Double Throw (SPDT) 125V 3A / 24V 3A, 10,000 cycles, Black Plugin Slide Switch ROHS).

#### LDO Regulators (U2, U3)
*   **Dual 3.3V LDOs**: [TLV74333PDBVR](https://robu.in/product/tlv74333pdbvr-texas-instruments-300ma-fixed-3-3v-positive-electrode-5-5v-sot-23-5-voltage-regulators-linear-low-drop-out-ldo-regulators-rohs/) (Texas Instruments 300mA Fixed 3.3V, 125mV dropout, SOT-23-5).


