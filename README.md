# Wlcomb - Wordlist Combine #

## What is wlcomb? ##
Wlcomb generates simple wordlists to be used in dictionary attacks. Wlcomb
combines phrases provided by the user to create a complete list of possible
passwords.

## Compiling ##
Execute make. This compiles the C++ password combiner.

## Usage ##
First compile the C++ password combiner, then run the wlc.py program:

        python wlc.py
        
Run this command for help:

        python wlc.py --help

Before generating any wordlists you must generate the combination dat file:

        python wlc.py -g -l 3 -o combos.dat
        
You may then create your wordlist. For example:

        python wlc.py -c -i combos.dat -p phrases.txt -o wordlist.txt
