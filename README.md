# smith-waterman

Labor Medizinische Informatik

Studiengang Medizintechnik

Hochschule Pforzheim

## Zusammenhang von Einüge- und Lösch-Operation beim Bewegen durch die Matrix

Beim Alignment der folgenden Sequenzen:

```text
s1: ABD
s2: ABCD
```

kann das Ziel erreicht werden, indem in s2 ein Zeichen (C) gelöscht wird. Das Ergebnis sieht dann so aus:

```text
AB-D
|| |
ABCD
```

In der Matrix steht s1 für die Zeilen und s2 für die Spalten. Zusammen mit dem gewählten Pfad sieht das dann so aus:

```text
  ABCD
A D
B  DL
D    D
```

Immer wenn man sich in der Matrix nach links bewegt, gibt es einen Stillstand in s1 und dabei wird in s2 ein Zeichen (hier C) übersprungen, was einer Löschung in s2 entspricht.

Der Umgekehrte Fall tritt bei folgenden Squenzen ein:

```text
s1: ABCD
s2: ABD
```

Hier muss ein Zeichen (C) eingefügt werden um zu einem möglichen Ziel zu gelangen:

```text
ABCD
AB-D
```

Die Matrix mit Pfad kann dann so aussehen:

```text
  ABD
A D
B  D
C  U
D   D
```

Durch die Bewegung nach oben, gibt es in s2 einen Stillstand, während man sich in s1 weiter bewegt. Dies entspricht dem Einfügen (hier C) eines Zeichens...

Daher gilt:

* **horizontale** Bewegung = **Löschung**,
* **vertikale** Bewegung = **Einfügung**