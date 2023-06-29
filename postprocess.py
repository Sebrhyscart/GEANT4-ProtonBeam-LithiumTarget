import pathlib
import csv

def extractData(fileName):

    try:
        with open((fileName), newline='') as csvfile:

            particleData = csv.reader(csvfile, delimiter=',')
            evtList = [False]

            i = 0
            for row in particleData:
                if (i > 0):
                    evt = int(row[0])
                    particle = str(row[1])

                    while (evt > len(evtList)):
                        evtList.append(False)
                    
                    if ((evt == len(evtList)) and (particle == "neutron")):
                        evtList.append(True)

                i += 1

            csvfile.close()

    except FileNotFoundError:
        path = str(pathlib.Path().resolve()) #gets the path to the source directory
        pathList = path.split("\\")
        fullFileName = ""
        for i in range(len(pathList)-1):
            fullFileName += (str(pathList[i]) + "/") #rebuild the path, not including /source/
        fullFileName += "Build/Release/" + fileName #replace /source with /build/Release/ since that is where the .csv files are generated
        
        with open((fileName), newline='') as csvfile:

            particleData = csv.reader(csvfile, delimiter=',')
            evtList = [False]

            i = 0
            for row in particleData:
                if (i > 0):
                    evt  = int(row[0]) #<------------------------------------fix this
                    particle = str(row[1])

                    while (evt > len(evtList)):
                        evtList.append(False)
                    
                    if ((evt == len(evtList)) and (particle == "neutron")):
                        evtList.append(True)

                i += 1

            csvfile.close()

    numNeutron = 0

    for i in range(len(evtList)):
        if (evtList[i] == True):
            numNeutron += 1
    
    return numNeutron

def getNumNeutron(nFiles):
    totalNumNeutron = 0

    for i in range(0,nFiles):
        fileName = "output" + str(i) + ".csv"
        totalNumNeutron += extractData(fileName)

    return totalNumNeutron

def calculateXSandWriteToFile(xsFileName, nFiles, numProton, targetThickness, targetDensity, targetMolarMass, beamEnergy):
    #specify targetThickness in cm
    #specify targetAtomicDensity in g/cm^3
    #specify targetMolarMass in g/mol
    #specify beamEnergy in MeV

    numNeutron = getNumNeutron(nFiles)
    targetAtomicDensity = (targetDensity / targetMolarMass) * 6.02214076e23 #(0.534 g/cm3) * ((1/6.94) mol/g) * (6.022e23 atoms/mol) //atoms/cm3

    xsMicro = (numNeutron / (numProton * targetThickness * targetAtomicDensity)) * 1e26 #b (barn)
    print("Calculated cross section: " + str(xsMicro) + " b")

    row = [beamEnergy, xsMicro, numNeutron, numProton]

    with open(xsFileName, "a") as xscsvFile:
        lineWriter = csv.writer(xscsvFile)
        lineWriter.writerow(row) #write row raggy

        xscsvFile.close()
