#!/usr/bin/python

import os


# arguments:
#   list_file: list of the raw binary files recorded by DAQ, with basename in first column and dirname in second column
#   suffix: new suffix to replace the original suffix of raw binary files
#   out_dir: new directory of the new list of files
# return:
#   raw_list: combination of the dirname and basename in the list_file
#   new_list: new list of files with new directory and suffix
def get_list(list_file, suffix, out_dir):
    # Get a new list of file names, replacing the old file extension with a new suffix (the new suffix should include the new extension), and prepending a output directory to the each filename.
    # The input list_file contains the old list to be modified, where the first column should be the basename, the second column be the dirname.
    new_list = []
    with open(list_file, "r") as fin:
        for line in fin:
            linesplit = line.split()
            infile = os.path.join(os.path.expanduser(out_dir), linesplit[0])
            infile = os.path.splitext(infile)
            infile = infile[0] + suffix
            new_list.append(infile)
    return new_list

def get_rawlist(list_file, suffix):
    new_list = []
    raw_list = []
    with open(list_file, "r") as fin:
        for line in fin:
            linesplit = line.split()
            infile = os.path.join(os.path.expanduser(linesplit[1]),
                                   linesplit[0])
            infile = os.path.splitext(infile)
            infile = infile[0] + suffix
            new_list.append(infile)

            rawfile = os.path.join(os.path.expanduser(linesplit[1]),
                                   linesplit[0])
            raw_list.append(rawfile)
    return new_list,raw_list
