#!/bin/bash
#if file $1 |grep -qi "text"; then 
#	echo " este fisier"
#fi
 #if [[ -z "$1" ]];then
	#if [ -z "$1" ];then
	#if [ ! -n "$1" ];then
	#if [[ "$1" == "" ]];then
	#if [[ ${#1} -eq 0 ]];then
	#if [[ !${#1} -ne 0 ]];then
	if [[ ! $1 =~ .+ ]];then
	echo "vid"
fi
