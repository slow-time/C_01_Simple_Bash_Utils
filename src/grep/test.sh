#!/bin/bash

check_flag() {
    local flag="$1"
    local pattern="$2"
    shift 2
    local files=("$@")


    OUTPUT1=$(mktemp)
    OUTPUT2=$(mktemp)

    ./s21_grep "$flag" "$pattern" "${files[@]}" > "$OUTPUT1"
    grep "$flag" "$pattern" "${files[@]}" > "$OUTPUT2"

    if diff "$OUTPUT1" "$OUTPUT2" > /dev/null ; then
        echo "
        ...........................
        .                         .
        .>>> Флаг $flag работает <<<.
        .                         .
        ..........................."

    else 
        echo "
        ......................................
        .                                    .
        .>>> Ошибка. Флаг $flag не работает <<<.
        .                                    .
        ......................................"
    fi

    rm "$OUTPUT1" "$OUTPUT2"
    echo "-------------------"
}


check_flag "-e" "cat" "test1.txt" "test2.txt"
check_flag "-c" "file" "test1.txt" "test2.txt" "test3.txt"
check_flag "-i" "FiLE" "test2.txt" "test3.txt"
check_flag "-l" "Number" "test2.txt" "test1.txt"
check_flag "-n" "cat" "test2.txt" "test3.txt" "test1.txt"
check_flag "-v" "cat" "test2.txt" "test3.txt"

check_flag "-h" "Number" "test1.txt" "test2.txt"
check_flag "-o" "Number" "test1.txt" "test2.txt"
check_flag "-s" "Number" "fdsfs"

check_flag "-ce" "Number" "test1.txt" "test2.txt"
check_flag "-ci" "Number" "test1.txt" "test2.txt"
check_flag "-cl" "Number" "test1.txt" "test2.txt"
check_flag "-cn" "Number" "test1.txt" "test2.txt"
check_flag "-cv" "Number" "test1.txt" "test2.txt"
check_flag "-ch" "Number" "test1.txt" "test2.txt"
check_flag "-co" "Number" "test1.txt" "test2.txt"
check_flag "-ie" "NUMber" "test1.txt" "test2.txt"
check_flag "-le" "Number" "test1.txt" "test2.txt"
check_flag "-ne" "Number" "test1.txt" "test2.txt"
check_flag "-ve" "Number" "test1.txt" "test2.txt"
check_flag "-li" "NUMber" "test1.txt" "test2.txt"
check_flag "-ni" "NUMber" "test1.txt" "test2.txt"
check_flag "-vi" "NUMber" "test1.txt" "test2.txt"
check_flag "-ln" "Number" "test1.txt" "test2.txt"
check_flag "-lv" "Number" "test1.txt" "test2.txt"
check_flag "-oe" "Number" "test1.txt" "test2.txt"
check_flag "-oi" "NUMber" "test1.txt" "test2.txt"
check_flag "-oc" "Number" "test1.txt" "test2.txt"
check_flag "-ol" "Number" "test1.txt" "test2.txt"
check_flag "-on" "Number" "test1.txt" "test2.txt"
check_flag "-ov" "Number" "test1.txt" "test2.txt"
check_flag "-oh" "Number" "test1.txt" "test2.txt"

check_flag "-he" "Number" "test1.txt" "test2.txt"
check_flag "-hi" "NUMber" "test1.txt" "test2.txt"
check_flag "-hl" "Number" "test1.txt" "test2.txt"
check_flag "-hn" "Number" "test1.txt" "test2.txt"
check_flag "-hv" "Number" "test1.txt" "test2.txt"
check_flag "-ho" "Number" "test1.txt" "test2.txt"


