# Sillabatore
Un sillabatore a riga di comando per Linux

![alt tag](https://github.com/GrazianoCapelli/Sillabatore/blob/master/doc/images/image_01.png)

## Descrizione
Questo è un semplice sillabatore didattico a riga di comando per Linux scritto in c++.<br>
Come regole per la sillabazione utilizza il file delle regole hyph_it_IT.dic di LibreOffice.<br>
Il programma riceve come parametro una parola e, applicando e visualizzando le regole di sillabazione, restituisce la parola divisa in sillabe.<br>

_Come tutti i sillabatori italiani basati su regole, anche questo ha il limite che non riconosce quali gruppi di vocali sono da dividere e quali invece no.<br>_

L'applicazione gira su Linux, 100% free e opensource.<br>
E' quindi liberamente scaricabile e utilizzabile da chiunque.<br>

## Utilizzo
1) Scaricare l'archivio dalla cartella /bin di questa repo ed estrarla nel proprio PC.<br>
2) Aprire un terminale, entrare nella cartella appena estratta e digitare:
```c++
./Sillabatore "parola_da_sillabare"
```

## Licenze
- Il software è pubblicato/rilasciato sotto i termini della licenza [GPL-3.0](https://github.com/GrazianoCapelli/Sillabatore/blob/master/LICENSE)
- File delle regole di LibreOffice: LibreOffice è Software Libero ed è soggetto ai termini della Mozilla Public License v2.0. È in parte basato sul codice originato da Apache OpenOffice (disponibile sotto la Apache License 2.0) ma include anche software che differisce da una versione all'altra, rilasciato sotto una gran varietà di altre licenze Open Source.
