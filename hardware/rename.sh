#!/bin/bash

find . -type f -regex '.*/[A-Z][^/]*\.\(pdf\|zip\)' -print0 |
while IFS= read -r -d '' f; do
    dir=$(dirname "$f")
    base=$(basename "$f")
    new=$(echo "$base" \
        | sed -E 's/^([A-Za-z]+)_(.*)_([0-9]{4}-[0-9]{2}-[0-9]{2})(\..*)$/\2-\1\4/' \
        | tr '_' '-' \
        | tr 'A-Z' 'a-z')
    if [ "$base" != "$new" ]; then
        mv "$f" "$dir/$new"
    fi
done