# Thema02: Adaptives Quiztool
## Beschreibung
In diesem Projekt haben wir ein konsolenbasiertes Quiztool implementiert. Über Ein- und Ausgabe wird der Benutzer durch das Quiz geführt. Dabei werden dem Benutzer Fragen, mit 4 Antwortmöglichkeiten, gestellt. Am Ende erhält man eine Punktzahl je nachdem wie viele Versuche man für die jeweiligen Fragen benötigt hat.
## Benutzung
Das Programm kann genutzt werden um neues Wissen zu erlangen und zu festigen. Um dieses Quiztool zu benutzen erstellen sie sich einen neuen Ordner und führen darin folgenden Befehl ein:

     git clone https://github.com/schibe01/ensw_project_02
Dann finden sie 5 Dateien, aus denen dieses Tool besteht:
- quiz.c: Funktionaler Inhalt
- quiz_main.c: Menüführung
- quiz.h: Bibliothek (Verknüpfung aller Dateien)
- questions.txt: Fragenpool
- highscore.txt: Liste der besten Dürchläufe

Um das Programm zu starten müssen quiz_main.c und quiz.c, wie folgt, zusammen compiliert werden:

     cl quiz_main.c quiz.c

Zum Ausführen des Programms muss nun quiz_main.exe ausgeführt werden:

    quiz_main.exe

Die Menüführung gibt dem Benutzer immer durchnummerierte Auswahlmöglichkeiten vor. Um eine davon auszuwählen muss die Entsprechende Zahl in die Konsole eingegeben werden.

Der zugrundeliegende Fragenpool kann geändert werden um eigene Fragen dem Quiz hinzuzufügen. Hierzu muss die Datei "questions.txt" verändert werden. Entweder fügt man Fragen hinten an oder man ersetzt die komplette Liste. Dabei muss folgendes Format unbedingt eingehalten werden:

    Frage

    Antwortmöglichkeit 1
    Antwortmöglichkeit 2
    Antwortmöglichkeit 3
    Antwortmöglichkeit 4

    richtige Antwortmöglichkeit (z.B. 3)


zwischen 2 Fragen müssen sich 2 Leerzeilen befinden.
