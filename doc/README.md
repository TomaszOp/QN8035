# QN8035 – dokumentacja

Datasheet QN8035 (Quintic, Single-Chip Low-Power FM Receiver for Portable Devices):

- Rev 0.08 Preliminary (02/2010): https://xn--p8jqu4215bemxd.com/wp-content/uploads/2019/08/QN8035.pdf
- Rev 1.0: http://img.hqew.com/File/Others/1320000-1329999/1322390/Electronic/2016112103356424049.pdf
- Kopia: http://down.cosou.com/xintechsz.com/QN8035.pdf

Zapisz plik PDF w tym katalogu jako `QN8035.pdf`.

Ważne fragmenty:
- 5.13: start > stop → skanowanie w dół, start < stop → skanowanie w górę.
- Reg 00h bit 1 (CHSC): kasowany automatycznie po zakończeniu skanowania.
- Rozdział 6: mapa rejestrów 00h–18h, w tym RDS (RDSD0–RDSD7, STATUS2).
