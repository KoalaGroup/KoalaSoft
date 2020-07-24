#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/checkClusterVsTof.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-s","--suffix",help="suffix of the output")
parser.add_argument("-g","--geometry",help="geometry file used for position")

args = parser.parse_args()
file_list = args.infile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

suffix = '_calib.root'
if(args.suffix):
    suffix = args.suffix

fgeo = 'geo_standard.root'
if(args.geometry):
    fgeo = args.geometry

# add rec each file in the list
list_files = batch.get_list(file_list, suffix, in_dir)
for fin in list_files:
    ffwdhit = fin.replace('.root', '_FwdHit.root')
    command = [exec_bin, macro, fin, 'koalasim', 'KoaRecCluster',
               ffwdhit, 'fwdhit_time',
               '500', '0', '10',
               '1500', '450', '750',
               fgeo]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
