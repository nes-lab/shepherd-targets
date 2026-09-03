# nrf52 demo for harvesting and rf

This firmware represents a typical intermittent application on a battery-free sensor node.
The app monitors the supply voltage and a GPIO pin.
It sends a BLE advertisement packet and switches on an LED If the supply voltage reaches 3.3 V or the pin goes high.
The LED stays on until the supply voltage drops below 3.3 V or the pin goes low.
The supply voltage is sampled with a frequency of 100 Hz.
The total current consumption in this mode is 5.6 uA.

Edit the definitions of the GPIO pins at the top of `src/app.c` to reflect your hardware.

An App like `LightBlue` or `RaMBLE` can be used to monitor rf-activity.

## Source

<https://github.com/geissdoerfer/shepherd-nrf52-demo>
