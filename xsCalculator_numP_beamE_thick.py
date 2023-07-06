from postprocess import *
import sys

numFiles = 12

targetDensity = 0.534 #g/cm3, Natural Li
targetMolarMass = 6.94 #g/mol, Natural Li

numProton = sys.argv[1]
beamEnergy = sys.argv[2]
targetThickness = sys.argv[3]

calculateXSandWriteToFile("finalXSfile.csv", numFiles, numProton, targetThickness, targetDensity, targetMolarMass, beamEnergy)
