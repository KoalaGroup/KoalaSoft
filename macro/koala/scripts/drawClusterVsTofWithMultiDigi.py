#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/checkClusterVsTofWithMultiDigi.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d", "--directory", help="directory where files are located",
                    default="./")
parser.add_argument("-s", "--suffix", help="suffix of the output",
                    default="_calib.root")
parser.add_argument("-b", "--branch", help="name of the branch containing the cluster",
                    default="KoaRecCluster")
parser.add_argument("--fwddir",help="directory where fwd timing files are located")
parser.add_argument("--geometry",help="geometry file used for position")
parser.add_argument("--elist_dir",help="directory where elist file is located")
parser.add_argument("--elist_suffix", help="suffix of the elist filename")
parser.add_argument("--elist_dirname",help="directory name of ROOT folder containing elist")
parser.add_argument("--elist_name",help="name of the elist")

args = parser.parse_args()

file_list = args.infile
in_dir = os.path.expanduser(args.directory)
fwd_dir = os.path.expanduser(args.fwddir)
geofile = os.path.expanduser(args.geometry)

# add rec each file in the list
list_files = batch.get_list(file_list, args.suffix, in_dir)
list_fwd = batch.get_list(file_list, "_FwdHit.root", fwd_dir)

if (args.elist_dir):
    elist_dir = os.path.expanduser(args.elist_dir)
    list_elist = batch.get_list(file_list, args.elist_suffix, elist_dir)
    for fin,ffwd,felist in zip(list_files, list_fwd, list_elist):
        command = [exec_bin, macro, fin, 'koalasim', args.branch,
                   ffwd, 'fwdhit_time',
                   '3000', '0', '6',
                   '1500', '450', '750',
                   geofile,
                   felist, args.elist_dirname, args.elist_name]
        print(command)
        process = subprocess.Popen(command)
        process.wait()
else:
    for fin,ffwd in zip(list_files, list_fwd):
        command = [exec_bin, macro, fin, 'koalasim', args.branch,
                   ffwd, 'fwdhit_time',
                   '3000', '0', '6',
                   '1500', '450', '750',
                   geofile]
        print(command)
        process = subprocess.Popen(command)
        process.wait()
