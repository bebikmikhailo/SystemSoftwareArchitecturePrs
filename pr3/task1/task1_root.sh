ulimit -n
ulimit -aH | grep "open files"
ulimit -Hn 3000
ulimit -aH | grep "open files"
ulimit -Hn 3001
ulimit -Hn 2000
ulimit -aH | grep "open files"
ulimit -Hn 3000