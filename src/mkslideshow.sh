#!/bin/sh

[ -z "$(whereis ffmpeg | awk '{print $2}')" ] && echo "Please install ffmpeg" && exit 1
[ -z "$(whereis ffprobe | awk '{print $2}')" ] && echo "Please install ffprobe" && exit 1
[ $# -ne 3 ] && echo "Usage: $0 <directory> <music> <output>" && exit 1

num_pepes=$(ls "$1"/*.png | wc -l)
length=$(ffprobe -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 "$2" 2> /dev/null)
framerate=$(echo "scale=6; ${num_pepes}.0 / $length" | bc)

echo $num_pepes
echo $length

cat "$1"/*.png | ffmpeg -y -framerate "$framerate" -f image2pipe -i - -i "$2" -acodec copy "$3"

