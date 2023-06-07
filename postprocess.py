import pathlib
import csv
import math
import statistics as stats

def extractData(fileName):
    path = str(pathlib.Path().resolve())
    path = path + "\\Release\\"

            #C:\\Users\\sebrh\\Desktop\\Geant4\\protonlithium1\\source\\Release\\output0.csv
    fullFileName = "C:/Users/sebrh/Desktop/Geant4/protonlithium1/build/Release/output0.csv"

    #fullFileName = path + str(fileName)
    with open((fullFileName), newline='') as csvfile: #open the .csv file

        particleData = csv.reader(csvfile, delimiter=',') #read the data

        evtList = [False]
        neutronList = [False]

        for row in particleData: #for each line, do:
            evt = int(row[0]) #get the event number for the line
            particle = str(row[1]) #get the particle name for the line

            for i in range(0,evt): #for all event numbers up to but not including the number we are currently on
                try:
                    if (evtList[i] != True): #if list[i] is already defined, keep entries as false or true
                        evtList[i] = False
                    if (neutronList[i] != True):
                        neutronList[i] = False
                except IndexError: #if list[i] is not yet defined, define it as false by extending the list
                    evtList.append(False)
                    neutronList.append(False)
                
            evtList.append(True) #this event is labeled as true since it did happen

            if (particle == "neutron"): #determine if an event caused a neutron to be generated
                neutronList.append(True) #if so, label this entry True
            else:
                neutronList.append(False) #if no neutron for this event, label this entry False

    numP = 0 #number of protons
    numN = 0 #number of neutrons

    for j in range(len(evtList)):
        if (evtList[j] == True): #the number of protons is the number of times we recorded true in the evtList
            numP += 1
        if (neutronList[j] == True): #the number of neutrons is the number of times we recorded true in the neutronList
            numN += 1
    
    return numP, numN

def xsCalculator(nFiles):

    numPTotal = 0 #total number of protons in the simulation
    xsMacroList = []

    for i in range(0,nFiles):
        fileName = "output" + str(i) +".csv"

        numP, numN = extractData(fileName) #extract the data from the simulation using the above function
        numPTotal += numP 

        xsMacro = numN / numP #need to include thickness
        xsMacroList.append(xsMacro)
    
    xsMacroAve = stats.fmean(xsMacroList) #the final xs (cross section) calculated is the average over each thread's cross section
    xsSTD_multithread = stats.stdev(xsMacroList) #calculate the STDev between the results from each thread
    xsSTD_MC = 1 / math.sqrt(numPTotal) #Monte Carlo simulations in general have a STDev of ~1/sqrt(number of iterations)

    return xsMacroAve, xsSTD_multithread, xsSTD_MC
