#include "PSI_Injection.h"
#include "SmileiMPI.h"
#include "Field2D.h"
#include "H5.h"


#include <cmath>
#include <iomanip>
#include <algorithm>
#include <ostream>
#include <sstream>

using namespace std;


// Constructor
PSI_Injection::PSI_Injection(PicParams& param, vector<Species*>& vecSpecies, SmileiMPI* smpi,
                       unsigned int n_PSI,
                       vector<unsigned int> species1,)
{

    n_PSI    		= (n_PSI    );
    species_group1  = (species_group1  );
    start           = (0               );




}

PSI_Injection::~PSI_Injection()
{

}



// Calculates the PSI for a given Collisions object
void PSI_Injection::performPSI(PicParams& params, vector<Species*>& vecSpecies, int itime)
{

    unsigned int nbins = vecSpecies[0]->bmin.size(); // number of bins
    vector<unsigned int> *sg1, *sg2, *sgtmp, bmin1, bmax1, bmin2, bmax2, index1, index2;
    unsigned int nspec1, nspec2; // numbers of species in each group
    unsigned int npart1, npart2; // numbers of macro-particles in each group
    unsigned int npairs; // number of pairs of macro-particles
    vector<unsigned int> np1, np2; // numbers of macro-particles in each species, in each group
    double n1, n2, n12, n123, n223; // densities of particles
    unsigned int i1, i2, ispec1, ispec2;
    Species   *s1, *s2;
    Particles *p1, *p2;



}
