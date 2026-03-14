# Belt Tensioner (AC Servo Version)

AC Servo based belt tensioner for **Sim Racing**, built using a Panasonic Minas A4 servo system.

This project is based on the original DIY belt tensioner project:

https://www.simhubdash.com/diy-belt-tensionner/

---

# Overview

This project uses:

* Panasonic **Minas A4 100W AC Servo**
* **ATG PGX42-20** planetary reducer
* Arduino control
* Hall sensor for homing

The goal was to build a **quiet and responsive belt tensioner system** for SimHub.

---

# Hardware

## Main Components

<p align="left">
<img src="image/MinasA4.jpg" width="320" >
<img src="image/pgx42.png" width="380">
</p>

| Component    | Model        |
| ------------ | ------------ |
| Servo Driver | MADDT1205    |
| Servo Motor  | MSMD012S1A   |
| Reducer      | ATG PGX42-20 |

---

# Arduino Wiring

<p align="left">
<img src="image/Arduino Wirling.jpg" width="900">
</p>

| Function    | Motor 1 | Motor 2 | Servo I/O |
| ----------- | ------- | ------- | --------- |
| Pulse       | 9       | 10      | 4         |
| Direction   | 7       | 8       | 6         |
| Hall Sensor | 2       | 3       | -         |
| GND         | GND     | GND     | 41        |

---

# Servo I/O Pin Map

<p align="left">
<img src="image/IO Wirling.jpg" width="900">
</p>

| Pin | Signal | Connection   |
| --- | ------ | ------------ |
| 3   | PULS1  | P24          |
| 4   | PULS2  | 0V (Arduino) |
| 5   | SIGN1  | P24          |
| 6   | SIGN2  | 0V (Arduino) |
| 7   | COM+   | P24          |
| 29  | SRV-ON | 0V           |
| 41  | COM-   | 0V           |

---

# Servo Drive Parameters

| Parameter | Description                 | Value |
| --------- | --------------------------- | ----- |
| Pr02      | Control Mode                | 0     |
| Pr04      | Disable Over-travel Input   | 1     |
| Pr40      | Command Pulse Input         | 0     |
| Pr42      | Pulse Input Mode            | 3     |
| Pr43      | Pulse Input Inhibition      | 1     |
| Pr4E      | Counter Clear Mode          | 2     |
| Pr4B      | Electronic Gear Denominator | 150   |

---

# Credits

Original project inspiration:

DIY Belt Tensioner
https://www.simhubdash.com/diy-belt-tensionner/
