#! /bin/sh
#---------------------------------------------------------------------
# $Id
#---------------------------------------------------------------------

mkfifo /dev/shm/cjm-dirs /dev/shm/cjm-dir-list
chmod g+w /dev/shm/cjm-dirs

cd ~/apps/dirhistory
nohup ./dirhistoryd /dev/shm/cjm-dirs /dev/shm/cjm-dir-list &
