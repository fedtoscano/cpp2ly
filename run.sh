#!/bin/bash

if [ -z "$1" ]; then
    echo "Errore: Devi fornire il nome del file LilyPond."
    echo "Esempio: $0 spartito.ly"
    exit 1
fi

FILENAME=$(basename "$1" .ly)

g++ main.cpp && ./a.out && lilypond "$1" && xdg-open "${FILENAME}.pdf"
