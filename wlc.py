#!/usr/bin/python3
'''
wlc.py
This is the main wlc program. It is used to run wlc_c to combine phrases.
'''
import argparse
import subprocess
import os #Used to see if wlc program exists
from combo_gen import combo_gen

wlc_c = "wlc_c"

def main():
    parser = argparse.ArgumentParser(description="WLC. Make a wordlist for cracking by \
        combining phrases.")
    parser.add_argument("--combine", "-c", action="store_true", help="Run the combine program.")
    parser.add_argument("--generate", "-g", action="store_true", help="Generate the combo dat file.")

    parser.add_argument("--combo_in", "-i", help="[Combine]: Alpha-Numeric combo data file input.")
    parser.add_argument("--phrase", "-p", help="[Combine]: Phrase list file.")
    parser.add_argument("--output", "-o", help="Output file.")
    parser.add_argument("--suffix", "-s", help="[Combine]: Comma seperated list of suffixes to add.")
    parser.add_argument("--combo_len", "-l", type=int, help="[Generate]: Max number of phrases to string together.")

    args = parser.parse_args()
    if not (args.combine or args.generate):
        print("[-] Error! Not enough arguments.")
        return

    if args.combine and args.generate:
        print("[-] Error! You can't run both the generate and the combine programs! Run one or the other.")
        return

    if args.combine:
        if not args.combo_in or not args.phrase:
            print("[-] Error! You did not provide enough arguments to run the combine program!")
            return
    if args.combine and not os.path.isfile(wlc_c):
        print("[-] Error! Could not find wlc_c executable!")
        return

    if args.generate:
        if not args.output or not args.combo_len:
            print("[-] Error! You did not provide enough arguments to the generate program!")
            return

    if args.combine:
        arg_list = [args.combo_in, args.phrase, args.output]
        if args.suffix:
            arg_list.append(args.suffix) #This is not a required arg

        run_list = ["./{}".format(wlc_c)]
        for a in arg_list:
            run_list.append(a)
        subprocess.run(run_list)

    if args.generate:
        combo_gen(args.output, args.combo_len)


if __name__ == "__main__":
    main()
