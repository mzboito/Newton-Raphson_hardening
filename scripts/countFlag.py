import sys

count = 0
neg_count = 0
with open(sys.argv[1],"r") as logs:
    for line in logs:
        if "[NEWTON] SDC DETECTED\n" == line:
            count +=1
        elif "[NEWTON] PASSED\n" == line:
            neg_count += 1

print count, neg_count