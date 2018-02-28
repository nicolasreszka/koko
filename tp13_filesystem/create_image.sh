#!/bin/bash

rm /tmp/image.ext3
rm 2m-img-parms.txt

# créer le fichier image.ext3 dont la taill est 4 Mo en utilisant /dev/zero comme source
dd if=/dev/zero of=/tmp/image.ext3 bs=512 count=8000

# formater l'image
mke2fs -jFv -E root_owner -t ext3 /tmp/image.ext3

# sauvegarder les parmètres du système de fichier dans un fichier
dumpe2fs /tmp/image.ext3 > 2m-img-parms.txt

# les valeurs :
# 	-First Block
#	-Blocks per group
#	-Inodes per group
#	-Inode blocks per group
# viennent du superblock  

# monter l'image
mount /tmp/image.ext3 
