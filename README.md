# Belt-tensioner-AC-Servo-

이 프로젝트는 https://www.simhubdash.com/diy-belt-tensionner/ 기반으로 제작되었습니다.



1. Parts

AC Servo _ Minas A4 100W
Reducer_ ATG PGX42-20

Driver _  MADDT1205
Motor _ MSMD012S1A


2. Arduino Pin
         MOTOR1  MOTOR2     Servo I/O PIN
PULS       9       10             4
SIGN       7        8             6
Hall S/S   2        3
SON                              
GND      GND      GND            41


3. Servo I/O PinMap

3     PULS1    P24
4     PULS2    0V    <--- Arduino
5     SIGN1    P24
6     SIGN2    0V    <--- Arduino
7     COM+    P24
29   SRV-ON    0V
41     COM-    0V


# Belt-tensioner-AC-Servo

이 프로젝트는  
https://www.simhubdash.com/diy-belt-tensionner/  
기반으로 제작되었습니다.

---

## 1. Parts

| Item | Model |
|-----|------|
| AC Servo | Minas A4 100W |
| Reducer | ATG PGX42-20 |
| Driver | MADDT1205 |
| Motor | MSMD012S1A |

---

## 2. Arduino Pin

| Function | MOTOR1 | MOTOR2 | Servo I/O Pin |
|---------|-------|-------|---------------|
| PULS | 9 | 10 | 4 |
| SIGN | 7 | 8 | 6 |
| Hall S/S | 2 | 3 | |
| SON | | | |
| GND | GND | GND | 41 |

---

## 3. Servo I/O Pin Map

| Pin | Signal | Connection |
|----|-------|-----------|
| 3 | PULS1 | P24 |
| 4 | PULS2 | 0V (Arduino) |
| 5 | SIGN1 | P24 |
| 6 | SIGN2 | 0V (Arduino) |
| 7 | COM+ | P24 |
| 29 | SRV-ON | 0V |
| 41 | COM- | 0V |




