#!/usr/bin/fish
for in in cases/mhb/*in*.txt
    set ref (string replace in out $in)
    set out (basename $ref)
    echo "checking $in"
    ./npuzzle -man -i $in -o $out
    # diff --strip-trailing-cr -cb $ref $out
    kdiff3 $ref $out & disown
end

