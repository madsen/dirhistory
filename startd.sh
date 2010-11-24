#! /bin/sh
#---------------------------------------------------------------------
# Start dirhistoryd in the background
#---------------------------------------------------------------------

mkfifo /dev/shm/cjm-dirs /dev/shm/cjm-dir-list
# If you want other users to be able to share your directory history:
chmod g+w /dev/shm/cjm-dirs

cd ~/apps/dirhistory
nohup ./dirhistoryd /dev/shm/cjm-dirs /dev/shm/cjm-dir-list &
