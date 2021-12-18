#!/bin/bash

set -euo pipefail

echo "salam $INPUT $OUTPUT"

bash "${SANDBOX}/run.sh" "$@"

