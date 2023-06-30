from postprocess import *

numFiles = 12

targetThickness = 0.2 #cm
targetDensity = 0.534 #g/cm3, Natural Li
targetMolarMass = 6.94 #g/mol, Natural Li

numProton = 1000000000
beamEnergy = 0

calculateXSandWriteToFile("finalXSfile.csv", numFiles, numProton, targetThickness, targetDensity, targetMolarMass, beamEnergy)
