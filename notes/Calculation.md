
### <u>Battery calculation</u>
power required for 4 hours of use

#### 2S Battery -> Buck (TPS563201) -> Dual LDO (Hardware Power Budget & Duty Cycle)
```math
volt3 = 3.3V
volt5 = 5V

# Active currents (datasheet parameters)
stm32 = 25mA
crypt = 10mA
lora = 120mA
gps = 67mA

# 5V rail total active current (LoRA, GPS, plus STM32 and Crypto through 3.3V LDOs)
total_5v_current = lora + gps + stm32 + crypt
power_5v = volt5 * total_5v_current to W

# 2S Li-ion battery pack specifications (2x 18650 in series)
# Nominal: 7.4V (2x 3.7V), Full charge: 8.4V (2x 4.2V), Buck dropout cutoff: 6.8V (2x 3.4V)
cell_capacity = 2600mAh
battery_capacity = 2600mAh
bat_nom_volt = 7.4V
bat_max_volt = 8.4V
bat_min_volt = 6.8V

# TPS563201 synchronous buck converter efficiency (~92%)
buck_eff = 0.92
bat_active_power = power_5v / buck_eff to W

# Battery active currents across discharge curve
bat_nom_current = bat_active_power / bat_nom_volt to mA
bat_min_current = bat_active_power / bat_min_volt to mA
bat_max_current = bat_active_power / bat_max_volt to mA
peak_current = bat_min_current

# 4 hours continuous active calculation
operating_time = 4hr
energy_4hr = bat_active_power * operating_time to Wh
mah_4hr = energy_4hr / bat_nom_volt to mAh

# Sleep currents
stm32_sleep = 15uA
crypt_sleep = 5uA
lora_sleep = 4uA
gps_sleep = 15uA
# Buck quiescent + LDO quiescent + divider bleed (R11+R12 = 38.1k: 7.4V/38.1k = 194uA)
quiescent = 250uA
bat_sleep_current = stm32_sleep + crypt_sleep + lora_sleep + gps_sleep + quiescent to mA

# Tactical duty cycle (1s active every 20s = 5% duty cycle)
t_active = 1s
t_sleep = 19s
duty_cycle = t_active / (t_active + t_sleep)

# Average battery current
bat_avg_current = (duty_cycle * bat_nom_current) + ((1 - duty_cycle) * bat_sleep_current) to mA

# Usable capacity factor due to 6.8V buck dropout (approx 75% usable capacity)
usable_capacity = battery_capacity * 0.75 to mAh

# Battery lifetime with 2S 2600mAh 18650
continuous_runtime = usable_capacity / bat_nom_current to hr
tactical_runtime = usable_capacity / bat_avg_current to hr
tactical_days = tactical_runtime to day
```

#### USB Power Bypass Mode (Direct 5V via D3 Schottky)
```math
volt_usb = 5.0V
v_schottky_drop = 0.40V
volt_5v_rail = volt_usb - v_schottky_drop to V

# Total 5V load current remains the same
usb_active_current = total_5v_current to mA
usb_active_power = volt_usb * usb_active_current to W

# LDO headroom: 4.60V rail - 3.3V out = 1.30V (TLV74333 dropout is only 125mV at 300mA)
ldo_headroom = volt_5v_rail - 3.3V to V
```

