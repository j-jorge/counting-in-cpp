#!/bin/bash

set -e

runs=10
step=50

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd)"

usage()
{
    echo "Usage:"
    echo "$0 --runs <R> --step <S> [ -h ]"
    echo
    echo "Where:"
    echo -e "\t--runs"
    echo -e "\t\tHow many repeated compilations to do. Default is ${runs}."
    echo -e "\t--step"
    echo -e "\t\tHow many compilations to add for each repeated compilations."
    echo -e "\t\tDefault is ${step}."
}

repeat_compilation()
{
    for ((i=0; i != $1; ++i))
    do
        g++ --std=c++"$2" -c "$script_dir/count-$2.cpp" -o /dev/null
    done
}

compile_with_standard()
{
    local count=0
    LANG=C

    for ((i=0; i < runs; ++i))
    do
        count=$((count + step))
        TIMEFORMAT="$count, %U"
        (time repeat_compilation "$count" "$1") 2>&1
    done
}

while [ $# -ne 0 ]
do
    arg="$1"
    shift

    case "$arg" in
        --help|-h)
            usage
            exit 0
            ;;
        --runs)
            runs="$1"
            shift
            ;;
        --runs=*)
            runs="${arg#--runs=}"
            ;;
        --step)
            step="$1"
            shift
            ;;
        --step=*)
            step="${arg#--step=}"
            ;;
    esac
done

original_directory="$PWD"
working_directory="$(mktemp -d)"
trap 'rm -fr "'"$working_directory"'"' EXIT

cd "$working_directory"

output_directory="$original_directory/figures/constexpr"
mkdir -p "$output_directory"

compile_with_standard 98 > "$output_directory/98.data"
compile_with_standard 11 > "$output_directory/11.data"

#gnuplot -e "tex_output_filename='$output_directory/constexpr-benchmark.tex'" \
#        "$script_dir"/plot.gp

#mv "$output_directory/"* "$original_directory/$output_directory/"
