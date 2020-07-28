#ifndef KOASIMPLEPIXELCLUSTERFINDER_H
#define KOASIMPLEPIXELCLUSTERFINDER_H

#include "PndSdsSimplePixelClusterFinder.h"
/// PndLmdSimplePixelClusterFinder.h
/// Simple cluster finder for pixel detectors.
///
/// It takes the first hit in the DigiArray and moves it into a new cluster.
/// Then it looks through the remaining hits in the DigiArray if there are hits
/// which are in the area around the first hit and moves them into the cluster.
/// The radius is given by the first parameter.
/// Then it takes the new hits in the cluster and looks if there are other hits
/// which are in the range of these hits and moves them into the cluster, too.
/// This process is repeated until no hits around the cluster are found
/// The the first hit of the remaining DigiHits is taken to create a new hit and
/// the cluster search process is started again.

class KoaSimplePixelClusterFinder : public PndSdsSimplePixelClusterFinder {
 public:
  KoaSimplePixelClusterFinder(Int_t verbose = 0);
};
#endif
