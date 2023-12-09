"""
Progress message generation
"""

from argparse import ArgumentParser
import os.path
import pickle
import json
from typing import Dict, List, Tuple

from prettytable import PrettyTable

import common as c

def load_progress_info(ctx: c.SourceContext, asm_list: str
                      ) -> Tuple[Dict[str, int], Dict[str, int]]:
    assert os.path.exists(ctx.labels), "Error: analysis has not ran!"

    # Get data
    raw = c.get_cmd_stdout(f"{c.PROGRESS} {ctx.binary} {ctx.labels} {ctx.slices}")
    dat = json.loads(raw)
    assert dat.get("version") == 2, "Outdated progress json version, try a clean & rebuild"
    decomp_sizes = dat["decomp_slices_sizes"]
    total_sizes = dat["total_sizes"]
    symbol_sizes = dat["symbol_sizes"]

    # Subtract undecompiled functions in decompiled slices
    # TODO: this assumes none of .init is decompiled
    with open(asm_list, 'rb') as f:
        funcs = pickle.load(f)
    for func in funcs:
        decomp_sizes[".text"] -= symbol_sizes[str(func)]
    
    return decomp_sizes, total_sizes

def print_binary_progress(sections: List[str], decomp_sizes: Dict[str, int],
                          total_sizes: Dict[str, int], binary: str, show_total: bool):
    table = PrettyTable(["Section", "Decompiled Bytes", "Total Bytes", "Percentage"])
    bin_decomp_size = 0
    bin_total_size = 0
    pct = lambda d, t: f"{(d/t)*100:.4f}"
    for sec in sections:
        decomp_size = decomp_sizes[sec]
        total_size = total_sizes[sec]
        bin_decomp_size += decomp_size
        bin_total_size += total_size
        table.add_row([
            sec, 
            hex(decomp_size),
            hex(total_size),
            pct(decomp_size, total_size)
        ])
    if show_total:
        table.add_row([
            "Total",
            hex(bin_decomp_size),
            hex(bin_total_size),
            pct(bin_decomp_size, bin_total_size)
        ])
    print(f"{binary} progress:")
    print(table)

if __name__=="__main__":
    parser = ArgumentParser()
    parser.add_argument("-f", "--full", action="store_true", help="Print progress of all sections")
    args = parser.parse_args()
    decomp_sizes, total_sizes = load_progress_info(c.DOL_CTX, c.DOL_ASM_LIST)
    rel_decomp_sizes, rel_total_sizes = load_progress_info(c.REL_CTX, c.REL_ASM_LIST)
    if args.full:
        print("Warning: progress for sections other than .text isn't fully accurate")
        dol_secs = [
            ".init",
            "extab_",
            "extabindex_",
            ".text",
            ".ctors",
            ".dtors",
            ".rodata",
            ".data",
            ".bss",
            ".sdata",
            ".sbss",
            ".sdata2",
        ]
        rel_secs = [
            ".text",
            ".rodata",
            ".data",
            ".bss",
        ]
    else:
        dol_secs = rel_secs = [".text"]
    print_binary_progress(dol_secs, decomp_sizes, total_sizes, "static.dol", args.full)
    print_binary_progress(rel_secs, rel_decomp_sizes, rel_total_sizes, "foresta.rel", args.full)