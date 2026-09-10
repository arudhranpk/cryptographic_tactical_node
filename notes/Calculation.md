
### <u>Battery calculation</u>
power required for 4 hours of use

#### Battery -> Buck
```math
volt3 = 3.3V
volt5 = 5V

#current
stm32 = 250mA
gps = 70mA
lora = 110mA
crypt = 50mA

power = (volt5 * lora) + (volt3 * (stm32 + gps + crypt))

#required watt hours
operating_time = 4hr

energy = power * operating_time to Wh

#required battery mah
li_typ_volt = 3.7V

mah = round((energy / li_typ_volt) to mAh, mAh) to mAh
peak_current = power / 3.7V



```

### Battery -> Buck -> LDO
```math
volt5 = 5V

#current
stm32 = 250mA
gps = 70mA
lora = 110mA
crypt = 50mA

total_current = stm32 + gps + lora + crypt

power = volt5 * total_current in W

#required energy
operating_time = 4hr

energy = power * operating_time in Wh

#required Battery
li_typ_volt = 3.7V

mah = round((energy / li_typ_volt) to mAh, mAh) to mAh
peak_current = power / 3.7V


```

### Battery -> Boost -> LDO (Hardware Power Budget & Duty Cycle)
```math
volt5 = 5V
li_typ_volt = 3.7V
boost_eff = 0.90

#active currents (datasheet parameters)
stm32 = 25mA
crypt = 10mA
lora = 120mA
gps = 67mA

total_active_current = stm32 + crypt + lora + gps
power_5v = volt5 * total_active_current to W

#battery active power & current through boost
bat_active_power = power_5v / boost_eff to W
bat_active_current = bat_active_power / li_typ_volt to mA

#4 hours continuous active calculation
operating_time = 4hr
energy_4hr = bat_active_power * operating_time to Wh
mah_4hr = energy_4hr / li_typ_volt to mAh
peak_current = bat_active_current

#sleep currents
stm32_sleep = 15uA
crypt_sleep = 5uA
lora_sleep = 4uA
gps_sleep = 15uA
quiescent = 107uA
bat_sleep_current = stm32_sleep + crypt_sleep + lora_sleep + gps_sleep + quiescent to mA

#tactical duty cycle (1s active every 20s = 5% duty cycle)
t_active = 1s
t_sleep = 19s
duty_cycle = t_active / (t_active + t_sleep)

#average battery current
bat_avg_current = (duty_cycle * bat_active_current) + ((1 - duty_cycle) * bat_sleep_current) to mA

#battery lifetime with 2000 mAh Li-Po
battery_capacity = 2000mAh
continuous_runtime = battery_capacity / bat_active_current to hr
tactical_runtime = battery_capacity / bat_avg_current to hr
tactical_days = tactical_runtime to day
```
