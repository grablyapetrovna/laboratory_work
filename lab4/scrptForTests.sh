#!/bin/bash

# Создаём корневую директорию ftp
mkdir -p ftp/{ib,bcs,otkritie,docs}

# Создаём файлы в директории ib
touch ftp/ib/balance_00001234_20231001.txt
touch ftp/ib/balance_00001234_20231002.txt
touch ftp/ib/balance_00001234_20231001.old.txt
touch ftp/ib/balance_00001346_20231001.txt

# Создаём файлы в директории bcs
touch ftp/bcs/balance_12341234_20231001.txt
touch ftp/bcs/balance_12341234_20231005.txt

# Создаём файлы в директории otkritie
touch ftp/otkritie/balance_98765432_20231001.txt

# Создаём файлы в директории docs
touch ftp/docs/readme.txt
touch ftp/docs/report.doc
