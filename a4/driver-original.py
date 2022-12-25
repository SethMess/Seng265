#!/usr/bin/env python3

import sys
import concord4

def main():
    saved_stdout, saved_stderr = sys.stdout, sys.stderr
    #sys.stdout, sys.stderr = None, None

    cc = concord4.concord()
    results = cc.full_concordance()

    sys.stdout, sys.stderr = saved_stdout, saved_stderr

    if results != []:
        print("\n".join(results))

if __name__ == "__main__":
    main()
