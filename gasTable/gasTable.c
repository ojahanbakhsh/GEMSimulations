/*
 * gasTable.c
 * Author: Jan Eysermans 
 * 2014
 */

// General libs
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdio.h>     
#include <stdlib.h> 
#include <math.h> 

// ROOT libs
#include <TROOT.h>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>
#include <TBenchmark.h>

// Garfield++ libs
#include "MediumMagboltz.hh"
#include "Random.hh"
#include "TrackHeed.hh"
#include "ComponentConstant.hh"
#include "Plotting.hh"

using namespace Garfield;
const std::string GARFIELD = "/afs/cern.ch/user/j/jeyserma/garfieldpp/";

int main(int argc, char * argv[]) {
       
    	TStopwatch watch;

 	gRandom = new TRandom3(0); // set random seed
     
    	MediumMagboltz* gas = new MediumMagboltz();
	gas->SetComposition("Ar", 75., "CO2", 25.);
	gas->SetTemperature(293.15);
	gas->SetPressure(760.);
	    
	gas->PrintGas();
 	
 	// Calculation from 0 kV/cm to 100 kV/cm in 50 steps
	gas->SetFieldGrid(0., 100000., 50, false, 0., 0., 1, 0., 0., 1);
	    
	gas->EnableDebugging();
	gas->Initialise();  
	gas->DisableDebugging();
	    
	// Generate gas table
  	gas->GenerateGasTable(5, true);
	    
	gas->WriteGasFile("data/Ar-CO2-75-25.gas");
	    
	std::cout << "--------------- TIMING ---------------" << std::endl;
	std::cout << watch.CpuTime() << std::endl;
	
	return 0;
}
