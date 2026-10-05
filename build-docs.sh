#!/bin/bash

if [ -d docs ]; then
    rm -rf docs
fi

java  -Djava.awt.headless=true -jar $PLANTUML_JAR -v -o $PWD/docs  "./**.(c|cpp|dox|h|java)"

doxygen

pushd docs/latex
pdflatex refman.tex
popd
