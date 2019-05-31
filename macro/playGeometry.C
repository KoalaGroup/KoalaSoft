void playGeometry_LocalInput(Double_t y, Double_t z, Double_t x= -0.05, Int_t sensorID=0, const char* filename="geofile_full.root")
{
  Double_t sensor_edge_minusz[4]={-2.64,2.61,9.175,16.035};
  Double_t sensor_edge_minusy[4]={-5.675,0.675,-5.675,0.675};

  // sensor_edge[i][j], index i represents Sensor from Si1, Si2, Ge1 to Ge2
  // index j represents the edge from -z, +z, -y, +y
  // Based on the build_geom.C on 09.05.2019
  Double_t sensor_edge[4][4]={
    {sensor_edge_minusz[0],sensor_edge_minusz[0]+7.68,sensor_edge_minusy[0],sensor_edge_minusy[0]+5},
    {sensor_edge_minusz[1],sensor_edge_minusz[1]+7.68,sensor_edge_minusy[1],sensor_edge_minusy[1]+5},
    {sensor_edge_minusz[2],sensor_edge_minusz[2]+8.04,sensor_edge_minusy[2],sensor_edge_minusy[2]+5},
    {sensor_edge_minusz[3],sensor_edge_minusz[3]+8.04,sensor_edge_minusy[3],sensor_edge_minusy[3]+5}
  }; // [cm]
  Double_t sensor_thickness[4]={0.1,0.1,0.5,1.1}; // [cm], x direction
  Double_t sensor_length[4] = {7.68,7.68,8.04,8.04}; // [cm], z direction
  Double_t sensor_width[4] = {5,5,5,5}; // [cm], y direction
  Double_t sensor_distance=101.096; // [cm]

  // strip merging
  Double_t strip_width=0.12; // [cm]

  const char sensor_name[4][10]={"SensorSi1","SensorSi2","SensorGe1","SensorGe2"};
  ////////////////////////////////////////////////////////////
  Double_t posLocal[3]={x,y,z};
  Double_t posGlobal_true[3];
  posGlobal_true[0] = posLocal[0] + sensor_thickness[sensorID]/2 - sensor_distance;
  posGlobal_true[1] = -posLocal[1] + sensor_width[sensorID]/2 + sensor_edge_minusy[sensorID];
  posGlobal_true[2] = posLocal[2] + sensor_length[sensorID]/2 + sensor_edge_minusz[sensorID];

  // get the geometry from file and the sensor node
  TFile* file=new TFile(filename);
  TGeoManager* geoMan=(TGeoManager*)file->Get("FAIRGeom");
  TString nodeName = Form("/cave/RecArm_0/RecArm_Vacuum_1/RecArm_Detectors_1/%s_1",sensor_name[sensorID]);
  // or
  // the suffix of the top volume is irrelavant, the name of deeper nodes should be exactly same including the daughter id (i.e. NAMEOFVOLUME_ID) 
  // The default daughter id of volumes constructed from txt file is 1
  // The default daughter id of volumes constructed from root file is 0
  //TString nodeName = Form("/cave_1/RecArm_0/RecArm_Vacuum_1/RecArm_Detectors_1/%s_1",sensor_name[sensorID]);
  if(!geoMan->cd(nodeName.Data()))
    std::cout << "Node: " << nodeName.Data() << "\" unknown!";

  // method 1: TGeoManager
  // Result: current
  Double_t posGlobal_manager[3];
  geoMan->LocalToMaster(posLocal,posGlobal_manager);

  // method 2: TGeoNode
  // Result: wrong
  // Comment: between local and mother, instead of local and global
  Double_t posGlobal_node[3];
  TGeoNode* curNode=geoMan->GetCurrentNode();
  curNode->LocalToMaster(posLocal,posGlobal_node);

  // method 3: TGeoHMatrix, recommended way
  Double_t posGlobal_matrix[3];
  // for transient usage
  TGeoHMatrix* currentTransMat = gGeoManager->GetCurrentMatrix();
  //  make clone for later use
  // TGeoMatrix* currentTransMat = gGeoManager->GetCurrentMatrix()->MakeClone();
  currentTransMat->LocalToMaster(posLocal,posGlobal_matrix);
  geoMan->cd("cave");
  // // the TransMatrix is not affected by the changing of current node
  // currentTransMat->LocalToMaster(posLocal, posGlobal_matrix);
  TGeoHMatrix* tmpTransMat = gGeoManager->GetCurrentMatrix();
  Double_t posGlobal_tmp[3];
  tmpTransMat->LocalToMaster(posGlobal_matrix,posGlobal_tmp);


  // method 4: TGeoNavigator
  Double_t posGlobal_navigator[3];
  TGeoNavigator* curNav = gGeoManager->GetCurrentNavigator();
  curNav->LocalToMaster(posLocal, posGlobal_navigator);
  // geoMan->cd("cave");
  // Navigator is affected by the changing of current node
  // Coordinate transformation should be invoked before next cd to get correct result
  // curNav->LocalToMaster(posLocal, posGlobal_navigator);
  // TGeoNavigator* tmpNav = gGeoManager->GetCurrentNavigator();
  // Double_t posGlobal_tmp[3];
  // tmpNav->LocalToMaster(posGlobal_navigator,posGlobal_tmp);

  //////////////////////////////////////////////////////////////
  std::cout<< "Input Local Coordinate in Sensor "<< sensorID << std::endl;
  std::cout<< posLocal[0] << "\t" << posLocal[1] << "\t" << posLocal[2] << std::endl;

  std::cout<< "True Global Coordinate by calculation:"<< std::endl;
  std::cout<< posGlobal_true[0] << "\t" << posGlobal_true[1] << "\t" << posGlobal_true[2] << std::endl;

  std::cout<< "Global Coordinate by TGeoManager:"<< std::endl;
  std::cout<< posGlobal_manager[0] << "\t" << posGlobal_manager[1] << "\t" << posGlobal_manager[2] << std::endl;

  std::cout<< "Global Coordinate by TGeoNode:"<< std::endl;
  std::cout<< posGlobal_node[0] << "\t" << posGlobal_node[1] << "\t" << posGlobal_node[2] << std::endl;

  std::cout<< "Global Coordinate by TGeoHMatrix:"<< std::endl;
  std::cout<< posGlobal_matrix[0] << "\t" << posGlobal_matrix[1] << "\t" << posGlobal_matrix[2] << std::endl;

  std::cout<< "Global Coordinate by TGeoNavigator:"<< std::endl;
  std::cout<< posGlobal_navigator[0] << "\t" << posGlobal_navigator[1] << "\t" << posGlobal_navigator[2] << std::endl;
  std::cout<< posGlobal_tmp[0] << "\t" << posGlobal_tmp[1] << "\t" << posGlobal_tmp[2] << std::endl;
  ///////////////////////////////////////////////////////////////
  delete file;
}
