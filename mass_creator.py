import subprocess
import sys

count = int(sys.argv[1])

for i in range(count):
    print 'Flow%d' % i,
    print subprocess.Popen(['./worker', 'Flow%d' % i]).pid
