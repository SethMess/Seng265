#!/usr/bin/env python3

# For a bit more about the argparse module, here is a decent
# tutorial: `http://bit.ly/3ER1yHb`
#
# (The link above leads to the `towardsdatascience.com` website.)
#

import sys
import argparse
import concord4

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', type=str, required=True)
    parser.add_argument('--output', type=str, required=True)
    args = parser.parse_args()

    saved_stdout, saved_stderr = sys.stdout, sys.stderr
    sys.stdout, sys.stderr = None, None

    cc = concord4.concord(args.input, args.output)

    sys.stdout, sys.stderr = saved_stdout, saved_stderr

if __name__ == "__main__":
    main()
