#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{} 

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //this method defines all of the materials and geometry in the simulation
    //1, materials and their properties are defined
    //2, the geometry is defined, and materials assigned to the geometry

    //=================================================================================================================================
    //DEFINE MATERIALS
    G4NistManager *nist = G4NistManager::Instance(); //get materials manager

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR"); //Air
    G4double vacuumPressure = 0.011; //approximately 0.011 Pa or 1.1e-4 mbar operating vaccum according to tandetron operator's manual
    G4double vacuumDensity = (vacuumPressure / (287 * 300));
    //ideal gas law, P=rho*R*T => rho = P/(R*T) Assume R=287 [J/kg*k] (for air) and T=300 [k]
    G4Material *vacuum = nist->BuildMaterialWithNewDensity("vacuum", "G4_AIR", vacuumDensity); //maybe switch from air to hydrogen??
    G4Material *Li = nist->FindOrBuildMaterial("G4_Li"); //Li -> Target
    G4Material *brass = nist->FindOrBuildMaterial("G4_BRASS"); //Brass -> Target holder
    G4Material *aluminum = nist->FindOrBuildMaterial("G4_Al"); //Aluminum -> BF3 detector sheath
    G4Material *polyethylene = nist->FindOrBuildMaterial("G4_POLYETHYLENE"); //Polyethylene -> Shielding plug
    G4Material *lead = nist->FindOrBuildMaterial("G4_Pb"); //Lead -> Shielding plug
    G4Material *graphite = nist->FindOrBuildMaterial("G4_GRAPHITE"); //Graphite -> Sheilding plug
    G4Material *concrete = nist->FindOrBuildMaterial("G4_CONCRETE"); //Concrete -> Sheilding
    G4Material *wax = nist->FindOrBuildMaterial("G4_PARAFFIN"); //Paraffin wax -> Sheilding behind detector
    
    //=================================================================================================================================
    //DEFINE GEOMETRY PARAMTERS
    //length and thickness parameters
    G4double LWorld = 1.31*m; //all simulation happens within this cubic universe

    G4double LCube = 1.*m; //concrete shielding cube half side length
    G4double RTunnel = 10.*cm; //radius of access tunnel in shielding cube

    G4double RTarget = 6.*cm; //Target radius
    G4double dzTarget = 2.*mm; //Target Thickness

    G4double dzBrass = 2.*cm; //Brass target holder thickness
    G4double dzPoly = 1.*cm; //Polyethylene plug thickness
    G4double dzLead = 6.*cm; //Lead plug thickness
    G4double dzGraphite1 = 10.*cm; //1st Graphite plug thickness
    G4double dzGraphite2 = 20.*cm; //2nd Graphite plug thickness
    G4double dzConcrete = 30.*cm; //Final concrete plug thickness

    G4double Ldetector = 12.*cm;
    G4double Rdetector = 2.*cm;
    G4double dRdetectorSheath = 0.2*cm;

    G4double dxWax = 30.*cm;
    G4double dzWax = 3.*cm;

    //positional parameters (location of center of solid)
        //position of solid's left side (w. respect to far left edge (-x direction edge) of world solid cube)
    G4double zLConcrete = 0*cm; 
    G4double zLGraphite2 = dzConcrete;
    G4double zLGraphite1 = dzConcrete + dzGraphite2;
    G4double zLLead = dzConcrete + dzGraphite2 + dzGraphite1;
    G4double zLPoly = dzConcrete + dzGraphite2 + dzGraphite1 + dzLead;
    G4double zLBrass = dzConcrete + dzGraphite2 + dzGraphite1 + dzLead + dzPoly;
    G4double zLTarget = dzConcrete + dzGraphite2 + dzGraphite1 + dzLead + dzPoly + dzBrass;

        //postion of soild's center (w. respect to the origin)
    G4double zConcrete = LCube - zLConcrete - (dzConcrete / 2);
    G4double zGraphite2 = LCube - zLGraphite2 - (dzGraphite2 / 2);
    G4double zGraphite1 = LCube - zLGraphite1 - (dzGraphite1 / 2);
    G4double zLead = LCube - zLLead - (dzLead / 2);
    G4double zPoly = LCube - zLPoly - (dzPoly / 2);
    G4double zBrass = LCube - zLBrass - (dzBrass / 2);
    G4double zTarget = LCube - zLTarget - (dzTarget / 2);

    //center of each solid's positions in 3D space (w. respect to the origin)
    G4ThreeVector xyzBox(0., 0., -(LWorld - LCube));

    G4ThreeVector xyzConcrete(0., 0., zConcrete);
    G4ThreeVector xyzGraphite2(0., 0., zGraphite2);
    G4ThreeVector xyzGraphite1(0., 0., zGraphite1);
    G4ThreeVector xyzLead(0., 0., zLead);
    G4ThreeVector xyzPoly(0., 0., zPoly);
    G4ThreeVector xyzBrass(0., 0., zBrass);
    G4ThreeVector xyzTarget(0., 0., zTarget);

    G4ThreeVector xyzDetector(0., 0., LCube + Rdetector + dRdetectorSheath -(LWorld - LCube) + 2*cm);

    //=================================================================================================================================
    //DEFINE GEOMETRY

    //Define World
    G4Box *solidWorld = new G4Box("solidWorld", LCube, LCube, LWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Define Sheilding Box
    G4Box *solidBox = new G4Box("solidBox", LCube, LCube, LCube);
    G4LogicalVolume *logicBox = new G4LogicalVolume(solidBox, polyethylene, "logicBox");
    G4VPhysicalVolume *physBox = new G4PVPlacement(0, xyzBox, logicBox, "physBox", logicWorld, false, 0, true);

    //Define the tunnel through the concrete shieling box
    G4double innerRadius = 0.*cm; //cylinder construction parameters
    G4double outerRadius = RTunnel;
    G4double hz = LCube;
    G4double startAngle = 0.*deg;
    G4double spanningAngle = 360.*deg;

    G4Tubs *solidVacuumTunnel = new G4Tubs("solidVacuumTunnel", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    //G4Tubs is the class that forms cylindrical /cylindrical shell objects
    //we create a SOLID VOLUME instance as a G4Tubs object 
    G4LogicalVolume *logicVacuumTunnel = new G4LogicalVolume(solidVacuumTunnel, vacuum, "logicVacuumTunnel");
    //we create a LOGICAL VOLUME instance from the G4LogicalVolume class
    //a LOGICAL VOLUME requires a SOLID VOLUME for its geometry, and a material for is composition
    G4VPhysicalVolume *physVacuumTunnel = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicVacuumTunnel, "physVacuumTunnel",
        logicBox, false, 0, true);
    //we create a PHYSICAL VOLUME instance using the G4PVPlacement class
    //a PHYSICAL VOLUME is a LOGICAL VOLUME that has been placed inside of the overall simulation geometry
    
    //Define Concrete plug
    outerRadius = RTunnel;
    hz = dzConcrete / 2;

    G4Tubs *solidConcretePlug = new G4Tubs("solidConcretePlug", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicConcretePlug = new G4LogicalVolume(solidConcretePlug, concrete, "logicConcretePlug");
    G4VPhysicalVolume *physConcretePlug = new G4PVPlacement(0, xyzConcrete, logicConcretePlug, "physConcretePlug",
        logicVacuumTunnel, false, 0, true);

    //Define Graphite plug 2
    outerRadius = RTunnel;
    hz = dzGraphite2 / 2;

    G4Tubs *solidGraphitePlug2 = new G4Tubs("solidGraphitePlug2", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicGraphitePlug2 = new G4LogicalVolume(solidGraphitePlug2, graphite, "logicGraphitePlug2");
    G4VPhysicalVolume *physGraphitePlug2 = new G4PVPlacement(0, xyzGraphite2, logicGraphitePlug2, "physGraphitePlug2",
        logicVacuumTunnel, false, 0, true);   

    //Define Graphite plug 1
    outerRadius = RTunnel;
    hz = dzGraphite1 / 2;

    G4Tubs *solidGraphitePlug1 = new G4Tubs("solidGraphitePlug1", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicGraphitePlug1 = new G4LogicalVolume(solidGraphitePlug1, graphite, "logicGraphitePlug1");
    G4VPhysicalVolume *physGraphitePlug1 = new G4PVPlacement(0, xyzGraphite1, logicGraphitePlug1, "physGraphitePlug1",
        logicVacuumTunnel, false, 0, true);   

    //Define Lead plug
    outerRadius = RTunnel;
    hz = dzLead / 2;

    G4Tubs *solidLeadPlug = new G4Tubs("solidLeadPlug", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicLeadPlug = new G4LogicalVolume(solidLeadPlug, lead, "logicLeadPlug");
    G4VPhysicalVolume *physLeadPlug = new G4PVPlacement(0, xyzLead, logicLeadPlug, "physLeadPlug",
        logicVacuumTunnel, false, 0, true);  

    //Define Polyethylene plug
    outerRadius = RTunnel;
    hz = dzPoly / 2;

    G4Tubs *solidPolyPlug = new G4Tubs("solidPolyPlug", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicPolyPlug = new G4LogicalVolume(solidPolyPlug, polyethylene, "logicPolyPlug");
    G4VPhysicalVolume *physPolyPlug = new G4PVPlacement(0, xyzPoly, logicPolyPlug, "physPolyPlug",
        logicVacuumTunnel, false, 0, true);  

    //Define Brass Target Holder
    outerRadius = RTunnel;
    hz = dzBrass / 2;

    G4Tubs *solidBrassHolder = new G4Tubs("solidBrassHolder", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume *logicBrassHolder = new G4LogicalVolume(solidBrassHolder, brass, "logicBrassHolder");
    G4VPhysicalVolume *physBrassHolder = new G4PVPlacement(0, xyzBrass, logicBrassHolder, "physBrassHolder",
        logicVacuumTunnel, false, 0, true);

    //Define Li Target
    outerRadius = RTarget;
    hz = dzTarget / 2;

    G4Tubs *solidTarget = new G4Tubs("solidTarget", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    logicTarget = new G4LogicalVolume(solidTarget, Li, "logicTarget");
    G4VPhysicalVolume *physTarget = new G4PVPlacement(0, xyzTarget, logicTarget, "physTarget",
        logicVacuumTunnel, false, 0, true);
    
    //Define BF3 detector
    outerRadius = Rdetector + dRdetectorSheath;
    hz = Ldetector + dRdetectorSheath;

    //the detector cylinder has its axis pointing in Y (up), but it defaults to pointing in Z (the beamline direction)
    //thus we need to rotate it 90 deg around the x axis to acheive the proper rotation
    //this is done with a rotation matrix (rotm) and a transform (the rotation matrix applied to a certain point in space)
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateX(90*deg);
    G4Transform3D transform = G4Transform3D(rotm,xyzDetector);
    
    G4Tubs *solidBF3Detector = new G4Tubs("solidBF3Detector", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    logicDetector = new G4LogicalVolume(solidBF3Detector, aluminum, "LogicDetector");
    G4VPhysicalVolume *physTDetector = new G4PVPlacement(transform, logicDetector, "physDetector",
        logicWorld, false, 0, true);
    
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    //this method defines sensitive detectors (SD) and electromagnetic fields if present (no EM fields in this simulation)
    //2 detectors are defined here: the Li target itself, and the actual neutron detector
    //a 'detector' in Geant4 means that Geant4 will record information about particles traveling within (it doesn't have to be a real detector irl)

    //Define the target itself as a detector to determine information directly from the reactions
    MySensitiveDetector *targetDet = new MySensitiveDetector("TargetDetector");
    logicTarget->SetSensitiveDetector(targetDet);
    
    //Define the neutron detector as used in the real experiment

    MySensitiveDetector *neutronDet = new MySensitiveDetector("NeutronDetector");
    logicDetector->SetSensitiveDetector(neutronDet);
    
}