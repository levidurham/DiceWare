# DiceWare

A simple program to generate diceware.com style pass phrases using the dictionary file from the EFF.

The dictionary file included is the one available from the EFF with only the second column. I.e. filtered through `awk '{print $2}' <infile >outfile`.

## Refrences
* http://www.diceware.com
* https://www.eff.org/deeplinks/2016/07/new-wordlists-random-passphrases
