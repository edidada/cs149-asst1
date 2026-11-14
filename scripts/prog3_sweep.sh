#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
# All variants are disposable copies. Student implementation stays unchanged.
for rows in 1 2 4 8 16 32 64 original; do
  variant=$(mktemp -d)
  cp -r common prog3_mandelbrot_ispc "$variant/"
  rm -rf "$variant/prog3_mandelbrot_ispc/objs"
  if [ "$rows" = original ]; then
    git show 05e602d3445123eab76ae1d0f81c370c34441e13:prog3_mandelbrot_ispc/mandelbrot.ispc > "$variant/prog3_mandelbrot_ispc/mandelbrot.ispc"
  else
    python3 - "$variant/prog3_mandelbrot_ispc/mandelbrot.ispc" "$rows" <<'PYCODE'
import sys
from pathlib import Path
p=Path(sys.argv[1]);s=p.read_text();rows=int(sys.argv[2])
# Exact divisors of the original 768-row benchmark, avoiding dropped rows.
s=s.replace('rowsPerTask = 1;',f'rowsPerTask = {rows};').replace('launch[height]','launch[height / rowsPerTask]')
p.write_text(s)
PYCODE
  fi
  make -C "$variant/prog3_mandelbrot_ispc" > "evidence/build-$rows.txt" 2>&1
  for view in 1 2; do
    (cd "$variant/prog3_mandelbrot_ispc"; ./mandelbrot_ispc --view "$view" --tasks) > "evidence/rows-$rows-view$view.txt"
    cmp "$variant/prog3_mandelbrot_ispc/mandelbrot-serial.ppm" "$variant/prog3_mandelbrot_ispc/mandelbrot-task-ispc.ppm"
  done
done
