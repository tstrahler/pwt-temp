# Temperaturmessung für PWT
Dieses Projekt behandelt die Entwicklung einer Temperaturmessung zur Verwendung mit Plattenwärmetauschern (PWT). Die Temperaturmessung hat die Aufgabe den Temperaturgradienten über PWT zu erfassen, um so den Grad der Verschmutzung erfassen zu können.

* [Anforderungen](#anforderungen)
* [Realisierung der Temperaturmessung](#realisierung-der-temperaturmessung)
    * [Berührungslose Messung](#berührungslose-messung)
    * [Oberflächenmessung](#oberflächenmessung)
* [Entwicklung der Elektronik](#entwicklung-der-elektronik)

Eine Profilaufnahme eines solchen PWT ist im Folgenden dargestellt.

![Profilaufnahme eines solchen PWT](/doc/img/pwt.jpg)

# Anforderungen
Um Verschmutzung mit ausreichender Genauigkeit erreichen zu können, sind Temperaturmessungen mit einem Abstand von ca. 10 mm erforderlich. Diese Temperaturmessungen müssen wie in der Abbildung in Y-Richtung gleichmäßig verteilt werden. Der zu messende Bereich entspricht in etwa einer Länge von 300 mm bis 800 mm. Eine Aufteilung in mehrere Messeinheiten bzw. Messkarten.

Die Genauigkeit der Temperaturmessung soll ≤1 °C betragen. Da jedoch ein Temperaturgradient zu messen ist, fällt die absolute Messabweichung in den Hintergund. Wichtiger ist eine homogene Messabweichung über alle Sensoren, sodass die Kalibrierung und Anpassung möglichst unkompliziert ist.

Da sich diese Wärmetauscher in feuchter und warmer Umgebung befinden, ist ein Wärmebereich zwischen -20 °C und 105 °C anzustreben. Die relative Luftfeuchtigkeit ist mit 70 % anzustreben.

# Realisierung der Temperaturmessung
Die Temperaturmessung kann nach unterschiedlichen Methoden durchgeführt werden. Im Folgenden wird zwischen der Berührungslosen und der Oberflächenmessung unterschieden. Beide Methoden habe Vor- und Nachteile.

## Berührungslose Messung
Die Berührungslose Messung basiert auf der Verwendung von Infrarot-Array-Sensoren. Das Grundprinzip dieser Sensoren basiert auf der Funktion bekannter Infrarot-Wärmebildsensoren. Diese Infrarot-Array-Sensoren besitzen jedoch eine weitaus geringere Auflösung.

Ein Produktbeispiel eines solchen Sensors ist der [AMG8834 von Panasonic](https://industrial.panasonic.com/cdbs/www-data/pdf/ADI8000/ADI8000C66.pdf). Dieser Sensor besitzt eine Auflösung von 8x8 Pixel und kann mittels I²C durch einen Mikrocontroller ausgelesen werden. Eine konzeptionelle Darstellung der Verwendung eines solchen Sensors ist in folgender Abbildung dargestellt.

![Verwendung eines Infrarot-Array-Sensors](/doc/img/infrarot.png)

Da der Sensor einen Bildwinkel von 60° besitzt, ist bei einer betrachteten Fläche mit 300 mm Seitenlänge eine Mindesthöhe von 260 mm erforderlich, um die gesamte Fläche mit einem Sensor abzudecken. Dabei kann eine Auflösung von max. 37.5 mm auf dem PWT erreicht werden. Diese Auflösung ist weit unter den geforderten 10 mm. Somit sind mehrere Sensoren erforderlich.

Die Genauigkeit des Sensor ist mit ±2.5 °C angegeben. Da jedoch ein Temperaturgradient zu erfassen ist, fällt die absolute Genauigkeit des Sensors in den Hintergrund. Weiterhin kann durch eine die Messabweichung des Sensors kalibriert und ausgeglichen werden.

Der Temperaturbereich der Umgebung wird mit -20 °C bis 80 °C angegeben. Da das Gerät jedoch nicht in direktem Kontakt mit dem PWT ist, wird dies als hinreichend angenommen. Ein Graph zur maximalen Umgebungsfeuchtigkeit ist im Datenblatt gegeben. Die maximal zu messende Temperatur ist mit 100 °C angegeben.

Aufgrund der metalischen Oberflächenbeschaffenheit des PWT, ist eine direkte Messung mittels Infrarot-Array-Sensors voraussichtlich nicht möglich. Durch ein aufkleben eines Papierstickers kann dieses Problem jedoch gelöst werden.

Der Preis eines solchen Sensors ist, abhängig vom Distributor, mit 30 € anzunehmen. Da mehrere Sensoren zur Erfassung der Mindestfläche erforderlich sind, ist sind Kosten von 60 € pro Sensor aufwärts anzunehmen.

## Oberflächenmessung
Eine weitere Methode zur Messung der Oberflächentemperatur des PWT, ist die Messung durch Kontakt zur Oberfläche. Dies kann entweder durch integrierte Lösungen oder durch Oberflächensensoren durchgeführt werden. Da Oberflächensensoren mit relativ hohen hosten und Montageaufwand verbunden sind, wird diese Möglichkeit nicht weiter verfolgt.

Integrierte Lösungen sind eine wesentlich kostengüstigere Methode zur Aufnahme von Temperaturen. Diese integrierten Temperaursensoren kommen jedoch mit dem Nachteil, dass sie in direktem Kontakt mit der unterliegenden Platine sind. Dies führt zu einer Beeinflussung der Messungen mehrerer Sensoren. Durch die Schaffung eines Überganges mit geringem Wärmewiderstand, lässt sich dieser Effekt jedoch etwas redizieren. So können die Sensoren beispielweise durch eine kleine Menge Wärmeleitkleber mit dem PWT verklebt werden. Es existieren weitere gleichartige Methoden zur Lösung dieses Problems.

Zu Beginn werden Sensoren mit digitaler Kommunikation untersucht. Diese sind mit verschiedenen Schnittstellen erhältlich. Darunter SPI, I²C und 1-Wire. Da bei dieser Anwendung eine großzahl an Sensoren erforderlich ist, ist die Verwendung von 1-Wire mit der wenigsten "Zusatzhardware" verbunden.

Sensoren welche über die 1-Wire Schnittstelle verfügen, können aufgrund ihrer itegrierten 64-Bit Adresse quasi endlos oft mit der selben Datenleitung verbunden werden. Dies ist in der vorliegenden Anwendung deutlich von Vorteil. Diese Sensoren bringen jedoch den Nachteil mit, dass sie relativ teuer sind, oder nicht auf dem gesamten Temperaturbereich die geforderte Genauigkeit von ≤1 °C besitzen. Durch vorheriges Kalibrieren und Ausgleichen des Messfehlers kann dem jedoch entgegen gekommen werden.

Sensoren mit 1-Wire Schnittstelle sind z.B. der bekanntere [DS18B20](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf) von Maxim. Dieser Sensor erfüllt zwar die Anforderung an die Messgenauigkeit, ist mit einem Preis von ca. 5,00 € sehr teuer. Ein weiteres Produkt von Maxim ist der [MAX31820](https://datasheets.maximintegrated.com/en/ds/MAX31820.pdf). Dieser Sensor ist mit 3,00 € wesentlich günstiger, besitzt jedoch im geforderten Temperaturbereich eine Messgenauigkeit von ±2 °C.

# Entwicklung der Elektronik
Da sich wie zuvor beschreiben für Infrarot-Array-Sensoren entschieden würde, wird die Architektur der Elektronik dementsprechend aufgebaut. Zu Beginn sind die Anforderungen an die Elektronik zu stellen.

## Anforderungen an die Elektronik
Die Anforderungen an die Elektronik unterscheiden sich von den Anforderungen an das Gesamtsystem. So wurden folgenden Anforderungen definiert:
* Modularität einzelner Messplatinen für unterschiedlich große PWT
* Geringer Verdrahtungsaufwand
* Wenig bis keine Konfiguration erforderlich
* Programmierung und Kalibrierung der Messplatinen schnell möglich
* Speicherung ohne weitere Geräte
* Großer Bereich der Versorgungsspannung

Aus diesen Anforderungen geht die unten abgebildete Grundarchitektur des gesammten Messystems hervor.

![Architektur des Messsystems](/doc/img/arch_system.png)

Die Temperatursensoren befinden sich jeweils auf einer Messplatine, um den Abstand dieser der Situation anzupassen. Da die AMG8834 lediglich zwei verschiedene Adressen besitzen können, ist auf jeder ein Mikrocontroller erforderlich. Dieser Mikrocontroller ist für die Kommunikation des Master mit den einzelnen AMG8834 zuständig.

Datenspeicherung sowie Versorgung des Systems wird durch das Master-Gerät durchgeführt. Als Speichermedium wird eine SD-Karte verwendet. Als günstigen Bereich der Spannungsversorgung wird 5 V bis 30 V verwendet.

Die Verbindung aller Geräte, zur Kommunikation sowie Versorgung, wird durch Flachbandkabel realisiert. Diese Flachbandkabel werden mittels [2.54 mm Pfostensteckverbinder](https://www.samtec.com/products/tst-103-01-g-d) mit der Platine verbunden. Um Crosstalk zwischen den I²C Leitungen zu minimieren, werden jeweils zwei Masse bzw. Versorgungssignale übertragen. So sind Steckverbinder mit 6 Kontakten erforderlich.

Programmierung, Kalibrierung und Justierung der Messgeräte wird durch eine USB-Schittstelle durchgeführt.

## Architektur der Messplatinen
Kern der Messplatinen bildet ein Mikrocontroller. Auf Grund der aktuell beschränkten Verfügbarkeit von Halbleiterbauteilen, wird sich für den [Raspberry Pi RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) entschieden.
Da sich mehrere dieser Geräte an einem I²C-Bus befinden, ist eine Adresswahl erforderlich. Die Adresse der Individuellen Messplatinen kann durch einen DIP-Schalter in den Bereich von 0 und 15 gewählt werden.

![Architektur der Messplatine](/doc/img/arch_messplatine.png)

## Architektur des Master-Gerätes
Es wurde sich dazu entschieden zwei LED-Indikatoren auf dem Master-Gerät zu verbauen. Ein Indikator zeit die funktionierende Spannungsversorgung von 3.3 V an. Dieser ist grün und leuchtet durchgegend. Zwei weitere Indikatoren dienen der Anzeige des Betriebszustands und sind grün und rot. Es sind folgende Anzeigemodi dieser Status-Indikatoren möglich:

## Kommunikationsschnittstelle
[NXP Application Node inkl. Auslegung von langen I²C Bussen](https://www.nxp.com/docs/en/user-guide/UM10204.pdf)
