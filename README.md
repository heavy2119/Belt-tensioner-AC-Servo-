# Belt-tensioner-AC-Servo-

이 프로젝트는 https://www.simhubdash.com/diy-belt-tensionner/ 기반으로 제작되었습니다.


## 1. Parts

<p align="center">
  <img src="image/MinasA4.jpg" width="400">
  <img src="image/pgx42.png" width="483">
</p>

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
| GND | GND | GND | 41 |

---

## 3. Servo I/O Pin Map

| Pin | Signal | Connection |
|----|-------|-----------|
| 3 | PULS1 | P24 |
| 4 | PULS2 | 0V (<------Arduino) |
| 5 | SIGN1 | P24 |
| 6 | SIGN2 | 0V (<------Arduino) |
| 7 | COM+ | P24 |
| 29 | SRV-ON | 0V |
| 41 | COM- | 0V |

## 4. Drive Parameter 

| Pr.No | Title | Value |
|----|-------|-----------|
| 02 | Setup of control mode| 0 |
| 04 | Invalidation of over-travel inhibit input | 1 |
| 40 | Selection of command pulse input | 0 |
| 42 | Mode setup of command pulse input | 3 |
| 43 |Inhibition setup of command pulse input  | 1 |
| 4E | Counter clear mode | 2 |
| 4B | Denominator of electronic gear | 150 |




