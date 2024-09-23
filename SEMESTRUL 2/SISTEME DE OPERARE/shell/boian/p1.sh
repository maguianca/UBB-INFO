#!/bin/bash

#who | cut -d' ' -f1 | sort -u | while read user; do echo -n "$user "; ps -u $user | wc -l; done
who | cut -d' ' -f1 | sort -u | while read user; do echo -n "$(finger $user | grep -m 1 Name | cut -d ':' -f 3), $user "; ps -u $user | wc -l; done
