check_flag() {
    local flag="$1"
    shift 1
    local files=("$@")


    OUTPUT1=$(mktemp)
    OUTPUT2=$(mktemp)

    ./s21_cat "$flag" "${files[@]}" > "$OUTPUT1"
    cat "$flag" "${files[@]}" > "$OUTPUT2"

    if diff "$OUTPUT1" "$OUTPUT2" > /dev/null; then
        echo "
        .............................
        .                           .
        >>>   Флаг $flag работает   <<<
        .                           .
        ............................."
    else 
        echo "
        ........................................
        .                                      .
        >>>   Ошибка. Флаг $flag не работает   <<<
        .                                      .
        ........................................
        "
    # vimdiff "$OUTPUT1" "$OUTPUT2"
    #    diff "$OUTPUT1" "$OUTPUT2"
    fi

    rm "$OUTPUT1" "$OUTPUT2"
}


check_flag "-b" "test2.txt" 
check_flag "-n" "test2.txt" 
check_flag "-e" "test_cat.txt" 
check_flag "-s" "test2.txt" 
check_flag "-t" "test_cat.txt" 
check_flag "-v" "test_cat.txt" 
check_flag "-bn" "test2.txt" 
check_flag "-es" "test3.txt"
check_flag "-te" "test3.txt" 