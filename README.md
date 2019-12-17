# Node MCU farmer 1.0 2019 DEC
Egy növény gondozó Node mcu (esp-32) project.
A projekt feladatai és főbb tulajdonságai:
* Automatizált rendszer
* A növény rendszeres öntözése a szenzor adatok alapján ha a táptalaj száraz lenne öntöz amíg el nem éri a kellő nedvességet a talaj. 
* A levegő hőmérséklet és páratartalom mérése , hőmérséklet alapján melegítés az optimális hőfok eléréséig.
* A növény táptalaj hőmérsékletének mérése. Lehetőség szerint ez alapján is történhet a melegítés indítása de alapjáraton a levegő hőmérséklete befolyásolja az eszköz működését ,illetve a két szenzor átlagát is vehetnénk.
* Összes szenzoradat kijelzése OLED kijelzőn
* Adatok nyomonkövetése telefonon illetve közbeavatkozás virtuális gombokon kersztül (pl öntözés indítása)
* Adat exportálás CSV fájlba

A test mappában találhatóak a teszt fájlok , kódok. 
A NodeMCU farmer mapában pedig a végleges program látható.

 

