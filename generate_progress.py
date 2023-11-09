from argparse import ArgumentParser
import os.path
import pickle
import json
from typing import Dict, Tuple

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

def generate_frogress_json(dol_size, dol_total, rel_size, rel_total):
    return json.dumps({
        "rel": {
            "code": rel_size,
            "code/total": rel_total
        },
        "dol": {
            "code": dol_size,
            "code/total": dol_total
        }
    })

if __name__=="__main__":
    decomp_sizes, total_sizes = load_progress_info(c.DOL_CTX, c.DOL_ASM_LIST)
    rel_decomp_sizes, rel_total_sizes = load_progress_info(c.REL_CTX, c.REL_ASM_LIST)
    json_str = generate_frogress_json(decomp_sizes[".text"], total_sizes[".text"], rel_decomp_sizes[".text"], rel_total_sizes[".text"])
    with open("out/progress.json", "w") as f:
        f.write(json_str)
