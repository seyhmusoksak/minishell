#!/bin/bash
# Renk kodları
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[4;36m'
RESET='\033[0m' # Varsayılan rengi sıfırlar
progress_bar() {
    total=99
    completed=0
    while [ $completed -le $total ]; do
        completed=$((completed + 1))
        bar=$(printf "%0.s#" $(seq 1 $((completed / 2))))
        # İlerleme çubuğunu ve yüzdesini renklendir
        printf "\r${RED}[${CYAN}%-50s${RED}] ${RED}%d%%${RESET}" "$bar" $completed
        sleep 0.1
    done
    printf "\n"
}
progress_bar
