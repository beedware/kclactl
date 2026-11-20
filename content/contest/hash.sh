# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
src=$(g++ -E -dD -P -fpreprocessed -x c++ -) || exit 1
printf '%s' "$src" | tr -d '[:space:]' | md5sum | cut -c-6
