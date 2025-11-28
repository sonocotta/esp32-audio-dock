#!/bin/bash

find . -type f \( -iname '[A-Z]*.pdf' -o -iname '[A-Z]*.zip' -o -iname '[A-Z]*.csv' -o -iname '[A-Z]*.step' \) -print0 |
while IFS= read -r -d '' f; do
    dir=$(dirname "$f")
    base=$(basename "$f")
    new=$(echo "$base" \
        | sed -E 's/^([A-Za-z]+)_(.*)_([0-9]{4}-[0-9]{2}-[0-9]{2})(\..*)$/\2-\1\4/' \
        | tr '_' '-' \
        | tr '[:upper:]' '[:lower:]')
    if [ "$base" != "$new" ]; then
        mv "$f" "$dir/$new"
    fi
done