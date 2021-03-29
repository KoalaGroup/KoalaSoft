#!/usr/bin/python

import argparse
import os
import subprocess
import batch

scpbin = 'scp'
remote_host = 'bt'

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the raw binary file list to be processed")
parser.add_argument("-d","--directory",help="directory where the decoded files will be located")

args = parser.parse_args()
file_list = args.infile
out_dir = './'
if(args.directory):
    out_dir = args.directory
out_dir = os.path.expanduser(out_dir)
#
list_decoded, list_raw = batch.get_rawlist(file_list,'_new.root')
for fin in list_raw:
    command = [scpbin, remote_host+':'+fin, out_dir]
    print(command)
    process = subprocess.Popen(command)
    # wait until process returns, so that mv in next step be meaningful
    process.wait()
