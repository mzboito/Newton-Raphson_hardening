#!/usr/bin/env python

import sys
import os
import csv
import re
import collections
import parseUtils
import glob


def processErrors(errList):
        errLimitList = [0.1,0.2,0.3,0.4,0.5,1,2,3,4,5,8,10,12,15]
        csvHeader = list()
        csvHeader.append("numberIterationErrors")
        csvHeader.append("maxRelativeError")
        csvHeader.append("minRelativeError")
        csvHeader.append("averageRelativeError")
        for errLimit in errLimitList:
            csvHeader.append("numberErrorsLessThan"+str(errLimit))


        csvOutDict = dict()
        csvOutDict["numberIterationErrors"]=len(errList)
        for errLimit in errLimitList:
            (maxRelErr, minRelErr, avgRelErr, relErrLowerLimit, errListFiltered) = parseUtils.relativeErrorParser(errList, errLimit)
            csvOutDict["maxRelativeError"] = maxRelErr
            csvOutDict["minRelativeError"] = minRelErr
            csvOutDict["averageRelativeError"] = avgRelErr
            csvOutDict["numberErrorsLessThan"+str(errLimit)] = relErrLowerLimit



	# Write info to csv file
        csvFullPath = "out.csv"

        if not os.path.isfile(csvFullPath):
	    csvWFP = open(csvFullPath, "a")
	    writer = csv.writer(csvWFP, delimiter=';')
            writer.writerow(csvHeader)
        else:
	    csvWFP = open(csvFullPath, "a")
	    writer = csv.writer(csvWFP, delimiter=';')
        row = list()
        for item in csvHeader:
            if item in csvOutDict:
                row.append(csvOutDict[item])
            else:
                row.append(" ")
        writer.writerow(row)

	csvWFP.close()


def parse_logs(folders_path, gold_path):
    #super_folders = glob.glob(folders_path + "*") #get all folders, each one has a file called output_500k.txt
    folders = []
    for super_folder in glob.glob(folders_path + "*/"):
        folders += glob.glob(super_folder + "/*" )
    output_file_name = "output_500k.txt"
    gold_values = [line.strip("\n") for line in open(gold_path, "r")]
    executions = []
    for folder in folders:
        execution = []
        lines = [line.strip("\n") for line in open(folder + "/" + output_file_name,"r")]
        assert len(gold_values) == len(lines)
        values = []
        for i in range(len(gold_values)):
            std_id = "value" + str(i+1)
            expected = gold_values[i]
            real = lines[i]
            values.append([std_id, expected, real])
        errItem = {"values": values}
        execution.append(errItem)
        executions.append(execution)
    return executions

def main():
    if len(sys.argv) < 3:
        print "Feed me some input!"
        sys.exit(1)

    csvDirOut = "csv_logs_parsed"
    print "\n\tCSV files will be stored in "+csvDirOut+" folder\n"

    folders_path = sys.argv[1] if sys.argv[1][-1] == '/' else sys.argv[1] + '/'
    executions = parse_logs(folders_path, sys.argv[2])
    print executions
    for execution in executions:
        processErrors(execution)

if __name__ == '__main__':
    main()
