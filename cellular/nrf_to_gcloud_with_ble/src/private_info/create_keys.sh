#!/bin/bash

read -p "Do you want to remove old secrets? " -n 1 -r
echo

if [[ $REPLY =~ ^[Yy]$ ]]
then
        read -p "Are you sure? " -n 1 -r
        echo

        echo "Removing old secrets\n"

        if [[ $REPLY =~ ^[Yy]$ ]]
        then
                dir=$(pwd)
                find $dir -type f -name "*.pem" -exec rm -rf {} \;
                echo "Removing key.c\n"
                rm -f key.c
        fi
fi

read -p 'Enter Device Name: ' devicename
echo

read -p "Are you sure? " -n 1 -r
echo

if [[ $REPLY =~ ^[Yy]$ ]]
then
        echo "Creating secrets"

        python3 create_keys.py -d $devicename -e

        echo Created $devicename certificates
        exit 0
fi