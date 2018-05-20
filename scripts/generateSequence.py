import sys
import random
#sys.argv[1] output file name 
#sys.argv[2] amount of numbers
#sys.argv[3] precision (last line from the file)




def main():
    if len(sys.argv) < 4:
        printf("feed me some parameters :(\n")
        sys.exit(1)
    else:
        n = int(sys.argv[2])
        p = sys.argv[3]
    with open(sys.argv[1],'w') as outputFile:
        for i in range(0,n):
            number = random.randint(1,9000000) #* 1000000 #if int, replace this by: random.randint(1,9000000) 
            outputFile.write(str(number) + "\n")
        outputFile.write(p + "\n")




if __name__ == '__main__':
    main()
