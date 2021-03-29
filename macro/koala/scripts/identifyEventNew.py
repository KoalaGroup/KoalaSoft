#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/scripts/identifyEventNew.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-s","--suffix",help="suffix of the input file")
parser.add_argument("-g","--geometry",help="geometry file")

args = parser.parse_args()
file_list = args.infile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

suffix = '_calib.root'
if(args.suffix):
    suffix = args.suffix

fgeoFile = 'geo_standard.root'
if(args.geometry):
    fgeoFile = args.geometry
fgeoFile = os.path.expanduser(fgeoFile)

#
list_cluster = batch.get_list(file_list, suffix, in_dir)
list_elist = batch.get_list(file_list, '_EntryList.root', in_dir)

for fcluster, felist in zip(list_cluster, list_elist):
    command = [exec_bin, macro, fcluster, '2.6',
               felist, 'fwd', 'elist_fwdhit',
               '33', '5', '0.3', '0.9', '3', '2', fgeoFile, 'true']
    print(command)
    process = subprocess.Popen(command)
    process.wait()
