#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")"
mkdir -p out

for f in layout*.json; do
  name="${f%.json}"
  node render-kle.js "$f" "out/$name.svg"
done
