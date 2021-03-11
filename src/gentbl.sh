#!/bin/sh

find_longest() {
   num=0
   for w in $1; do
      tmp_len=$(echo "$w" | wc -m)
      [ $tmp_len -gt $num ] && num=$tmp_len
   done
   echo "$num"
}

# line
# num
# ch
print_line() {
   len=$(($2 - $(echo "$1" | wc -m) + 1))
   printf " %s%*s$3" "$1" "$len" ""
}

# s
# len
print_repeat() {
   i0=0
   while [ "$i0" -lt "$2" ]; do
      printf "%s" "$1"
      i0=$((i0 + 1))
   done
}

[ $# -ne 1 ] && echo "Usage: $0 <file>" && exit 1
if [ ! -f $1 ] && [ $1 != "-" ]; then echo "$0: $1: file not found" && exit 1; fi
file="$1"

cols=$(head -n1 "$file" | wc -w)
rows=$(awk '{print $1}' "$file" | wc -l)

i=1
lens=""
total_len=0
while [ $i -le $cols ]; do
   len=$(find_longest "$(awk "{print \$$i}" "$file")")
   lens="$lens $len"
   total_len=$((total_len + len))
   i=$((i + 1))
done

printf "╔"
j="$(echo "$lens" | awk '{print $1}')"
print_repeat "═" $((j + 1))
i=1
while [ $i -lt "$cols" ]; do
   printf "╤"
   j="$(echo "$lens" | awk "{print \$$((i + 1))}")"
   print_repeat "═" $((j + 1))
   i=$((i + 1))
done
printf "╗\n"

i=1
printf "║"
while [ $i -lt "$cols" ]; do
   print_line $(head -n1 "$file" | awk "{print \$$i}") $(echo "$lens" | awk "{print \$$i}") "│"
   i=$((i + 1))
done
print_line $(head -n1 "$file" | awk "{print \$$i}") $(echo "$lens" | awk "{print \$$i}") "║"
echo

printf "╟"
j="$(echo "$lens" | awk '{print $1}')"
print_repeat "─" $((j + 1))
i=1
while [ $i -lt "$cols" ]; do
   printf "┼"
   j="$(echo "$lens" | awk "{print \$$((i + 1))}")"
   print_repeat "─" $((j + 1))
   i=$((i + 1))
done
printf "╢\n"

i=2
while [ $i -le "$rows" ]; do
   printf "║"
   line=$(head -n$i "$file" | tail -n1)
   j=1
   while [ $j -lt "$cols" ]; do
      print_line "$(echo "$line" | awk "{print \$$j}")" $(echo "$lens" | awk "{print \$$j}") "│"
      j=$((j + 1))
   done
   print_line "$(echo "$line" | awk "{print \$$j}")" "$(echo "$lens" | awk "{print \$$j}")" "║"
   i=$((i + 1))
   echo
done

printf "╚"
j="$(echo "$lens" | awk '{print $1}')"
print_repeat "═" $((j + 1))
i=1
while [ $i -lt "$cols" ]; do
   printf "╧"
   j="$(echo "$lens" | awk "{print \$$((i + 1))}")"
   print_repeat "═" $((j + 1))
   i=$((i + 1))
done
printf "╝\n"



