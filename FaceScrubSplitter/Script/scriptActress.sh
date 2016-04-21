#!/bin/bash

IFS=$'\r\n' GLOBIGNORE='*' command eval 'LINES=($(cat facescrub_actresses.txt))'
echo "${LINES[0]}"


for L in "${LINES[@]}"
do
	IFS='	' read -a words <<< "${L}"
	
	nm="${words[0]}"
	sp="/"
	id="${words[2]}"
	ul="${words[3]}"
	ex=".jpg"

	mkdir $nm
	sv=$nm$sp$id$ex

	wget -nc $ul --output-document=$sv --tries=1
done

