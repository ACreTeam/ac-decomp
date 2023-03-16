#! /usr/bin/env python3

# Written by Ethan Roseman (ethteck)
# MIT License
# Copyright 2021

# Modified by EpochFlame

import argparse

# Byte sequences
BLR_BYTE_SEQ = b"\x4E\x80\x00\x20"
MTLR_BYTE_SEQ = b"\x7C\x08\x03\xA6"

# Example invocation: ./frank.py vanilla.o profile.o output.o
parser = argparse.ArgumentParser()
parser.add_argument("vanilla", help="Path to the vanilla object", type=argparse.FileType('rb'))
parser.add_argument("target", help="Path to the target object (to write)")

args = parser.parse_args()

# Read contents into bytearrays and close files
vanilla_bytes = args.vanilla.read()
args.vanilla.close()

# Reunify mtlr/blr instructions, shifting intermediary instructions up
idx = 0

while idx < len(vanilla_bytes):
    # Find mtlr position
    mtlr_found_pos = vanilla_bytes.find(MTLR_BYTE_SEQ, idx)
    if mtlr_found_pos == -1:
        break # break while loop when no targets remain
    if mtlr_found_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue
    # Find paired blr position
    blr_found_pos = vanilla_bytes.find(BLR_BYTE_SEQ, mtlr_found_pos)
    if blr_found_pos == -1:
        break # break while loop when no targets remain
    if blr_found_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue
    if mtlr_found_pos + 4 == blr_found_pos:
        idx += 4
        continue # continue if mtlr is followed directly by blr
    
    vanilla_bytes = vanilla_bytes[:mtlr_found_pos] + vanilla_bytes[mtlr_found_pos+4:blr_found_pos] + vanilla_bytes[mtlr_found_pos:mtlr_found_pos+4] + vanilla_bytes[blr_found_pos:]
    idx = mtlr_found_pos + len(MTLR_BYTE_SEQ)

with open(args.target, "wb") as f:
    f.write(vanilla_bytes)
