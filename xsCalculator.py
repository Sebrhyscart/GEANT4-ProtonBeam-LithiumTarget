from postprocess import *

numFiles = 8

targetThickness = 0.1 #cm
targetDensity = 0.534 #g/cm3, Natural Li
targetMolarMass = 6.94 #g/mol, Natural Li

numProton = 1000000
beamEnergy = 0

calculateXSandWriteToFile("finalXSfile.csv", numFiles, numProton, targetThickness, targetDensity, targetMolarMass, beamEnergy)
