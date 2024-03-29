/*! @file PicParams.h

 @brief PicParams.h is the class that hold the simulation parameters and can read from a file the namelist

 @date 2013-02-15
 */

#ifndef PICPARAMS_H
#define PICPARAMS_H

#include <Python.h>
#include <vector>
#include <string>

class InputData;

// ---------------------------------------------------------------------------------------------------------------------
//! This structure contains the properties of each Profile
// ---------------------------------------------------------------------------------------------------------------------
struct ProfileStructure {

    //! Magnitude of the profile if constant profile
    double profile;

    //! in case profile is give in Python
    PyObject *py_profile;

};


// ---------------------------------------------------------------------------------------------------------------------
//! This structure contains the properties of each species
// ---------------------------------------------------------------------------------------------------------------------
struct SpeciesStructure {

    //! kind of species possible values: "ion" "eon" "test"
    std::string species_type;

    //! position initialization type, possible values: "regular" or "random"
    std::string initPosition_type;

    //! momentum initialization type, possible values: "cold" or "maxwell-juettner"
    std::string initMomentum_type;

    //! coefficient on the maximum number of particles for the species
    double c_part_max;

    //! mass [electron mass]
    double mass;

    //! atomic number
    unsigned int atomic_number;

    //! thermalizing temperature [\f$m_e c^2\f$]
    std::vector<double> thermT;
    //! thermal velocity [\f$c\f$]
    std::vector<double> thermalVelocity;
    //! thermal momentum [\f$m_e c\f$]
    std::vector<double> thermalMomentum;

    //! dynamics type. Possible values: "Norm" "Radiation Reaction"
    std::string dynamics_type;

    //! Time for which the species is frozen
    double time_frozen;

    //! logical true if particles radiate
    bool radiating;

    //! logical true if particles radiate
    bool isTest;

    //! nDim_fields
    int nDim_fields;

    //! Boundary conditions for particules
    std::string bc_part_type_west;
    std::string bc_part_type_east;
    std::string bc_part_type_south;
    std::string bc_part_type_north;
    std::string bc_part_type_bottom;
    std::string bc_part_type_up;

    //! Ionization model per Specie (tunnel)
    std::string ionization_model;

    //! density profile
    ProfileStructure dens_profile;
    ProfileStructure charge_profile;
    std::string density_type;

    //! velocity profile
    ProfileStructure mvel_x_profile;
    ProfileStructure mvel_y_profile;
    ProfileStructure mvel_z_profile;


    //! temperature profile
    ProfileStructure temp_x_profile;
    ProfileStructure temp_y_profile;
    ProfileStructure temp_z_profile;

    ProfileStructure ppc_profile;

};



// ---------------------------------------------------------------------------------------------------------------------
//! PicParams class: holds all the properties of the simulation that are read from the input file
// ---------------------------------------------------------------------------------------------------------------------
class PicParams {

public:
    //! Creator for PicParams
    PicParams(InputData &);

    //! extract profiles
    bool extractProfile         (InputData &, PyObject *, ProfileStructure &);
    bool extractOneProfile      (InputData &, std::string, ProfileStructure &, int);
    void extractVectorOfProfiles(InputData &, std::string, std::vector<ProfileStructure*> &, int);

    //! compute grid-related parameters & apply normalization
    void compute();

    //! read species
    void readSpecies(InputData &);

    //! compute species-related parameters & apply normalization
    void computeSpecies();

    //! print a summary of the values in txt
    void print();

    //! sets nDim_particle and nDim_field based on the geometry
    void setDimensions();

    //! defines the geometry of the simulation
    std::string geometry;

    //! defines the interpolation/projection order
    unsigned int interpolation_order;

    //! number of space dimensions for the particles
    unsigned int nDim_particle;

    //! number of space dimensions for the fields
    unsigned int nDim_field;

    //! normalization (used in the input files only)
    std::string sim_units;

    /*! \brief Time resolution
     Number of timesteps in \f$ 2\pi/\omega_N \f$ where \f$ \omega_N \f$ is the normalization (plasma or laser) frequency
     */
    double res_time;

    //! simulation exit time in units of \f$ 2\pi/\omega_N \f$
    double sim_time;

    /*! \brief Space resolution
     Number of cells in every direction in \f$ 2\pi/k_N \f$ where \f$ k_N=\omega_N/c \f$ is the normalization wavenumber
     */
    std::vector<double> res_space;

    //! local simulation box size in \f$2\pi/k_N \f$
    std::vector<double> sim_length;

    //! time during which the Maxwell's equations are not solved
    double time_fields_frozen;

    //! Boundary conditions for ElectroMagnetic Fields
    std::vector<std::string> bc_em_type_x;
    std::vector<std::string> bc_em_type_y;
    std::vector<std::string> bc_em_type_z;

    std::vector<double> bc_em_value_x;
    std::vector<double> bc_em_value_y;
    std::vector<double> bc_em_value_z;

    //! Clusters width
    //unsigned int clrw;
    int clrw;
    //! Number of cells per cluster
    int n_cell_per_cluster;

    //! parameters of the species
    std::vector<SpeciesStructure> species_param;

    //! initial number of particles
    unsigned int n_particles;

    //! number of total timesteps to perform in the simulation
    unsigned int n_time;

    //! dt for the simulation
    double timestep;

    //! max value for dt (due to usual FDTD CFL condition: should be moved to ElectroMagn solver (MG))
    double dtCFL;

    //! number of cells in every direction of the local domain
    std::vector<unsigned int> n_space;

    //! number of cells in every direction of the global domain
    std::vector<unsigned int> n_space_global;

    //! spatial step (cell dimension in every direction)
    std::vector<double> cell_length;

    //! volume of cell (this will be removed by untructured mesh!)
    double cell_volume;

    //! wavelength (in SI units)
    double wavelength_SI;

    //! Oversize domain to exchange less particles
    std::vector<unsigned int> oversize;

    //! Timestep to dump everything
    unsigned int dump_step;

    //! Human minutes to dump everything
    double dump_minutes;

    //! exit once dump done
    bool exit_after_dump;

    //! check for file named "stop"
    bool check_stop_file;

    //! keep the last dump_file_sequence dump files
    unsigned int dump_file_sequence;

    //! restart namelist
    bool restart;

    //! frequency of exchange particles (default = 1, disabled for now, incompatible with sort)
    int exchange_particles_each;

    //! Number of MPI process per direction (default : as square as possible)
    std::vector<int> number_of_procs;

    //! global number of time exits (it will be used if not specified in various diags/fields)
    unsigned int global_every;

    //! Method to find the numbers of requested species, sorted, and duplicates removed
    std::vector<unsigned int> FindSpecies(std::vector<std::string>);

};

#endif
