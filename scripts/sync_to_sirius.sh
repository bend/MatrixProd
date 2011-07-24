#!/bin/bash
[[ $(basename $PWD) != Project1 ]] && echo "Go into the project's directory before running this command" && exit 1;
[[ $(basename $PWD) == Project1 ]] && rsync -av --exclude gen.txt --exclude .git --exclude gmp-4.3.2 ./ sirius:Project1/
