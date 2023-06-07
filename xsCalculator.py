from postprocess import *

numFiles = 8    #the number of output<n>.csv file the GEANT4 program has created
                #each file is an output of one thread used in the simulation
                #our GEANT4 simulation will automatically choose the optimum number of threads on your computer!

xsMacro, xsSTD_multithread, xsSTD_MC = xsCalculator(numFiles)   #This function extracts the information in the .csv files
                                                                #See the definition in postprocess.py for more!

#see the lab manual & postprocess.py for how and why the cross section is calculated this way
#there are 2 ways to estimate the standard deviation. Both values should be reasonable for the results to be trusted
#xsSTD_multithread is the standard deviation from compairing the calculated xs (cross section) of each thread
#xsSTD_MC is an estimate of the standard deviation since a Monte Carlo simulation has STDev of ~1/sqrt(# of iterations)

print("The Macrosopic cross section is: " + str(xsMacro))
print("With thread-estimated standard deviation of: " + str(xsSTD_multithread))
print("And Monte Carlo-estimated standard deviation of: " + str(xsSTD_MC))