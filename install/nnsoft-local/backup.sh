#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DATABASE=shadow
FILEPATH=$DIR/$DATABASE-`date +%Y-%m-%d_%H-%M-%S`.sql

mysqldump -u root -p $DATABASE --routines > $FILEPATH
