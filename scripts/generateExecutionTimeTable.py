import sys
from scipy import arange

''' found these values by filtering by max value on sdc and csv time sheets '''
precision = 0.01
max_value = 4.0
min_value = 0.0

def create_dictinary(min_value, max_value, precision):
    new_dict = dict()
    for i in arange(min_value, max_value, precision):
        i = round(i, 2)
        new_dict[i] = 0
    return new_dict

def read_summary(path):
    errors_dict = create_dictinary(min_value, max_value, precision)
    lines = [line.strip("\n") for line in open(path,"r")]
    lines = lines[1:] #removes the header
    for line in lines:
        split = line.split(";")
        time = round(float(split[3]), 2) #reducing precision for the execution time graphic
        errors_dict[time] +=1

    return errors_dict

def write_output(path, sdc_dict, crash_dict):
    with open(path,"w") as output:
        output.write("time\tsdc\tcrash\n")
        for key in sorted(sdc_dict.keys()):
            output.write("%1.2f\t%d\t%d\n" % (key, sdc_dict[key], crash_dict[key]))

def main():
    if len(sys.argv) < 3:
        print "feed me some parameters :("
        print "USAGE: python generateExecutionTimeTable.py <sdc_summary> <crash_summary> <output_name>"
        sys.exit(1)
    

    SDC_dict = read_summary(sys.argv[1])
    CRASH_dict = read_summary(sys.argv[2]) 
    write_output(sys.argv[3],SDC_dict, CRASH_dict)


if __name__ == '__main__':
    main()