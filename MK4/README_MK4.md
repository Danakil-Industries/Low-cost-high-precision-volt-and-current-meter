# Low-cost-high-precision-volt-and-current-meter
MK4 Readme
This project is WIP
Up to ±18V and ±20A. Up to ±2.5V difference may be present between the current input terminals and the V- input terminal.
First posted attempt. Hermetically sealed 24 bit multimeter attempt with low common mode leakage, guarding, ADS1256, ADR1399, and ADA4523s sprinkled to taste.
Has analog voltage rail sensing; because it makes sure none of the rails converters are drifty.
A single, low value shunt resstor is used for all current ranges, resulting in minimal impact on all signals, while also using a LNA to (hopefully) give beautiful performance.
High voltage input impedance is present in all ranges.  

NOT ALL THINGS ARE POSTED YET