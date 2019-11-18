# DIC Wetterstation 
Wetterstation Projekt für den DIC Unterricht.
<table>
  <tr>
    <td>
      master branch
    </td>
    <td>
      <a href="https://travis-ci.org/andi1603/dic_wetterstation"><img src="https://travis-ci.org/Andi1603/DIC_Wetterstation.svg?branch=master"></a>
    </td>
  </tr>
</table>

## How to use
`git clone https://github.com/andi1603/dic_wetterstation.git DIC_Wetterstation`

Anschließend das 'ESP32-SG' Board mit dem Rechner verbinden und
`pio run --target upload` ausführen.

## BMP180
Der BMP180 ist ein digitaler Drucksensor und operiert mit einer Versorgungsspannug von 3.3V. Mittels I2C kann eine Messung gestartet werden. Je nach Art der Messung kann ein Ergebnis nach 5ms - 25ms aus dem verbauten EEPROM abgerufen werden. Der gelesene Wert muss mit vorbestimmten Kalibrierungswerten transformiert werden (gem. Datenblatt).

## Dependencies
- PlatformIO
- ESP32 Pico Kit
