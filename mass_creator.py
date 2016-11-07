import subprocess
import sys

count = int(sys.argv[1])
tokens = int(sys.argv[2])

for i in range(count):
    print 'Flow%d' % i,
    print subprocess.Popen(['./worker', 'Flow%d' % i, str(tokens)], stdout=None, stderr=None).pid
